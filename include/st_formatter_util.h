/*  Copyright (c) 2018 Michael Hansen

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

#ifndef _ST_FORMATTER_UTIL_H
#define _ST_FORMATTER_UTIL_H

#include "st_formatter.h"
#include <functional>

namespace _ST_PRIVATE
{
    typedef std::function<void (const ST::format_spec &, ST::format_writer &)>
        formatter_ref_t;

    template <typename type_T>
    formatter_ref_t make_formatter_ref(type_T value)
    {
        return [value](const ST::format_spec &format, ST::format_writer &output) {
            ST_INVOKE_FORMATTER(format, output, value);
        };
    }

    template <typename... args_T>
    void apply_format(ST::format_writer &data, args_T ...args)
    {
        std::array<formatter_ref_t, sizeof...(args)> formatters = {
            make_formatter_ref(args)...
        };
        size_t index = 0;
        while (data.next_format()) {
            ST::format_spec format = data.parse_format();
            formatter_ref_t &formatter = formatters.at(format.arg_index >= 0
                                                       ? format.arg_index - 1
                                                       : index++);
            formatter(format, data);
        }
    }
}

#endif // _ST_FORMATTER_UTIL_H
