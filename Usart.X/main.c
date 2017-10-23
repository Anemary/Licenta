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
int flag_directie;

#define PIN_RS LATDbits.LATD3 // USE FOR LCD
#define PIN_RW LATDbits.LATD1
#define PIN_E LATDbits.LATD0
#define releu LATDbits.LATD4


#define PIN1 LATCbits.LATC0
#define PIN2 LATCbits.LATC3
#define PIN3 LATCbits.LATC4
#define PIN4 LATCbits.LATC5
#define PIN1_direction TRISCbits.TRISC0
#define PIN2_direction TRISCbits.TRISC3
#define PIN3_direction TRISCbits.TRISC4
#define PIN4_direction TRISCbits.TRISC5
extern char txt_receive[];
char line1[] = "haha   ";  //use for umiditi
char line2[]=  "merge   "; //used for temperature
/*
                         Main application
 */

//FUNCTII PENTRU LCD

void send_nibble(unsigned char nibble);
void send_command_byte(unsigned char byte);
void send_data_byte(unsigned char byte);


 void init_lcd()
{
    PIN_RW = 0;
    PIN_RS = 0;
    PIN_E = 1;
    
//  initializare LCD;
      __delay_ms(16); // must be more than 15ms
    send_nibble(0b0011);
    __delay_ms(5); // must be more than 4.1ms
    send_nibble(0b0011);
    __delay_ms(1); // must be more than 100us
    send_nibble(0b0011);
    __delay_ms(5); // must be more than 4.1ms
    send_nibble(0b0010); // select 4-bit mode
    
}
 
 void comand_lcd()
{
    send_command_byte(0b00101000); // N=0 : 2 lines (half lines!), F=0 : 5x7 font
    send_command_byte(0b00001000); // Display: display off, cursor off, blink off
    send_command_byte(0b00000001); // Clear display
    send_command_byte(0b00000110); // Set entry mode: ID=1, S=0
   // send_command_byte(0b00001111); // Display: display on, cursor on, blink on
    send_command_byte(0x0C); // Display: display on, cursor off
}
 
 void send_nibble(unsigned char nibble)
{
   
     //Set RB0-3 without affecting RB4-7
    
    //nibble=nibble<<4;
     LATB = (LATB & 0xF0)+nibble;
   // LATB= nibble;
    
    __delay_ms(1);
    // Note: data is latched on falling edge of pin E
    PIN_E = 0;
    __delay_ms(1);
    PIN_E = 1;
    
    __delay_ms(2); // Enough time even for slowest command
}
 
 
 // Send a command byte (i.e. with pin RS low)
void send_command_byte(unsigned char byte)
{
    PIN_RS = 0;
    send_nibble(byte >> 4);
    send_nibble(byte & 0x0F);
    __delay_ms(1);
}
  
// Send a data byte (i.e. with pin RS high)
void send_data_byte(unsigned char byte)
{
    PIN_RS = 1;
    send_nibble(byte >> 4);
    send_nibble(byte & 0xF);
}
void turn_egs()
{
    static unsigned char step_index;
    static unsigned int step_nr=1;
    //while (step_nr<300)   //in functie de valoarea pusa v-om sti cat se
                      //roteste motorul 
                      //steps = Number of steps in One Revolution  * Gear ratio  
                      //steps= (360°/5.625°)*64"Gear ratio" = 64 * 64 =4096 
       //{
        
        if((step_nr<300)&&(flag_500_ms==1))
         {
            if(flag_directie==1)
            {
                step_nr++;
                if(step_index==0)
                {
                step_index++;
                PIN1=1;//pin0
                PIN2=0;//pin3
                PIN3=0; //pin4
                PIN4=0;  ///pin5
                }
                else if(step_index==1)
                {
                step_index++;
                PIN1=0;
                PIN2=1;
                PIN3=0;
                PIN4=0;
                }
                else if(step_index==2)
                {
                step_index++;
                PIN1=0;
                PIN2=0;
                PIN3=1;
                PIN4=0;
                }
                else if(step_index==3)
                {
                step_index++;
                PIN1=0;
                PIN2=0;
                PIN3=0;
                PIN4=1;
                }
                else if(step_index==4)
                {
                    step_index=0;
                }

                flag_500_ms=0;
            }
            else if(flag_directie==0)
            {
                step_nr++;
            if(step_index==0)
            {
            step_index++;
            PIN4=1;//pin0
            PIN3=0;//pin3
            PIN2=0; //pin4
            PIN1=0;  ///pin5
            }
            else if(step_index==1)
            {
            step_index++;
            PIN4=0;
            PIN3=1;
            PIN2=0;
            PIN1=0;
            }
            else if(step_index==2)
            {
            step_index++;
            PIN4=0;
            PIN3=0;
            PIN2=1;
            PIN1=0;
            }
            else if(step_index==3)
            {
            step_index++;
            PIN4=0;
            PIN3=0;
            PIN2=0;
            PIN1=1;
            }
            else if(step_index==4)
            {
                step_index=0;
            }

            flag_500_ms=0;
            }
        }
        else if(step_nr==300)
        { 
            flag_N=0;
            flag_G=0;
            step_nr=0;
            if(flag_directie==1)
            {
                flag_directie=0;
            }
            else if(flag_directie==0)
            {
                flag_directie=1;
            }
            step_index=0;

        }
        
}
        

