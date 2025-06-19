#include "lexer.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

static char peek_char(Lexer* lexer) {
    return lexer->src[lexer->pos];
}

static char advance(Lexer* lexer) {
    char c = lexer->src[lexer->pos];
    if (c != '\0') {
        lexer->pos++;
        if (c == '\n') {
            lexer->line++;
        }
    }
    return c;
}

static void skip_whitespace(Lexer* lexer) {
    while (1) {
        char c = peek_char(lexer);
        if (c == ' ' || c == '\t' || c == '\r') {
            advance(lexer);
        } else {
            break;
        }
    }
}

static Token make_token(Lexer* lexer, TokenType type, const char* start, size_t length) {
    Token token;
    token.type = type;
    token.length = length;
    token.line = lexer->line;

    token.lexeme = (char*)malloc(length + 1);
    if (token.lexeme) {
        memcpy(token.lexeme, start, length);
        token.lexeme[length] = '\0';
    }
    else {
        token.lexeme = NULL; // en cas d’échec malloc
    }
    return token;
}

void lexer_init(Lexer* lexer, const char* source) {
    lexer->src = source;
    lexer->pos = 0;
    lexer->line = 1;
}

Token lexer_next_token(Lexer* lexer) {
    skip_whitespace(lexer);
    size_t start_pos = lexer->pos;
    char c = peek_char(lexer);

    if (c == '\0') {
        return make_token(lexer, TOKEN_EOF, "", 0);
    }

    // Identificateur ou mot-clé (lettres et _)
    if (isalpha(c) || c == '_') {
        advance(lexer);
        while (isalnum(peek_char(lexer)) || peek_char(lexer) == '_') {
            advance(lexer);
        }
        size_t length = lexer->pos - start_pos;
        return make_token(lexer, TOKEN_IDENT, &lexer->src[start_pos], length);
    }

    // Nombre (int ou float)
    if (isdigit(c)) {
        bool is_float = false;
        advance(lexer);
        while (isdigit(peek_char(lexer))) {
            advance(lexer);
        }
        if (peek_char(lexer) == '.') {
            is_float = true;
            advance(lexer);
            while (isdigit(peek_char(lexer))) {
                advance(lexer);
            }
        }
        size_t length = lexer->pos - start_pos;
        return make_token(lexer, is_float ? TOKEN_FLOAT_LITERAL : TOKEN_INT_LITERAL,
                          &lexer->src[start_pos], length);
    }

    // Opérateurs et ponctuation simples
    advance(lexer);
    switch (c) {
        case '+': return make_token(lexer, TOKEN_PLUS, &lexer->src[start_pos], 1);
        case '-': return make_token(lexer, TOKEN_MINUS, &lexer->src[start_pos], 1);
        case '*': return make_token(lexer, TOKEN_MUL, &lexer->src[start_pos], 1);
        case '/': return make_token(lexer, TOKEN_DIV, &lexer->src[start_pos], 1);
        case '(': return make_token(lexer, TOKEN_LPAREN, &lexer->src[start_pos], 1);
        case ')': return make_token(lexer, TOKEN_RPAREN, &lexer->src[start_pos], 1);
        case '=': return make_token(lexer, TOKEN_ASSIGN, &lexer->src[start_pos], 1);
        case '\n': return make_token(lexer, TOKEN_NEWLINE, &lexer->src[start_pos], 1);
        default: return make_token(lexer, TOKEN_UNKNOWN, &lexer->src[start_pos], 1);
    }
}

void lexer_free_token(Token* token) {
    if (token && token->lexeme) {
        free(token->lexeme);
        token->lexeme = NULL;
    }
}
