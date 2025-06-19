#ifndef RENDER_H
#define RENDER_H

#include <stdbool.h>
#include "state.h"

// Contexte de rendu opaque (par exemple gestion buffers graphiques)
typedef struct RenderContext RenderContext;

// Initialise le contexte de rendu avec largeur/hauteur en caractères
RenderContext* render_init(int width_chars, int height_chars);

// Libère le contexte de rendu
void render_free(RenderContext* ctx);

// Efface l'écran (buffer de texte)
void render_clear(RenderContext* ctx);

// Dessine une chaîne de caractères à (x,y) caractères
void render_draw_text(RenderContext* ctx, int x, int y, const char* text);

// Affiche le curseur à (x,y)
void render_draw_cursor(RenderContext* ctx, int x, int y, bool visible);

// Rafraîchit l'affichage (swap buffers, flush)
void render_refresh(RenderContext* ctx);

// Dessine l’état complet (texte + curseur) à l’écran
void render_draw_state(RenderContext* ctx, const State* state);

#endif // RENDER_H
