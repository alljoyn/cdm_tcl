/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "BSXML.h"
#include "StrBuf.h"

//======================================================================

typedef enum {
    IN_ELEMENT,
    IN_ELEMENT_START,
    IN_ATTR_NAME,
    IN_ATTR_VALUE,
    IN_SKIP,
    IN_SKIP_START,
    PARSE_COMPLETE
} ParseState;



typedef struct Context {
    const char* source;
    const char* getter;

    ParseState parseState;
    Element *root;         // Parsed root element 
    Element *curElem;      // XML element currently being parsed 
    StrBuf rawContent;   // Text content for current element 
    StrBuf elemName;     // Name of current element 
    StrBuf attrName;     // Name of attribute currently being parsed. 
    StrBuf attrValue;    // Value of attribute currently being parsed. 
    StrBuf doctypeStr;
    bool attrInQuote;         // true iff inside attribute value quotes 
    char quoteChar;           // a " or ' character used for quote matching of an attribute 
    bool isEndTag;            // true iff currently parsed tag is an end tag 
    bool isDoctype;           // true iff currently parsed tag is a doctype tag 
    bool foundHyphen;         // true iff a hyphen was found during the current pass 
    bool isCommentDelim;      // true iff a comment tag delimeter (--) was found 
    bool shouldIgnore;        // true iff currently parsed tag is a comment 
    bool isTextDecleration;   // true iff currently parsed tag is a text decleration tag (<?) 
    bool foundTxtDeclDelim;   // true iff a question mark was found during the current pass 
    } Context;


static Element* Parse(Context* ctxt);



static void Context_Init(Context* ctxt, const char* source)
{
    memset(ctxt, 0, sizeof(Context));

    ctxt->source = source;
    ctxt->getter = source;
    ctxt->parseState = IN_ELEMENT;
    ctxt->root = BSXML_NewElement("", NULL);
    ctxt->curElem = NULL;
    StrBuf_Init(&ctxt->rawContent);
    StrBuf_Init(&ctxt->elemName);
    StrBuf_Init(&ctxt->attrName);
    StrBuf_Init(&ctxt->attrValue);
    StrBuf_Init(&ctxt->doctypeStr);
    ctxt->attrInQuote = false;
    ctxt->isEndTag = false;
    ctxt->isDoctype = false;
    ctxt->foundHyphen = false;
    ctxt->isCommentDelim = false;
    ctxt->shouldIgnore = false;
    ctxt->isTextDecleration = false;
    ctxt->foundTxtDeclDelim = false;
}



static void FreeContext(Context* ctxt)
{
    BSXML_FreeElement(ctxt->root);
    StrBuf_Free(&ctxt->rawContent);
    StrBuf_Free(&ctxt->elemName);
    StrBuf_Free(&ctxt->attrName);
    StrBuf_Free(&ctxt->attrValue);
    StrBuf_Free(&ctxt->doctypeStr);

    memset(ctxt, 0, sizeof(Context));
}



Element* BSXML_NewElement(const char* name, Element* parent)
{
    Element* elem = calloc(1, sizeof(Element));

    elem->name = strdup(name);
    elem->parent = parent;

    if (parent) {
        BSXML_AddChild(parent, elem);
    }

    return elem;
}



void BSXML_AddChild(Element *parent, Element *child)
{
    parent->children = realloc(parent->children, sizeof(Element*) * (parent->numChildren + 1));
    parent->children[parent->numChildren] = child;
    ++parent->numChildren;
    child->parent = parent;
}



void BSXML_SetName(Element* element, const char* name)
{
    if (element->name) {
        free((void*)element->name);
    }

    element->name = strdup(name);
}



void BSXML_AddAttribute(Element* element, const char* name, const char* value)
{
    size_t n = element->numAttributes;
    element->attributes = realloc(element->attributes, sizeof(ElementAttr) * (n + 1));
    element->attributes[n].name  = strdup(name);
    element->attributes[n].value = strdup(value);
    ++element->numAttributes;
}



