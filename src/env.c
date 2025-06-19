#include <stdlib.h>
#include <string.h>
#include "env.h"

void env_init(Env* env) {
    env->head = NULL;
}

void env_free(Env* env) {
    EnvEntry* current = env->head;
    while (current) {
        EnvEntry* next = current->next;
        free(current->name);
        if (current->value.type == VAL_STRING) {
            free(current->value.string_val);
        }
        free(current);
        current = next;
    }
    env->head = NULL;
}

void env_set(Env* env, const char* name, Value val) {
    EnvEntry* current = env->head;
    EnvEntry* prev = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            // Libère ancienne string si nécessaire
            if (current->value.type == VAL_STRING) {
                free(current->value.string_val);
            }
            current->value = val;
            return;
        }
        prev = current;
        current = current->next;
    }

    // Ajout nouveau
    EnvEntry* entry = malloc(sizeof(EnvEntry));
    entry->name = strdup(name);
    entry->value = val;
    entry->next = NULL;

    if (prev) {
        prev->next = entry;
    } else {
        env->head = entry;
    }
}

Value* env_get(Env* env, const char* name) {
    EnvEntry* current = env->head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return &current->value;
        }
        current = current->next;
    }
    return NULL;
}
