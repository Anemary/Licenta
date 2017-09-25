/*
 * File:   main.c
 * Author: Nicku
 *
 * Created on 09 august 2017, 21:29
 */


#include <xc.h>
#include <string.h>
#include <stdio.h>





// PIN D2 REZERED FOR THE INPUT DIGIDAT OF THE DHT11
#pragma config FOSC = HS    // Oscillator EXTERN USING QUARTZ
//#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)
#define _XTAL_FREQ 18432000

#define STRLEN 12

 unsigned char t;
volatile unsigned char rcindex=0;
  char rcbuf[100];
 char ok[10];
 volatile unsigned char  AT_flag;
 char AT[]="AT";   // To initialize mode
 char noecho[]="ATE0";   // To stop echo
 
 char mode_text[]="AT+CMGF=1";   // to set text mode
 char mode_pin[]="AT+CPIN=\"1234\"";   // to set text mode
 char receive[]="AT+CNMI=2,2,0,0,0";
 char receive1[]="AT+CMGL=\"ALL\"";
 char char_mode[]="AT+CSCS=\"GSM\"";   // to set character mode
 char param[]="AT+CSMP=17,167,0,0";   // set the parameter of character
 char mobile_no[]="AT+CMGS=\"0757494823\"";   //use to set receinpent number and mesg
 char terminator=0x1A;     // chartacter form of control + z terminator character
 char mesg[]="dragule ";   // mesg we want to send
 char CMGR="AT+CMGR=4";
 
 

 
 int verify_AT(char rcbuf[])
 {
     return (strcmp(rcbuf,ok));
         
 }
void USART_init(void)
{
    TXSTAbits.TXEN = 1;     // enable transmitter
    TXSTAbits.BRGH = 1;     // high baud rate mode
    RCSTAbits.CREN = 1;     // enable continous receiving
    //SYNC=0;
   // BRG16=1;
    // configure I/O pins
    ANSELBbits.ANSB5 = 0;   // RX input type is digital
    TRISCbits.TRISC7 = 1;     // RX pin is input
    TRISCbits.TRISC6 = 1;     // TX pin is input (automatically configured)

    SPBRG=119;            // set baud rate to 9600 baud (4MHz/(16*baudrate))-1

    PIE1bits.RCIE = 1;      // enable USART receive interrupt
    RCSTAbits.SPEN = 1;     // enable USART
}

void USART_putc(unsigned char c)
{
    while (!TXSTAbits.TRMT); // wait until transmit shift register is empty
    TXREG = c;               // write character to TXREG and start transmission
}

void USART_puts(unsigned char *s)
{
    while (*s)
    {
        USART_putc(*s);     // send character pointed to by s
        s++;                // increase pointer location to the next character
    }
    USART_putc(0x0D);
}
void send_sms()
 {
USART_puts(mesg);
 __delay_ms(100);
 USART_putc(terminator);
 __delay_ms(3000);
 }
int main(void)
{
    //OSCCONbits.IRCF = 0x0D; // INTOSC frequency 4MHz

    USART_init();
    INTCONbits.PEIE = 1;    // enable peripheral interrupts
    INTCONbits.GIE = 1;     // enable interrupts
    TRISB=0x00;
    //TRISAbits.TRISA1=0;
  /// ANSELAbits.ANSA1=0;
    ANSELB=0x00;
    LATB=0x00;
    __delay_ms(1000);
  USART_puts(AT);
  
    __delay_ms(3000); 
   USART_puts(mode_pin);
  
    __delay_ms(3000);
   
     USART_puts(mode_text);
     
     __delay_ms(2000);
     USART_puts(CMGR);
  
    __delay_ms(3000);
    USART_puts(receive);
    
    // __delay_ms(3000);
    while(1)
    {
       
        
       //USART_puts(rcbuf); 
       //rcindex = 0;        // reset string index
      // USART_puts("O PULA");  // echo received string
       //__delay_ms(3000);
        
    }

    //return 0;
    
}

void interrupt ISR(void)
{
    USART_puts("O PULA");
    if (PIR1bits.RCIF)  // check if receive interrupt has fired
    {
        t = RCREG;      // read received character to buffer
      //  if((t=='+'||t=='C'||t=='M'||t=='T'))
      //  {
       rcbuf[rcindex] = t; // append received character to string
       rcindex++;          // increment string index    
        
       // }
       //  else
       // {
          //  rcindex = 0;        // reset string index
           // USART_puts(rcbuf);  // echo received string
       // }
        PIR1bits.RCIF = 0;      // reset receive interrupt flag
    }
    
}