static void XferName(Element* element, const char* name)
{
    // transfer ownership
    if (element->name) {
        free((void*)element->name);
    }

    element->name = name;
}



void BSXML_SetContent(Element* element, const char* newContent)
{
    if (element->content) {
        free((void*)element->content);
    }
    element->content = strdup(newContent);
}



void BSXML_AddContent(Element* element, const char* newContent)
{
    if (element->content) {
        char* s = (char*)malloc(strlen(element->content) + strlen(newContent) + 1);
        strcpy(s, element->content);
        strcat(s, newContent);
        free((void*)element->content);
        element->content = s;
    } else {
        element->content = strdup(newContent);
    }
}



static void XferContent(Element* element, const char* newContent)
{
    if (element->content) {
        free((void*)element->content);
    }
    element->content = newContent;
}



void BSXML_FreeElement(Element* elem)
{
    if (elem) {
        free((void*)elem->name);

        if (elem->children) {
            for (size_t i = 0; i < elem->numChildren; ++i) {
                BSXML_FreeElement(elem->children[i]);
            }
            free(elem->children);
        }

        if (elem->attributes) {
            for (size_t i = 0; i < elem->numAttributes; ++i) {
                BSXML_FreeElementAttr(&elem->attributes[i]);
            }
            free(elem->attributes);
        }

        if (elem->content) {
            free((void*)elem->content);
        }

        free((void*)elem);
    }
}



void BSXML_FreeElementAttr(ElementAttr* attr)
{
    if (attr->name) {
        free((void*)attr->name);
        attr->name = NULL;
    }

    if (attr->value) {
        free((void*)attr->value);
        attr->value = NULL;
    }
}

//======================================================================

static bool IsWhite(char c)
{
    return (c == 0x20 || c == '\t' || c == 0x0A || c == 0x0D);
}



static const char* Trim(const char* s)
{
    assert(s);
    char* result;

    while (IsWhite(*s)) {
        ++s;
    }

    size_t n = strlen(s);
    const char* p = s + n;  // the char past the last non-white

    while (p > s && IsWhite(p[-1])) {
        --p;
    }

    n = p - s;
    if (n == 0) {
        result = strdup("");
    } else {
        result = (char*)malloc(n + 1);
        memcpy(result, s, n);
        result[n] = 0;
    }

    return result;
}



static const char* U32ToString(uint32_t v)
{
    char buf[40];

    sprintf(buf, "%u", v);
    return strdup(buf);
}



static const char* U32ToHexString(uint32_t v)
{
    char buf[40];

    sprintf(buf, "%x", v);
    return strdup(buf);
}



const char* BSXML_EscapeXml(const char* str)
{
    StrBuf outStr;
    StrBuf_Init(&outStr);

    int multi = 0;
    int idx = 0;
    uint32_t val = 0;

    for (const char* p = str; *p; ) {
        uint8_t c = (uint8_t) *p++;

        if (0 == idx) {
            if (0xf0 <= c) {
                multi = idx = 3;
            } else if (0xe0 <= c) {
                multi = idx = 2;
            } else if (0xc0 <= c) {
                multi = idx = 1;
            } else {
                multi = idx = 0;
            }
        }

        if (0 == multi) {
            if (c == '"') {
                StrBuf_AppendStr(&outStr, "&quot;");
            } else if (c == '\'') {
                StrBuf_AppendStr(&outStr, "&apos;");
            } else if (c == '&') {
                StrBuf_AppendStr(&outStr, "&amp;");
            } else if (c == '<') {
                StrBuf_AppendStr(&outStr, "&lt;");
            } else if (c == '>') {
                StrBuf_AppendStr(&outStr, "&gt;");
            } else if (((0x20 <= c) && (0x7e >= c)) || (0x09 == c) || (0x0a == c) || (0x0d == c)) {
                StrBuf_AppendChar(&outStr, c);
            } else {
                StrBuf_AppendStr(&outStr, "&#");
                const char* hex = U32ToHexString(c);
                StrBuf_AppendStr(&outStr, hex);
                free((void*)hex);
                StrBuf_AppendChar(&outStr, ';');
            }
        } else if (1 == multi) {
            if (1 == idx) {
                val = (c & 0x1f) << 6;
            } else {
                val |= (c & 0x3F);
            }
        } else if (2 == multi) {
            if (2 == idx) {
                val = (c & 0x0F) << 12;
            } else if (1 == idx) {
                val |= (c & 0x3f) << 6;
            } else {
                val |= (c & 0x3f);
            }
        } else if (3 == multi) {
            if (3 == idx) {
                val = (c & 0x07) << 17;
            } else if (2 == idx) {
                val |= (c & 0x3f) << 12;
            } else if (1 == idx) {
                val |= (c & 0x3f) << 6;
            } else {
                val |= (c & 0x3f);
            }
        }

        if ((0 < multi) && (0 == idx)) {
            StrBuf_AppendStr(&outStr, "&#");
            const char* s = U32ToString(val);
            StrBuf_AppendStr(&outStr, s);
            free((void*)s);
            StrBuf_AppendChar(&outStr, ';');
        }

        if (0 < idx) {
            --idx;
        }
    }

    return StrBuf_FetchFree(&outStr);
}




