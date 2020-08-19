/*
 * atividade7.c
 *
 * Created: 10/8/2019 9:42:00 AM
 * Author : julia lazari
 */ 

/*BIBLIOTECAS*/
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

/*LED RGB: 0 -> R , 1 -> G , 2 -> B*/
unsigned char *drb = (unsigned char*) 0x24; //DDRB -> 0x24 
unsigned char *prtb = (unsigned char*) 0x25; //PORTB - > 0x25

/*INTERRUPÇÕES*/
unsigned char *sreg = (unsigned char*) 0x5f; //SREG -> 0X5F

/*CONFIGURAR UART*/
unsigned char *ubrrh = (unsigned char*) 0xC5; //UBRR0H -> 0xC5
unsigned char *ubrrl = (unsigned char*) 0xC4; //UBRR0L -> 0xC4
unsigned char *ucsra = (unsigned char*) 0xC0; //UCSR0A -> 0xC0
unsigned char *ucsrb = (unsigned char*) 0xC1; //UCSR0A -> 0xC1
unsigned char *ucsrc = (unsigned char*) 0xC2; //UCSR0A -> 0xC2
unsigned char *udr = (unsigned char*) 0xC6; //UDR0 -> 0xC6

/*BUFFER*/
volatile char buffer[10]; // reserva 10 espaços na memória
volatile int adicionar; // índice para adicionar
volatile int remover; // índice para remover
volatile int count_buffer; //contador do buffer

/*COMANDO - cor do led*/
volatile char comando; //variável onde será armazenada o valor removido

 /*MENSAGEM*/
volatile int count_msg = 0; //contador da mensagem
volatile int controle_msg = 1; //variável que indica se há uma mensagem a ser impressa
volatile int fim_msg = 1; //variável que indica o fim da mensagem impressa
char msg [50]; //mensagem a ser impressa

void setup(){
	//leds
	*drb = *drb | 0x07; //setar bits 0 a 2 da portb como saída
	*prtb = *prtb & 0x00; //leds inicialmente com 0 - apagado
	//interrupções
	*ucsrb = 0b11011000; //habilitar interupções -> TXCIE0 = RXCIEO = UDRIE0 = 1
	//configurar BAUD -> velocidade de 9.600 bps
	*ubrrh = 0;
	*ubrrl = 103;
	//limpar bit de status
	*ucsra = 0x00;
	//configurar data frame -> modo assícrono, sem bit de paridade, 2 bits de parada, 8 bits por frame
	*ucsrc = 0b00001110;
	//ativar interrupção global
	*sreg = *sreg | 0x80; 
}

void adicionar_buffer(char comando) {
	if(count_buffer < 10){ //se o bufffer não está cheio
		buffer[adicionar] = comando; //colocar o valor da variável no buffer
		adicionar = (adicionar + 1)%10; //incrementa índice de adição
		count_buffer ++; //incrementa contador
	}
}

void remover_buffer() {
	comando = buffer[remover]; //o que foi removido é armazenado na variável comando
	remover = (remover + 1)%10; //incrementa índice de remoção
	count_buffer --; //decrementa contador
}

void acender_led(){
	//comando r => acender vermelho
		if (comando == 0x72){
			*prtb = 0x01;
			strcpy( msg,"Comando : Acender LED - cor vermelha\n");
		}
			
	//comando g => acender verde
		else if (comando == 0x67){
			*prtb = 0x02;
			strcpy (msg, "Comando : Acender LED - cor verde\n");
		}
			
	//comando b => acender azul
		else if (comando == 0x62){
			*prtb = 0x04;
			strcpy (msg, "Comando : Acender LED - cor azul\n");
		}
		
	//comando y => acender amarelo
		else if (comando ==0x79){
			*prtb = 0x03;
			strcpy (msg, "Comando : Acender LED - cor amarela\n");
		}
		
	//comando c => acender ciano
		else if (comando == 0x63){
			*prtb = 0x06;
			strcpy (msg, "Comando : Acender LED - cor ciano\n");
		}
		
	//comando m => acender magenta
		else if (comando == 0x6D){
			*prtb = 0x05;
			strcpy (msg, "Comando : Acender LED - cor magenta\n");
		}
		
	//comando w => acender branco
		else if (comando == 0x77){
			*prtb = 0x07;
			strcpy (msg, "Comando : Acender LED - cor branca\n");
		}
		
	//qualquer outro caractere => comando inválido
		else{
			*prtb = 0x00;
			strcpy (msg,  "Comando incorreto\n");	
		}
	}
	
//interrupção "recepção completa"
ISR(USART_RX_vect){
	adicionar_buffer (*udr); //adicionar comando no buffer	
}

//interrupção "transmissão completa"
ISR(USART_TX_vect){	

		if (msg[count_msg]!='\0'){//enquanto não chegar ao final da mensagem
			*udr = msg [count_msg]; //envia o caractere correspondente ao índice do contador
			count_msg ++; //incrementa contador
			fim_msg = 0; //mensagem não chegou ao final
		}
		else{
			controle_msg = 1; //indica que não há mensagem a ser impressa
			fim_msg = 1; //indica que a impressão chegou ao fim
			count_msg = 0; //zera contador da mensagem
		}
}

int main(void){	
	
	setup();
 
    while (1){
		if (fim_msg == 1){ //caso uma mensagem esteja sendo impressa nada mais deve ser executado
			if(controle_msg == 1){//se a transmissão de uma mensagem foi encerrada
				*udr = '\0'; //incializa udr
				controle_msg = 0; //indica que há uma mensagem a ser impressa
				}
			if (count_buffer != 0){ //caso o buffer não esteja vazio
				remover_buffer(); //retira do buffer o comando a ser executado
				acender_led(comando); //executa o comando
				_delay_ms(200); //led aceso por 200 ms
				*prtb = 0x00; //apaga led
			}
			else{ //se o buffer vazio
				*prtb = 0x00; //led apagado
				strcpy (msg, "Vazio!\n"); //mensagem 'vazio'
		}
	}
   }
}

