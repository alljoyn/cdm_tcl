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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
//#include <stdint.h>

#include "HAL.h"

static int PathExists(const char *path) {
    struct stat st = {0};
    return stat(path, &st) != -1;
}

static int CreateDirectories(char *path)
{
    char *token = strtok(path, "/");
    char *prev = token - 1;

    while (token != NULL)
    {
        if (prev != path)
            *prev = '/';

        token = strtok(NULL, "/");

        if (!PathExists(path))
        {
            if (mkdir(path, 0700) != 0)
            {
                perror("mkdir");
                return 0;
            }
        }

        prev = token - 1;
    }

    return 1;
}

#define MAX_PATH_LEN 256
const char *ROOT = NULL;
const char *EXT = NULL;

void HAL_Init(const char *base_path, const char *ext)
{
    ROOT = base_path;
    EXT = ext;
}

void HAL_DefaultInit()
{
    static const char *root = "device_state";
    static const char *ext = ".state";
    ROOT = root;
    EXT = ext;
}


int HAL_WriteProperty(const char *objPath, const char *interface, const char *property, HAL_WriterFunc write, void *data)
{
    FILE *fp;

    char path[MAX_PATH_LEN];
    size_t totalPathLen;
    int result = 0;

    if (ROOT == NULL || EXT == NULL)
    {
        fprintf(stderr, "HAL hasn't been initialised.\n");
        return 0;
    }

    totalPathLen = strlen(ROOT) + strlen(objPath) + 1 + strlen(interface) + 1 + strlen(property) + strlen(EXT);
    if (totalPathLen >= MAX_PATH_LEN)
    {
        fprintf(stderr, "Path length too long %lu >= %d\n", totalPathLen, MAX_PATH_LEN);
        return 0;
    }

    memset(path, 0, MAX_PATH_LEN);
    strcat(path, ROOT);
    strcat(path, objPath);
    strcat(path, "/");
    strcat(path, interface);

    if (!PathExists(path))
    {
        if (!CreateDirectories((char*)path))
            return 0;
    }

    strcat(path, "/");
    strcat(path, property);
    strcat(path, EXT);

    fp = fopen(path, "w");
    result = write(fp, data);
    fclose(fp);

    return result;
}

int HAL_ReadProperty(const char *objPath, const char *interface, const char *property, HAL_ReaderFunc read, void *out)
{
    long fSize;
    long numRead;
    char *buf;
    int result = 0;
    FILE *fp;

    char path[MAX_PATH_LEN];
    size_t totalPathLen;

    if (ROOT == NULL || EXT == NULL)
    {
        fprintf(stderr, "HAL hasn't been initialised.\n");
        return 0;
    }

    totalPathLen = strlen(ROOT) + strlen(objPath) + 1 + strlen(property) + strlen(EXT);
    if (totalPathLen >= MAX_PATH_LEN)
    {
        fprintf(stderr, "Path length too long %lu >= %d\n", totalPathLen, MAX_PATH_LEN);
        return 0;
    }

    memset(path, 0, MAX_PATH_LEN);
    strcat(path, ROOT);
    strcat(path, objPath);
    strcat(path, "/");
    strcat(path, interface);
    strcat(path, "/");
    strcat(path, property);
    strcat(path, EXT);

    fp = fopen(path, "r");

    fseek(fp, 0L, SEEK_END);
    fSize = ftell(fp);
    rewind(fp);

    buf = (char*)malloc(fSize);
    if (buf == NULL)
        goto ERROR;

    numRead = fread(buf, 1, fSize, fp);
    if (numRead != fSize)
        goto CLEANUP;

    result = read(fp, buf, out);

    CLEANUP:
    free(buf);
    ERROR:
    fclose(fp);

    return result;
}

int HAL_WriteBool(FILE *fp, void* data)
{
    int *value = (int*)data;
    int result = fprintf(fp, "%d", *value);

    return (result <= 0) ? 0 : 1;
}

int HAL_WriteInt(FILE *fp, void* data)
{
    int64_t *value = (int64_t*)data;
    long result = fprintf(fp, "%lld", *value);

    return (result <= 0) ? 0 : 1;
}

int HAL_ReadBool(FILE *fp, const char *buf, void *data)
{
    int *value = (int*)data;
    if (strlen(buf)!= 1)
        return 0;

    *value = (buf[0] == '0') ? 0 : 1;
    return 1;
}

int HAL_ReadInt(FILE *fp, const char *buf, void *data)
{
    int64_t v;
    char *ptr;
    int64_t *value = (int64_t*)data;

    v = strtol(buf, &ptr, 10);
    *value = v;

    return 1;
}