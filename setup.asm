%include "consts.asm"

[org 0x10000]
[bits 32]

start:
init_register:
  mov bx, SDataSelector
  mov ds, bx
  mov es, bx
  mov fs, bx
  mov gs, bx
  mov ss, bx

init_idt:
  cld
  mov ax, SDataSelector
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

overwrite_idt:
  mov edi, 0
  lea esi, [idt_zero_devide]
  mov cx, 8
  rep movsb
  
  mov edi, 8*0x20
  lea esi, [idt_32_timer]
  mov cx, 8
  rep movsb

  mov edi, 8*0x021
  lea esi, [idt_33_keyboard]
  mov cx, 8
  rep movsb

load_idt:
  lidt [idtr]

; enable timer interrupt
  mov al, 0xfc
  out 0x21, al
  sti

end:
  jmp 0x10400

;------------------------------------
; Sub Routines
;------------------------------------
; puts
; esi = source string
; edi = distination string

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
msg_isr_zero_devide db "Zero Devide Exception!", 0
msg_isr_32_timer db "Timer interrupt", 0
msg_isr_33_keyboard db "Keyboard interrupt", 0

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

  mov ax, VideoSelector
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

isr_zero_devide:
  push gs
  push fs
  push es
  push ds
  pushad
  pushfd
  
  mov al, 0x20
  out 0x20, al

  mov ax, VideoSelector
  mov es, ax
  mov edi, (80*6*2)
  lea esi, [msg_isr_zero_devide]
  call puts

  jmp $

  popfd
  popad
  pop ds
  pop es
  pop fs
  pop gs

  iret

isr_32_timer:
  push gs
  push fs
  push es
  push ds
  pushad
  pushfd

  mov al, 0x20
  out 0x20, al

  mov ax, VideoSelector
  mov es, ax
  mov edi, (80*2*2)
  lea esi, [msg_isr_32_timer]
  call puts
  inc byte [msg_isr_32_timer]

  popfd
  popad
  pop ds
  pop es
  pop fs
  pop gs

  iret

isr_33_keyboard:
  pushad
  push gs
  push fs
  push es
  push ds
  pushfd

  in al, 0x60

  mov al, 0x20
  out 0x20, al
  mov ax, VideoSelector
  mov es, ax
  mov edi, (80*4*2)
  lea esi, [msg_isr_33_keyboard]
  call puts
  inc byte [msg_isr_33_keyboard]

  popfd
  pop ds
  pop es
  pop fs
  pop gs
  popad
  iret


;------------------------------------
; IDT
;------------------------------------
idtr:
  dw 256*8-1  
  dd 0

idt_ignore:
  dw isr_ignore
  dw SCodeSelector
  db 0
  db 0x8e
  dw 0x0001

idt_zero_devide:
  dw isr_zero_devide
  dw 0x08
  db 0
  db 0x8e
  dw 0x0001

idt_32_timer:
  dw isr_32_timer
  dw SCodeSelector
  db 0
  db 0x8e
  dw 0x0001

idt_33_keyboard:
  dw isr_33_keyboard
  dw 0x08
  db 0
  db 0x8e
  dw 0x0001

times 1024-($-$$) db 0
