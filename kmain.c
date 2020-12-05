/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */

char *fb = (char *) 0x000B8000;
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

#include "io.h"

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *  @param pos The new position of the cursor
 */

void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}

// TODO: Create an enum with all the colors
int sum_of_three(int arg1, int arg2, int arg3) {
    fb_move_cursor(80);
    fb_write_cell(0, 'B', 15, 0);
    return arg1 + arg2 + arg3;
}

