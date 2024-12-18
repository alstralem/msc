#ifndef LEXER_H
#define LEXER_H
#include "token.h"


typedef struct {
    const char *input;
    size_t i;
} Lexer;

Token next(Lexer *lxr);

#endif