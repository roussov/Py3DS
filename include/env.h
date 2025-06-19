#ifndef ENV_H
#define ENV_H

#include <stddef.h>
#include "ast.h"

typedef enum {
    VAL_INT,
    VAL_FLOAT,
    VAL_STRING,
    VAL_NONE
} ValueType;

typedef struct {
    ValueType type;
    union {
        int int_val;
        double float_val;
        char* string_val;
    };
} Value;

typedef struct EnvEntry {
    char* name;
    Value value;
    struct EnvEntry* next;
} EnvEntry;

typedef struct {
    EnvEntry* head;
} Env;

// Initialise un nouvel environnement
void env_init(Env* env);

// Libère toute la mémoire de l’environnement
void env_free(Env* env);

// Définit une variable dans l’environnement (ajoute ou remplace)
void env_set(Env* env, const char* name, Value val);

// Récupère la variable par nom, retourne NULL si non trouvée
Value* env_get(Env* env, const char* name);

#endif
