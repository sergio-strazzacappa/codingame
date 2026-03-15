#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../lib/ds/include/matrix.h"
#include "data.h"

void read_init(void);
void read_turn(void);
void parse_body(const int id, char *body);
void print_map(void);
void print_bots(snakebot_t *bots, char *title);
void print_powers(void);

#endif /* IO_H */
