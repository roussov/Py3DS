#ifndef STATE_H
#define STATE_H

#include <stdbool.h>

// Taille maximale d'une ligne de texte
#define MAX_LINE_LENGTH 256

typedef struct {
    char lines[1024][MAX_LINE_LENGTH];  // 1024 lignes max, chacune max 256 chars
    int line_count;                      // Nombre actuel de lignes utilisées

    int cursor_x;                       // Position curseur colonne (dans la ligne)
    int cursor_y;                       // Position curseur ligne

    bool insert_mode;                   // true = insertion, false = remplacement

    // Sélection texte (coordonnées)
    bool has_selection;
    int sel_start_x;
    int sel_start_y;
    int sel_end_x;
    int sel_end_y;

    int scroll_offset;                  // Scroll vertical

} State;

// Initialise un nouvel état avec une ligne vide
void state_init(State* state);

// Libère les ressources si besoin (ici non dynamique, donc vide)
void state_free(State* state);

// Insère un caractère à la position du curseur, décalage selon mode insert
void state_insert_char(State* state, char c);

// Supprime un caractère avant la position curseur (backspace)
void state_delete_char(State* state);

// Déplace le curseur de dx, dy (avec bornes)
void state_move_cursor(State* state, int dx, int dy);

#endif // STATE_H
