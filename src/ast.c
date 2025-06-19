#include "ast.h"
#include <stdlib.h>
#include <string.h>

static ASTNode* alloc(ASTNodeType type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = type;
    return node;
}

ASTNode* ast_new_literal_int(int value) {
    ASTNode* node = alloc(AST_LITERAL);
    node->literal.value.type = LIT_INT;
    node->literal.value.as_int = value;
    return node;
}

ASTNode* ast_new_literal_float(float value) {
    ASTNode* node = alloc(AST_LITERAL);
    node->literal.value.type = LIT_FLOAT;
    node->literal.value.as_float = value;
    return node;
}

ASTNode* ast_new_literal_string(const char* str) {
    ASTNode* node = alloc(AST_LITERAL);
    node->literal.value.type = LIT_STRING;
    node->literal.value.as_string = strdup(str);
    return node;
}

ASTNode* ast_new_variable(const char* name) {
    ASTNode* node = alloc(AST_VARIABLE);
    node->variable.name = strdup(name);
    return node;
}

ASTNode* ast_new_unary(TokenType op, ASTNode* operand) {
    ASTNode* node = alloc(AST_UNARY);
    node->unary.op = op;
    node->unary.operand = operand;
    return node;
}

ASTNode* ast_new_binary(ASTNode* left, TokenType op, ASTNode* right) {
    ASTNode* node = alloc(AST_BINARY);
    node->binary.left = left;
    node->binary.op = op;
    node->binary.right = right;
    return node;
}

ASTNode* ast_new_assign(const char* name, ASTNode* value) {
    ASTNode* node = alloc(AST_ASSIGN);
    node->assign.name = strdup(name);
    node->assign.value = value;
    return node;
}

ASTNode* ast_new_call(const char* name, ASTNode** args, int arg_count) {
    ASTNode* node = alloc(AST_CALL);
    node->call.function_name = strdup(name);
    node->call.args = malloc(sizeof(ASTNode*) * arg_count);
    for (int i = 0; i < arg_count; ++i) {
        node->call.args[i] = args[i];
    }
    node->call.arg_count = arg_count;
    return node;
}

ASTNode* ast_new_expr_stmt(ASTNode* expr) {
    ASTNode* node = alloc(AST_EXPR_STMT);
    node->expr_stmt.expression = expr;
    return node;
}

ASTNode* ast_new_if(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch) {
    ASTNode* node = alloc(AST_IF);
    node->if_stmt.condition = condition;
    node->if_stmt.then_branch = then_branch;
    node->if_stmt.else_branch = else_branch;
    return node;
}

ASTNode* ast_new_block(ASTNode** statements, int count) {
    ASTNode* node = alloc(AST_BLOCK);
    node->block.statements = malloc(sizeof(ASTNode*) * count);
    for (int i = 0; i < count; ++i) {
        node->block.statements[i] = statements[i];
    }
    node->block.count = count;
    return node;
}

void ast_free(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case AST_LITERAL:
            if (node->literal.value.type == LIT_STRING)
                free(node->literal.value.as_string);
            break;

        case AST_VARIABLE:
            free(node->variable.name);
            break;

        case AST_UNARY:
            ast_free(node->unary.operand);
            break;

        case AST_BINARY:
            ast_free(node->binary.left);
            ast_free(node->binary.right);
            break;

        case AST_ASSIGN:
            free(node->assign.name);
            ast_free(node->assign.value);
            break;

        case AST_CALL:
            free(node->call.function_name);
            for (int i = 0; i < node->call.arg_count; ++i)
                ast_free(node->call.args[i]);
            free(node->call.args);
            break;

        case AST_EXPR_STMT:
            ast_free(node->expr_stmt.expression);
            break;

        case AST_IF:
            ast_free(node->if_stmt.condition);
            ast_free(node->if_stmt.then_branch);
            if (node->if_stmt.else_branch)
                ast_free(node->if_stmt.else_branch);
            break;

        case AST_BLOCK:
            for (int i = 0; i < node->block.count; ++i)
                ast_free(node->block.statements[i]);
            free(node->block.statements);
            break;
    }

    free(node);
}
