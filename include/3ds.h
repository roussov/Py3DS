#ifndef _3DS_H_
#define _3DS_H_

// Inclure le header principal de libctru 3DS
#include <3ds.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

// Définition des résolutions écrans 3DS
#define SCREEN_WIDTH_TOP     400
#define SCREEN_HEIGHT_TOP    240
#define SCREEN_WIDTH_BOTTOM  320
#define SCREEN_HEIGHT_BOTTOM 240

// Macro pour vérifier un Result et afficher message en cas d'erreur
#define CHECK_RETVAL(res, msg) \
    do { \
        if (R_FAILED(res)) { \
            printf("Erreur: %s (0x%08X)\n", msg, (unsigned int)(res)); \
            return res; \
        } \
    } while (0)

// Macro de boucle principale
#define MAIN_LOOP while (aptMainLoop())

// Initialisation simplifiée des services 3DS
static inline Result init_3ds_system(void) {
    Result res;

    res = gfxInitDefault();
    if (R_FAILED(res)) return res;

    res = hidInit(NULL);
    if (R_FAILED(res)) {
        gfxExit();
        return res;
    }

    res = srvInit();
    if (R_FAILED(res)) {
        hidExit();
        gfxExit();
        return res;
    }

    consoleInit(GFX_TOP, NULL);

    return 0;
}

// Nettoyage des services 3DS
static inline void exit_3ds_system(void) {
    consoleExit(NULL);
    srvExit();
    hidExit();
    gfxExit();
}

// Affichage formaté sur la console
static inline void print_fmt(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

// Effacer l'écran console (ANSI escape)
static inline void console_clear(void) {
    printf("\x1b[2J"); // clear screen
    printf("\x1b[H");  // cursor home (top-left)
    fflush(stdout);
}

// Lecture des touches (renvoie état des touches maintenues)
static inline u32 get_keys_held(void) {
    hidScanInput();
    return hidKeysHeld();
}

// Lecture des touches (renvoie état des touches pressées)
static inline u32 get_keys_down(void) {
    hidScanInput();
    return hidKeysDown();
}

// Lecture des touches (renvoie état des touches relâchées)
static inline u32 get_keys_up(void) {
    hidScanInput();
    return hidKeysUp();
}

// Lecture tactile, retourne true si touché et remplit pos
static inline bool get_touch_pos(touchPosition* pos) {
    hidScanInput();
    if (hidKeysDown() & KEY_TOUCH) {
        hidTouchRead(pos);
        return true;
    }
    return false;
}

// Vibration 3DS simple (durée en ms)
static inline void rumble_3ds(int duration_ms) {
    static int rumble_timer = 0;
    if (duration_ms > 0) rumble_timer = duration_ms;

    if (rumble_timer > 0) {
        hidVibrationStart();
        rumble_timer -= 16; // approx 16 ms/frame (60fps)
        if (rumble_timer <= 0) hidVibrationStop();
    }
}

// Pause/sleep (ms)
static inline void delay_ms(u64 ms) {
    svcSleepThread(ms * 1000000ULL);
}

// Exemple pour dessiner rectangle ASCII dans console
static inline void draw_rect(int x, int y, int w, int h) {
    for (int i = 0; i < h; i++) {
        printf("\x1b[%d;%dH", y + i + 1, x + 1);
        if (i == 0 || i == h - 1) {
            for (int j = 0; j < w; j++) printf("-");
        } else {
            printf("|");
            for (int j = 0; j < w - 2; j++) printf(" ");
            printf("|");
        }
    }
    fflush(stdout);
}

#endif // _3DS_H_
