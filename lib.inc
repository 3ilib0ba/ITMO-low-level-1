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
	mov rsi, rdi		; saving an adress of string
	call string_length	; find a length of string
	mov rdx, rax		; prepare length to a syscall
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
	mov rdi, 11		; TEST 

	mov rcx, 61		;
	push r12		; r12 is a new buffer1
	
  .loop:
	dec rcx
	SAR rax, cl
	mov r12, rax
	and r12, 0xf
	cmp r12, 10
	jl .zero_to_ch
    .one_to_ch:
	push 1
	sub rax, 10
	SHL rax, cl
	jmp .iter_loop	
    .zero_to_ch:
	push 0
	SHL rax, cl
	jmp .iter_loop
     .iter_loop:
	cmp rcx, 0
	jz .exit
	jmp .loop
  .exit:	
	mov rdi, rax		;
	add rdi, 48
	call print_char
	ret

; Выводит знаковое 8-байтовое число в десятичном формате 
print_int:
    xor rax, rax
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









