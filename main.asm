;
; atividade4.asm
;
; Created: 9/11/2019 9:36:47 PM
; Author : J�lia L�zari
;

/* configurar LED */
	sbi 0x04, 5 ;setar bit 5 do DDRB - definir como sa�da

/* PAR�METROS */
		/*no caso a rotina deve gerar um atraso de 500ms */
	ldi r24, 0xF4 ;carregar par�metro em r24 
	ldi r25, 0x01 ;carregar par�metro em r25

/* acender e apagar led num intervalo de 500 ms */
led: 
	sbi 0x05, 5 ;seta bit 5 do PORTB - acende led
	call atraso ;chama rotina de atraso
	cbi 0x05, 5 ;zera bit 5 do PORTB - apaga led
	call atraso ;chama a rotina de atraso

/*rotina de atraso */
atraso:
		/*salvar valor dos registradores na pilha para que esses permane�am inalterados ap�s a rotina*/
	push r18
	push r19
	push r20
	push r24
	push r25
	
	parte1:
		cp r19, r24 ;compara o r19 com o r24 (par�metro)
			breq fimpt1 ; quando forem iguais encerra parte 1
		clr r20 ;clear no r20 para que o parte2 sempre comece com esse registrador no 0
		inc r19 ;incrementa o r19
		rjmp parte2 ;vai para o segunda parte
		rjmp parte1 ;repete primeira parte (qtd de repeti��es de acordo com o valor em r24)

		fimpt1:
			rjmp parte4 ;quando encerrar a parte1, vai para a parte 4 (lidar com o r25)

	parte2:
		cpi r20, 14 ;compara r20 com 14 (n�mero de vezes que essa parte deve ser executada)
			breq fimpt2 ;quando for igual encerra essa parte
		inc r20 ;incrementa o r20
		clr r18 ;clear no r18 para que a parte3 sempre comece com esse registrador no 0
		rjmp parte3 ;chama a parte3
		rjmp parte2 ;repete a segunda parte, essa ser� repetida 14 vezes para cada repeti��o da parte1

		fimpt2:
			rjmp parte1 ;retorna � primeira parte quando a segunda tiver sido executada 14 vezes

	parte3:
		cpi r18, 227 ;compara r18 com (n�mero de vezes que essa parte deve ser executada)
			breq fimpt3 ;quando for igual encerra parte 3
		inc r18 ;incrementar o r18
		rjmp parte3 ;repete parte3
	
		fimpt3:
			rjmp parte2 ;retorna � segunda parte quando a terceira tiver sido executada 227 vezes

	parte4:
		cpi r25,0 ;compara r25 e 0
			breq final ;quando iguais a rotina ser� encerrada
		dec r25 ;decrementa r25
		ldi r24, 0xFF ;carrega FF no r24, para que a parte1 gaste 255 ms para cada vez que for executada
		clr r19 ;clear no r19 para que a parte1 comece com ele zerado
		rjmp parte1 ;vai para a parte1
		
final:
		/*retornar os valores salvos na pilha para os registradores*/
	pop r25
	pop r24
	pop r20
	pop r19
	pop r18
	ret