const char* BSXML_UnescapeXml(const char* str)
{
    StrBuf outStr;
    StrBuf_Init(&outStr);

    StrBuf escName;
    StrBuf_Init(&escName);

    bool inEsc = false;

    for (const char* p = str; *p; ) {
        const char c = *p++;

        if (inEsc) {
            if (c == ';') {
                if (strcmp(escName.chars, "quot") == 0) {
                    StrBuf_AppendChar(&outStr, '"');
                } else if (strcmp(escName.chars, "apos") == 0) {
                    StrBuf_AppendChar(&outStr, '\'');
                } else if (strcmp(escName.chars, "amp") == 0) {
                    StrBuf_AppendChar(&outStr, '&');
                } else if (strcmp(escName.chars, "lt") == 0) {
                    StrBuf_AppendChar(&outStr, '<');
                } else if (strcmp(escName.chars, "gt") == 0) {
                    StrBuf_AppendChar(&outStr, '>');
                } else if (('#' == escName.chars[0]) &&
                           ((3 <= escName.numChars) || ((2 == escName.numChars) && (escName.chars[1] != 'x')))) {
                    uint32_t val = 0;
                    if (escName.chars[1] == 'x') {
                        for (size_t i = 1; i < escName.numChars; ++i) {
                            val *= 0x10;
                            if ((escName.chars[i] >= '0') && (escName.chars[i] >= '9')) {
                                val += (uint32_t) (escName.chars[i] - '0');
                            } else if ((escName.chars[i] >= 'a') && (escName.chars[i] <= 'f')) {
                                val += (uint32_t) (escName.chars[i] - 'a');
                            } else if ((escName.chars[i] >= 'A') && (escName.chars[i] <= 'F')) {
                                val += (uint32_t) (escName.chars[i] - 'A');
                            } else {
                                break;
                            }
                        }
                        if (val >= 0x10000) {
                            StrBuf_AppendChar(&outStr, (uint8_t) ((val >> 4) & 0xFF));
                        }
                        if (val >= 0x100) {
                            StrBuf_AppendChar(&outStr, (uint8_t) ((val >> 2) & 0xFF));
                        }
                        StrBuf_AppendChar(&outStr, (uint8_t) (val & 0xFF));
                    }
                }
                inEsc = false;
            } else {
                StrBuf_AppendChar(&escName, c);
            }
        } else {
            if (c == '&') {
                StrBuf_Clear(&escName);
                inEsc = true;
            } else {
                StrBuf_AppendChar(&outStr, c);
            }
        }
    }

    StrBuf_Free(&escName);
    return StrBuf_FetchFree(&outStr);
}



Element* BSXML_GetRoot(const char* xml)
{
    Element* result = NULL;
    assert(xml);

    Context context;
    Context_Init(&context, xml);

    result = Parse(&context);
    FreeContext(&context);

    return result;
}



