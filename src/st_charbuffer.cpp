/*  Copyright (c) 2016 Michael Hansen

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE. */

#include "st_charbuffer.h"

#include <cstring>

ST_STATIC_ASSERT(ST_SHORT_STRING_LEN >= sizeof(void *),
                 "ST_SHORT_STRING_LEN must be at least as large as a pointer")
ST_STATIC_ASSERT(ST_STACK_STRING_LEN >= sizeof(void *),
                 "ST_STACK_STRING_LEN must be at least as large as a pointer")

void _ST_PRIVATE::_zero_buffer(void *buffer, size_t size)
{
    memset(buffer, 0, size);
}

void _ST_PRIVATE::_fill_buffer(void *buffer, int ch, size_t count)
{
    memset(buffer, ch, count);
}

void _ST_PRIVATE::_copy_buffer(void *dest, const void *src, size_t size)
{
    memcpy(dest, src, size);
}

int _ST_PRIVATE::_compare_buffer(const void *left, const void *right, size_t size)
{
    return memcmp(left, right, size);
}
