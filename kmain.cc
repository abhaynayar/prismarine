extern "C" {
    #include "serial.h"
    #include "io.h"
    #include "fb.h"
}

// TODO: Use fixed datatypes (u8, u16, etc.)
// TODO: Create a strlen() function
// TODO: QEMU serial output

int main() {
    
    // NOTE: https://littleosbook.github.io/#segmentation
    char str[] = "abhay nayar\nis a good boy";

    FrameBuffer fb;
    fb.clear_screen();
    fb.write(str, 25);

    Serial s;
    s.write('w');
    return 0;
}


