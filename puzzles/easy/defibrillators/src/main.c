#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define NUMBER_LEN  150
#define STRING_LEN  257
#define MAX_DEFS    10000

typedef struct point_s {
    double lon;
    double lat;
} point_t;

typedef struct defib_s {
    char name[STRING_LEN];
    double lon;
    double lat;
} defib_t;

void solve(defib_t defs[], size_t n, point_t user) {
    char name[STRING_LEN];
    double min_distance = DBL_MAX;

    for (size_t i = 0; i < n; i++) {
        fprintf(stderr, "[DEBUG] (%s %0.20f %0.20f)\n",
            defs[i].name, defs[i].lon, defs[i].lat);

        double d = sqrt(
                    pow(defs[i].lon - user.lon, 2) +
                    pow(defs[i].lat - user.lat, 2));

        fprintf(stderr, "[DEBUG] Distance: %f\n", d);

        if (d < min_distance) {
            min_distance = d;
            strcpy(name, defs[i].name);
        }
    }
    printf("%s\n", name);
}

/**
 * return the string s converted to double and replacing the , for a .
 */
double str_to_double(char s[]) {
    char *comma = strchr(s, ',');
    if (comma != NULL)
        *comma = '.';
    return atof(s);
}

int main(void) {
    char lon[NUMBER_LEN], lat[NUMBER_LEN];
    size_t n;

    scanf("%s%s%zu", lon, lat, &n);
    fgetc(stdin);

    point_t user = {
        .lon = str_to_double(lon),
        .lat = str_to_double(lat)
    };

    // read the data of the defibrillators
    defib_t defs[MAX_DEFS];

    for (size_t i = 0; i < n; i++) {
        char defib[STRING_LEN];
        scanf("%[^\n]", defib);
        fgetc(stdin);

        // extract the needed fields
        // 1. Id
        // 2. Name <-
        // 3. Address
        // 4. Phone number
        // 5. Longitude <-
        // 6. Latitude <-

        char *start = defib;
        char *end;
        size_t field = 1;

        do {
            while (*start == ';') {
                start++;
                field++;
            }

            switch (field) {
                case 2:
                    end = strchr(start, ';');
                    strncpy(defs[i].name, start, end - start);
                    break;
                case 5:
                    end = strchr(start, ';');
                    *end = '\0';
                    defs[i].lon = str_to_double(start);
                    *end = ';';
                    break;
                case 6:
                    defs[i].lat = str_to_double(start);
                    break;
                default:
                    break;
            }
        } while ((start = strchr(start, ';')));
    }

    for (size_t i = 0; i < n; i++) {
        fprintf(stderr, "[DEBUG] %s - %f - %f\n",
            defs[i].name, defs[i].lon, defs[i].lat);
    }

    solve(defs, n, user);

    return EXIT_SUCCESS;
}
