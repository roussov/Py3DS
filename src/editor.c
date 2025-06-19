#include "editor.h"
#include <string.h>

void editor_init(Editor* editor) {
    editor->line_count = 1;
    editor->lines[0][0] = '\0';
    editor->cursor_x = 0;
    editor->cursor_y = 0;
}

void editor_insert_char(Editor* editor, char c) {
    if (editor->cursor_y >= editor->line_count) return;
    char* line = editor->lines[editor->cursor_y];
    size_t len = strlen(line);
    if (len + 1 >= EDITOR_MAX_LINE_LENGTH) return; // limite

    // Décale le texte à droite du curseur d'1
    for (size_t i = len; i >= editor->cursor_x && i < EDITOR_MAX_LINE_LENGTH - 1; --i) {
        line[i+1] = line[i];
        if (i == 0) break; // éviter underflow size_t
    }

    line[editor->cursor_x] = c;
    editor->cursor_x++;
    line[len+1] = '\0';

    // Ajuste la ligne si besoin
}

void editor_delete_char(Editor* editor) {
    if (editor->cursor_y >= editor->line_count) return;
    if (editor->cursor_x == 0) {
        // TODO: fusion de lignes ou rien si première ligne
        return;
    }
    char* line = editor->lines[editor->cursor_y];
    size_t len = strlen(line);

    for (size_t i = editor->cursor_x -1; i < len; ++i) {
        line[i] = line[i+1];
    }
    editor->cursor_x--;
}

void editor_move_cursor(Editor* editor, int dx, int dy) {
    int new_y = (int)editor->cursor_y + dy;
    if (new_y < 0) new_y = 0;
    if (new_y >= (int)editor->line_count) new_y = (int)editor->line_count - 1;

    int new_x = (int)editor->cursor_x + dx;
    size_t line_len = strlen(editor->lines[new_y]);
    if (new_x < 0) new_x = 0;
    if (new_x > (int)line_len) new_x = (int)line_len;

    editor->cursor_x = (size_t)new_x;
    editor->cursor_y = (size_t)new_y;
}

const char* editor_get_current_line(const Editor* editor) {
    if (editor->cursor_y >= editor->line_count) return NULL;
    return editor->lines[editor->cursor_y];
}
