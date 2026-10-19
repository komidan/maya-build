#include <stdio.h>

#include <cktan/tomlc17.h>
#include <maya/config.h>
#include <maya/error.h>
#include <tsoding/arena.h>

static int get_string(Arena *arena, toml_datum_t table, const char *field, const char *fallback, const char **dest)
{
    toml_datum_t datum = toml_seek(table, field);
    const char *value = NULL;

    if (datum.type == TOML_UNKNOWN)
    {
        if (fallback == NULL)
        {
            maya_error(ERR_MISSING_FIELD, "Missing field '%s'", field);
            return 1;
        }

        value = fallback;
    }
    else if (datum.type != TOML_STRING)
    {
        maya_error(ERR_TYPE, "Incorrect type on field '%s'", field);
        return 1;
    }
    else
    {
        value = datum.u.str.ptr;
    }

    *dest = arena_strdup(arena, value);

    if (*dest == NULL)
    {
        maya_error(ERR_MEMORY, "Unable to allocate field '%s'", field);
        return 1;
    }

    return 0;
}

int config_build(Arena *arena, toml_result_t *toml, Config *config)
{
    size_t e = 0;

    // Project Field
    e += get_string(arena, toml->toptab, "project.name", NULL,
                    &config->project_name);
    e += get_string(arena, toml->toptab, "project.author", "Unknown",
                    &config->project_author);
    e += get_string(arena, toml->toptab, "project.version", NULL,
                    &config->project_version);

    // Build Field


    if (e)
    {
        printf("[MAYA] Validation Errors: %zu\n", e);
        return 1;
    }

    return 0;
}
