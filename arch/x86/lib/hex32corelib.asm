segment .text
[global OpHLT]
[global OpCLI]
[global OpSTI]
[global OpSTIHLT]
[global OpIn8]
[global OpIn16]
[global OpIn32]
[global OpOut8]
[global OpOut16]
[global OpOut32]
[global LoadEFlags]
[global StoreEFlags]
[global LoadGDTR]
[global LoadIDTR]

; void OpHlt(void);
OpHLT:
  hlt
  ret

; void OpCLI(void)
OpCLI:
  cli
  ret

; void OpSTI(void)
OpSTI:
  sti
  ret

; void OpSTIHLT(void)
OpSTIHLT:
  sti
  hlt
  ret

;int OpIn8(int port)
OpIn8:
  mov edx, [esp+4]
  mov eax, 0
  in al, dx
  ret

;int OpIn16(int port)
OpIn16:
  mov edx, [esp+4]
  mov eax, 0
  in ax, dx
  ret

;int OpIn32(int port)
OpIn32:
  mov edx, [esp+4]
  in eax, dx
  ret

; void OpOut8(int port, int data)
OpOut8:
  mov edx, [esp+4]
  mov al, [esp+8]
  out dx, al
  ret

; void OpOut16(int port, int data)
OpOut16:
  mov edx, [esp+4]
  mov eax, [esp+8]
  out dx, ax
  ret

; void OpOut32(int port, int data)
OpOut32:
  mov edx, [esp+4]
  mov eax, [esp+8]
  out dx, eax
  ret

; int LoadEFlags(void)
LoadEFlags:
  pushfd
  pop eax
  ret

; void StoreEFlags(int eflags)
StoreEFlags:
  mov eax, [esp+4]
  push eax
  popfd
  ret

LoadGDTR:
	mov ax, [esp+4]
	mov [esp+6], ax
	lgdt [esp+6]
	ret

LoadIDTR:
	mov ax, [esp+4]
	mov [esp+6], ax
	lidt[esp+6]
	ret
