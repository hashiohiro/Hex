%include "consts.asm"

[org 0x07c00]

init:
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
  mov al, 1                   ; Number of sectors to be loaded
  mov ch, 0                   ; Cylinder
  mov cl, 2                   ; Sector
  mov dh, 0                   ; Head
  mov dl, 0                   ; Drive
  int 0x13

  jc read

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
  mov bx, SData_Selector
  mov ds, bx
  mov es, bx
  mov fs, bx
  mov gs, bx
  mov ss, bx

; shift to 32bits protected mode!
  jmp dword SCode_Selector:0x10000

gdtr:
  dw gdt_end-gdt-1
  dd gdt
gdt:
  dd 0, 0
  dd 0x0000ffff, 0x00cf9a00
  dd 0x0000ffff, 0x00cf9200
  dd 0x8000ffff, 0x0040920b
gdt_end:

pad:
  times 510-($-$$) db 0
  db 0x55,0xaa
