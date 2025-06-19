#include <3ds.h>
#include <stdio.h>
#include "state.h"
#include "kboard.h"
#include "render.h"

int main() {
    // Initialisation 3DS
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    // Initialiser état, clavier, rendu
    State state;
    state_init(&state);

    KBoard keyboard;
    kboard_init(&keyboard);
    kboard_show(&keyboard, true);

    RenderContext* render_ctx = render_init(40, 30); // par exemple 40x30 caractères
    if (!render_ctx) {
        printf("Erreur init rendu\n");
        gfxExit();
        return 1;
    }

    // Boucle principale
    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();

        if (kDown & KEY_START) {
            break;  // Quitter si START
        }

        // Gérer clavier virtuel
        char c = kboard_process_input(&keyboard);
        if (c) {
            if (c == '\b') {
                state_delete_char(&state);
            } else if (c == '\n') {
                // TODO : gérer saut ligne (non fait ici)
            } else {
                state_insert_char(&state, c);
            }
        }

        // (Optionnel) gérer mouvements curseur avec boutons D-Pad
        if (kDown & KEY_UP) state_move_cursor(&state, 0, -1);
        if (kDown & KEY_DOWN) state_move_cursor(&state, 0, 1);
        if (kDown & KEY_LEFT) state_move_cursor(&state, -1, 0);
        if (kDown & KEY_RIGHT) state_move_cursor(&state, 1, 0);

        // Rendu
        render_draw_state(render_ctx, &state);

        // Afficher clavier virtuel dans la console
        kboard_draw(&keyboard);

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    // Libération
    render_free(render_ctx);
    gfxExit();
    return 0;
}
