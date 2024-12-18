#include <stdio.h>

#include "include/lexer.h"


int main(int argc, char **argv) {
    if (argc < 2)
        return 1;

    Lexer lxr = {.input = argv[1], .i = 0};
    Token t;
    while ((t = next(&lxr)).type != EOS)
        printf("%d ", t.type);
    return 0;
}