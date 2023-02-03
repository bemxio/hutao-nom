[bits 16] ; 16-bit code
[org 0x7c00] ; bootloader offset

%include "src/bootloader/print.asm"

mov bx, MESSAGE
call println

mov bx, SIGNATURE
call println

; constants
MESSAGE db "Om nom nom, I ate your files!", 0
SIGNATURE db "- :HuTaoNom:", 0

times 510 - ($ - $$) db 0 ; pad to 510 bytes
dw 0xaa55 ; boot signature