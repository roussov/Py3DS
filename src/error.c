#include "error.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

void error_init(Error* err, ErrorType type, const char* fmt, ...) {
    if (!err) return;
    err->type = type;
    err->line = -1; // par défaut pas de ligne

    va_list args;
    va_start(args, fmt);
    vsnprintf(err->message, sizeof(err->message), fmt, args);
    va_end(args);
}

void error_print(const Error* err) {
    if (!err) return;
    const char* type_str = "UNKNOWN ERROR";

    switch (err->type) {
        case ERROR_NONE: type_str = "No error"; break;
        case ERROR_SYNTAX: type_str = "Syntax error"; break;
        case ERROR_RUNTIME: type_str = "Runtime error"; break;
        case ERROR_NAME: type_str = "Name error"; break;
        case ERROR_TYPE: type_str = "Type error"; break;
        case ERROR_VALUE: type_str = "Value error"; break;
        case ERROR_IO: type_str = "IO error"; break;
        case ERROR_INTERNAL: type_str = "Internal error"; break;
    }

    if (err->line >= 0)
        fprintf(stderr, "[%s] Line %d: %s\n", type_str, err->line, err->message);
    else
        fprintf(stderr, "[%s]: %s\n", type_str, err->message);
}
