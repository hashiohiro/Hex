.PHONY default:
default: clean compile link img run

.PHONY compile:
compile: loader.asm setup.asm
	nasm -f bin -o loader.bin loader.asm
	nasm -f bin -o setup.bin setup.asm
	nasm -f coff -o hex32core_asm.o hex32core.asm
	i386-elf-gcc -c hex32kernel.c

.PHONY link:
link: loader.bin setup.bin hex32kernel.o
	i386-elf-ld -T hex32kernel.ld -Map hex32kernel.map -nostdlib -o hex32_tmp.o hex32kernel.o hex32core_asm.o
	i386-elf-objcopy -R .note -R.comment -S -O binary hex32_tmp.o hex32.bin 
	cat loader.bin setup.bin hex32.bin > bootimg.bin

.PHONY img:
img: bootimg.bin
	qemu-img create -f raw hex32boot.img 1440k
	dd if=bootimg.bin of=hex32boot.img conv=notrunc

.PHONY run:
run: hex32boot.img
	qemu-system-i386 -drive file=hex32boot.img,format=raw,if=floppy -boot a -monitor stdio

.PHONY clean:
clean:
	rm -f *.img *.bin *.o *.map dump
