#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "ast.h"
#include <stdbool.h>

typedef struct {
    Token* tokens;
    int token_count;
    int current;      // index dans tokens
    ASTNode* root;    // racine AST produite par le parseur
} Parser;

// Crée un parseur et lance le parsing (renvoie Parser avec root)
Parser parser_create(Token* tokens, int count);

// Fonctions internes si besoin (exemple)
ASTNode* parse_expression(Parser* parser);

#endif
