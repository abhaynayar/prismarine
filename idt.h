#ifndef IDT_H
#define IDT_H

#include "types.h"

/* Segment selectors */
#define KERNEL_CS 0x08

/* Functions implemented in idt.c */
void set_idt_gate(int n, u32 handler);
void set_idt();

#endif
