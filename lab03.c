/*
 * GPIO.c
 *
 * Created: 9/6/2019 11:23:08 AM
 * Author : Júlia Lázari
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL

#include <util/delay.h>

/*botão*/
unsigned char *drc = (unsigned char*) 0x27; /*ponteiro no endereço 0x27 - DDRC*/
unsigned char *pnc = (unsigned char*) 0x26; /* ponteiro no endereço 0x26 - PINC */

/*display - 7 segmentos nos pinos 1 a 7 da porta D*/
unsigned char *drd = (unsigned char*) 0x2A; /* ponteiro no endereço 0x2A - DDRD*/
unsigned char *prtd = (unsigned char*) 0x2B; /* ponteiro no endereço 0x2B - PORTD */

/*Resistor de pull up*/
unsigned char *prtc = (unsigned char*) 0x28; /* ponteiro no endereço 0x28 - PORTC */
unsigned char *pullup = (unsigned char*) 0x55;

/*para o tx*/
unsigned char *tx = (unsigned char*) 0xC1; /*ponteiro no endereço 0xC1*/

/*estados para o display*/
void estado_zero(){ /* segmentos a,b,c,d,e,f acesos*/
	*prtd = *prtd | 0x02; /*seg a*/
	*prtd = *prtd | 0x04; /*seg b*/
	*prtd = *prtd | 0x08; /*seg c*/
	*prtd = *prtd | 0x10; /*seg d*/
	*prtd = *prtd | 0x20; /*seg e*/
	*prtd = *prtd | 0x40; /*seg f*/
	*prtd = *prtd & 0x7F; /*seg g*/
}

void estado_um(){/* segmentos b,c acesos*/
	*prtd = *prtd & 0xFD; /*seg a*/
	*prtd = *prtd | 0x04; /*seg b*/
	*prtd = *prtd | 0x08; /*seg c*/
	*prtd = *prtd & 0xEF; /*seg d*/
	*prtd = *prtd & 0xDF; /*seg e*/
	*prtd = *prtd & 0xBF; /*seg f*/
	*prtd = *prtd & 0x7F; /*seg g*/
}

void estado_dois(){/* segmentos a,b,d,e,g acesos*/
	*prtd = *prtd | 0x02; /*seg a*/
	*prtd = *prtd | 0x04; /*seg b*/
	*prtd = *prtd & 0xF7; /*seg c*/
	*prtd = *prtd | 0x10; /*seg d*/
	*prtd = *prtd | 0x20; /*seg e*/
	*prtd = *prtd & 0xBF; /*seg f*/
	*prtd = *prtd | 0x80; /*seg g*/
}

