#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "ps2.h"
#include "../lib/proc.h"

/* Globals */
extern ProcessQueue *keyboard_queue_ptr;

void keyboard_init(void);
void keyboard_interrupt_scancode(void);




#endif /* keyboard.h */
