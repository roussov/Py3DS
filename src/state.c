#include "state.h"
#include <string.h>

void state_init(State* state) {
    state->line_count = 1;
    memset(state->lines[0], 0, MAX_LINE_LENGTH);
    state->cursor_x = 0;
    state->cursor_y = 0;
    state->insert_mode = true;
    state->has_selection = false;
    state->sel_start_x = state->sel_start_y = 0;
    state->sel_end_x = state->sel_end_y = 0;
    state->scroll_offset = 0;
}

void state_free(State* state) {
    // Rien à faire ici car pas d’allocation dynamique
}

void state_insert_char(State* state, char c) {
    if (state->cursor_y >= state->line_count) return;
    char* line = state->lines[state->cursor_y];
    int len = strlen(line);
    if (len >= MAX_LINE_LENGTH - 1) return; // ligne pleine

    if (state->insert_mode) {
        // Décale caractères à droite
        for (int i = len; i >= state->cursor_x; --i) {
            line[i+1] = line[i];
        }
        line[state->cursor_x] = c;
    } else {
        // Remplacement
        line[state->cursor_x] = c;
    }
    state->cursor_x++;
}

void state_delete_char(State* state) {
    if (state->cursor_y >= state->line_count) return;
    char* line = state->lines[state->cursor_y];
    if (state->cursor_x == 0 && state->cursor_y == 0) return;

    if (state->cursor_x > 0) {
        int len = strlen(line);
        for (int i = state->cursor_x - 1; i < len; ++i) {
            line[i] = line[i+1];
        }
        state->cursor_x--;
    } else {
        // TODO: gérer fusion avec ligne précédente si besoin
    }
}

void state_move_cursor(State* state, int dx, int dy) {
    int new_y = state->cursor_y + dy;
    if (new_y < 0) new_y = 0;
    if (new_y >= state->line_count) new_y = state->line_count -1;
    state->cursor_y = new_y;

    int line_len = strlen(state->lines[state->cursor_y]);
    int new_x = state->cursor_x + dx;
    if (new_x < 0) new_x = 0;
    if (new_x > line_len) new_x = line_len;
    state->cursor_x = new_x;
}
