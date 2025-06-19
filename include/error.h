#ifndef ERROR_H
#define ERROR_H

typedef enum {
    ERROR_NONE,
    ERROR_SYNTAX,
    ERROR_RUNTIME,
    ERROR_NAME,
    ERROR_TYPE,
    ERROR_VALUE,
    ERROR_IO,
    ERROR_INTERNAL
} ErrorType;

typedef struct {
    ErrorType type;
    char message[256];
    int line;
} Error;

void error_init(Error* err, ErrorType type, const char* fmt, ...);
void error_print(const Error* err);

#endif
