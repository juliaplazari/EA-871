/*
 * atividade5.c
 *
 * Created: 9/17/2019 8:51:41 AM
 * Author : júlia lázari
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

extern void atraso (short int q);

/*LED RGB: 0 -> R , 1 -> G , 2 -> B*/
unsigned char *drb = (unsigned char*) 0x24; //ponteiro no endereço 0x24 - DDRB
unsigned char *prtb = (unsigned char*) 0x25; //ponteiro no endereço 0x25 - PORTB

/*BOTÃO A - INT0*/
asm("sei"); // habilita globalmente interrupões
unsigned char *i0 = (unsigned char*) 0x3C;

/*BOTÃO B - PORTC*/
unsigned char *drc = (unsigned char*) 0x27; //ponteiro no endereço 0x27 - DDRC
unsigned char *pnc = (unsigned char*) 0x26; // ponteiro no endereço 0x26 - PINC 
unsigned char *pcmsk = (unsigned char*) 0x6C; // ponteiro no endereço 0x06 - PCMSK1 

/*INTERRUPÇÕES*/
unsigned char * sreg = (unsigned char *) 0x5f; //ponteiro no registrador sreg
unsigned char * eicra = (unsigned char *) 0x69; //ponteiro no registrador eicra
unsigned char * eimsk = (unsigned char *) 0x3d; //ponteiro noregistrador eimsk
unsigned char * pcicr = (unsigned char *) 0x68; //ponteiro no registrador pcicr

/*declaração de variáveis*/
short int q; //usada na rotina de atraso
int s; //sentido
int l; // auxiliar para reconhecer a borda do botão B
int i; //contador para os estados

/*INT0 - muda o tempo da rotina de atraso - botão A*/
ISR(INT0_vect){
	if (q == 125){
		q = 1000;}
	else{
		q = q/2;}
}

/*PCINT1 - muda o sentido - botão B*/
ISR(PCINT1_vect){
	if (l==0){
		if (s == 0){
			s = 1;}
		else if (s == 1){
			s = 0;}
		l = 1;
	}
	else{
		l = 0;
	}
}

int main(void)
{
/*variáveis*/
	i = 0;
	q = 1000;
	l = 0;
	s = 0;
	
/*setup*/
	*drb = *drb | 0x07; //setar bits 0 a 2 da portb como saída
	*i0 = *i0 | 0x01; //setar bit 0, responsável pelo int0
	*pcmsk = *pcmsk | 0x01; //setar bit 0 -PCINT8
	*pcicr = *pcicr | 0x02; // ativa pcie1 - PCINT8
	*eicra = *eicra | 0x03; //ISC01 e ISC00 = 1 
	*eimsk = *eimsk | 0x01; //habilita int0 
	*sreg = *sreg | 0x80; //ativa a interrupção global
	*prtb = *prtb & 0x00; //leds inicialmente com 0
    
	while (1) 
    {
/*sentido horário*/
		if (s == 0){
			atraso (q);
			if (i==7){
				i = 0;}
			else{
				i ++;}
		}
/*sentido anti - horário*/
		if (s == 1){
			atraso (q);
			if (i==0){
				i = 7;}
			else{
				i --;}
		}

/* de acordo com o valor de i vai para um estado, que irá setar os bits necessários do portb*/
if (i==0){
	*prtb = 0x00; /*apagado - 0  0  0*/
}
else if (i==1){ /*vermelho - 1  0  0*/
	*prtb = 0x01;
}
else if (i==2){ /*verde - 0  1  0*/
	*prtb = 0x02;
}
else if (i==3){ /*azul - 0  0  1*/
	*prtb = 0x04;
}
else if (i==4){ /*amarelo - 1  1  0*/
	*prtb = 0x03;
}
else if (i==5){ /*ciano - 0  1  1*/
	*prtb = 0x06;
}
else if (i==6){ /*magenta - 1  0  1*/
	*prtb = 0x05;
}
else if (i==7){ /*branco - 1  1  1*/
	*prtb = 0x07;
}

	}
}