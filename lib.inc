section .text 
 
; Принимает код возврата и завершает текущий процесс
exit: 
    xor rax, rax,
    ret 

; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:
	xor rax, rax		; 0 -> rax(counter)
  .loop:			; cycle to search null-terminated symbol
	mov cl, [rdi + rax]	; fetch symbol
	test cl, cl		; maybe this symbol is 0 ->
	jz .exit		; -> and logical exit
				; next symbol and
	inc rax			; counter++
	jmp .loop		; next iteration
  .exit:
	ret

; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
	push rdi		; saving an adress of string
	call string_length	; find a length of string
	mov rdx, rax		; prepare length to a syscall
	pop rsi			; adress of str -> rsi	
	mov rax, 1		; "write" state to syscall
	mov rdi, 1		; "stdout" description
	syscall			; output the string
  .end: 
	ret

; Принимает код символа и выводит его в stdout
print_char:
	push rdi		; saving a value to stack
	mov rsi, rsp		; link to stack value
	mov rax, 1		; "write" state to syscall
	mov rdx, 1		; length of char = 1
	mov rdi, 1		; "stdout" description
	syscall
	pop rdi			; "pop" to reset rsp
  .end:    
	ret

; Переводит строку (выводит символ с кодом 0xA)
print_newline:
    xor rax, rax
    ret

; Выводит беззнаковое 8-байтовое число в десятичном формате 
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
print_uint:
	push r10		; 0->r10, r10 is counter
	xor r10, r10

	push r11		; 0->r11, r11 is local var
	mov r11, 10		; number / 10(r11)
	mov rax, rdi		;
  .divide_number:
	inc r10
	xor rdx, rdx		; 
	div r11			;
	add rdx, 30h		; number to ASCII code
	push rdx	
	cmp rax, 0		; checking for next iteration
	jz .out_number
	jmp .divide_number
  .out_number:
	pop rdi
	call print_char
	dec r10
	test r10, r10
	jnz .out_number	
  .end:
	pop r11		; return a value to r11
	pop r10		; return a value to r10
	ret

; Выводит знаковое 8-байтовое число в десятичном формате 
print_int:			; just try to use print_Uint function
  .print_sign:
	mov rax, rdi		; rdi -> rax, rax to check sign
	sar rax, 63
	and rax, 0x1
	cmp rax, 0
	je .print_num
  .prepare_negative_num:
	push rdi
	mov rdi, 2Dh
	call print_char
	pop rdi
	neg rdi
  .print_num:
	call print_uint
  .end:
	ret

; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
string_equals:
    xor rax, rax
    ret

; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:
    xor rax, rax
    ret 

; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор

read_word:
    ret
 

; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
parse_uint:
    xor rax, rax
    ret




; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был) 
; rdx = 0 если число прочитать не удалось
parse_int:
    xor rax, rax
    ret 

; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
; rdi -> на строку, rsi -> на буфер, rdx -> на длину буфера
string_copy:
	xor rax, rax		; 0 -> rax
	push rdi		; saving all arguments 
	push rsi		; to a stack
	push rdx		;
	call string_length	; calling a string_length function
	pop rdx			; to find a length of string
	pop rsi			; then length(of str) into a rax
	pop rdi			; then restore our arguments
	
	cmp rax, rdx		; check the buffer size for string placement 
	jg .errsize		; exit if str_size > buf_size
	
	push rax		; saving str size
	push r12		; r12 now is buffer
  .loop_copy:
	dec rax
	mov r12, [rdi+rax]	; symb_str ->	
	mov [rsi+rax], r12	; -> symb_buf
	cmp rax, 0		; is it last(first) symb?
	jz .end
	jmp .loop_copy

  .end:
	pop r12
	pop rax
  .errsize:
	mov rax, 0
	ret









