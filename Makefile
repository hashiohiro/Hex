.PHONY default:
default: clean compile link img run

.PHONY compile:
compile: loader.asm setup.asm
	nasm -f bin -o loader.bin loader.asm
	nasm -f bin -o setup.bin setup.asm
#	nasm -f coff -o hexlib_asm.o hexlib.asm
#	i386-elf-gcc -c hex.c
#	i386-elf-gcc -c hexlib.c

.PHONY link:
#link: loader.bin setup.bin hexlib_asm.o
link: loader.bin setup.bin
#	i386-elf-ld -Ttext 0x105ff -Map hex.map -e hex_main -nostdlib -o hexos.o hex.o hexlib.o hexlib_asm.o
#	i386-elf-objcopy -R .note -R.comment -S -O binary hexos.o hexos.bin 
#	cat loader.bin setup.bin hexos.bin > bootimg.bin
	cat loader.bin setup.bin > bootimg.bin

.PHONY img:
img: bootimg.bin
	qemu-img create -f raw boot.img 1440k
	dd if=bootimg.bin of=boot.img conv=notrunc

.PHONY run:
run: boot.img
	qemu-system-i386 -drive file=boot.img,format=raw,if=floppy -boot a -monitor stdio

.PHONY clean:
clean:
	rm -f *.img *.bin *.o *.map dump