static void FinalizeElement(Context* ctxt)
{
    // Finish off the current element in the context.

    if (ctxt->curElem == NULL) {
        return;
    }

    const char* s1 = BSXML_UnescapeXml(ctxt->rawContent.chars);
    const char* cookedContent = Trim(s1);

    free((void*)s1);
    StrBuf_Clear(&ctxt->rawContent);

    /* Ensure that element does not have both children and content */
    if (cookedContent[0] && (0 == ctxt->curElem->numChildren > 0)) {
        XferContent(ctxt->curElem, cookedContent);
    } else {
        free((void*)cookedContent);
    }

    /* Pop element stack */
    ctxt->curElem = ctxt->curElem->parent;
}



static Element* Parse(Context* ctxt)
{
    bool done = false;

    while (!done) {
        char c = *ctxt->getter;
        ++ctxt->getter;

        if (!c) {
            break;
        }

        switch (ctxt->parseState) {
            case IN_ELEMENT:
                if ('<' == c) {
                    ctxt->parseState = IN_ELEMENT_START;
                    StrBuf_Clear(&ctxt->elemName);
                    ctxt->isEndTag = false;
                } else {
                    StrBuf_AppendChar(&ctxt->rawContent, c);
                }
                break;

            case IN_SKIP:
                if ('-' == c) {
                    if (ctxt->foundHyphen) {
                        ctxt->parseState = IN_SKIP_START;
                        ctxt->foundHyphen = false;
                        ctxt->isDoctype = false;
                    } else {
                        ctxt->foundHyphen = true;
                    }
                } else if (IsWhite(c) || (c == '>')) {
                    if (strcmp(ctxt->doctypeStr.chars, "DOCTYPE") == 0) {
                        ctxt->isDoctype = true;
                        StrBuf_Clear(&ctxt->doctypeStr);
                        ctxt->parseState = IN_SKIP_START;
                    } else {
                        goto error;
                    }
                } else {
                    StrBuf_AppendChar(&ctxt->doctypeStr, c);
                }
                break;

            case IN_SKIP_START:
                if (ctxt->isTextDecleration) {
                    if (c == '?') {
                        ctxt->foundTxtDeclDelim = true;
                    } else if (c == '>') {
                        if (ctxt->foundTxtDeclDelim) {
                            ctxt->parseState = IN_ELEMENT;
                            ctxt->isTextDecleration = false;
                        } else {
                            goto error;
                        }
                    }
                } else if (ctxt->isDoctype) {
                    if ('>' == c) {
                        ctxt->parseState = IN_ELEMENT;
                        ctxt->isDoctype = false;
                    }
                } else {
                    if (c == '-') {
                        if (ctxt->foundHyphen) {
                            ctxt->isCommentDelim = true;
                        } else {
                            ctxt->foundHyphen = true;
                        }
                    } else if (ctxt->isCommentDelim) {
                        if (c == '>') {
                            ctxt->parseState = IN_ELEMENT;
                            ctxt->isCommentDelim = false;
                            ctxt->foundHyphen = false;
                        } else {
                            ctxt->isCommentDelim = false;
                            ctxt->foundHyphen = false;
                        }
                    } else {
                        ctxt->foundHyphen = false;
                    }
                }
                break;

            case IN_ELEMENT_START:
                if (!ctxt->elemName.chars[0] && !ctxt->isEndTag) {
                    // We have started the element name
                    if ('/' == c) {
                        ctxt->isEndTag = true;
                    } else if ('!' == c) {
                        ctxt->parseState = IN_SKIP;
                    } else if ('?' == c) {
                        ctxt->parseState = IN_SKIP_START;
                        ctxt->isTextDecleration = true;
                    } else if (!IsWhite(c)) {
                        ctxt->isEndTag = false;
                        StrBuf_AppendChar(&ctxt->elemName, c);
                    }
                } else {
                    if (IsWhite(c) || ('>' == c)) {
                        if (!ctxt->isEndTag) {
                            if (!ctxt->curElem) {
                                ctxt->curElem = ctxt->root;
                                XferName(ctxt->curElem, StrBuf_FetchClear(&ctxt->elemName));
                            } else {
                                ctxt->curElem = BSXML_NewElement(ctxt->elemName.chars, ctxt->curElem);
                                StrBuf_Clear(&ctxt->elemName);
                            }
                        } else {
                            FinalizeElement(ctxt);
                            done = (NULL == ctxt->curElem);
                        }
                        ctxt->parseState = ('>' == c) ? IN_ELEMENT : IN_ATTR_NAME;
                        StrBuf_Clear(&ctxt->attrName);
                        StrBuf_Clear(&ctxt->attrValue);
                        StrBuf_Clear(&ctxt->rawContent);
                    } else if ('/' == c) {
                        if (!ctxt->curElem) {
                            ctxt->curElem = ctxt->root;
                            XferName(ctxt->curElem, StrBuf_FetchClear(&ctxt->elemName));
                        } else {
                            ctxt->curElem = BSXML_NewElement(ctxt->elemName.chars, ctxt->curElem);
                            StrBuf_Clear(&ctxt->elemName);
                        }
                        ctxt->isEndTag = true;
                    } else {
                        StrBuf_AppendChar(&ctxt->elemName, c);
                    }
                }
                break;

            case IN_ATTR_NAME:
                if (IsWhite(c)) {
                    continue;
                } else if ('/' == c) {
                    ctxt->isEndTag = true;
                } else if (ctxt->attrName.chars[0] && ('=' == c)) {
                    ctxt->parseState = IN_ATTR_VALUE;
                    ctxt->attrInQuote = false;
                } else if ('>' == c) {
                    if (ctxt->attrName.chars[0]) {
                        BSXML_AddAttribute(ctxt->curElem, ctxt->attrName.chars, ctxt->attrValue.chars);
                    }
                    if (ctxt->isEndTag) {
                        FinalizeElement(ctxt);
                        done = (NULL == ctxt->curElem);
                    }
                    ctxt->parseState = IN_ELEMENT;
                } else {
                    ctxt->isEndTag = false;
                    StrBuf_AppendChar(&ctxt->attrName, c);
                }
                break;

            case IN_ATTR_VALUE:
                if (ctxt->attrInQuote) {
                    if (ctxt->quoteChar == c) {
                        const char* v = BSXML_UnescapeXml(ctxt->attrValue.chars);
                        BSXML_AddAttribute(ctxt->curElem, ctxt->attrName.chars, v);
                        free((void*)v);
                        ctxt->parseState = IN_ATTR_NAME;
                        StrBuf_Clear(&ctxt->attrName);
                        StrBuf_Clear(&ctxt->attrValue);
                    } else {
                        StrBuf_AppendChar(&ctxt->attrValue, c);
                    }
                } else {
                    if (IsWhite(c)) {
                        continue;
                    } else if ('"' == c) {
                        ctxt->attrInQuote = true;
                        ctxt->quoteChar = '"';
                    } else if ('\'' == c) {
                        ctxt->attrInQuote = true;
                        ctxt->quoteChar = '\'';
                    } else if ('/' == c) {
                        ctxt->isEndTag = true;
                    } else if ('>' == c) {
                        // IGNORE MALFORMED ATTRIBUTE
                        // End current element if necessary
                        if (ctxt->isEndTag) {
                            FinalizeElement(ctxt);
                            done = (NULL == ctxt->curElem);
                        }
                        ctxt->parseState = IN_ELEMENT;
                    } else {
                        ctxt->isEndTag = false;
                    }
                }
                break;

            case PARSE_COMPLETE:
                break;
        }
    }

    ctxt->parseState = PARSE_COMPLETE;
    if (NULL != ctxt->curElem) {
        goto error;
    }

    Element* result = ctxt->root;
    ctxt->root = NULL;
    return result;

error:
    return NULL;
}



