#pragma once

#ifndef CONFIG_H_
#define CONFIG_H_

#include "../cktan/tomlc17.h"
#include "../tsoding/arena.h"

typedef struct {
    const char *project_name;
    const char *project_author;
    const char *project_version;
} Config;

/**
 * @brief Builds the configuration and validates it.
 *
 * @param *toml    Toml configuration
 *
 * @return false if success, true if fail
 */
int config_build(Arena *arena, toml_result_t *toml, Config *config);

#endif // CONFIG_H_
