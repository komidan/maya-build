#include <stdio.h>
#include <stdarg.h>

#include <maya/error.h>

const char *get_err_name(Error err)
{
    switch (err)
    {
        case ERR_NONE:          return "None";

        case ERR_MISSING_FIELD: return "MissingField";
        case ERR_INVALID_FIELD: return "InvalidField";
        case ERR_TYPE:          return "TypeError";
        case ERR_VALUE:         return "ValueError";

        case ERR_PARSE:         return "ParseError";
        case ERR_MEMORY:        return "MemoryError";

        default:                return "UnknownError";
    }
}

void maya_error(Error err, const char *msg, ...)
{
    fprintf(stderr, "[MAYA] %s: ", get_err_name(err));

    va_list args;
    va_start(args, msg);

    vfprintf(stderr, msg, args);

    va_end(args);

    fputc('\n', stderr);
}
