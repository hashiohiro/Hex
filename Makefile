.PHONY default:
default: compile link run

.PHONY compile:
compile:
	nasm -f bin -o loader.bin loader.asm
	nasm -f bin -o kernel.bin kernel.asm


.PHONY link:
link: loader.bin kernel.bin
	cat loader.bin kernel.bin > hex.bin

.PHONY img:
img: hex.img
	qemu-img create -f raw hex.img 1440k
	dd if=hex.bin of=hex.img conv=notrunc

.PHONY run:
run: hex.img
	qemu-system-i386 -drive file=hex.img,format=raw,if=floppy -boot a

.PHONY clean:
clean:
	rm loader.bin kernel.bin hex.bin
