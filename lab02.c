/* Buffer circular
 *
 * J�lia L�zari RA: 200298
 */

#include <stdio.h>
#include <ctype.h>

char buffer[5]; /*reserva 5 espa�os na mem�ria para o buffer*/
char *i; /*ponteiro que ser� utilizado no adionar_buffer*/
char *j; /*ponteiro que ser� utilizado no remover_buffer*/


void adicionar_buffer(char c) { /* incluir valor se for um n�mero */
			
			if(i <= &buffer[4]){ /* se o ponteiro est� no �ltimo endere�o do buffer ou antes*/					
				*i = c;	/*colocar o valor de c no endere�o do ponteiro*/
				i ++;} /*incrementar ponteiro*/				
		}

void remover_buffer() {
			
			j = &buffer[0]; /*ponteiro j inicialmente na posi��o buffer[0]*/
			int l; /*declara um inteiro*/
			l = 0;
			while (l<5){	/*fun��o ser� executada para l <5*/			
				*j = *(j+1);	/* deslocar buffer*/
				j ++; /*incrementa j*/
				l ++; /*incrementa l*/
			}
			if (i!=&buffer[0]){	/*se i n�o apontar para buffer[0]*/	
				i = i - 1; /*decrementa i*/
			}
		}

void imprimir_buffer () { 	
		int k; /*declara um inteiro*/
		for (k=0; k<5; k++){ /*para k menor que 5, sendo k incrementado a cada la�o*/
			if(&buffer[k] < (i-1)){ /*se buffer[k] anterior a �ltima posi��o imprime com espa�o*/
				printf("%c ", buffer[k]);	
			}
			if(&buffer[k]==(i-1)){	/*se buffer[k] a �ltima posi��o imprime sem espa�o*/
				printf("%c", buffer[k]);									
			}
		}
		printf("\n"); /*muda de linha*/
}

int main() {

  char c; /*entrada*/
  i = &buffer[0]; /*ponteiro i aponta inicialmente para o endere�o do buffer[0]*/
  
  do {
    scanf("%c", &c);
    if (c == '\n') break; /*se  c == \n encerra o c�digo*/
	
	if (isalpha(c)==0) {
		adicionar_buffer(c); /* se c um d�gito, ir para adicionar_buffer */
		}
	else {
		remover_buffer(c); /* se c uma letra, ir para remover_buffer */
		}
	imprimir_buffer(); /* independente do que ocorrer acima, ir para imprimir-buffer */							
							
  } while (1);

  return 0;
}
