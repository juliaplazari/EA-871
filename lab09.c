/*
 * atividade9.c
 *
 * Created: 11/5/2019 8:13:59 AM
 * Author : J�lia L�zari
 */ 

/*controlar intensidade de um led por PWM
intensidade cresce at� seu m�ximo em 1s
e depois reduz ao m�nimo em 1s tamb�m

como T = prescale*(OCR2A + 1)*255/(16Mhz)
e T = 1s
OCR2A = 245
Prescale = 256
T=1,004s
 */

/*BIBLIOTECAS*/
#include <avr/io.h>
#include <avr/interrupt.h>

int controle = 0;

void setup (){
	TCCR2A = TCCR2A | 0b00100011; //modo fast pwmm OC2B on compare match
	TCCR2B = TCCR2B | 0b00001110; //prescaler = 256
	TIMSK2 = TIMSK2 | 0b00000001; //overflow interrupt
	DDRD = DDRD | 0b00001000; //setar bit 3 (pino 11)
	OCR2A = 245; //carregar 245 no OCR2A (contador vai at� esse valor)
	asm ("sei"); //interrup��es geral
}

ISR(TIMER2_OVF_vect){
	if (controle == 0){ //se led est� acendendo
		if (OCR2B != 255){ //e OCR2B n�o � igual a 255
			OCR2B ++;} //incrementar
		else{
			controle = 1;} //quando OCR2B = 255, trocar valor da vari�vel controle
	}
	else{//se led est� apagando
		if (OCR2B != 0){ //e OCR2B n�o � 0
			OCR2B --;}//decrementar
		else{
			controle = 0;}//quando OCR2B = 0, trocar valor da vari�vel controle
	}
		
}

int main(void)
{
	setup();
    while (1) 
    {
    }
}