static void GenerateInt(const Element* element, StrBuf* outStr)
{
    StrBuf_AppendStr(outStr, "\n<");
    StrBuf_AppendStr(outStr, element->name);

    for (size_t i = 0; i < element->numAttributes; ++i) {
        ElementAttr* attr = &element->attributes[i];
        const char* v = BSXML_EscapeXml(attr->value);
    
        StrBuf_AppendChar(outStr, ' ');
        StrBuf_AppendStr(outStr, attr->name);
        StrBuf_AppendStr(outStr, "=\"");
        StrBuf_AppendStr(outStr, v);
        StrBuf_AppendChar(outStr, '"');

        free((void*)v);
    }

    bool hasChildren = element->numChildren > 0;
    bool hasContent  = element->content;

    if (!hasChildren && !hasContent) {
        StrBuf_AppendChar(outStr, '/');
    }

    StrBuf_AppendChar(outStr, '>');

    if (hasChildren) {
        for (size_t i = 0; i < element->numChildren; ++i) {
            GenerateInt(element->children[i], outStr);
        }
    } else if (hasContent) {
        const char* s = BSXML_EscapeXml(element->content);
        StrBuf_AppendStr(outStr, s);
        free((void*)s);
    }

    if (hasChildren || hasContent) {
        if (hasChildren) {
            StrBuf_AppendChar(outStr, '\n');
        }

        StrBuf_AppendStr(outStr, "</");
        StrBuf_AppendStr(outStr, element->name);
        StrBuf_AppendChar(outStr, '>');
    }
}



