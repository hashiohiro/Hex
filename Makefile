.PHONY default:
default: clean compile link img run

.PHONY compile:
compile: arch/x86/boot/loader.asm arch/x86/entry/setup.asm arch/x86/kernel/hex32core.asm kernel/hex32core.c kernel/hex32kernel.c
	nasm -f bin  -i include/asm/ -o bin/loader.bin arch/x86/boot/loader.asm
	nasm -f bin  -i include/asm/ -o bin/setup.bin arch/x86/entry/setup.asm
	nasm -f coff -i include/asm/ -o bin/hex32core_asm.o arch/x86/kernel/hex32core.asm
	i386-elf-gcc -I include/ -o bin/hex32core.o -c kernel/hex32core.c
	i386-elf-gcc -I include/ -o bin/hex32kernel.o -c kernel/hex32kernel.c

.PHONY link:
link: bin/loader.bin bin/setup.bin bin/hex32kernel.o bin/hex32core_asm.o bin/hex32core.o
	i386-elf-ld -T hex32kernel.ld -Map bin/hex32kernel.map -nostdlib -o bin/hex32_tmp.o bin/hex32kernel.o bin/hex32core_asm.o bin/hex32core.o
	i386-elf-objcopy -R .note -R.comment -S -O binary bin/hex32_tmp.o bin/hex32.bin 
	cat bin/loader.bin bin/setup.bin bin/hex32.bin > bin/bootimg.bin

.PHONY img:
img: bin/bootimg.bin
	qemu-img create -f raw bin/hex32boot.img 1440k
	dd if=bin/bootimg.bin of=bin/hex32boot.img conv=notrunc

.PHONY run:
run: bin/hex32boot.img
	qemu-system-i386 -drive file=bin/hex32boot.img,format=raw,if=floppy -boot a -monitor stdio

.PHONY clean:
clean:
	rm -f bin/*.img bin/*.bin bin/*.o bin/*.map
