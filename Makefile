.PHONY default:
default: compile link run

.PHONY compile:
compile:
	nasm -f bin -o loader.bin loader.asm
	nasm -f bin -o setup.bin setup.asm
# i386-elf-gcc -c kernel.c
# i386-elf-ld -Ttext 


.PHONY link:
link: loader.bin setup.bin
	cat loader.bin setup.bin > hex.bin
# ld -o kernel -Ttext 0x

.PHONY img:
img: hex.img
	qemu-img create -f raw hex.img 1440k
	dd if=hex.bin of=hex.img conv=notrunc

.PHONY run:
run: hex.img
	qemu-system-i386 -drive file=hex.img,format=raw,if=floppy -boot a -monitor stdio

.PHONY clean:
clean:
	rm loader.bin setup.bin hex.bin
