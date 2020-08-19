/* Contador de bits
 *
 * Este programa conta o numero de bits em um byte
 */

#include <stdio.h>

int main() {

  unsigned char entrada;
  unsigned int tmp;
  unsigned int n_bits;
  unsigned char result;
  unsigned int i;
  

  /* Ler entrada em hexadecimal */
  scanf("%x", &tmp);
  entrada = (unsigned char)tmp;
  n_bits = 0;
  
  i = 0;
  while (i < 9) {
	  result = entrada & 0x01;
	  if (result == 0x01) n_bits = n_bits + 1;
	  entrada = entrada >> 1;	 
	  i++;
  }


  

  /* Escrever numero de bits */
  printf("%d\n", n_bits);
  return 0;
}
