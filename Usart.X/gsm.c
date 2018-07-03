
#include "gsm.h"
#include "lcd_hd44780_pic16.h"
#include "mcc_generated_files/eusart.h"
#include <xc.h>

     void sms_text(void)
{
     
     
     
    char smstext[]="";
    char umid[]="";
   static int sms_index=0;
    
        printf("AT+CSCS=\"GSM\"");
        putch(0x0d);
       __delay_ms(200);
         printf("AT+CMGS=\"0758426929\"");
         putch(0x0d);
        __delay_ms(600);
        
        sprintf(smstext," Temper=%d      ", temp);
         printf(smstext);
         
        sprintf(umid," Umid=%d        ",RH_byte1);
        printf(umid);
        __delay_ms(400);
        putch(26);
        putch(0x0d);
       
            sms_index=0;
            flag_A=0;
            flag_B=0;
        
}  

     void int_gsm(void)
{
    
            printf("AT");
            putch(0x0d);
            __delay_ms(3000);
            printf("AT+CPIN=\"0000\"");
            putch(0x0d);
            
            
            __delay_ms(5000);
            printf("AT+CMGF=1");
            putch(0x0d);
            __delay_ms(5000);
            printf("AT+CNMI=1,2,0,0,0");
            putch(0x0d);
            __delay_ms(5000);
            printf("AT+CSCS=\"GSM\"");
            putch(0x0d);
            __delay_ms(5000);
              
}
     
     
     void check_status_incubator(void)
     {
     if (flag_A==1)
        {
           if (flag_B==1)
            {
                 LCD_Init_apdatat();
                 LCDWriteString(" Trimitere sms");
                 sms_text();
               
             }
               
        }
     }