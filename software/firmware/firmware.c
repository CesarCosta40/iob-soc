//#include "stdlib.h"
#include "system.h"
#include "periphs.h"
#include "iob-uart.h"

#define N 100
#define N_DIG 21
unsigned char fibonacci[N][N_DIG];


void add(unsigned char* a, unsigned char* b, unsigned char* r){
  int carry = 0;
  int aux;
  for(int i = 0; i < N_DIG; i++){
    aux=a[i]+b[i]+carry;
    if(aux>9){
      carry=1;
      aux-=10;
    }else
      carry=0;
    r[i]=aux;
  }
}

void print(unsigned char* s){
  int a=1;
  for(int i = N_DIG-1; i >= 0; i--){
    if(s[i]==0&&a==1)
      continue;
    if(s[i]!=0)
      a=0;

    uart_printf("%c", s[i]+'0');
  }
  uart_printf("\n");
}


int main()
{
  //init uart 
  uart_init(UART_BASE,FREQ/BAUD);   
  //uart_printf("\n\n\nHello world!\n\n\n");
  char result[50];
  short aux;
  unsigned long long power;
  
  for(int i = 1; i < N_DIG; i++){
    fibonacci[0][i]=0;
    fibonacci[1][i]=0;
  }
  
  fibonacci[0][0]=1;
  fibonacci[1][0]=1;

  for(int i = 2; i < N; i++){
    add(fibonacci[i-2], fibonacci[i-1], fibonacci[i]);
  }
  
  for(int i = 0; i < N; i++){
    //uart_printf("\n%d: ", i+1);
    print(fibonacci[i]);

  }
} 
