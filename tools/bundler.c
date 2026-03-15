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
 * Usage: gcc -o bundler bundler.c && ./bundler file
 *
 * Issues: the #define directives don't accept _H in its name, the bundler
 * will remove it as if it were a guard directive
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 256
#define PATH_SIZE 256
#define FILE_SIZE 32

char *processed_files[MAX_FILES];
size_t file_count = 0;
char *included_files[MAX_FILES];
size_t included_files_count = 0;

void extract_filename(const char*const, char*const);
int extract_dirname(const char*const , char*const);
int is_processed(const char*const);
int is_included(const char*const);
void print_processed_files(void);
void print_included_files(void);
int parse_file(const char *const);
int process_file(const char*const, const char*const);

void extract_filename(const char *const path, char *const filename) {
    char *last_slash = strrchr(path, '/');

    if (last_slash == NULL) {
        size_t path_len = strlen(path);
        strncpy(filename, path, path_len);
        filename[path_len] = '\0';
    } else {
        char *start = last_slash + 1;
        size_t file_len = strlen(start);
        strncpy(filename, start, file_len);
        filename[file_len] = '\0';
    }
}

int extract_dirname(const char *const path, char *const dirname) {
    if (path == NULL || dirname == NULL)
        return EXIT_FAILURE;

    char *last_slash = strrchr(path, '/');

    if (last_slash == NULL) {
        strcpy(dirname, ".");
        return EXIT_SUCCESS;
    }

    size_t dir_len = last_slash - path;

    if (dir_len == 0) {
        strcpy(dirname, "/");
    } else {
        strncpy(dirname, path, dir_len);
        dirname[dir_len] = '\0';
    }
    return EXIT_SUCCESS;
}

int is_processed(const char *const filename) {
    for (size_t i = 0; i < file_count; i++)
        if (strcmp(filename, processed_files[i]) == 0)
            return 1;
    return 0;
}

int is_included(const char *const filename) {
    for (size_t i = 0; i < included_files_count; i++)
        if (strcmp(filename, included_files[i]) == 0)
            return 1;
    return 0;
}

void print_processed_files(void) {
    fprintf(stderr, "[DEBUG] List of processed files:\n");

    for (size_t i = 0; i < file_count; i++) {
        fprintf(stderr, "\t%s\n", processed_files[i]);
    } 
}

void print_included_files(void) {
    fprintf(stderr, "List of included files:\n");

    for (size_t i = 0; i < included_files_count; i++) {
        fprintf(stderr, "\t%s\n", included_files[i]);
    }
}

int parse_file(const char *const fullpath) {
    FILE *file = fopen(fullpath, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open the file %s\n", fullpath);
        perror("error");
        return EXIT_FAILURE;
    }

    char filename[FILE_SIZE];
    extract_filename(fullpath, filename);

    // add the file to the list of processed files
    char *copy_file = (char *)malloc(sizeof(char) * FILE_SIZE);
    strcpy(copy_file, filename);
    processed_files[file_count++] = copy_file;
    print_processed_files();

    printf("\n/*\n");
    printf(" * BEGIN %s\n", filename);
    printf(" */\n\n");

    // process the current file
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        if ((strstr(buffer, "#ifndef") && strstr(buffer, "_H")) ||
            (strstr(buffer, "#define") && strstr(buffer, "_H")) ||
            strstr(buffer, "#endif"))
                continue;

        char *include_pos = strstr(buffer, "#include");

        if (include_pos != NULL) {
            // extract system includes
            char *start = strchr(include_pos, '<');
            char *end = NULL;

            if (start != NULL) {
                start++;
                end = strchr(start, '>');

                char *copy_file = (char *)malloc(FILE_SIZE * sizeof(char));
                size_t file_len = end - start;
                strncpy(copy_file, start, file_len);
                copy_file[file_len] = '\0';

                if (is_included(copy_file)) {
                    continue;
                } else {
                    included_files[included_files_count++] = copy_file;
                    print_included_files();
                }
            }

            // extract user includes
            start = strchr(include_pos, '"');
            end = NULL;

            if (start != NULL) {
                start++;
                end = strchr(start, '"');

                char dirpath[PATH_SIZE];
                extract_dirname(fullpath, dirpath);
                size_t dir_len = strlen(dirpath);
                dirpath[dir_len] = '/';
                dirpath[dir_len + 1] = '\0';
                *end = '\0';
                process_file(dirpath, start) ;
                continue;
            }
        }
        printf("%s", buffer);
    }

    printf("\n/*\n");
    printf(" * END %s\n", filename);
    printf(" */\n\n");
    fclose(file);

    return EXIT_SUCCESS;
}

int process_file(const char *const currentpath, const char *const filepath) {
    fprintf(stderr, "[DEBUG] process_file(%s, %s)\n", currentpath, filepath);

    // build the fullpath
    char fullpath[PATH_SIZE];
    snprintf(fullpath, sizeof(fullpath), "%s%s", currentpath, filepath);

    // extract the filename
    char filename[FILE_SIZE];
    extract_filename(fullpath, filename);

    fprintf(stderr, "[DEBUG] full path:%s - file name:%s\n", fullpath, filename);

    // check if it was process to not include duplicate files
    if (is_processed(filename)) {
        return EXIT_SUCCESS;
    }

    // output the content of the file
    parse_file(fullpath);

    // if it is a .h file search for a .c file to copy the implementation
    size_t len = strlen(fullpath);
    if (fullpath[len - 2] == '.' && fullpath[len - 1] == 'h') {
        //update the basepath
        char newpath[PATH_SIZE];
        extract_dirname(fullpath, newpath);
        size_t newpath_len = strlen(newpath);
        newpath[newpath_len - 7] = 's';
        newpath[newpath_len - 6] = 'r';
        newpath[newpath_len - 5] = 'c';
        newpath[newpath_len - 4] = '/';
        newpath[newpath_len - 3] = '\0';

        char newfile[FILE_SIZE];
        strcpy(newfile, filename);
        newfile[strlen(newfile) - 1] = 'c';

        process_file(newpath, newfile);
    }
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    process_file("", argv[1]);

    // clean memory
    for (size_t i = 0; i < file_count; i++) {
        free(processed_files[i]);
    }
    file_count = 0;

    for (size_t i = 0; i < included_files_count; i++) {
        free(included_files[i]);
    }
    included_files_count = 0;

    return EXIT_SUCCESS;
}
