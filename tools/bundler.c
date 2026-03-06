/*
 * Bundler that copy the content of user's #include macros and generates
 * one output file
 *
 * 1. Finds the substring between "" in the #include directives and process
 *    the inner files recursively
 *
 * 2. Handle directories in the #include directives
 *
 * 3. Removes guards in header files, like #ifndef, #define, and #endif
 *
 * TODO: The code seems to work.
 * Make some tests
 * remove comments
 *
 * Issues: the #define directives don't accept _H in its name, the bundler
 * will remove it as if it were a guard directive
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 256

char *processed_files[MAX_FILES];
size_t file_count = 0;

int is_processed(const char *filename) {
    for (int i = 0; i < file_count; i++)
        if (strcmp(filename, processed_files[i]) == 0)
            return 1;
    return 0;
}

int process_file(const char *base_path, const char *filename) {
    // build the fullpath
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", base_path, filename);

    //update the basepath
    char new_base[256];
    snprintf(new_base, sizeof(new_base), "%s", base_path);
    char *last_slash = strrchr(filename, '/');
    if (last_slash != NULL) {
        int dir_len = last_slash - filename + 1;
        strncat(new_base, filename, dir_len);
    }

    // check if it was process to not include duplicate files
    if (is_processed(full_path))
        return EXIT_SUCCESS;

    FILE *file = fopen(full_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open the file %s\n", filename);
        return EXIT_FAILURE;
    }

    // add the file to the list of processed files
    char *copy = (char *)malloc(strlen(full_path) + 1);
    if (copy != NULL) {
        strcpy(copy, full_path);
        processed_files[file_count++] = copy;
    }

    // process the current file
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        if ((strstr(buffer, "#ifndef") && strstr(buffer, "_H")) ||
            (strstr(buffer, "#define") && strstr(buffer, "_H")) ||
            strstr(buffer, "#endif"))
                continue;

        char *include_pos = strstr(buffer, "#include");

        if (include_pos != NULL) {
            char *start = strchr(include_pos, '"');
            char *end = NULL;

            if (start != NULL) {
                start++;
                end = strchr(start, '"');
            }
            if (end != NULL) {
                *end = '\0';
            }

            if (start && end) {
                process_file(new_base, start);
                continue;
            }
        }
        printf("%s", buffer);
    }
    fclose(file);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Use: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    process_file("./", argv[1]);
    return EXIT_SUCCESS;
}
