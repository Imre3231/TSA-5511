#include <xc.h> 
#include"p18f4520.h"
#include "DELAY.h"
#include "CONFIG.h"
#include "i2c.h"
#include <stdlib.h>
 #include "FONT.h"
#include "lcd.h"
#include "FUNCTIONS.h"






#define Button1 PORTAbits.RA2
#define Button2 PORTAbits.RA3
#define RESET PORTDbits.RD3
#define FSYNC PORTDbits.RD2
                                                                                                                                             

unsigned char hi_byte, lo_byte;  
 long long data2;
 long long data;
unsigned int num = 174;
 
unsigned char txt7[16]={" ^       "}; 
unsigned char txt6[16]={"   ^     "};
unsigned char txt5[16]={"    ^    "};
unsigned char txt4[16]={"     ^   "};
unsigned char txt3[16]={"       ^ "}; 
unsigned char txt2[16]={"        ^ "};
unsigned char txt1[16]={"         ^"};

unsigned char buff[10] ;
unsigned char buff2[10] ; 
 signed int value = 0;
 signed int value2 = 0;
unsigned int x=00000;
unsigned int x2=00000;
unsigned int xhigh;
unsigned int xlow;
unsigned int ii;
unsigned int count=0;
unsigned char  buttonState1;
unsigned char  previousState1;
unsigned char  buttonState2;
unsigned char  previousState2;
unsigned int pll_freq;
unsigned int  freq =0;
 

void TSA5511(unsigned int freq )
{

 
          pll_freq = (freq );

          
          StartI2C();
          WriteI2C(0xC2);
         
          WriteI2C((pll_freq& 0xFF00) >> 8);
      
          WriteI2C(pll_freq & 0xFF);
        
          WriteI2C(0x8E);
          WriteI2C(0xff); 
          StopI2C();





}



int main()
{
  ADCON1 = 0x0F;  // Configure AN pins as digital    
  TRISB = 0; //0 as Output PIN
  TRISC = 0;
  TRISD = 0x00;
  TRISA  = 0xff; 
  OpenI2C(MASTER, SLEW_OFF);
    SSPADD = 40;
 
  delay_ms(10);

    LCD_init();

    CLS();
    LCD_cmd(LCD_LINE1+(1)); 
  
 
    
  xlow=Read_b_eep(1);
  xhigh=Read_b_eep(2);
   x=((xhigh<<8)|(xlow&0xff));
  if(x>(112*4)){x=(112*4); }
  if(x< (80*4)){x= (80*4); }
 
  
   TSA5511(x);
   
   PRINT( x);  
   while(1){
    

      if ( Button1==0)
      { x++; count++;if(count>30)count=30; 
      if(x>(112*4)){x=(112*4); }
      TSA5511(x);PRINT( x);  }
          
      
      if ( Button2==0)
      { x-- ; count++;if(count>30)count=30;  
      if(x< (80*4)){x= (80*4); }
      TSA5511(x);  PRINT( x);  }  
           
      if((Button1 ==1)&(Button2==1 )){ count=0; }
     
      
     if(count<15){delay_ms(50);}
     if(count>15){ if(count>25){delay_ms(10); } else {delay_ms(20);}} 
      
      
      xlow=(x&0xFF);
      xhigh=((x>>8)&0xFF);
      
      
      
      if(x!=x2){Write_b_eep(1,xlow);Write_b_eep(2,xhigh);  x2=x;}
      
      
      
   }
   
     
 }
 