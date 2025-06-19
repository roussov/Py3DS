#ifndef EDITOR_H
#define EDITOR_H

#include <stddef.h>

#define EDITOR_MAX_LINES 1024
#define EDITOR_MAX_LINE_LENGTH 256

typedef struct {
    char lines[EDITOR_MAX_LINES][EDITOR_MAX_LINE_LENGTH];
    size_t line_count;

    size_t cursor_x;  // Position horizontale (colonne)
    size_t cursor_y;  // Position verticale (ligne)
} Editor;

// Initialise l'éditeur (vide)
void editor_init(Editor* editor);

// Insère un caractère à la position du curseur
void editor_insert_char(Editor* editor, char c);

// Supprime le caractère avant le curseur (Backspace)
void editor_delete_char(Editor* editor);

// Déplace le curseur (dx horizontal, dy vertical)
void editor_move_cursor(Editor* editor, int dx, int dy);

// Retourne la ligne courante (const)
const char* editor_get_current_line(const Editor* editor);

#endif