void estado_tres(){/* segmentos a,b,c,d,g acesos*/
	*prtd = *prtd | 0x02; /*seg a*/
	*prtd = *prtd | 0x04; /*seg b*/
	*prtd = *prtd | 0x08; /*seg c*/
	*prtd = *prtd | 0x10; /*seg d*/
	*prtd = *prtd & 0xDF; /*seg e*/
	*prtd = *prtd & 0xBF; /*seg f*/
	*prtd = *prtd | 0x80; /*seg g*/
}
void estado_quatro(){/* segmentos b,c,f,g acesos*/
	*prtd = *prtd & 0xFD; /*seg a*/
	*prtd = *prtd | 0x04; /*seg b*/
	*prtd = *prtd | 0x08; /*seg c*/
	*prtd = *prtd & 0xEF; /*seg d*/
	*prtd = *prtd & 0xDF; /*seg e*/
	*prtd = *prtd | 0x40; /*seg f*/
	*prtd = *prtd | 0x80; /*seg g*/
}
void estado_cinco(){/* segmentos a,c,d,f,g acesos*/
	*prtd = *prtd | 0x02; /*seg a*/
	*prtd = *prtd & 0xFB; /*seg b*/
	*prtd = *prtd | 0x08; /*seg c*/
	*prtd = *prtd | 0x10; /*seg d*/
	*prtd = *prtd & 0xDF; /*seg e*/
	*prtd = *prtd | 0x40; /*seg f*/
	*prtd = *prtd | 0x80; /*seg g*/
}
void estado_seis(){/* segmentos a,c,d,e,f,g acesos*/
	*prtd = *prtd | 0x02; /*seg a*/
	*prtd = *prtd & 0xFB; /*seg b*/
	*prtd = *prtd | 0x08; /*seg c*/
	*prtd = *prtd | 0x10; /*seg d*/
	*prtd = *prtd | 0x20; /*seg e*/
	*prtd = *prtd | 0x40; /*seg f*/
	*prtd = *prtd | 0x80; /*seg g*/
}
void estado_sete(){/* segmentos a,b,c acesos*/
	*prtd = *prtd | 0x02; /*seg a*/
	*prtd = *prtd | 0x04; /*seg b*/
	*prtd = *prtd | 0x08; /*seg c*/
	*prtd = *prtd & 0xEF; /*seg d*/
	*prtd = *prtd & 0xDF; /*seg e*/
	*prtd = *prtd & 0xBF; /*seg f*/
	*prtd = *prtd & 0x7F; /*seg g*/	
}
void estado_oito(){/* segmentos a,b,c,d,e,f,g acesos*/
	*prtd = *prtd | 0x02; /*seg a*/
	*prtd = *prtd | 0x04; /*seg b*/
	*prtd = *prtd | 0x08; /*seg c*/
	*prtd = *prtd | 0x10; /*seg d*/
	*prtd = *prtd | 0x20; /*seg e*/
	*prtd = *prtd | 0x40; /*seg f*/
	*prtd = *prtd | 0x80; /*seg g*/
}
void estado_nove(){/* segmentos a,b,c,d,f,g acesos*/
	*prtd = *prtd | 0x02; /*seg a*/
	*prtd = *prtd | 0x04; /*seg b*/
	*prtd = *prtd | 0x08; /*seg c*/
	*prtd = *prtd | 0x10; /*seg d*/
	*prtd = *prtd & 0xDF; /*seg e*/
	*prtd = *prtd | 0x40; /*seg f*/
	*prtd = *prtd | 0x80; /*seg g*/
}


int main(void)
{	/*botão*/
	*drc = *drc & 0x00; /*setar DDRC como entrada*/
	
	/*display*/
	*drd = *drd | 0xFE; /*or lógico para setar os bits de 1 a 7 como 1, isto é, como saída*/
	/*a saída no registrador 0x2B será alterada de acordo com o estado atual*/
	
	/*ativar resistor de pull up*/
	*prtc = *prtc | 0x01;
	*pullup = *pullup & 0xEF;
	
	/*arrumar tx*/
	*tx = *tx & 0xF7; 
	
	/*variável i funcionará como um contador, e indicará o estado para o 
	qual o programa deve ir, iniciando em 0*/
	int i;
	i = 0;
	
	
	/*a mudança de estado de solto para apertado deve ocasionar um 
	incremento no contador e a mudança no display*/
    while (1) { 
		if((*pnc & 0x01) == 0x01){ /*se botão solto*/
			_delay_ms (50);/*delay para o debounce*/
			if ((*pnc & 0x01) == 0x00){ /*se botão apertado*/
				_delay_ms (50); /*delay para o debounce*/
				if ((*pnc & 0x01) == 0x00){/*se continuar apertado*/
					if (i == 0x09){ /* se o contador estiver no estado final (i == 9)*/
						i = 0;	/*volta para o início*/
					}
					else{ /* caso contrário*/
						i++; /*incrementa contador*/
					}
				}
			}
		}
		/* de acordo com o valor de i vai para um estado, que irá acender os displays necessários*/
		if (i==0){
			estado_zero();
		}
		else if (i==1){
			estado_um();
		}
		else if (i==2){
			estado_dois();
		}	
		else if (i==3){
			estado_tres();
		}	
		else if (i==4){
			estado_quatro();
		}	
		else if (i==5){
			estado_cinco();
		}
		else if (i==6){
			estado_seis();
		}
		else if (i==7){
			estado_sete();
		}
		else if (i==8){
			estado_oito();
		}
		else if (i==9){
			estado_nove();
		}
	}
}

