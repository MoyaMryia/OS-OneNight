CC = riscv64-unknown-elf-gcc
OBJCOPY = riscv64-unknown-elf-objcopy
OBJDUMP = riscv64-unknown-elf-objdump
QEMU = qemu-system-riscv64

INC_DIR = include
SRC_DIR = src

CFLAGS = -march=rv64gc -mabi=lp64d -static -mcmodel=medany \
         -fno-common -nostdlib -fno-builtin -ffreestanding \
         -I$(INC_DIR) -Wall -O0 -g 

SRCS = entry.S main.c $(SRC_DIR)/uart.c $(SRC_DIR)/standio.c
OBJS = $(SRCS:.S=.o)
OBJS := $(OBJS:.c=.o)

kernel.elf: $(SRCS) linker.ld
	$(CC) $(CFLAGS) -T linker.ld $(SRCS) -o kernel.elf

run: kernel.elf
	$(QEMU) -machine virt -nographic -bios none -kernel kernel.elf

debug: kernel.elf
	$(QEMU) -machine virt -nographic -bios none -kernel kernel.elf -S -gdb tcp::1234

clean:
	rm -f *.o kernel.elf

test:
	make
	make run

update:
	git add .
	git commit
	git push