#ifndef KBOARD_H
#define KBOARD_H

#include <stdbool.h>

// Taille du clavier (exemple 3 lignes x 10 touches)
#define KBOARD_ROWS 3
#define KBOARD_COLS 10

typedef struct {
    char keys[KBOARD_ROWS][KBOARD_COLS];  // caractères affichés sur le clavier
    int cursor_row;                        // sélection actuelle
    int cursor_col;
    bool visible;                         // clavier visible ou non
} KBoard;

// Initialise le clavier virtuel (définit touches, position curseur, visible=false)
void kboard_init(KBoard* kb);

// Affiche/Cache le clavier virtuel
void kboard_show(KBoard* kb, bool show);

// Dessine le clavier à l’écran (adapté à ta plateforme)
void kboard_draw(const KBoard* kb);

// Gère l'entrée utilisateur (boutons + tactile), retourne le caractère appuyé ou 0 sinon
char kboard_process_input(KBoard* kb);

#endif // KBOARD_H
