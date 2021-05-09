
#include <xc.h>






 
void GLCD_FONT2 (unsigned int character,unsigned int x,unsigned int y,unsigned int space,const unsigned short *FONT);


void PRINT( unsigned long  Number)
{
    
       unsigned char buf1[8];
    
          LCD_cmd(LCD_LINE1+(1)); 
            
            Number=(Number)*25;
            
            buf1[0]=((Number/10000)%10)+48;
            buf1[1]=((Number/1000)%10)+48;
            buf1[2]=((Number/100)%10)+48 ;
            buf1[3]=(46);
            buf1[4]=((Number/10)%10)+48;
            buf1[5]=((Number/1)%10)+48; 
            buf1[6]=0;
            
            LCD_text(buf1);
            
            LCD_cmd((LCD_LINE1+(8))); 
            
             LCD_text("Mhz");

}




 void number_print(unsigned char *buffer,unsigned int x,unsigned int y );
 

unsigned char CHARACTER_WIDTH(unsigned int character,const unsigned short *FONT);
 

void Draw_Filled_Rectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,  unsigned int color);
void slideshow(void);
unsigned int CHARACTER_POSITON;

unsigned char CHARACTER_WIDTH(unsigned int character,const unsigned short *FONT)
{
    
    unsigned char    CHARACTER_W;    
    CHARACTER_W = FONT[(8+(character*4))];
    if(character==0){CHARACTER_W = FONT[(8+(4*4))]; };
    return CHARACTER_W;

}





void GLCD_FONT2 (unsigned int character,unsigned int x,unsigned int y,unsigned int space,const unsigned short *FONT)
{
    unsigned int    counter;
    unsigned int    i;
    unsigned int    ii;
    unsigned int    xx;
    unsigned int    STARTINGPOINT;
    unsigned int    CHARACTER_HEIGHT;
    unsigned int    CHARACTER_W;
    unsigned int    DATA;
    unsigned int    VERTICAL;
    unsigned int    HORIZONTAL;
    unsigned int    HORIZONTAL_COUNTER;
    unsigned int    VERTICAL_COUNTER;
    unsigned int    LOWBYTE;
    unsigned int    HIGHBYTE;
    unsigned int    LOW1;
    unsigned int    HIGH1;
    unsigned int    BYTEWIDTH; 
    
    LOW1=0;
    HIGH1=0;
    CHARACTER_HEIGHT = FONT[6];
    CHARACTER_W = FONT[(8+(character*4))];
    BYTEWIDTH=((CHARACTER_W/8));
    if((CHARACTER_W%8)!=0){BYTEWIDTH++; };
    
    LOWBYTE= FONT[(9+(character*4))];
    HIGHBYTE= FONT[(10+(character*4))];
    HIGH1=((HIGHBYTE<<8)&0xFF00);
    LOW1=((LOWBYTE&0x00FF));
    HORIZONTAL_COUNTER = CHARACTER_W ;
    VERTICAL_COUNTER = CHARACTER_HEIGHT ;
    STARTINGPOINT= ((LOW1)|(HIGH1));
    
        
    VERTICAL=0;
    HORIZONTAL=0;
    counter=0;      
    DATA = FONT[(STARTINGPOINT)];           
      for(xx=0;xx<CHARACTER_HEIGHT;xx++) 
        {   counter=0;
            for(ii=0;ii<BYTEWIDTH;ii++) 
            {                               
                for(i=0;i<8;i++)          
                {
                    
                    if(((DATA>>(i))&0x01)==0){ Pixel_Black( ( (counter+x)),(xx+y));};
                    if(((DATA>>(i))&0x01)==1){ Pixel_White( ( (counter+x)),(xx+y));};                          
                            VERTICAL++;
                            counter++;
                }
                    STARTINGPOINT++;
                    DATA = FONT[(STARTINGPOINT)];
            }                                  
                        
                    HORIZONTAL++; VERTICAL=0; 
                    for(i=0;i<space;i++) { Pixel_Black( (((counter+x)+i)),(HORIZONTAL+y));  }; //CLEAR END                           
        }   
        
    
   }    

                 
 void number_print(unsigned char *buffer,unsigned int x,unsigned int y )
{
    unsigned char count=0;
    while(*buffer)              // Write data to LCD up to null
    {
       
        GLCD_FONT2((*buffer-48),(x+(35*count)) ,y ,3,Tahoma35x54);      // Write character to LCD
        
        
        buffer++;  // Increment buffer 
        count++;
    }
}
 




 

void tohex(unsigned char in,  char * out)
{
  
    const char * hex = "0123456789ABCDEF";
    char * pout = out;
    
    
        
        pout[0] = hex[(in>>4) & 0xF];
        pout[1] = hex[ in     & 0xF];
       
        pout[2] = 0;
   
}



void tostring2(unsigned int Number ,  char * out)
{
    
 
        char * pout = out;
        pout[4] = ((Number/1)%10)+48;
        pout[3] = ((Number/10)%10)+48;
        pout[2] = ((Number/100)%10)+48;
        pout[1] = ((Number/1000)%10)+48;;
        pout[0] = ((Number/10000)%10)+48;;
        pout[5] = 0;
   
}




