AS = nasm
ASFLAGS = -f elf

OBJECTS =  io.o fb.o loader.o kmain.o serial.o
LDFLAGS = -T link.ld -melf_i386

CC = g++
#TODO: See which flags to remove
CFLAGS = -Wall -Wextra -Werror \
		-c -O2 -m32 -ffreestanding \
		-fno-builtin -fno-stack-protector -fno-exceptions -fno-rtti \
		-nostartfiles -nodefaultlibs -nostdlib -nostdinc \

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

image: os.iso

# TODO: Make sense of this
os.iso: kernel.elf
	mkdir -p iso/boot/grub              # create the folder structure
	cp stage2_eltorito iso/boot/grub/   # copy the bootloader
	cp kernel.elf iso/boot/             # copy the kernel
	cp menu.lst iso/boot/grub  # tells GRUB where the kernel is located
	genisoimage -R                      \
		-b boot/grub/stage2_eltorito    \
		-no-emul-boot                   \
		-boot-load-size 4               \
		-A os                           \
		-input-charset utf8             \
		-quiet                          \
		-boot-info-table                \
		-o os.iso                       \
		iso

bochs: os.iso
	bochs -f bochsrc.txt -q

qemu: os.iso
	qemu-system-x86_64 -boot d -cdrom os.iso -m 512

%.o: %.cc
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf os.iso
	rm -rf bochslog.txt com1.out
	rm -rf iso
