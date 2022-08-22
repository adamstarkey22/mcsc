#include <stdio.h>

#include "debug.h"

const char *token_type_str(TokenType type)
{
    switch (type) {
        case TOKEN_LEFT_PAREN: return "TOKEN_LEFT_PAREN";
        case TOKEN_RIGHT_PAREN: return "TOKEN_RIGHT_PAREN";
        case TOKEN_EQUAL: return "TOKEN_EQUAL";
        case TOKEN_PLUS: return "TOKEN_PLUS";
        case TOKEN_MINUS: return "TOKEN_MINUS";
        case TOKEN_STAR: return "TOKEN_STAR";
        case TOKEN_SLASH: return "TOKEN_SLASH";
        case TOKEN_PERCENT: return "TOKEN_PERCENT";
        case TOKEN_GREATER: return "TOKEN_GREATER";
        case TOKEN_LESS: return "TOKEN_LESS";
        case TOKEN_AMPERSAND: return "TOKEN_PIPE";
        case TOKEN_PLUS_EQUAL: return "TOKEN_PLUS_EQUAL";
        case TOKEN_MINUS_EQUAL: return "TOKEN_MINUS_EQUAL";
        case TOKEN_STAR_EQUAL: return "TOKEN_STAR_EQUAL";
        case TOKEN_SLASH_EQUAL: return "TOKEN_SLASH_EQUAL";
        case TOKEN_PERCENT_EQUAL: return "TOKEN_PERCENT_EQUAL";
        case TOKEN_GREATER_EQUAL: return "TOKEN_GREATER_EQUAL";
        case TOKEN_LESS_EQUAL: return "TOKEN_LESS_EQUAL";
        case TOKEN_BANG_EQUAL: return "TOKEN_BANG_EQUAL";
        case TOKEN_DO: return "TOKEN_DO";
        case TOKEN_ELSE: return "TOKEN_ELSE";
        case TOKEN_FOR: return "TOKEN_FOR";
        case TOKEN_FUNCTION: return "TOKEN_FUNCTION";
        case TOKEN_IF: return "TOKEN_IF";
        case TOKEN_RETURN: return "TOKEN_RETURN";
        case TOKEN_WHILE: return "TOKEN_WHILE";
        case TOKEN_INT: return "TOKEN_INT";
        case TOKEN_FLOAT: return "TOKEN_FLOAT";
        case TOKEN_IDENTIFIER: return "TOKEN_IDENTIFIER";
        case TOKEN_LINE_BREAK: return "TOKEN_LINE_BREAK";
        case TOKEN_ERROR: return "TOKEN_ERROR";
        case TOKEN_EOF: return "TOKEN_EOF";
    }
}
