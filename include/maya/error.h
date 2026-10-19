#pragma once

#ifndef ERROR_H_
#define ERROR_H_

typedef enum {
    ERR_NONE = 0,

    // Configuration / Validation
    ERR_MISSING_FIELD,
    ERR_INVALID_FIELD,
    ERR_TYPE,
    ERR_VALUE,

    ERR_PARSE,
    ERR_MEMORY,
} Error;

/**
 * @brief Reports an error to stderr.
 *
 * @param msg    Description of the error.
 * @param err    Error category.
 * @param ...    Formatter args
 *
 * @noreturn
 */
void maya_error(Error err, const char *msg, ...);

/**
 * @brief Converts error type into readable string.
 *
 * @param err    Error enum category
 *
 * @return String representation of the error.
 */
const char *get_err_name(Error err);

#endif // ERROR_H_
