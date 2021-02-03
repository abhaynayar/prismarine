extern "C" {
#include "serial.h"
#include "io.h"
#include "fb.h"
}

int FrameBuffer::row = 0;
int FrameBuffer::col = 0;

void FrameBuffer::write_cell(int x, int y, char c) {
    unsigned char* base = (unsigned char*) VIDEO_ADDRESS;
    base[(x*SCREEN_WIDTH + y)*2] = c;
    //base[i+1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

char FrameBuffer::read_cell(int x, int y) {
    unsigned char* base = (unsigned char*) VIDEO_ADDRESS;
    return base[(x*SCREEN_WIDTH + y)*2];
}

void FrameBuffer::scroll() {
    for (int i=0; i<SCREEN_HEIGHT; ++i) {
        for (int j=0; j<SCREEN_WIDTH; ++j) {
            char temp = FrameBuffer::read_cell(i+1,j);
            FrameBuffer::write_cell(i,j,temp);
        }
    }
}

void FrameBuffer::move_cursor(int x, int y) {
    
    // Check for horizontal limit before vertical because if we exceed the
    // horizontal space on the last line it will overflow the vertical which
    // can then be handled after this.
    
    if (y >= SCREEN_WIDTH) {
        x++;
        y=0;
    }

    if (x >= SCREEN_HEIGHT) {
        FrameBuffer::scroll();
        x--;
        y=-1;  // When we are at the last row and we hit ENTER
               // the cursor row remains the same while the column
               // goes back to 0. The content scrolls up.
    }

    // The cursor should be ahead
    int pos = x*SCREEN_WIDTH + (y+1);
    
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);

    row = x;
    col = y+1;
}


void FrameBuffer::write(const char *str) {
    for (unsigned int i=0; str[i] != '\0'; ++i) {

        if (str[i] == '\n') {
            row++;
            col=-1;
        }

        else {
            FrameBuffer::write_cell(row, col, str[i]);
        }
        
        FrameBuffer::move_cursor(row, col);
    }

}

void FrameBuffer::clear_screen() {
    for (int i=0; i<SCREEN_HEIGHT; ++i) {
        for (int j=0; j<SCREEN_WIDTH; ++j) {
            FrameBuffer::write_cell(i, j, ' ');
        }
    }
}
