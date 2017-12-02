#include "dht11.h"
#include "gsm.h"
#include <xc.h>

void StartSignal(void)
{
 TRISDbits.TRISD2 = 0;    //Configure RD0 as output
 PORTDbits.RD2 = 0;    //RD0 sends 0 to the sensor
 __delay_ms(18);
 PORTDbits.RD2 = 1;    //RD0 sends 1 to the sensor
 __delay_us(30);
 TRISDbits.TRISD2 = 1;    //Configure RD0 as input
  }


void CheckResponse(void)
 {
 Check = 0;
 __delay_us(40);
 if (PORTDbits.RD2  == 0){
 __delay_us(80);
 if (PORTDbits.RD2  == 1)   Check = 1;   __delay_us(40);}
 }

char ReadData(void)           //used for DHT11
 {
 char i, j;
 for(j = 0; j < 8; j++){
 while(!PORTDbits.RD2 ); //Wait until PORTD.F0 goes HIGH
 __delay_us(30);
 if(PORTDbits.RD2  == 0)
       i&= ~(1<<(7 - j));  //Clear bit (7-b)
 else {i|= (1 << (7 - j));  //Set bit (7-b)
 while(PORTDbits.RD2 );}  //Wait until PORTD.F0 goes LOW
 }
 return i;
 }

void DHT_result(void)
{
  RH_byte1 = ReadData();
            RH_byte2 = ReadData();
            T_byte1 = ReadData();
            T_byte2 = ReadData();
            Sum = ReadData();
           // LATB=T_byte1;
                if(Sum == ((RH_byte1+RH_byte2+T_byte1+T_byte2) & 0XFF))
                          {
                          Temp = T_byte1;
                          RH = RH_byte1;
                          }
            int x=RH_byte1;
            umiditate=RH_byte1;
            
}