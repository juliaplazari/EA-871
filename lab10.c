/*
 * atividade10.c
 *
 * Created: 11/12/2019 8:22:33 AM
 * Author : Júlia Lázari
 */ 

/*BIBLIOTECAS*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

/*VARIÁVEIS*/
//mensagem
unsigned char msg [50];
unsigned int count_msg;
volatile unsigned int flag = 0;
//led
volatile unsigned int led = 0;
volatile unsigned int count_led = 0;
volatile unsigned int estado_led = 0;
//formas de onda
unsigned int onda;
volatile unsigned int count = 0;
unsigned char am[200] = {128, 141, 155, 168, 181, 192, 203, 211, 218, 223, 226, 226, 223, 218, 211, 201, 189, 176, 161, 145, 128, 110, 93, 76, 60, 46, 34, 23, 16, 10, 8, 9, 13, 19, 29, 41, 55, 71, 89, 108, 127, 147, 166, 185, 202, 217, 230, 241, 249, 253, 255, 253, 249, 241, 230, 217, 202, 185, 166, 147, 128, 108, 89, 71, 55, 41, 29, 19, 13, 9, 8, 10, 16, 23, 34, 46, 60, 76, 93, 110, 127, 145, 161, 176, 189, 201, 211, 218, 223, 226, 226, 223, 218, 211, 203, 192, 181, 168, 155, 141, 128, 114, 102, 91, 81, 72, 65, 60, 57, 55, 56, 58, 62, 67, 73, 81, 90, 99, 108, 118, 127, 137, 145, 153, 160, 166, 171, 175, 177, 178, 178, 177, 174, 171, 166, 161, 155, 148, 142, 135, 128, 121, 114, 108, 102, 97, 93, 89, 87, 86, 85, 86, 87, 89, 93, 97, 102, 108, 114, 121, 127, 135, 142, 148, 155, 161, 166, 171, 174, 177, 178, 178, 177, 175, 171, 166, 160, 153, 145, 137, 128, 118, 108, 99, 90, 81, 73, 67, 62, 58, 56, 55, 57, 60, 65, 72, 81, 91, 102, 114};
unsigned char sen[200] = {132, 136, 139, 143, 147, 151, 155, 159, 163, 167, 171, 174, 178, 182, 185, 189, 192, 196, 199, 202, 206, 209, 212, 215, 218, 220, 223, 226, 228, 231, 233, 235, 237, 239, 241, 243, 245, 246, 247, 249, 250, 251, 252, 253, 253, 254, 254, 255, 255, 255, 255, 255, 254, 254, 253, 253, 252, 251, 250, 249, 247, 246, 245, 243, 241, 239, 237, 235, 233, 231, 228, 226, 223, 220, 218, 215, 212, 209, 206, 202, 199, 196, 192, 189, 185, 182, 178, 174, 171, 167, 163, 159, 155, 151, 147, 143, 139, 136, 132, 128, 123, 119, 116, 112, 108, 104, 100, 96, 92, 88, 84, 81, 77, 73, 70, 66, 63, 59, 56, 53, 49, 46, 43, 40, 37, 35, 32, 29, 27, 24, 22, 20, 18, 16, 14, 12, 10, 9, 8, 6, 5, 4, 3, 2, 2, 1, 1, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 4, 5, 6, 8, 9, 10, 12, 14, 16, 18, 20, 22, 24, 27, 29, 32, 35, 37, 40, 43, 46, 49, 53, 56, 59, 63, 66, 70, 73, 77, 81, 84, 88, 92, 96, 100, 104, 108, 112, 116, 119, 123, 128};
unsigned char dente[200] = {1, 3, 4, 5, 6, 8, 9, 10, 11, 13, 14, 15, 17, 18, 19, 20, 22, 23, 24, 26, 27, 28, 29, 31, 32, 33, 34, 36, 37, 38, 40, 41, 42, 43, 45, 46, 47, 48, 50, 51, 52, 54, 55, 56, 57, 59, 60, 61, 62, 64, 65, 66, 68, 69, 70, 71, 73, 74, 75, 77, 78, 79, 80, 82, 83, 84, 85, 87, 88, 89, 91, 92, 93, 94, 96, 97, 98, 99, 101, 102, 103, 105, 106, 107, 108, 110, 111, 112, 113, 115, 116, 117, 119, 120, 121, 122, 124, 125, 126, 128, 129, 130, 131, 133, 134, 135, 136, 138, 139, 140, 142, 143, 144, 145, 147, 148, 149, 150, 152, 153, 154, 156, 157, 158, 159, 161, 162, 163, 164, 166, 167, 168, 170, 171, 172, 173, 175, 176, 177, 179, 180, 181, 182, 184, 185, 186, 187, 189, 190, 191, 193, 194, 195, 196, 198, 199, 200, 201, 203, 204, 205, 207, 208, 209, 210, 212, 213, 214, 215, 217, 218, 219, 221, 222, 223, 224, 226, 227, 228, 230, 231, 232, 233, 235, 236, 237, 238, 240, 241, 242, 244, 245, 246, 247, 249, 250, 251, 252, 254, 255};
unsigned char tri[200] = {3, 5, 8, 10, 13, 15, 18, 20, 23, 26, 28, 31, 33, 36, 38, 41, 43, 46, 48, 51, 54, 56, 59, 61, 64, 66, 69, 71, 74, 77, 79, 82, 84, 87, 89, 92, 94, 97, 99, 102, 105, 107, 110, 112, 115, 117, 120, 122, 125, 128, 130, 133, 135, 138, 140, 143, 145, 148, 150, 153, 156, 158, 161, 163, 166, 168, 171, 173, 176, 179, 181, 184, 186, 189, 191, 194, 196, 199, 201, 204, 207, 209, 212, 214, 217, 219, 222, 224, 227, 230, 232, 235, 237, 240, 242, 245, 247, 250, 252, 255, 255, 252, 250, 247, 245, 242, 240, 237, 235, 232, 230, 227, 224, 222, 219, 217, 214, 212, 209, 207, 204, 201, 199, 196, 194, 191, 189, 186, 184, 181, 179, 176, 173, 171, 168, 166, 163, 161, 158, 156, 153, 150, 148, 145, 143, 140, 138, 135, 133, 130, 128, 125, 122, 120, 117, 115, 112, 110, 107, 105, 102, 99, 97, 94, 92, 89, 87, 84, 82, 79, 77, 74, 71, 69, 66, 64, 61, 59, 56, 54, 51, 48, 46, 43, 41, 38, 36, 33, 31, 28, 26, 23, 20, 18, 15, 13, 10, 8, 5, 3};

