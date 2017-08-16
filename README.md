# Hex
## What is hex?
Hex is an 32bit Operating System under development for learning purposes.
It works on x86 compatible processors.
## Requirement
### NASM
site      : [www.nasm.us](http://www.nasm.us/)
version   : 2.13.01

### QEMU Emulator
site    : [www.qemu.org](https://www.qemu.org/)
version : 2.9.0

## Install

### 1. Make an empty disk image

Hex installation target is a floppy disk.
the image's size is 1440 KB.

``` bash
qemu-img create -f raw floppy.img 1440k
```

### 2. Assemble the boot loader and kernel

``` bash
nasm -f bin -o loader.bin loader.asm
nasm -f bin -o kernel.bin kernel.asm
cat loader.bin kernel.bin > hex.bin
```

### 3. Write the assembled Hex to disk image

``` bash
dd if=hex.bin of=hex.img conv=notrunc
```

### 4. Try it!

``` bash
qemu-system-i386 -drive file=hex.img,format=raw,if=floppy -boot a
```

## License
Hex, version 1.0.0 (c) 2017 Hiroshi Hashimoto.
Hex is freely distributable under the terms of an MIT-style license. 

