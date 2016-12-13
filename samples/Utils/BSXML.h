/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef ALLJOYN_BSXML_H
#define ALLJOYN_BSXML_H

#include <stdint.h>
#include <stdlib.h>

//======================================================================

/**
 * This is not a full-blown XML parser/generator and performs no DTD validation
 * or other advanced features.
 */

typedef struct ElementAttr {
    const char* name;
    const char* value;
    } ElementAttr;


typedef struct Element {
    const char* name;                   // Element name 
    struct Element** children;          // array of pointers to child nodes
    size_t numChildren;
    ElementAttr* attributes;            // array of attribute records
    size_t numAttributes;
    const char* content;                // XML text content (unescaped) 
    struct Element* parent;             // XML parent element or NULL if root 
    } Element;



/**
 * Retrieves the root of the XML in form of a Element.
 *
 * @param[in]     xml     Input XML.
 * @return    the element if successful
 */
extern Element* BSXML_GetRoot(const char* xml);


/**
 * Construct an Element with a given name and parent.
 *
 * @param parent   Parent element or NULL if this element is the root.
 * @param name     XML element name.
 */
extern Element* BSXML_NewElement(const char* name, Element* parent);


/** 
 * This will free all child elements too and the element itself.
 */
extern void BSXML_FreeElement(Element* element);


/** 
 * This will only free the strings in the attribute.
 */
extern void BSXML_FreeElementAttr(ElementAttr* attr);


/**
 * Output an XML fragment of this Element including any childeren.
 *
 * @param outStr  Optional string to be used for output. (Defaults to empty string.)
 * @return  XML Fragment. The caller must free it.
 */
const char* BSXML_Generate(Element* element);

/**
 * Return a C string representation of the Element
 *
 * @return   XML in form of a zero-terminated string.
 *           The caller must free it.
 */
const char* BSXML_ToString(Element* element);


/**
 * Set the element name.
 *
 * @param elementName    Name of XML element.  The name will be copied.
 */
void BSXML_SetName(Element* element, const char* name);

/**
 * Get an attribute with a given name or NULL if it doesn't exist.
 *
 * @param attName   Name of attribute
 * @return a pointer to the value of the attribute. The caller must not free it.
 */
const char* BSXML_GetAttribute(Element* element, const char* attName);

/**
 * Add an Xml Attribute
 * The strings will be copied.
 */
void BSXML_AddAttribute(Element* element, const char* name, const char* value);

/**
 * Add a child element. The parent will take over memory managment for the child.
 *
 * @param child  The child Element.
 */
void BSXML_AddChild(Element *parent, Element *child);

/**
 * Get all children with a given name.
 *
 * Only return direct children. This method will not do a recursive search
 * of the child nodes.
 *
 * @param name   XML child elements name to search for.
 * @return  An array of pointers to elements, terminated by a NULL pointer. The caller must free it.
 */
Element**  BSXML_GetChildren(Element* element, const char* name);

/**
 * Get the child element with a given name if it exists.
 *
 * @param name   XML child element name to search for.
 * @return  Pointer to XML child element or NULL if not found.
 */
Element* BSXML_GetChild(Element* element, const char* name);


/**
 * Set the (unesacped) text content.
 *
 * @param  newContent    Unescaped ("&" not "&amp;") text content for this node.
 * The content will be copied.
 */
void BSXML_SetContent(Element* element, const char* newContent);

/**
 * Add text content to this node.
 * An Element can only have content or children. Not both. If content is added
 * to an Element that has children, the text content will be silently ignored.
 *
 * @param newContent   Text content to add to this node.
 */
void BSXML_AddContent(Element* element, const char* newContent);

/**
 * Get all elements that have the specified path relative to the current element. The path is a
 * series of tag names separated by '/' with an optional attribute specified by an '@' character
 * followed by the attribute name.
 *
 * Given the XML below GetPath("foo/bar/value@first") will return the <value> element
 * containing "hello" and GetPath("foo/bar/value@second") will return the <value> element
 * containing "world". GetPath("foo/bar/value") will return both <value> elements.
 *
 * <foo>
 *    <bar>
 *       <value first="hello"/>
 *       <value second="world"/>
 *    </bar>
 * </foo>
 *
 * @param key   The key is a dotted path (with optional attribute) to a value in the XML
 *
 * @param path   The path to elements in the XML tree.
 *
 * @return an array of Element pointers, terminated by a NULL. The caller must free the array.
 */
Element** BSXML_GetPath(Element* element, const char* path);

/**
 * Utility function to escape text for use in XML
 *
 * @param str The unescaped string
 * @return The escaped string which the caller must free.
 */
const char* BSXML_EscapeXml(const char* str);

/**
 * Utility function to unescape text from XML
 *
 * @param str The escaped string
 * @return The unescaped string which the caller must free.
 */
const char* BSXML_UnescapeXml(const char* str);

//======================================================================
#endif //ALLJOYN_BSXML_H