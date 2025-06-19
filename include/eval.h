#ifndef AST_H
#define AST_H

#include <stddef.h>

typedef enum {
    AST_INT_LITERAL,
    AST_FLOAT_LITERAL,
    AST_IDENT,
    AST_BINARY_OP,
    // Ajoute d’autres types AST ici (ex: assign, call, etc.)
} ASTNodeType;

typedef struct ASTNode ASTNode;

typedef struct {
    ASTNode* left;
    ASTNode* right;
    char* op;  // opérateur sous forme de chaîne, ex: "+", "-", "*"
} ASTBinary;

struct ASTNode {
    ASTNodeType type;

    union {
        int int_value;          // pour AST_INT_LITERAL
        double float_value;     // pour AST_FLOAT_LITERAL
        char* ident_name;       // pour AST_IDENT
        ASTBinary binary;       // pour AST_BINARY_OP
        // Ajoute d’autres structures si besoin
    };
};

#endif // AST_H
