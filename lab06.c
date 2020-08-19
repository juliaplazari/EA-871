/*
 * atividade6.c
 *
 * Created: 10/7/2019 11:00:52 PM
 * Author : Julia Lazari
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

//ponteiros
unsigned char *ubrrh = (unsigned char*) 0xC5; //UBRR0H -> 0xC5
unsigned char *ubrrl = (unsigned char*) 0xC4; //UBRR0L -> 0xC4
unsigned char *ucsra = (unsigned char*) 0xC0; //UCSR0A -> 0xC0
unsigned char *ucsrb = (unsigned char*) 0xC1; //UCSR0A -> 0xC1
unsigned char *ucsrc = (unsigned char*) 0xC2; //UCSR0A -> 0xC2
unsigned char *udr = (unsigned char*) 0xC6; //UDR0 -> 0xC6

//mensagem a ser enviada
char msg[] = "I have a dream\nthat my four little children will one day live in a nation\nwhere they will not be judged by the color of their skin\nbut by the content of their character.\nI have a dream today.\n\n";
//mensagem de confirmação
char msg2 [] = "Mensagem transmitida com sucesso!\n\n";
//contador 
unsigned int conta;


int main(void)
{
    //configurar BAUD -> velocidade de 38.400 bps
		*ubrrh = 0;
		*ubrrl = 25;
	//limpar bit de status
		*ucsra = 0x00;
	//habilitar transmissor
		*ucsrb = 0b0001000;
	//configurar data frame -> modo assícrono, bit de paridade ímpar, bit de parada, 8 bits por frame
		*ucsrc = 0b00111110;
	
	//enviar mensagem
	while(1){
		conta = 0;
		while (msg[conta]!='\0'){//enquanto não chegar ao final da mensagem
			*udr = msg [conta]; //envia o caractere correspondente ao índice do contador
			while (!(*ucsra & 0x20));//verifica se foi enviado
			conta ++; //incrementa contador
		}
		
		conta = 0;
		while (msg2[conta]!='\0'){//enquanto não chegar ao final da mensagem
			*udr = msg2[conta]; //envia o caractere correspondente ao índice do contador
			while (!(*ucsra & 0x20)); //verifica se foi enviado
			conta ++; //incrementa contador
		}
		
		_delay_ms(5000);//aguarda 5s antes de enviar novamente
	}
}

