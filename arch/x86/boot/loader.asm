%include "allocmap.asm"

[org 0x07c00]

init:

; Initialize display(vga graphics 320x200x8BitColor).
  mov al, 0x13
  mov ah, 0x00
  int 0x10

  mov byte  [ReadSectors], 18
  mov byte  [VideoMode], 8
  mov word  [ScreenX], 320
  mov word  [ScreenY], 200
  mov dword [VRAMOrigin], 0x000a0000

; Set current Keyboard LEDs status.
  mov ah, 0x02
  int 0x16
  mov [KeyboardLEDs], al

; Initialize registers
  mov ax, cs  
  mov ds, ax
  mov es, ax

; "Read phase"
; The loader loads one sector from floppy disk to memory(0x1000:0000).
; When error occured, the loader execute read label again.
read:
  mov ax, 0x1000
  mov es, ax
  mov bx, 0

  mov ah, 2
  mov al, byte [ReadSectors]        ; Number of sectors to be loaded
  mov ch, 0                   ; Cylinder
  mov cl, 2                   ; Sector
  mov dh, 0                   ; Head
  mov dl, 0                   ; Drive
  int 0x13

  jc read

; Turn off the floppy disk motor.
  mov dx, 0x3f2
  xor al, al
  out dx, al

; "PIC Initialize phase"
; 1. Execute ICW1: Set policy to use pic.
; 2. Execute ICW2: Set interrupt orign in (master/slave) pic.
; 3. Execute ICW3: Set irq that the (master/slave) is connected to (master/slave) pic.
; 4. Execute ICW4: Setting the use of 8086 mode.
; 5. Suppress interruptes: Suppress all interrupts of the (master/slave) PIC.
; [Notes]
;   About "0x00eb"
;     0x00eb is equivalent to jmp $ + 2.
;     In this section 0x00eb is used to generate a delay.

; Execute ICW1
; (master)
mov al, 0x11
out 0x20, al ; master pic
dw 0x00eb, 0x00eb ;jmp$+2 jmp$+2

; (slave)
out 0xa0, al ; slave pic
dw 0x00eb, 0x00eb

; Execute ICW2
; (master)
mov al, 0x20
out 0x21, al
dw 0x00eb, 0x00eb

; (slave)
mov al, 0x28
out 0xa1, al
dw 0x00eb, 0x00eb

; Execute ICW3
; (master)
mov al, 0x04
out 0x21, al
dw 0x00eb, 0x00eb

; (slave)
mov al, 0x02
out 0xa1, al
dw 0x00eb, 0x00eb

; Execute ICW4
; (master)
mov al, 0x01
out 0x21, al
dw 0x00eb, 0x00eb

; (slave)
out 0xa1, al
dw 0x00eb, 0x00eb

; Suppress interruptes
; (slave)
mov al, 0xff
out 0xa1, al
dw 0x00eb, 0x00eb

; (master)
mov al, 0xfb
out 0x21, al
dw 0x00eb, 0x00eb

; "Prepare phase"
; 1. Set 32 bits effective in cr0 register.
; 2. Initialize cpu units. 
; 3. initialize 16bits registers.
;
; [Notes]
;   About "Initialize cpu units"
;     Actually it is a fetch unit and a decode unit.
;     Because there is a possibility of unexpected movement
;     when shifting to 32 bits while each 16-bit op code is included.
;
prepare:
  cli

  lgdt [gdtr]

; set 32 bits effective
  mov eax, cr0
  or eax, 0x00000001
  mov cr0, eax

; initialize cpu units
  jmp $+2
  nop
  nop

; initialize 16bits registers
  mov bx, SDataSelector
  mov ds, bx
  mov es, bx
  mov fs, bx
  mov gs, bx
  mov ss, bx

; shift to 32bits protected mode!
  jmp dword SCodeSelector:0x10000

gdtr:
  dw gdt_end-gdt-1
  dd gdt
gdt:
  dd 0, 0
  dd 0x0000ffff, 0x00cf9a00
  dd 0x0000ffff, 0x00cf9200
  dd 0x8000ffff, 0x0040920b
gdt_end:

signature:
  times 510-($-$$) db 0
  db 0x55,0xaa
