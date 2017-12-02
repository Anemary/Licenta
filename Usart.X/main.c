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

#define _XTAL_FREQ  18432000
#define releu LATDbits.LATD4



extern char txt_receive[];

/*
                         Main application
 */

//FUNCTII PENTRU LCD




    



int comparare(int resistor_value)
{
	unsigned int res[]={3002,2689,2377,2136,1895,1707,1520,1374,1228,1114,1000,908,817,745,673,615,557,510,463,423,383};
	int result=1000;
    float dif=0,step=0;
	float table[25]={};
	for(int i=0;i<21;i++)
	{
		if((resistor_value<=res[i])&(resistor_value>=res[i+1]))	
		{
			dif=res[i]-res[i+1];
			step=dif/25;
			for(int j=0;j<25;j++)
			{
				
				table[j]=res[i]-j*step;
				
			}
			for(int j=0;j<25;j++)
			{
				if((resistor_value<=table[j])&(resistor_value>=table[j+1]))
				{
					result=(i*25+1*j);
					break;
				}
			}
		}
	}
	return result;
}
struct incubaator
        {
    char tip_oua[];
    float umiditate;
    float temperatura;
    int id_tip;
        }
;

void main(void)
{
    char x=0;
    
    // initialize the device
    SYSTEM_Initialize();
    TRISCbits.TRISC2=0; // set as output for the sourse of heater
    ADC_StartConversion();
   
    
  
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:
   
   // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
   
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
  // INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
   // INTERRUPT_PeripheralInterruptDisable();
    
    flag_directie=1;
    int_gsm();
    float volt;
    LCDInit(1);
    
    
    
    while (1)
    {/*
        if(flag_100_ms==1)
        {
            Keyboard_Manager();
            if (Check_key(BTN_OK_MASK)==1)
            {
                LCDClear();
                LCDWriteString(" btn ok         ");
            }
            if (Check_key(BTN_DOWN_MASK)==1)
            {
                LCDClear();
                LCDWriteString(" btn minus       ");
            }
            if (Check_key(BTN_UP_MASK)==1)
            {
                LCDClear();
                LCDWriteString(" btn PLUS       ");
            }
            
            flag_100_ms=0;
        }
       */
        //__delay_ms(300);
        
        
         if (flag_1000_ms==1)
        {
         TMR1_disable();
         StartSignal();
         CheckResponse();
        if(Check == 1)
        {
            DHT_result();
        
        }
        ADC_StartConversion();
        volt=(rez_conversie*4.887)/1.492;
       // volt=(rez_conversie*4.7461)/1.533;
       temp=comparare(volt);//conversie rezistenta->temperatura
       if (temp<300)
        
            LATCbits.LATC2=1;
        else 
            LATCbits.LATC2=0;
        LCDClear();
        LCDCmd(0xB0);
        LCDWriteString("Temper=  ");
         // LCDGotoXY(9,1);
        LCDWriteInt(temp,3);
        LCDCmd(0xC0);
        LCDWriteString("Umid=  ");
         // LCDGotoXY(9,2);
        LCDWriteInt(umiditate,3);
         
        flag_1000_ms=0;
        TMR1_enable(); 
        
        }
        command_turn();
        check_status_incubator();
        
        
  
    }
      
    
        return;
}

/**
 End of File
*/