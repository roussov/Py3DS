#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

#define MAX_LINE_LEN 1024

int main(void) {
    char input[MAX_LINE_LEN];

    printf("Mini REPL (tape 'exit' pour quitter)\n");

    while (1) {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) {
            printf("\nFin du REPL\n");
            break;
        }

        // Supprimer le saut de ligne final
        size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[len-1] = '\0';
            len--;
        }

        if (strcmp(input, "exit") == 0) {
            printf("Sortie du REPL\n");
            break;
        }

        Lexer *lexer = lexer_new(input);
        if (!lexer) {
            fprintf(stderr, "Erreur allocation lexer\n");
            continue;
        }

        Parser *parser = parser_new(lexer);
        if (!parser) {
            fprintf(stderr, "Erreur allocation parser\n");
            lexer_free(lexer);
            continue;
        }

        // Ici on parse, on pourrait construire un AST, l'évaluer, etc.
        parser_parse(parser);

        printf("Parsing done.\n");

        parser_free(parser);
        lexer_free(lexer);
    }

    return 0;
}
