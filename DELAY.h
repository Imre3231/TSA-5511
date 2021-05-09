#include <xc.h>

void delay_ms(int x)
{
   int i, j;
   for(i=0;i<x;i++)
      {
       for(j=0;j<1000;j++){   /**Some delay***/   }
      }      
      
}



void delay_us(int x)
{
   int i, j;
   for(i=0;i<x;i++)
      {
       for(j=0;j<2;j++){   /**Some delay***/   }
      }      
      
}