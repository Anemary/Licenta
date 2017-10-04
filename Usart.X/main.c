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
//extern int flag;
extern char txt_receive[];
/*
                         Main application
 */

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
    LATB=0x00;
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
           
            sms_text();
            flag_N=0;
            flag_G=0;
            __delay_ms(200);
        }
        
     
    }
}
/**
 End of File
*/