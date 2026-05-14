#ifndef BUNDLER_H
#define BUNDLER_H

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
 *
 */

#include <stddef.h>

#define MAX_FILES   256
#define PATH_SIZE   256
#define FILE_SIZE   32
#define SRC_DIR     CURRENT

typedef enum src_dir_e {
    CURRENT,
    SRC
} src_dir_t;

extern char *processed_files[MAX_FILES];
extern size_t file_count;
extern char *included_files[MAX_FILES];
extern size_t included_files_count;

int process_file(const char *const currentpath, const char *const filepath);
int parse_file(const char *const fullpath);
void extract_filename(const char *const path, char*const filename);
int extract_dirname(const char *const oath, char *const dirname);
bool is_processed(const char *const filename);
bool is_included(const char *const filename);
void print_processed_files(void);
void print_included_files(void);
int bun_clear(void);

#endif /* BUNDLE_H */
