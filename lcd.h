



#define HIGH 1
#define LOW 0
/****************** PIN Mapping *******************/
#define RS PORTDbits.RD7
#define RW PORTDbits.RD6
 
 
#define EN PORTDbits.RD5
#define BF PORTBbits.RB7
#define DATAPORT LATB
/************** Line Addr Mapping ******************/
#define LCD_LINE1 0x80
#define LCD_LINE2 0xC0
#define LCD_LINE3 0x94
#define LCD_LINE4 0xD4

#define CLRSCR 0x01
#define DISPLAY_ON 0x0C
#define DISPLAY_OFF 0x08
#define CURSOR_ON 0x0A
#define CURSOR_OFF 0x08
#define CURSOR_INC 0x06
#define MODE_8BIT 0x38
#define MODE_4BIT 0x28

void LCD_init(void);
void LCD_data(unsigned char data);
void LCD_cmd(unsigned char cmd);
void LCD_string(const char *ptr);
void LCD_isbusy(void);
void LCD_blink(void);




void LCD_init(void){
    TRISD=0x00;
    TRISB=0x00;
    LCD_cmd(MODE_8BIT);                   // 2 Line, 5x7 display, 8 bit
    LCD_cmd(CLRSCR);                      // clear the screen
    LCD_cmd(CURSOR_INC);                  // Cursor Incremetns on each write
    LCD_cmd(DISPLAY_ON | CURSOR_OFF);     // Display on and Cursor Off
    return;
}	

void LCD_data(unsigned char data){
    
    RS = HIGH;
    RW = LOW;
    EN = HIGH;
    DATAPORT = data;
    delay_us(10);
    EN = LOW;
}
	
void LCD_cmd(unsigned char cmd){
    
    RS = LOW;
    RW = LOW;
    EN = HIGH;
    DATAPORT = cmd;
    delay_us(10);
    EN = LOW;
}
 

void LCD_text(unsigned char *buffer)
{
    while(*buffer)              // Write data to LCD up to null
    {
        LCD_isbusy();           // Wait while LCD is busy
        LCD_data(*buffer);      // Write character to LCD
        buffer++;               // Increment buffer
    }
}


void LCD_isbusy(void)
{
    TRISBbits.TRISB7=1;         // Make D7 as input
    RS = LOW;
    RW = HIGH;
    EN = HIGH;
    delay_us(20);
    while(BF);
    TRISBbits.TRISB7=0;         // Back to Output
    EN = LOW;
}


void CLS (void)
{

LCD_cmd(CLRSCR); 


};



void intToStr(unsigned long value, char *str, char leading_zero, char digits)
{
    static long powers[9] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    char temp_digit,digit_cnt=10,first_non_zero=1;
 
    while (digit_cnt!=1)  // initially this value is 10 so the loop is executed 9 times
    {
        temp_digit = 48;  // ASCII 0
        while (value >= powers[digit_cnt-2])  // while number bigger than power value
        {
            value -= powers[digit_cnt-2];       // subtract the power value
            temp_digit++;                       // and increase variable
        }
        if (digit_cnt<=digits) *str++ = temp_digit; // only store requested number of digits  
 
        digit_cnt--;   // used as a counter to detect when we have reached the last char of the array
    }
    *str = (char) value+48; // assign the last character
 
    if (leading_zero==0)   // if parameter is set for no leading zeros
    {   str-=digits;    // go to the first char of the array
        while(first_non_zero==1)    // if the first digit of the number is not found
        {   str++;  // move to next array character
            if (*str=='0') *str=32;      // if digit value is ADCII 0 then replace with space (user selectable)
            else first_non_zero=0;      // else set the flag that the first digit of the number was found
 
        }
    }
}



void tostring3(unsigned long Number ,  char * out)
{
    
 
        char * pout = out;
        
        pout[9] = ((Number/1)%10)+48;
        pout[8] = ((Number/10)%10)+48;
        pout[7] = ((Number/100)%10)+48;
        
        pout[6] = 0x20;
        pout[5] = ((Number/1000)%10)+48;
        pout[4] = ((Number/10000)%10)+48;
        pout[3] = ((Number/100000)%10)+48;
        
        pout[2] = 0x20;
        pout[1] = ((Number/1000000)%10)+48;
        pout[0] = ((Number/10000000)%10)+48;
 
        
        pout[10] = 0;
   
}
