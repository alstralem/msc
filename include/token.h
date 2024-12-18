#ifndef TOKEN_H
#define TOKEN_H
#include <stddef.h>
#include <stdint.h>


typedef enum {
    UNKNOWN,

    /* Identifiers */
    ID_VARIABLE,

    /* Literals */
    INTEGER,

    /* Operators */
    OP_ASSIGN, OP_ADD, OP_SUB, OP_MUL, OP_DIV,

    /* Markers */
    SEMICOLON, LPAREN, RPAREN,

    /* End of Stream */
    EOS
} TokenType;

typedef struct {
    TokenType type;
    union {
        struct {
            const char *string;
            size_t length;
        } lexeme;
        int64_t integer;
    } attribute;
} Token;

#endif