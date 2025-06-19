#include "buffer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void buffer_init(Buffer *buf) {
    buf->line_count = 1;
    memset(buf->lines, 0, sizeof(buf->lines));
}

const char *buffer_get_line(Buffer *buf, int line) {
    if (line < 0 || line >= buf->line_count) return "";
    return buf->lines[line];
}

int buffer_line_count(Buffer *buf) {
    return buf->line_count;
}

bool buffer_insert_char(Buffer *buf, int line, int col, char ch) {
    if (line < 0 || line >= MAX_LINES) return false;
    if (col < 0 || col >= MAX_LINE_LEN - 1) return false;

    char *str = buf->lines[line];
    int len = strlen(str);
    if (len >= MAX_LINE_LEN - 2) return false;

    // Décale à droite
    for (int i = len; i >= col; --i) {
        str[i + 1] = str[i];
    }
    str[col] = ch;
    return true;
}

bool buffer_delete_char(Buffer *buf, int line, int col) {
    if (line < 0 || line >= MAX_LINES) return false;

    char *str = buf->lines[line];
    int len = strlen(str);
    if (col < 0 || col >= len) return false;

    // Décale à gauche
    for (int i = col; i < len; ++i) {
        str[i] = str[i + 1];
    }
    return true;
}

bool buffer_delete_line(Buffer *buf, int line) {
    if (line < 0 || line >= buf->line_count) return false;
    for (int i = line; i < buf->line_count - 1; ++i) {
        strcpy(buf->lines[i], buf->lines[i + 1]);
    }
    memset(buf->lines[buf->line_count - 1], 0, MAX_LINE_LEN);
    buf->line_count--;
    return true;
}

bool buffer_insert_line(Buffer *buf, int index) {
    if (buf->line_count >= MAX_LINES) return false;
    if (index < 0 || index > buf->line_count) return false;

    for (int i = buf->line_count; i > index; --i) {
        strcpy(buf->lines[i], buf->lines[i - 1]);
    }
    memset(buf->lines[index], 0, MAX_LINE_LEN);
    buf->line_count++;
    return true;
}

bool buffer_clear(Buffer *buf) {
    buf->line_count = 1;
    memset(buf->lines, 0, sizeof(buf->lines));
    return true;
}

// Rassemble tout le contenu du buffer dans un malloc (REPL)
char *buffer_all_text(Buffer *buf) {
    size_t total = 0;
    for (int i = 0; i < buf->line_count; ++i) {
        total += strlen(buf->lines[i]) + 1;
    }

    char *text = malloc(total + 1);
    if (!text) return NULL;

    text[0] = '\0';
    for (int i = 0; i < buf->line_count; ++i) {
        strcat(text, buf->lines[i]);
        strcat(text, "\n");
    }

    return text;
}
