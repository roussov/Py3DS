#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <stdint.h>

// Enum des touches physiques supportées
typedef enum {
    KEY_NONE = 0,
    KEY_A,
    KEY_B,
    KEY_X,
    KEY_Y,
    KEY_START,
    KEY_SELECT,
    KEY_L,
    KEY_R,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    // Ajoute d’autres touches si nécessaire
    KEY_COUNT
} KeyCode;

// Structure représentant l’état du clavier/tactile
typedef struct {
    bool keys_down[KEY_COUNT];            // État de chaque touche (appuyée ou non)
    uint8_t keys_pressed_count;           // Nombre de touches pressées depuis dernier reset
    KeyCode keys_pressed[16];             // Liste des touches pressées (FIFO)
    // Données pour le tactile (exemple : coordonnées)
    int touch_x;
    int touch_y;
    bool touch_active;
} InputState;

// Initialise la structure InputState
void input_init(InputState* input);

// Met à jour l’état d’une touche physique
void input_update_key(InputState* input, KeyCode key, bool pressed);

// Réinitialise la liste des touches pressées
void input_clear_pressed(InputState* input);

// Met à jour l’état tactile (active ou non, position)
void input_update_touch(InputState* input, bool active, int x, int y);

// Vérifie si une touche est actuellement appuyée
bool input_is_key_down(const InputState* input, KeyCode key);

#endif // INPUT_H
