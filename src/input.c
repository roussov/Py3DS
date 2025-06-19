#include "input.h"
#include <string.h>

void input_init(InputState* input) {
    if (!input) return;
    memset(input->keys_down, 0, sizeof(input->keys_down));
    input->keys_pressed_count = 0;
    memset(input->keys_pressed, 0, sizeof(input->keys_pressed));
    input->touch_x = 0;
    input->touch_y = 0;
    input->touch_active = false;
}

void input_update_key(InputState* input, KeyCode key, bool pressed) {
    if (!input || key <= KEY_NONE || key >= KEY_COUNT)
        return;

    if (pressed) {
        if (!input->keys_down[key]) {
            input->keys_down[key] = true;
            // Ajoute dans la liste des touches pressées si possible
            if (input->keys_pressed_count < 16) {
                input->keys_pressed[input->keys_pressed_count++] = key;
            }
        }
    } else {
        input->keys_down[key] = false;
        // Optionnel : enlever la touche de keys_pressed si nécessaire
    }
}

void input_clear_pressed(InputState* input) {
    if (!input) return;
    input->keys_pressed_count = 0;
    memset(input->keys_pressed, 0, sizeof(input->keys_pressed));
}

void input_update_touch(InputState* input, bool active, int x, int y) {
    if (!input) return;
    input->touch_active = active;
    if (active) {
        input->touch_x = x;
        input->touch_y = y;
    }
}

bool input_is_key_down(const InputState* input, KeyCode key) {
    if (!input || key <= KEY_NONE || key >= KEY_COUNT)
        return false;
    return input->keys_down[key];
}
