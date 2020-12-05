AS = nasm
ASFLAGS = -f elf

OBJECTS = loader.o kmain.o io.o
LDFLAGS = -T link.ld -melf_i386

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf
all: kernel.elf
image: os.iso
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

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@


clean:
	rm -rf *.o kernel.elf os.iso
	rm -rf bochslog.txt
	rm -rf iso

