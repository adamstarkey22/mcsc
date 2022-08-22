#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "scanner.h"

typedef struct {
    const char *start;
    const char *current;
    int line;
} Scanner;

Scanner scanner;

void init_scanner(const char *source)
{
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

static bool is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        c == '_';
}

static bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static bool is_at_end()
{
    return *scanner.current == '\0';
}

static char advance()
{
    scanner.current++;
    return scanner.current[-1];
}

static char peek()
{
    return *scanner.current;
}

static bool match(char expected)
{
    if (is_at_end()) return false;
    if (*scanner.current != expected) return false;
    scanner.current++;
    return true;
}

static Token make_token(TokenType type)
{
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

static Token error_token(const char *message)
{
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;
    return token;
}

static void skip_whitespace()
{
    for (;;) {
        char c = peek();
        switch(c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            default:
                return;
        }
    }
}

static TokenType check_keyword(int start, int length, const char *rest, TokenType type)
{
    if (scanner.current - scanner.start == start + length & memcmp(scanner.start + start, rest, length) == 0) {
        return type;
    }

    return TOKEN_IDENTIFIER;
}

static TokenType identifier_type()
{
    switch (scanner.start[0]) {
        case 'd': return check_keyword(1, 1, "o", TOKEN_DO);
        case 'e': return check_keyword(1, 3, "lse", TOKEN_ELSE);
        case 'f':
            if (scanner.current - scanner.start > 1) {
                switch(scanner.start[1]) {
                    case 'o': return check_keyword(2, 1, "r", TOKEN_FOR);
                    case 'u': return check_keyword(2, 6, "nction", TOKEN_FUNCTION);
                }
            }
            break;
        case 'i': return check_keyword(1, 1, "f", TOKEN_IF);
        case 'r': return check_keyword(1, 5, "eturn", TOKEN_RETURN);
        case 'w': return check_keyword(1, 4, "hile", TOKEN_WHILE);
    }

    return TOKEN_IDENTIFIER;
}

static Token identifier()
{
    while (is_alpha(peek()) || is_digit(peek())) {
        advance();
    }

    return make_token(identifier_type());
}

static Token number()
{
    if (*scanner.start != '0') {
        while (is_digit(peek())) {
            advance();
        }
    }

    if (peek() != '.') {
        return make_token(TOKEN_INT);
    }

    advance();

    if (!is_digit(peek())) {
        return error_token("Expected fractional part for float literal.");
    }

    while (is_digit(peek())) {
        advance();
    }

    return make_token(TOKEN_FLOAT);
}

Token scan_token()
{
    skip_whitespace();

    scanner.start = scanner.current;
    if (is_at_end()) return make_token(TOKEN_EOF);

    char c = advance();
    if (is_alpha(c)) return identifier();
    if (is_digit(c)) return number();

    switch (c) {
        case '(': return make_token(TOKEN_LEFT_PAREN);
        case ')': return make_token(TOKEN_RIGHT_PAREN);
        case '=': return make_token(TOKEN_EQUAL);
        case '&': return make_token(TOKEN_AMPERSAND);
        case '|': return make_token(TOKEN_PIPE);

        case '+':
            return make_token(match('=') ? TOKEN_PLUS_EQUAL : TOKEN_PLUS);
        case '-':
            return make_token(match('=') ? TOKEN_MINUS_EQUAL : TOKEN_MINUS);
        case '*':
            return make_token(match('=') ? TOKEN_STAR_EQUAL : TOKEN_STAR);
        case '/':
            return make_token(match('=') ? TOKEN_SLASH_EQUAL : TOKEN_SLASH);
        case '%':
            return make_token(match('=') ? TOKEN_PERCENT_EQUAL : TOKEN_PERCENT);
        case '>':
            return make_token(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
        case '<':
            return make_token(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);

        case '\n':
            scanner.line++;
            return make_token(TOKEN_LINE_BREAK);
    }

    return error_token("Unexpected character.");
}

