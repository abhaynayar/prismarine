#ifndef INCLUDE_FB_H
#define INCLUDE_FB_H

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 50

// TODO: Implement scroll
class FrameBuffer {
    
    char *base;

    // Cursor
    int row, col;

    // Text color
    int fg, bg;

public:
    FrameBuffer();
    void write_cell(unsigned int i, char c);
    void move_cursor();
    void write(char *str, unsigned int len);
    void clear_screen();
};

#endif /* INCLUDE_FB_H */
