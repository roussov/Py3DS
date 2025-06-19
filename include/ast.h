#ifndef AST_H
#define AST_H

#include "token.h"

typedef enum {
    LIT_INT,
    LIT_FLOAT,
    LIT_STRING
} LiteralType;

typedef struct {
    LiteralType type;
    union {
        int as_int;
        float as_float;
        char* as_string;
    };
} LiteralValue;

typedef enum {
    AST_LITERAL,
    AST_VARIABLE,
    AST_BINARY,
    AST_UNARY,
    AST_ASSIGN,
    AST_CALL,
    AST_BLOCK,
    AST_IF,
    AST_EXPR_STMT
} ASTNodeType;

typedef struct ASTNode ASTNode;

struct ASTNode {
    ASTNodeType type;

    union {
        struct {
            LiteralValue value;
        } literal;

        struct {
            char* name;
        } variable;

        struct {
            TokenType op;
            ASTNode* operand;
        } unary;

        struct {
            ASTNode* left;
            TokenType op;
            ASTNode* right;
        } binary;

        struct {
            char* name;
            ASTNode* value;
        } assign;

        struct {
            char* function_name;
            ASTNode** args;
            int arg_count;
        } call;

        struct {
            ASTNode** statements;
            int count;
        } block;

        struct {
            ASTNode* condition;
            ASTNode* then_branch;
            ASTNode* else_branch; // optional
        } if_stmt;

        struct {
            ASTNode* expression;
        } expr_stmt;
    };
};

// Constructeurs
ASTNode* ast_new_literal_int(int value);
ASTNode* ast_new_literal_float(float value);
ASTNode* ast_new_literal_string(const char* str);
ASTNode* ast_new_variable(const char* name);
ASTNode* ast_new_unary(TokenType op, ASTNode* operand);
ASTNode* ast_new_binary(ASTNode* left, TokenType op, ASTNode* right);
ASTNode* ast_new_assign(const char* name, ASTNode* value);
ASTNode* ast_new_call(const char* name, ASTNode** args, int arg_count);
ASTNode* ast_new_expr_stmt(ASTNode* expr);
ASTNode* ast_new_if(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch);
ASTNode* ast_new_block(ASTNode** statements, int count);

// Libération
void ast_free(ASTNode* node);

#endif