void setup (){
	TCCR2A = TCCR2A | 0b10000011; //modo fast pwmm 
	TCCR2B = TCCR2B | 0b00000001; //no prescaler
	TIMSK2 = TIMSK2 | 0b00000001; //overflow interrupt
	DDRB = DDRB | 0b00101000; //setar bit 5 (led do arduino) e bit 3 (saída do OC2A)
	PORTB = PORTB & ~0x20; //led começa apagado
	
	//configurar BAUD -> velocidade de 9.600 bps
	UBRR0H = UBRR0H & 0x00;
	UBRR0L = 0x67;
	//limpar bit de status
	UCSR0A = UCSR0A & 0x00;
	//habilitar transmissor
	UCSR0B = UCSR0B | 0xD8;
	//configurar data frame -> modo assícrono, sem bit de paridade, 2 bits de parada, 8 bits por frame
	UCSR0C = UCSR0C | 0x0E;
	
	asm ("sei"); //interrupções geral
}


void forma_onda(){
	if (onda == 0x73){ //senoidal
		led = 62500; //controle do tempo que o led pisca
		strcpy( msg,"nda senoidal\n");//mensagem a ser transmitida
		UDR0 = 'O'; //incializar
	}
	
	else if (onda == 0x74){ //triangular
		led = 31250;//controle do tempo que o led pisca
		strcpy( msg,"nda triangular\n");//mensagem a ser transmitida
		UDR0 = 'O'; //incializar
	}
	
	else if (onda == 0x64){ //dente de serra
		led = 15625;//controle do tempo que o led pisca
		strcpy( msg,"nda dente-de-serra\n");//mensagem a ser transmitida
		UDR0 = 'O'; //incializar
	}
	
	else if (onda == 0x61){ //AM
		led = 7813;//controle do tempo que o led pisca
		strcpy( msg,"nda AM\n");//mensagem a ser transmitida
		UDR0 = 'O'; //incializar
	}
	else{
		strcpy( msg,"enhuma forma de onda selecionada\n"); //mensagem a ser transmitida
		UDR0 = 'N'; //incializar
	}
}


void piscar_led(){
	if (count_led == led){//se o contador do led atingiu o valor da variável de controle, mudar o estado
		if (estado_led == 0){ //se led apagado
			PORTB = 0b00100000; //acender
			estado_led  = 1; //indicar que está aceso
		}
		else{ //se led aceso
			PORTB = 0b00000000; //apagar
			estado_led = 0; //indicar que está apagado
			}
		count_led = 0; //zerar contador
	}	
}

ISR(USART_RX_vect){
	onda = UDR0; //variável onda recebe o valor digitado
	flag = 1; //flag para a mensagem
}

ISR(TIMER2_OVF_vect){
	
		if(onda == 0x73){//senoidal
			OCR2A = sen[count];
		}
		else if(onda ==  0x74){//triangular
			OCR2A = tri[count];
		}
		else if(onda ==  0x64){//dente de serra
			OCR2A = dente[count];
		}
		else if(onda ==  0x61){//onda am
			OCR2A = am[count];
		}
		else{
			OCR2A = 0; //sem forma de onda
			count_led = 0; //zerar contador do led
			PORTB = PORTB & ~0x20; //apagar led
			}
		count ++; //incrementar contador da forma de onda
	if(count == 200){//se esse tiver em 200
		count = 0; //zerar
	}
	//led	
	count_led ++; //incrementar contador
	piscar_led(); //chamar função de piscar o led
}


ISR(USART_TX_vect){

	if (msg[count_msg]!='\0'){//enquanto não chegar ao final da mensagem
		UDR0 = msg [count_msg]; //envia o caractere correspondente ao índice do contador
		count_msg ++; //incrementa contador
	}
	else{
		count_msg = 0; //quando chegar ao final da mensagem zera o contador
	}
}

int main(void)
{
    setup();
    while (1) 
    {
		if (flag == 1){ //se a flag é 1
			forma_onda(); //função da forma de onda
			flag = 0; //zerar flag
		}
    }
}



