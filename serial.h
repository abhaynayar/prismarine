#ifndef INCLUDE_SERIAL_H
#define INCLUDE_SERIAL_H


/* The I/O ports */

/* All the I/O ports are calculated relative to the data port. This is because
 * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
 * order, but they start at different values.
 */

#define SERIAL_COM1_BASE                0x3F8      /* COM1 base port */

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

class Serial {
    unsigned short com;
    unsigned short divisor;

public:
    Serial();
    void write(char a);
    int  is_transmit_fifo_empty();

    // Configuration stuff
    void configure_baud_rate();
    void configure_line();
    void configure_buffers();
    void configure_modem();

};

#endif /* INCLUDE_SERIAL_H */
