#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <string.h>
#include <assert.h>

int parse_month(const char month[]) {
    if (strcmp(month, "Jan") == 0)  return 0;
    if (strcmp(month, "Feb") == 0)  return 1;
    if (strcmp(month, "Mar") == 0)  return 2;
    if (strcmp(month, "Apr") == 0)  return 3;
    if (strcmp(month, "May") == 0)  return 4;
    if (strcmp(month, "Jun") == 0)  return 5;
    if (strcmp(month, "Jul") == 0)  return 6;
    if (strcmp(month, "Aug") == 0)  return 7;
    if (strcmp(month, "Sep") == 0)  return 8;
    if (strcmp(month, "Oct") == 0)  return 9;
    if (strcmp(month, "Nov") == 0)  return 10;
    if (strcmp(month, "Dec") == 0)  return 11;

    assert(0);

    return EXIT_FAILURE;
}

int parse_wday(const char wday[]) {
    if (strcmp(wday, "Sunday") == 0)    return 0;
    if (strcmp(wday, "Monday") == 0)    return 1;
    if (strcmp(wday, "Tuesday") == 0)   return 2;
    if (strcmp(wday, "Wednesday") == 0) return 3;
    if (strcmp(wday, "Thursday") == 0)  return 4;
    if (strcmp(wday, "Friday") == 0)    return 5;
    if (strcmp(wday, "Saturday") == 0)  return 6;

    assert(0);

    return EXIT_FAILURE;
}

void solve(struct tm source, struct tm target) {
    int wday = source.tm_wday;
    time_t date1 = mktime(&target);
    time_t date2 = mktime(&source);

    double diff = difftime(date1, date2);

    diff /= (3600 * 24);

    const char *WDAYS[7] = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };

    int index = (wday + (int)diff) % 7;

    if (index < 0)
        index += 7;

    printf("%s\n", WDAYS[index]);
}

int main(void) {
    int leap_year;
    scanf("%d", &leap_year);

    char source_day_of_week[16];
    char source_month[16];
    int source_day_of_month;
    scanf("%s%s%d", source_day_of_week, source_month, &source_day_of_month);

    char target_month[16];
    int target_day_of_month;
    scanf("%s%d", target_month, &target_day_of_month);

    int year = 1995;
    if (leap_year)
        year = 1996;

    struct tm source = {0};
    source.tm_mday = source_day_of_month;
    source.tm_mon = parse_month(source_month);
    source.tm_wday = parse_wday(source_day_of_week);
    source.tm_year = year - 1900;

    struct tm target = {0};
    target.tm_mday = target_day_of_month;
    target.tm_mon = parse_month(target_month);
    target.tm_year = year - 1900;

    solve(source, target);

    return EXIT_SUCCESS;
}
