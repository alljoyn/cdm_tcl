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


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "FileIO.h"

//======================================================================


bool ReadFile(const char *filepath, StrBuf* outBuf)
{
    char buf[BUFSIZ];
    bool ok = false;

    FILE* fp = fopen(filepath, "r");

    if (fp) {
        for (;;) {
            int n = fread(buf, 1, BUFSIZ, fp);

            if (n > 0) {
                StrBuf_AppendStrNum(outBuf, buf, n);
            } else if (n == 0) {
                ok = true;
                break;
            } else {
                fprintf(stderr, "%s", filepath);
                fprintf(stderr, ": %s\n", strerror(errno));
                break;
            }
        }

        fclose(fp);
    }

    return ok;
}

//======================================================================

