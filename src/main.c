#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <cktan/tomlc17.h>
#include <maya/config.h>
// #include <maya/process.h>
#include <maya/error.h>

#define ARENA_IMPLEMENTATION
#include <tsoding/arena.h>

#define VERSION "0.1.0"

// TODO: This eventually needs to be moved out to a separate include
// that can check for all folders/files necessary depending on the
// system/environment using system-specific functions.
int file_exists(const char *path)
{
    FILE *fp = fopen(path, "rb");

    if (fp == NULL)
    {
        if (errno == ENOENT)
        {
            fprintf(stderr, "[MAYA] No configuration file found. You need to create one!\n  (insert link to documentation here)\n");
        }
        else
        {
            fprintf(stderr, "[MAYA] Cannot open configuration file: %s\n",
                strerror(errno));
        }

        return 0;
    }

    return 1;
}

static const char HELP[] =
    "Usage: maya [options]\n"
    "\n"
    "Options:\n"
    "    -h, --help        Display this help message\n"
    "    -v, --version     Display version information\n"
    "    -c, --clean       Clean build artifacts\n"
    "    -d, --debug       Compile in configured debug mode\n"
    "    -r, --release     Compile in configured release mode\n"
    "\n";

static void print_help(void)
{
    fputs(HELP, stdout);
}

int main(int argc, char *argv[])
{
    if (!file_exists("maya.toml"))
    {
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0 ||
            strcmp(argv[i], "-h") == 0)
        {
            print_help();
            return 0;
        }
        else if (strcmp(argv[i], "--version") == 0 ||
                 strcmp(argv[i], "-v") == 0)
        {
            printf("maya %s\n", VERSION);
            return 0;
        }

        if (strcmp(argv[i], "--clean") == 0 ||
            strcmp(argv[i], "-c") == 0)
        {
            printf("clean...\n");
            return 0;
        }
    }

    const char *fname = "maya.toml";

    toml_result_t toml = toml_parse_file_ex(fname);
    Arena arena = {0};

    if (!toml.ok)
    {
        maya_error(ERR_PARSE, "Failed to parse toml file '%s'", fname);
        return 1;
    }

    Config config = {0};

    if (config_build(&arena, &toml, &config))
    {
        return 1;
    }

    toml_free(toml);
    arena_free(&arena);

    return 0;
}