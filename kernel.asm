%include "consts.asm"

[org 0x10000]
[bits 32]

start:
  mov bx, SData_Selector
  mov ds, bx
  mov es, bx
  mov fs, bx
  mov gs, bx
  mov ss, bx

  xor eax, eax
  mov ax, Video_Selector
  mov es, ax
  mov edi, 80*2*10+2*10
  lea esi, [msg_pm]
  call puts

end:
  hlt
  jmp $

;------------------------------------
; Routines
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
msg_pm:
  db "We are in Protected Mode", 0

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
  call printf

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
