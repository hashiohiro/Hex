nasminc=./arch/x86/include/asm/
gccinc=./include/
gccarchinc=./arch/x86/include/

tmpoutput_dir=./bin/tmp
output_dir=./bin

.PHONY default:
default: compile link img run

.PHONY compile:
compile: arch/x86/boot/loader.asm arch/x86/lib/hex32corelib.asm lib/hex32corelib.c kernel/hex32kernel.c
	./tools/BitmapFontGenerator/bin/BitmapFontGenerator.o ./fonts/bitmap/default.txt ./fonts/default.c DEFBitmap 4096
	nasm -f bin  -i $(nasminc) -o $(tmpoutput_dir)/loader.bin arch/x86/boot/loader.asm
	nasm -f coff -i $(nasminc) -o $(tmpoutput_dir)/hex32corelib_asm.o arch/x86/lib/hex32corelib.asm
	i386-elf-gcc -I $(gccinc) -I $(gccarchinc) -o $(tmpoutput_dir)/setup.o -c arch/x86/entry/setup.c
	i386-elf-gcc -I $(gccinc) -I $(gccarchinc) -o $(tmpoutput_dir)/hex32corelib.o -c lib/hex32corelib.c
	i386-elf-gcc -I $(gccinc) -I $(gccarchinc) -o $(tmpoutput_dir)/hex32graphic.o -c lib/hex32graphic.c
	i386-elf-gcc -I $(gccinc) -I $(gccarchinc) -o $(tmpoutput_dir)/hex32kernel.o -c kernel/hex32kernel.c
	i386-elf-gcc -I $(gccinc) -I $(gccarchinc) -o $(tmpoutput_dir)/fonts/default.o -c fonts/default.c
	i386-elf-gcc -I $(gccinc) -I $(gccarchinc) -o $(tmpoutput_dir)/fonts/mousecursor.o -c fonts/mousecursor.c

.PHONY link:
link: bin/tmp/loader.bin $(tmpoutput_dir)/hex32kernel.o $(tmpoutput_dir)/hex32corelib_asm.o $(tmpoutput_dir)/hex32corelib.o $(tmpoutput_dir)/hex32graphic.o $(tmpoutput_dir)/setup.o
	i386-elf-ld -T hex32kernel.ld -Map $(tmpoutput_dir)/hex32kernel.map -nostdlib -o $(tmpoutput_dir)/hex32_tmp.o $(tmpoutput_dir)/hex32kernel.o $(tmpoutput_dir)/hex32corelib_asm.o $(tmpoutput_dir)/hex32corelib.o $(tmpoutput_dir)/fonts/default.o $(tmpoutput_dir)/fonts/mousecursor.o $(tmpoutput_dir)/hex32graphic.o $(tmpoutput_dir)/setup.o 
	i386-elf-objcopy -R .note -R.comment -S -O binary $(tmpoutput_dir)/hex32_tmp.o $(tmpoutput_dir)/hex32.bin 
	cat $(tmpoutput_dir)/loader.bin $(tmpoutput_dir)/hex32.bin > $(tmpoutput_dir)/bootimg.bin

.PHONY img:
img: $(tmpoutput_dir)/bootimg.bin
	qemu-img create -f raw $(output_dir)/hex32boot.img 1440k
	dd if=$(tmpoutput_dir)/bootimg.bin of=$(output_dir)/hex32boot.img conv=notrunc

.PHONY run:
run: $(output_dir)/hex32boot.img
	qemu-system-i386 -drive file=$(output_dir)/hex32boot.img,format=raw,if=floppy -boot a -monitor stdio

.PHONY clean:
clean:
	rm $(output_dir)/hex32boot.img
	rm $(tmpoutput_dir)/bootimg.bin
	rm $(tmpoutput_dir)/hex32_tmp.o
	rm $(tmpoutput_dir)/hex32.bin
	rm $(tmpoutput_dir)/hex32core_asm.o
	rm $(tmpoutput_dir)/hex32core.o
	rm $(tmpoutput_dir)/hex32kernel.map
	rm $(tmpoutput_dir)/hex32kernel.o
	rm $(tmpoutput_dir)/loader.bin
