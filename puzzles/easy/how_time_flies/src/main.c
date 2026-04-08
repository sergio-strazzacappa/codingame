#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct date_s {
    size_t day;
    size_t month;
    size_t year;
} date_t;

const int DAYS_PER_MONTH[12] = {
    31, 28, 31,
    30, 31, 30,
    31, 31, 30,
    31, 30, 31
};

bool is_leap_year(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int number_of_leap_years(int year1, int year2) {
    return
        (year2 / 4 - (year1 - 1) / 4) -
        (year2 / 100 - (year1 - 1) / 100) +
        (year2 / 400 - (year1 - 1) / 400);
}

int get_total_days(date_t date) {
    int total = date.year * 365 + number_of_leap_years(1, date.year);

    for (size_t m = 0; m < date.month - 1; m++)
        total += DAYS_PER_MONTH[m];

    if (date.month <= 2 && is_leap_year(date.year))
        total--;

    total += date.day;

    return total;
}

void solve(date_t begin, date_t end) {
    int year_diff, month_diff;

    // calculate the years diff and months diff
    year_diff = end.year - begin.year;

    if (begin.month > end.month) {
        year_diff--;
        month_diff = 12 - (begin.month - end.month);
    } else {
        month_diff = end.month - begin.month;
    }

    if (begin.day > end.day)
        month_diff--;

    if (month_diff < 0) {
        month_diff = 11;
        year_diff--;
    }

    // calculate the total days
    int total_days = get_total_days(end) - get_total_days(begin);

    // print the result
    if (year_diff > 0)
        printf("%d year%s, ", year_diff, year_diff > 1 ? "s" : "");
    if (month_diff > 0)
        printf("%d month%s, ", month_diff, month_diff > 1 ? "s" : "");

    printf("total %d days\n", total_days);
}

void parse_input(date_t *begin, date_t *end) {
    char b[32], e[32];

    if (fgets(b, sizeof(b), stdin))
        sscanf(b, "%zu.%zu.%zu", &begin->day, &begin->month, &begin->year);

    if (fgets(e, sizeof(e), stdin))
        sscanf(e, "%zu.%zu.%zu", &end->day, &end->month, &end->year);
}

int main(void) {
    date_t begin, end;
    parse_input(&begin, &end);
    solve(begin, end);

    return EXIT_SUCCESS;
}
