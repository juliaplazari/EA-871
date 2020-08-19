/*
 * atividade8.c
 *
 * Created: 10/29/2019 8:36:55 AM
 * Author : j�lia l�zari
 */ 

/*
led incorporado pisca a cada 500ms
led do pino 12 pisca a cada 780ms
enviar mensagem a cada 5s
*/

/*Configura��o do temporizador
Interrup��o gerada a cada 0,1 ms
Prescale = 8
OCR2A = 200
temp int = (prescale * OCR2A)/CLK
0.1 ms = (8*200)/16*10^6
*/


/*BIBLIOTECAS*/
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int count_led1 = 0; //led incorporado -> 0,5 s
int count_led2 = 0; //led do pino 12 -> 0,78 
int count_msg = 0; //contador mensagem
char msg[] = "Atividade 8 � Interrupcoes temporizadas tratam concorrencia entre tarefas! \n"; //mensagem a ser enviada

void setup(){
	//configura��es temporizador
	TCCR2A = TCCR2A | 0b00000010; //modo ctc
	TCCR2B = TCCR2B | 0b00000010; //prescaler = 8
	TIMSK2 = TIMSK2 | 0b00000010; //compare match interrupt
	OCR2A = 200; //valor para que a interrup��o seja gerada a cada 0,1 ms
	
	//leds
	DDRB = DDRB | 0b0011000; //setar bit 4 e 5 como sa�da
	PORTB = 0x00; //leds come�am apagado
	
	//configurar BAUD -> velocidade de 38.400 bps
	UBRR0H = UBRR0H & 0xF0;
	UBRR0L = 25;
	//limpar bit de status
	UCSR0A = UCSR0A & 0xF0;
	//habilitar transmissor
	UCSR0B = UCSR0B | 0b0001000;
	//configurar data frame -> modo ass�crono, bit de paridade �mpar, bit de parada, 8 bits por frame
	UCSR0C = UCSR0C | 0b00111110;
	
	asm ("sei"); //interrup��es geral
}

void led1(){//led interno
	if ((PORTB & 0b00100000) == 0b00100000){//caso led esteja aceso
		PORTB = PORTB & 0b00010000; //apagar led (sem influenciar o outro led)
	}
	else{ //caso led esteja apagado
		PORTB = PORTB | 0b00100000; //acender (sem influenciar o outro led)
	}
}

void led2(){//led do pino 12
	if ((PORTB & 0b00010000) == 0b00010000){//caso led esteja aceso
		PORTB = PORTB & 0b00100000; //apagar led (sem influenciar o outro led)
	}
	else{//caso led esteja apagado
		PORTB = PORTB | 0b00010000; //acender (sem influenciar o outro led)
	}
}

ISR(TIMER2_COMPA_vect){
	if (count_led1 != 5000){ //enquanto contador1 n�o atingir 5000 (500ms)
		count_led1 ++; //incrementa
	}
	else{ //quando for
		count_led1 = 0; //zera contador
		led1(); //fun��o para trocar o estado do led 1
	}
	if (count_led2 != 7800){//enquanto contador2 n�o atingir 7800 (780ms)
		count_led2 ++; //incrementa
	}
	else{//quando for
		count_led2 = 0;//zera contador
		led2();//fun��o para trocar o estado do led 2
	}
}

int main(void)
{
		setup();
    
	while (1){
		count_msg = 0; //zera contador da mensagem
		while (msg[count_msg]!='\0')//enquanto n�o chegar ao final da mensagem
		{
			UDR0 = msg [count_msg]; //envia o caractere correspondente ao �ndice do contador
			while (!(UCSR0A & 0x20));//verifica se foi enviado
			count_msg ++; //incrementa contador
		}
		_delay_ms(5000); //aguarda 5s para enviar mensagem novamente
	}
}

