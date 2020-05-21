/*   _                _
*   | |              (_)
*   | |  __ _  _   _  _
*   | | / _` || | | || |
*   | || (_| || |_| || |
*   |_| \__, | \__,_||_|
*        __/ |
*       |___/
*
* Copyright (c) 2015-20 frank256
*
* License (BSD):
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice, this
*    list of conditions and the following disclaimer in the documentation and/or
*    other materials provided with the distribution.
*
* 3. Neither the name of the copyright holder nor the names of its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "error.h"
#include <cstdio>
#include <cstdarg>

namespace lgui {

void error(const char *heading, const char *format, ...)
{
    char buff[ERROR_MSG_BUFFER_SIZE+1];
    va_list arg;
    va_start(arg, format);
    vsnprintf(buff, ERROR_MSG_BUFFER_SIZE, format, arg);
    va_end(arg);
    _error(heading, buff);
}


void warning(const char *format, ...)
{
    char buff[ERROR_MSG_BUFFER_SIZE+1];
    va_list arg;
    va_start(arg, format);
    vsnprintf(buff, ERROR_MSG_BUFFER_SIZE, format, arg);
    va_end(arg);
    _warning(buff);
}

void debug(const char *format, ...)
{
    char buff[ERROR_MSG_BUFFER_SIZE+1];
    va_list arg;
    va_start(arg, format);
    vsnprintf(buff, ERROR_MSG_BUFFER_SIZE, format, arg);
    va_end(arg);
    _debug(buff);
}

void info(const char *format, ...)
{
    char buff[ERROR_MSG_BUFFER_SIZE+1];
    va_list arg;
    va_start(arg, format);
    vsnprintf(buff, ERROR_MSG_BUFFER_SIZE, format, arg);
    va_end(arg);
    _info(buff);
}

void _handle_assert(const char *expression, const char *_file_, const int _line_)
{
    error("Internal error", "Assertion failed in %s at line %d:\n%s", _file_, _line_, expression);
}

void _handle_assert(const char *expression, const char *_file_, const int _line_, const char* msg)
{
    error("Internal error", "Assertion failed in %s at line %d:\n%s\n%s", _file_, _line_, expression, msg);
}

}
