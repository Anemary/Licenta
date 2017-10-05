/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs 

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs  - 1.45
        Device            :  PIC16F1937
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"

#define PIN1 LATCbits.LATC0
#define PIN2 LATCbits.LATC3
#define PIN3 LATCbits.LATC4
#define PIN4 LATCbits.LATC5
#define PIN1_direction TRISCbits.TRISC0
#define PIN2_direction TRISCbits.TRISC3
#define PIN3_direction TRISCbits.TRISC4
#define PIN4_direction TRISCbits.TRISC5
//extern int flag;
extern char txt_receive[];
/*
                         Main application
 */


void turn_egs()
{
    int nr=0;
   if (nr<512)   //in functie de valoarea pusa v-om sti cat se
                      //roteste motorul 
                      //steps = Number of steps in One Revolution  * Gear ratio  
                      //steps= (360°/5.625°)*64"Gear ratio" = 64 * 64 =4096 
       {
         nr++;
        PIN4=1;//pin0
        PIN3=0;//pin3
        PIN2=0; //pin4
        PIN1=1;  ///pin5
        __delay_ms(5);
        PIN4=1;
        PIN3=1;
        PIN2=0;
        PIN1=0;
        __delay_ms(5);
        PIN4=0;
        PIN3=1;
        PIN2=1;
        PIN1=0;
        __delay_ms(5);
        PIN4=0;
        PIN3=0;
        PIN2=1;
        PIN1=1;
        __delay_ms(5);
          
        
        }     
}
void sms_text()
{
 
        
        printf("AT+CSCS=\"GSM\"");
        putch(0x0d);
        __delay_ms(4000);
         printf("AT+CMGS=\"0757494823\"");
         putch(0x0d);
        __delay_ms(4000);
        printf("hello");
        putch(26);
        putch(0x0d);
        __delay_ms(500);
}   

void int_gsm()
{
printf("AT");
        putch(0x0d);
        __delay_ms(4000);
        printf("AT+CPIN=\"1234\"");
        putch(0x0d);
        __delay_ms(4000);
        printf("AT+CMGF=1");
        putch(0x0d);
        __delay_ms(4000);
        printf("AT+CNMI=1,2,0,0,0");
        putch(0x0d);
        __delay_ms(4000);
        
}

void main(void)
{
    char x=0;
    PIN1_direction=0;  //pini folositi pentru control
    PIN2_direction=0;
    PIN3_direction=0;
    PIN4_direction=0;
    // initialize the device
    SYSTEM_Initialize();
   

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:
    
   // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
   
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    __delay_ms(3000);
     
      int_gsm();
      
      
    //sms_text();
    while (1)
    {
        if((flag_N==1)&&(flag_G==1))
        {
           turn_egs();
            //sms_text();
            flag_N=0;
            flag_G=0;
            __delay_ms(200);
        }
        
     
    }
}
/**
 End of File
*/