extern "C" {
#include "io.h"
#include "serial.h"
}

Serial::Serial() {
    com = SERIAL_COM1_BASE;
    divisor = 3;

    // Configuration stuff
    Serial::configure_baud_rate();
    Serial::configure_line();
    Serial::configure_buffers();
    Serial::configure_modem();
}

/** serial_is_transmit_fifo_empty:
 *  Checks whether the transmit FIFO queue is empty or not for the given COM
 *  port.
 *
 *  @param  com The COM port
 *  @return 0 if the transmit FIFO queue is not empty
 *          1 if the transmit FIFO queue is empty
 */
int Serial::is_transmit_fifo_empty() {
    /* 0x20 = 0010 0000 */
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void Serial::write(char ch) {
   while (is_transmit_fifo_empty() == 0);
   outb(SERIAL_DATA_PORT(com), ch);
}


/* The I/O port commands */

/* SERIAL_LINE_ENABLE_DLAB:
 * Tells the serial port to expect first the highest 8 bits on the data port,
 * then the lowest 8 bits will follow
 */
#define SERIAL_LINE_ENABLE_DLAB 0x80

/** serial_configure_baud_rate:
 *  Sets the speed of the data being sent. The default speed of a serial
 *  port is 115200 bits/s. The argument is a divisor of that number, hence
 *  the resulting speed becomes (115200 / divisor) bits/s.
 *
 *  @param com      The COM port to configure
 *  @param divisor  The divisor
 */
void Serial::configure_baud_rate() {
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

/** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 */
void Serial::configure_line() {
    /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content: | d | b | prty  | s | dl  |
     * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
     */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

/** serial_configure_buffer:
 *  Configures the buffers (FIFO?)
 */
void Serial::configure_buffers() {
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

/** serial_configure_modem:
 *  Configures the modem
 */
void Serial::configure_modem() {
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

