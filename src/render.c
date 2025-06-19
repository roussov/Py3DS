#include "render.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Exemple simple avec un buffer texte en mémoire (simulation console)

struct RenderContext {
    int width;
    int height;
    char** buffer;      // tableau 2D de caractères [height][width]
};

RenderContext* render_init(int width_chars, int height_chars) {
    RenderContext* ctx = malloc(sizeof(RenderContext));
    if (!ctx) return NULL;

    ctx->width = width_chars;
    ctx->height = height_chars;

    ctx->buffer = malloc(sizeof(char*) * height_chars);
    if (!ctx->buffer) {
        free(ctx);
        return NULL;
    }
    for (int i = 0; i < height_chars; ++i) {
        ctx->buffer[i] = malloc(sizeof(char) * (width_chars + 1));
        if (!ctx->buffer[i]) {
            // free previous lines
            for (int j = 0; j < i; ++j) free(ctx->buffer[j]);
            free(ctx->buffer);
            free(ctx);
            return NULL;
        }
        memset(ctx->buffer[i], ' ', width_chars);
        ctx->buffer[i][width_chars] = '\0';
    }
    return ctx;
}

void render_free(RenderContext* ctx) {
    if (!ctx) return;
    for (int i = 0; i < ctx->height; ++i) {
        free(ctx->buffer[i]);
    }
    free(ctx->buffer);
    free(ctx);
}

void render_clear(RenderContext* ctx) {
    if (!ctx) return;
    for (int i = 0; i < ctx->height; ++i) {
        memset(ctx->buffer[i], ' ', ctx->width);
    }
}

void render_draw_text(RenderContext* ctx, int x, int y, const char* text) {
    if (!ctx) return;
    if (y < 0 || y >= ctx->height) return;
    int len = strlen(text);
    if (x < 0) x = 0;
    if (x + len > ctx->width) len = ctx->width - x;
    if (len <= 0) return;

    memcpy(&ctx->buffer[y][x], text, len);
}

void render_draw_cursor(RenderContext* ctx, int x, int y, bool visible) {
    if (!ctx) return;
    if (!visible) return;
    if (x < 0 || x >= ctx->width || y < 0 || y >= ctx->height) return;

    // Ici on inverse le caractère pour marquer le curseur (exemple simple)
    char c = ctx->buffer[y][x];
    if (c == ' ') c = '_';
    else c = (c >= 'a' && c <= 'z') ? c - 32 : c;  // Majuscule comme surbrillance

    ctx->buffer[y][x] = c;
}

void render_refresh(RenderContext* ctx) {
    if (!ctx) return;

    // Exemple console : efface l’écran puis affiche le buffer
    printf("\033[H\033[J");  // ANSI clear screen + cursor home
    for (int i = 0; i < ctx->height; ++i) {
        printf("%s\n", ctx->buffer[i]);
    }
    fflush(stdout);
}

void render_draw_state(RenderContext* ctx, const State* state) {
    if (!ctx || !state) return;

    render_clear(ctx);
    for (int i = 0; i < state->line_count && i < ctx->height; ++i) {
        render_draw_text(ctx, 0, i, state->lines[i]);
    }

    // Affiche curseur clignotant visible à la position du curseur
    render_draw_cursor(ctx, state->cursor_x, state->cursor_y, true);

    render_refresh(ctx);
}
