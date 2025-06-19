#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>

typedef enum {
    TOKEN_EOF,
    TOKEN_ERROR,

    // Littéraux
    TOKEN_NUMBER,          // int
    TOKEN_FLOAT_LITERAL,   // float
    TOKEN_STRING,          // "abc"
    TOKEN_IDENT,           // variable nommée

    // Opérateurs
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,
    TOKEN_EQUAL,
    TOKEN_EQUAL_EQUAL,
    TOKEN_BANG_EQUAL,
    TOKEN_LESS,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER,
    TOKEN_GREATER_EQUAL,

    // Délimiteurs
    TOKEN_LPAREN,   // (
    TOKEN_RPAREN,   // )
    TOKEN_LBRACE,   // {
    TOKEN_RBRACE,   // }
    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_COLON,
    TOKEN_SEMICOLON,

    // Mots-clés (optionnels selon ton implémentation)
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_DEF,
    TOKEN_RETURN,
    TOKEN_PRINT,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NONE,

} TokenType;

typedef struct {
    TokenType type;
    char* lexeme;
    int line;
} Token;

const char* token_type_to_string(TokenType type);
void print_token(Token token);

#endif
