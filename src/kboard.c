#include "kboard.h"
#include <string.h>   // pour memset
#include <stdio.h>    // pour debug (printf)
#include <3ds.h>      // ou ta lib 3DS

static const char default_keys[KBOARD_ROWS][KBOARD_COLS] = {
    {'A','B','C','D','E','F','G','H','I','J'},
    {'K','L','M','N','O','P','Q','R','S','T'},
    {'U','V','W','X','Y','Z','_','-','.',','}
};

void kboard_init(KBoard* kb) {
    memcpy(kb->keys, default_keys, sizeof(default_keys));
    kb->cursor_row = 0;
    kb->cursor_col = 0;
    kb->visible = false;
}

void kboard_show(KBoard* kb, bool show) {
    kb->visible = show;
}

void kboard_draw(const KBoard* kb) {
    if (!kb->visible) return;

    // Exemple console (adapter selon SDL, 3DS gfx etc)
    for (int r=0; r<KBOARD_ROWS; ++r) {
        for (int c=0; c<KBOARD_COLS; ++c) {
            if (r == kb->cursor_row && c == kb->cursor_col)
                printf("[%c] ", kb->keys[r][c]);
            else
                printf(" %c  ", kb->keys[r][c]);
        }
        printf("\n");
    }
}

char kboard_process_input(KBoard* kb) {
    if (!kb->visible) return 0;

    hidScanInput();
    u32 kDown = hidKeysDown();

    if (kDown & KEY_UP) {
        if (kb->cursor_row > 0) kb->cursor_row--;
    }
    else if (kDown & KEY_DOWN) {
        if (kb->cursor_row < KBOARD_ROWS -1) kb->cursor_row++;
    }
    else if (kDown & KEY_LEFT) {
        if (kb->cursor_col > 0) kb->cursor_col--;
    }
    else if (kDown & KEY_RIGHT) {
        if (kb->cursor_col < KBOARD_COLS -1) kb->cursor_col++;
    }
    else if (kDown & KEY_A) {
        return kb->keys[kb->cursor_row][kb->cursor_col];
    }
    else if (kDown & KEY_B) {
        return '\b';  // Backspace
    }

    // Pour toucher tactile (exemple)
    // if (touchpad_pressed) {
    //    calculer position,
    //    modifier cursor_row/cursor_col,
    //    return caractère correspondant
    // }

    return 0;
}
