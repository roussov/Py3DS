#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

typedef enum {
    TOKEN_EOF,
    TOKEN_INT_LITERAL,
    TOKEN_FLOAT_LITERAL,
    TOKEN_IDENT,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_ASSIGN,
    TOKEN_NEWLINE,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char* lexeme;       // chaîne textuelle du token (allouée dynamiquement)
    size_t length;      // longueur lexeme
    int line;           // numéro de ligne (pour erreurs)
} Token;

typedef struct {
    const char* src;    // source input
    size_t pos;         // position courante dans src
    int line;           // ligne courante
} Lexer;

// Initialise le lexer sur la source donnée
void lexer_init(Lexer* lexer, const char* source);

// Récupère le token suivant (le lexer alloue lexeme qu’il faut libérer)
// Retourne un token, à libérer avec lexer_free_token()
Token lexer_next_token(Lexer* lexer);

// Libère la mémoire associée au token (notamment lexeme)
void lexer_free_token(Token* token);

#endif
