#include "../include/io.h"

/* 
 * #####################################################################
 * ############################## INPUT ################################
 * #####################################################################
 */ 

void read_init(void) {
    // read my_id, rows and cols
    int rows, cols;
    scanf("%d%d%d", &my_id, &cols, &rows);
    fgetc(stdin);

    // read the map
    mat_init(starting_map, rows, cols, sizeof(char));
    for (size_t y = 0; y < rows; y++) {
        char *row = (char *)calloc(cols + 1, sizeof(char));
        scanf("%[^\n]", row);
        fgetc(stdin);
        for (size_t x = 0; x < cols; x++) {
            mat_insert(starting_map, y, x, row[x]);
        }
        free(row);
    }

    // read initial bot info
    scanf("%zu", &bots_per_player);

    my_bots = (snakebot_t *)malloc(bots_per_player * sizeof(snakebot_t));
    opp_bots = (snakebot_t *)malloc(bots_per_player * sizeof(snakebot_t));

    for (size_t i = 0; i < bots_per_player; i++) {
        int my_snakebot_id;
        scanf("%d", &my_snakebot_id);
        my_bots[i].id = my_snakebot_id;
        my_bots[i].body_len = 0;
        my_bots[i].status = ALIVE;
    }

    for (size_t i = 0; i < bots_per_player; i++) {
        int opp_snakebot_id;
        scanf("%d", &opp_snakebot_id);
        opp_bots[i].id = opp_snakebot_id;
        opp_bots[i].body_len = 0;
        opp_bots[i].status = ALIVE;
    }
}

void read_turn(void) {
    scanf("%zu", &powers_size);
    powers = (point_t *)malloc(sizeof(point_t) * powers_size);

    for (size_t i = 0; i < powers_size; i++) {
        scanf("%zu%zu", &powers[i].x, &powers[i].y);
        mat_insert(map, powers[i].y, powers[i].x, 'P');
    }

    int snakebot_count;
    scanf("%d", &snakebot_count);

    for (size_t i = 0; i < snakebot_count; i++) {
        int snake_bot_id;
        char body[513] = "";
        scanf("%d%s", &snake_bot_id, body);
        parse_body(snake_bot_id, body);
    }
}

void parse_body(const int id, char *body) {
    size_t owner = 0;
    size_t index = 0;

    // check if it is my bot
    for (size_t i = 0; i < bots_per_player; i++) {
        if (my_bots[i].id == id) {
            owner = 1;
            index = i;
            break;
        } 
    }

    // check if it is my opp bot
    for (size_t i = 0; i < bots_per_player; i++) {
        if (owner)
            break;
        if (opp_bots[i].id == id) {
            index = i;
            break;
        }
    }

    // parse the body
    int parts = 1;
    for (size_t i = 0; i < strlen(body); i++) {
        if (body[i] == ':')
            parts++;
    }

    if (owner) {
        my_bots[index].body = (point_t *)malloc(parts * sizeof(point_t));
    } else {
        opp_bots[index].body = (point_t *)malloc(parts * sizeof(point_t));
    }

    char *tok = strtok(body, ":");
    int piece = 0;
    while (tok != NULL) {
        size_t pt = 0;
        for (size_t c = 0; c < strlen(tok); c++) {
            if (tok[c] == ',') {
                // save the x
                if (owner) {
                    my_bots[index].body[my_bots[index].body_len].x = pt;
                } else {
                    opp_bots[index].body[opp_bots[index].body_len].x = pt;
                }
                pt = 0;
            } else {
                pt = pt * 10 + tok[c] - '0';
            }
        }
        // save the y
        if (owner) {
            my_bots[index].body[my_bots[index].body_len].y = pt;
            point_t p = {
                my_bots[index].body[my_bots[index].body_len].x,
                my_bots[index].body[my_bots[index].body_len].y
            };
            my_bots[index].body_len++;
            mat_insert(map, p.y, p.x, 'S');
        } else {
            opp_bots[index].body[opp_bots[index].body_len].y = pt;
            point_t p = {
                opp_bots[index].body[opp_bots[index].body_len].x,
                opp_bots[index].body[opp_bots[index].body_len].y
            };
            opp_bots[index].body_len++;
            mat_insert(map, p.y, p.x, 's');
        }
        tok = strtok(NULL, ":");
        piece++;
    }
}

/* 
 * #####################################################################
 * ############################# OUTPUT ################################
 * #####################################################################
 */ 

void print_map(void) {
    for (size_t y = 0; y < mat_get_rows(map); y++) {
        for (size_t x = 0; x < mat_get_cols(map); x++) {
            fprintf(stderr, "%c", mat_get(map, y, x));
        }
        fprintf(stderr, "\n");
    }
}
void print_bots(snakebot_t *bots, char *title) {
    fprintf(stderr, "%s\n", title);

    for (size_t i = 0; i < bots_per_player; i++) {
        snakebot_t b = bots[i];

        if (b.status == ALIVE) {
            fprintf(stderr, "%d = [ ", b.id);

            for (size_t j = 0; j < b.body_len; j++) {
                fprintf(stderr, "(%zu, %zu) ", b.body[j].x, b.body[j].y);
            }
            fprintf(stderr, "]\n");
        }
    }
}

void print_powers(void) {
    fprintf(stderr, "Powers\n");

    for (size_t i = 0; i < powers_size; i++) {
        fprintf(stderr, "(%zu, %zu)\n", powers[i].x, powers[i].y);
    }
}
