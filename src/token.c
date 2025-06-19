#include "token.h"
#include <stdio.h>

const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_EOF: return "EOF";
        case TOKEN_ERROR: return "ERROR";
        case TOKEN_NUMBER: return "NUMBER";
        case TOKEN_FLOAT_LITERAL: return "FLOAT";
        case TOKEN_STRING: return "STRING";
        case TOKEN_IDENT: return "IDENT";

        case TOKEN_PLUS: return "+";
        case TOKEN_MINUS: return "-";
        case TOKEN_STAR: return "*";
        case TOKEN_SLASH: return "/";
        case TOKEN_PERCENT: return "%";

        case TOKEN_EQUAL: return "=";
        case TOKEN_EQUAL_EQUAL: return "==";
        case TOKEN_BANG_EQUAL: return "!=";
        case TOKEN_LESS: return "<";
        case TOKEN_LESS_EQUAL: return "<=";
        case TOKEN_GREATER: return ">";
        case TOKEN_GREATER_EQUAL: return ">=";

        case TOKEN_LPAREN: return "(";
        case TOKEN_RPAREN: return ")";
        case TOKEN_LBRACE: return "{";
        case TOKEN_RBRACE: return "}";
        case TOKEN_COMMA: return ",";
        case TOKEN_DOT: return ".";
        case TOKEN_COLON: return ":";
        case TOKEN_SEMICOLON: return ";";

        case TOKEN_IF: return "if";
        case TOKEN_ELSE: return "else";
        case TOKEN_WHILE: return "while";
        case TOKEN_FOR: return "for";
        case TOKEN_DEF: return "def";
        case TOKEN_RETURN: return "return";
        case TOKEN_PRINT: return "print";
        case TOKEN_AND: return "and";
        case TOKEN_OR: return "or";
        case TOKEN_NOT: return "not";
        case TOKEN_TRUE: return "true";
        case TOKEN_FALSE: return "false";
        case TOKEN_NONE: return "none";

        default: return "unknown";
    }
}

void print_token(Token token) {
    printf("[Token] type=%s, lexeme='%s', line=%d\n",
           token_type_to_string(token.type), token.lexeme, token.line);
}
