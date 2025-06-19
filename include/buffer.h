#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>
#include <stdbool.h>

#define MAX_LINES    256
#define MAX_LINE_LEN 128

typedef struct {
    char lines[MAX_LINES][MAX_LINE_LEN];
    int line_count;
} Buffer;

// Initialisation
void buffer_init(Buffer *buf);

// Accès
const char *buffer_get_line(Buffer *buf, int line);
int buffer_line_count(Buffer *buf);

// Édition
bool buffer_insert_char(Buffer *buf, int line, int col, char ch);
bool buffer_delete_char(Buffer *buf, int line, int col);
bool buffer_delete_line(Buffer *buf, int line);
bool buffer_insert_line(Buffer *buf, int index);
bool buffer_clear(Buffer *buf);

// Utilitaire
char *buffer_all_text(Buffer *buf); // malloc le contenu complet

#endif
