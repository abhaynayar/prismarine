extern "C" {

#include "isr.h"
#include "keyboard.h"
#include "serial.h"
#include "io.h"
#include "fb.h"

}

// TODO:
// + GDT (what? why?)
// + Implement scroll
// + Implement timers
// + Fix blinking cursor position
// + Implement QEMU serial support
// + Implement serial->write(char*)
// + Fix newline after a text wrap
// + Fix FrameBuffer::static variable confusion

int main() {
    char str[] = "abhay nayar\nis a good boy";
    FrameBuffer::clear_screen();
    FrameBuffer::write(str);

    //Serial s;
    //s.write('w');

    asm volatile("sti");
    isr_install();
    init_keyboard();
    //__asm__ __volatile__("int $2");
    //__asm__ __volatile__("int $3");
    return 0;
}
