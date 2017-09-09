; Define some selectors.
SCodeSelector equ 0x08       ; System Code Selector
SDataSelector equ 0x10       ; System Data Selector
VideoSelector equ 0x18       ; Video Selector
TSS1Selector  equ 0x20
TSS2Selector  equ 0x28

; Define the location of read sectors num
ReadSectors   equ 0x0ff0

; Define the location of keyboard LED status information location
KeyboardLEDs  equ 0x0ff1

; Define the location of video mode information
VideoMode     equ 0x0ff2
ScreenX       equ 0x0ff4
ScreenY       equ 0x0ff6
VRAMOrigin    equ 0x0ff8

