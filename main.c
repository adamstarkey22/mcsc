#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "scanner.h"

static char *read_file(const char *path)
{
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file \"%s\".\n", path);
        return NULL;
    }

    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory for file \"%s\".\n", path);
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
    if (bytes_read < file_size) {
        fprintf(stderr, "Failed to read file \"%s\".\n", path);
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[bytes_read] = '\0';
    fclose(file);
    return buffer;
}

int main(int argc, char **argv)
{
    const char *input_path;
    const char *output_path;

    if (argc == 3) {
        input_path = argv[1];
        output_path = argv[2];
    } else {
        fprintf(stderr, "Usage: mcsc <input> <output>\n");
        exit(64);
    }

    char *source = read_file(input_path);
    if (source == NULL) {
        exit(74);
    }

    init_scanner(source);

    int line = 0;
    for (;;) {
        Token token = scan_token();
        if (token.line != line) {
            printf("%4d ", token.line);
            line = token.line;
        } else {
            printf("   | ");
        }

        printf("%-24s ", token_type_str(token.type));

        if (token.type != TOKEN_LINE_BREAK) {
            printf("'%.*s'", token.length, token.start);
        }

        printf("\n");

        if (token.type == TOKEN_EOF) {
            break;
        }
    }

    free(source);
    return 0;
}
