#ifndef REPL_H
#define REPL_H

#include <stdbool.h>

// Taille max d’une ligne d’entrée dans le REPL
#define REPL_INPUT_BUFFER_SIZE 256

// Structure représentant l’état du REPL
typedef struct {
    char input_buffer[REPL_INPUT_BUFFER_SIZE];
    int input_length;

    bool running;           // Indique si la boucle REPL est active
    // Ajoute ici d’autres éléments comme l’environnement d’évaluation,
    // historique, pointeurs vers AST, etc.
} REPL_State;

// Initialise le REPL (réinitialise le buffer, état, etc)
void repl_init(REPL_State* state);

// Lit une ligne d’entrée dans le buffer REPL (ex: clavier virtuel ou console)
bool repl_read_line(REPL_State* state);

// Évalue la ligne courante (parser + évaluer l’AST) et retourne vrai si succès
bool repl_eval(REPL_State* state);

// Affiche le résultat ou un message d’erreur
void repl_print_result(REPL_State* state);

// Affiche le prompt REPL (ex: ">>> ")
void repl_print_prompt(void);

// La boucle principale REPL, retourne quand `state->running` devient false
void repl_loop(REPL_State* state);

#endif // REPL_H
