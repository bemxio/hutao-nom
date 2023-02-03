print:
    pusha

print_loop: ; the comparison for string end (null byte)
    mov al, [bx] ; 'bx' is the base address for the string
    cmp al, 0
    je print_end ; if 'al' is the null byte

    mov ah, 0x0e
    int 0x10 ; 'al' already contains the char

    ; increment pointer and loop
    add bx, 1
    jmp print_loop

print_end:
    popa
    ret

println:
    call print
    mov ah, 0x0e

    ; print a line break
    mov al, 0x0a
    int 0x10

    ; print a carriage return
    mov al, 0x0d
    int 0x10

    call print_end