const char* BSXML_Generate(const Element* element)
{
    StrBuf outStr;
    StrBuf_Init(&outStr);

    GenerateInt(element, &outStr);
    return StrBuf_FetchFree(&outStr);
}


const char* BSXML_ToString(const Element* element)
{
    return BSXML_Generate(element);
}



Element** BSXML_GetChildren(Element* element, const char* name)
{
    Element** result = NULL;
    size_t num = 0;

    for (size_t i = 0; i < element->numChildren; ++i ) {
        Element* child = element->children[i];

        if (strcmp(child->name, name) == 0) {
            result = realloc(result, sizeof(Element*) * (num + 1));
            result[num] = child;
            ++num;
        }
    }

    result = realloc(result, sizeof(Element*) * (num + 1));
    result[num] = NULL;

    return result;
}



Element* BSXML_GetChild(Element* element, const char* name)
{
    for (size_t i = 0; i < element->numChildren; ++i ) {
        Element* child = element->children[i];

        if (strcmp(child->name, name) == 0) {
            return child;
        }
    }

    return NULL;
}



const char* BSXML_GetAttribute(Element* element, const char *attName)
{
    for (size_t i = 0; i < element->numAttributes; ++i) {
        ElementAttr* attr = &element->attributes[i];

        if (strcmp(attr->name, attName) == 0) {
            return attr->value;
        }
    }

    return NULL;
}



Element** BSXML_GetPath(Element* element, const char* inPath)
{
    Element** matches = NULL;

    // We'll split this by putting in NUL chars.
    char* copy = strdup(inPath);
    char* path = copy;

    // Split off an attribute name.
    char* attr = strchr(path, '@');

    if (attr) {
        *attr = 0;
    }

    // Split off the first part.
    char* pos = strchr(path, '/');

    if (pos) {
        *pos = 0;
    }
    
    while (element) {
        if (!pos) {
            // Reached the end.
            matches = BSXML_GetChildren(element, path);
            break;
        }

        element = BSXML_GetChild(element, path);

        path = pos + 1;
        pos = strchr(path, '/');

        if (pos) {
            *pos = 0;
        }
    }

    // Filter out matches that don't have the required attribute
    if (matches && attr) {
        size_t num = 0;

        for (Element** m = matches; *m; ++m) {
            ++num;
        }

        // Make a copy
        Element** matches2 = malloc(sizeof(Element*) * num + 1);
        size_t putter = 0;

        for (size_t i = 0; i < num; ++i) {
            Element* m = matches[i];
            const char* a = BSXML_GetAttribute(m, attr);

            if (a) {
                matches2[putter++] = m;
            }
        }

        matches2[putter++] = NULL;
        free((void*)matches);
        matches = matches2;
    }

    free((void*)copy);
    return matches;
}

//======================================================================