void sms_text()
{
    int sms_index=0;
    if (flag_4000_ms==1)
    {
        if (sms_index==0)
        {
        printf("AT+CSCS=\"GSM\"");
        putch(0x0d);
        sms_index++;
        }
        else if (sms_index==1)
        {
         printf("AT+CMGS=\"0757494823\"");
         putch(0x0d);
         sms_index++;
        }
        else if (sms_index==2)
        {
        printf("iupii merge");
        putch(26);
        putch(0x0d);
        sms_index++;
        }
        else if  (sms_index==3)
        {
            sms_index=0;
        }
        flag_4000_ms==0;
        }
        
}   

void int_gsm()
{
   static int sms1_index;
    if (flag_4000_ms==1)
    {
        if (sms1_index==0)
        {
        printf("AT");
        putch(0x0d);
        sms1_index++;
        }
        else if (sms1_index==1)
        {
        printf("AT+CPIN=\"1234\"");
        putch(0x0d);
        sms1_index++;
        }
        else if (sms1_index==2)
        {
        printf("AT+CMGF=1");
        putch(0x0d);
        sms1_index++;
        }
        else if (sms1_index==3)
        {
        printf("AT+CNMI=1,2,0,0,0");
        putch(0x0d);
         sms1_index++;
        }
         else if (sms1_index==4)
        {
        printf("AT+CSCS=\"GSM\"");
        putch(0x0d);
        sms1_index++;
        }
        flag_4000_ms=0;
    }
     
        
}

int comparare(int resistor_value)
{
	unsigned int res[]={3002,2689,2377,2186,1895,1707,1520,1374,1228,1114,1000,908,817,745,673,615,557,496,463,425,387};
	int result=1000;
float dif=0,step=0;
	float table[25]={};
	for(int i=0;i<19;i++)
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



void main(void)
{
    char x=0;
    
    // initialize the device
    SYSTEM_Initialize();
    ADC_StartConversion();
    PIN1_direction=0;  //pini folositi pentru control motorului pentru intoarcerea oualor
    PIN2_direction=0;
    PIN3_direction=0;
    PIN4_direction=0;
    TRISB = 0b00000000; // Set RB0-7 as digital output
    TRISD = 0x00;   //set as output
    ANSELD=ANSELD & 0b11100000; //RD0-RD4 setam ca pini digitali folositi pentru LCD si senzorul digital DHT11
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
    
    init_lcd();
    comand_lcd();
    flag_directie=1;
    //sms_text();
    float volt;
    int temp;
    while (1)
    {
        
        
        if (flag_500_ms==1)
        {
       // volt=(rez_conversie*4.882)/1.614;
        volt=(rez_conversie*4.7461)/1.533;
        temp=comparare(volt);//conversie rezistenta->temperatura
        flag_500_ms=0;
        }
        
        
        
        int_gsm();
        send_command_byte(0x80); // Go to start of line 1
        __delay_ms(10);
        
        for (int n=0 ; line2[n]!=0 ; n++) send_data_byte(line2[n]);
        send_command_byte(0xC0); // Go to start of line 2
        __delay_ms(10);
        sprintf(line1," Temper=%d      ", temp);
        for (int n=0 ; line1[n]!=0; n++) send_data_byte(line1[n]);
        __delay_ms(10);
         
        
        if (flag_G==1)
        {
           if (flag_N==1)
            {
               
            turn_egs();
            //flag_G=0;
            //flag_N=0;
             }
               
        }
    }
       // turn_egs();
}

/**
 End of File
*/