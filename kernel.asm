%include "consts.asm"

[org 0x10000]
[bits 32]

start:
init_register:
  mov bx, SData_Selector
  mov ds, bx
  mov es, bx
  mov fs, bx
  mov gs, bx
  mov ss, bx

init_idt:
  cld
  mov ax, SData_Selector
  mov es, ax
  xor eax, eax
  xor ecx, ecx
  mov ax, 256
  mov edi, 0

init_idt_loop:
  lea esi, [idt_ignore]
  mov cx, 8
  rep movsb
  dec ax
  jnz init_idt_loop

init_idt_end:
  lidt [idtr]
  sti
  int 0x77

end:
  xor eax, eax
  mov ax, Video_Selector
  mov es, ax
  mov edi, 80*2*10+2*10
  lea esi, [msg_pm]
  call puts

  hlt
  jmp $

;------------------------------------
; Sub Routines
;------------------------------------
puts:
  push eax

puts_loop:
  or al, al
  jz puts_end

  mov al, byte[esi]
  mov byte [es:edi], al
  inc edi
  mov byte [es:edi], 0x06
  inc esi
  inc edi
  jmp puts_loop
puts_end:
  pop eax
  ret

;------------------------------------
; Data Area
;------------------------------------
msg_pm db "We are in Protected Mode", 0
msg_isr_ignore db "This is an ignorable interrupt", 0

;------------------------------------
; Interrupt Service Routines
;------------------------------------
isr_ignore:
  push gs
  push fs
  push es
  push ds
  pushad
  pushfd

  mov ax, Video_Selector
  mov es, ax
  mov edi, (80*7*2)
  lea esi, [msg_isr_ignore]
  call puts

  popfd
  popad
  pop ds
  pop es
  pop fs
  pop gs

  iret

;------------------------------------
; IDT
;------------------------------------
idtr:
  dw 256*8-1  
  dd 0

idt_ignore:
  dw isr_ignore
  dw SCode_Selector
  db 0
  db 0x8e
  dw 0x0001

times 512-($-$$) db 0
