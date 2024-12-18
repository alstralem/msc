#include <ctype.h>

#include "include/lexer.h"


#define CURRENT (lxr->input[lxr->i])
#define LOOKAHEAD(k) (lxr->input[lxr->i+(k)])

#define ADVANCE(k) (lxr->i += (k))

static inline void skip_whitespaces(Lexer *lxr) {
    while (isspace(CURRENT))
        ADVANCE(1);
}

Token next(Lexer *lxr) {
    Token ret = {.type = UNKNOWN};

    skip_whitespaces(lxr);

    if (CURRENT == '\0') {
        ret.type = EOS;
        return ret;
    }

    // Single-character token
    #define SC_TOK(c, t) case (c): { ret.type = (t); ADVANCE(1); return ret; }
    switch (CURRENT) {
        case '@': {
            ADVANCE(1);
            size_t j = 0;
            while (isalpha(LOOKAHEAD(j)) || isdigit(LOOKAHEAD(j)) || LOOKAHEAD(j) == '_')
                ++j;
            ret.type = ID_VARIABLE;
            ret.attribute.lexeme.string = lxr->input+lxr->i;
            ret.attribute.lexeme.length = j;
            ADVANCE(j);
            return ret;
        }
        SC_TOK('=', OP_ASSIGN)
        SC_TOK('+', OP_ADD)
        SC_TOK('-', OP_SUB)
        SC_TOK('*', OP_MUL)
        SC_TOK('/', OP_DIV)
        SC_TOK(';', SEMICOLON)
        SC_TOK('(', LPAREN)
        SC_TOK(')', RPAREN)
    }
    #undef SC_TOK

    if (isdigit(CURRENT)) {
        int64_t value = 0;
        do {
            value = value*10 + (CURRENT - '0');
            ADVANCE(1);
        } while (isdigit(CURRENT));
        ret.type = INTEGER;
        ret.attribute.integer = value;
        return ret;
    }

    ADVANCE(1);
    return ret;
}