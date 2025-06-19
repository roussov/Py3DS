#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static Token peek(Parser* parser) {
    if (parser->current < parser->token_count) {
        return parser->tokens[parser->current];
    }
    Token eof_token = {TOKEN_EOF, NULL, 0};
    return eof_token;
}

static Token advance(Parser* parser) {
    if (parser->current < parser->token_count) {
        return parser->tokens[parser->current++];
    }
    Token eof_token = {TOKEN_EOF, NULL, 0};
    return eof_token;
}

static bool match(Parser* parser, TokenType type) {
    if (peek(parser).type == type) {
        advance(parser);
        return true;
    }
    return false;
}

// Forward declarations
static ASTNode* parse_expression(Parser* parser);
static ASTNode* parse_primary(Parser* parser);

static ASTNode* parse_primary(Parser* parser) {
    Token token = peek(parser);
    if (match(parser, TOKEN_NUMBER)) {
        return ast_new_literal_int(atoi(token.lexeme));
    }
    if (match(parser, TOKEN_FLOAT_LITERAL)) {
        return ast_new_literal_float(atof(token.lexeme));
    }
    if (match(parser, TOKEN_IDENT)) {
        return ast_new_variable(token.lexeme);
    }
    if (match(parser, TOKEN_LPAREN)) {
        ASTNode* expr = parse_expression(parser);
        if (!match(parser, TOKEN_RPAREN)) {
            fprintf(stderr, "Erreur : parenthèse fermante attendue\n");
        }
        return expr;
    }

    fprintf(stderr, "Erreur : token inattendu '%s'\n", token.lexeme ? token.lexeme : "EOF");
    return NULL;
}

static ASTNode* parse_factor(Parser* parser) {
    ASTNode* node = parse_primary(parser);

    while (true) {
        Token t = peek(parser);
        if (t.type == TOKEN_STAR || t.type == TOKEN_SLASH) {
            TokenType op = t.type;
            advance(parser);
            ASTNode* right = parse_primary(parser);
            node = ast_new_binary(node, op, right);
        } else {
            break;
        }
    }
    return node;
}

static ASTNode* parse_term(Parser* parser) {
    ASTNode* node = parse_factor(parser);

    while (true) {
        Token t = peek(parser);
        if (t.type == TOKEN_PLUS || t.type == TOKEN_MINUS) {
            TokenType op = t.type;
            advance(parser);
            ASTNode* right = parse_factor(parser);
            node = ast_new_binary(node, op, right);
        } else {
            break;
        }
    }
    return node;
}

static ASTNode* parse_expression(Parser* parser) {
    return parse_term(parser);
}

Parser parser_create(Token* tokens, int count) {
    Parser parser;
    parser.tokens = tokens;
    parser.token_count = count;
    parser.current = 0;
    parser.root = parse_expression(&parser);
    return parser;
}
