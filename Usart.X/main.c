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


extern int flag_on;
 
 char val;
  int valoare;
  int test_eeprom;
 uint16_t supplay_security;
extern char txt_receive[];
int temp_setata=37;
int virgula_temp_setata;
char temp_real,temp_virgula,temp_real1,temp_virgula1;
volatile unsigned char menu_flag=0;
/*
                         Main application
 */

//FUNCTII PENTRU LCD


void write_eeprom_int32(unsigned char addr, unsigned int data)
{
    eeprom_write(addr, data & 0xFF);
    eeprom_write(addr + 1, (data >> 8) & 0xFF);
    eeprom_write(addr + 2, (data >> 16) & 0xFF);
    eeprom_write(addr + 3, (data >> 24) & 0xFF);
}

uint32_t read_eeprom_int32(unsigned char addr)
{
    uint32_t result;

    result = eeprom_read(addr + 3);
    result <<= 8;
    result += eeprom_read(addr + 2);
    result <<= 8;
    result += eeprom_read(addr + 1);
    result <<= 8;
    result += eeprom_read(addr);
    return result;
}
    



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
void afisare_inf_lcd()
{
    //LCDClear();
       LCD_Init_apdatat();
       temp_virgula=temp%10;
       temp_real=temp/10;
       temp_virgula=temp_virgula;
       LCDCmd(0xB0);
       LCDWriteStringXY(0,0,"Temp=");
       LCDWriteInt(temp_real,2);
       LCDWriteString(".");
       LCDWriteInt(temp_virgula,1);
       LCDWriteString("C ");
       LCDCmd(0xC0);
      LCDWriteString("Umid=");
      // LCDWriteStringXY(1,1,"UMIDITATE=");
       LCDWriteInt(umiditate,3);
    // LCDWriteInt(step_nr,3);
         
      //  __delay_ms(3);
}

/*
void state_of_button()
{
 
 if (Check_key(BTN_OK_MASK)==1)
            {
     do 
                
     {
                
               
                    if (Check_key(BTN_UP_MASK)==1)
                    {
                        
                        temp_setata++;
                        
                    }
                    if (Check_key(BTN_DOWN_MASK)==1)
                       {
                        //LCDClear();
                        temp_setata--;
                        
                    }
                    LCDClear();
                    LCDWriteString("setare temp=");
                    LCDWriteInt(temp_setata,3);
                 //if (Check_key(BTN_OK_MASK)==1)
                 //   afisare_inf_lcd();
                
     }while(Check_key(BTN_OK_MASK)==0);   
         afisare_inf_lcd();            
            }
}
*/
void setare_temperatura()
{
    
    //LCDClear();
     LCD_Init_apdatat();
    // LCDWriteInt(flag_directie_read,1);
     LCDWriteString(" Temp setat este");
     /*
      LCDWriteString("F dir " );
      LCDWriteInt(flag_directie,1);
      LCDCmd(0xC0);
        */
     
     
     //afisare eeprom
     /*
       LCDCmd(0xC0);
       LCDWriteString("eeprom");
       LCDWriteInt(valoare,4);
       */
     LCDCmd(0xC0);
   
     LCDWriteInt(step_nr,3);
     
     
     
     LCDCmd(0xC0);

    
     LCDWriteString("   ");
     LCDWriteInt(temp_setata,2);
     LCDWriteString(".");
     LCDWriteInt(virgula_temp_setata,1);
     LCDWriteString("C"); 
     //LCDWriteString(".");
    // LCDWriteInt(temp_virgula1,1);
    
     __delay_ms(3);
}
void state_of_button()
{
   if (Check_key(BTN_OK_MASK)==1)
   {
       flag_directie=eeprom_read(0x00);
       LCD_Init_apdatat();
       LCDWriteString(" Intoarcere oua!");
        LCDCmd(0xC0);
   
     LCDWriteInt(step_nr,3);
       turn_egs();
       eeprom_write(0x00,flag_directie);
      //write_eeprom_int32(0x01,350);
	   menu_flag=~menu_flag;
        
	
   }
   else if((menu_flag==0)&(Check_key(BTN_UP_MASK)==1))
	{
       
      
      //incrementare temp
		virgula_temp_setata++; 
        if (virgula_temp_setata==10)
       {
           virgula_temp_setata=0;
           temp_setata++;
       }
        
	}
		else if((menu_flag==0)&(Check_key(BTN_DOWN_MASK)==1))
	{
            //decrementare temp
            virgula_temp_setata--; 
            if (virgula_temp_setata==-1)
       {
           virgula_temp_setata=9;
           temp_setata--;
       }
		 
      
	}
   if (menu_flag!=0 )
		{
			
			afisare_inf_lcd();
             
			
		}
		else if(menu_flag==0)
		{
			
		setare_temperatura();
			
		}
   
}
int btn=20;


void main(void)
{
    char x=0;
    int flag_scriere=0,flag_citire=0;
    // initialize the device
    SYSTEM_Initialize();
    TRISCbits.TRISC2=0; // set as output for the sourse of heater
     TRISCbits.TRISC1=0; // set as output for the FAN
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
    
    
    
    float volt,volt1,volt2;
    
    LCDInit(1);
    LCD_Init_apdatat();
    flag_directie_read=eeprom_read(0x00);
    step_nr=read_eeprom_int32(0x01);
    
    if((flag_directie_read!=0)&&(flag_directie_read!=1))
    {
       
        flag_directie=1;
        eeprom_write(0x00,flag_directie);
       
    }
    else 
        
        flag_directie=eeprom_read(0x00);
   if (step_nr==-1)
   {
       step_nr=0;
   }
   else 
       step_nr=read_eeprom_int32(0x01);
    if (step_nr)
    {
        turn_egs();
    }
   
  //  turn_egs();
    LCDWriteString("   Wait for  ");
     LCDCmd(0xC0);
     LCDWriteString("   initialize  ");
      int_gsm();
    __delay_ms(3000);
    // LCDCmd(0xB0);
    
    
    
    while (1)
    {
        
         LATCbits.LATC1=1;  //ventilator
       
        
         supplay_security=ADC_GetConversion(1); 
           
         if( (supplay_security<200)&& (flag_on==0))
           {
               flag_on=1;
               
             eeprom_write(0x00,flag_directie);
             //write_eeprom_int32(0x01, step_nr);
           }     
      
        
         if (flag_1000_ms==1)
        {
        
        LCDClear();
        
         TMR1_disable();
         StartSignal();
         CheckResponse();
        if(Check == 1)
        {
            DHT_result();
        
        }
        ADC_StartConversion();
       // volt=(rez_conversie*4.887)/0.5;
        
       // rez=ADC_conversii();
          //volt=(ADC_GetConversion(0)*1.97)/0.555;
        volt=(ADC_conversii()*1.97)/0.555;
       //  volt=(rez_conversie*1.97)/0.5; 
       // volt1=(rez_conversie*1.97)/0.5;
      //  volt2=(rez_conversie*1.97)/0.5;
       // volt=(rez_conversie*4.7461)/1.533;
       temp=comparare(volt);//conversie rezistenta->temperatura
      // temp=temp+comparare(volt1)+comparare(volt2);
       //temp=temp/3;
         
       if (temp<(temp_setata-10))
       {
            LATCbits.LATC2=1;
            //LATCbits.LATC1=1;
       }
       else if(temp>(temp_setata+10))
       {
           LATCbits.LATC2=0;
          // LATCbits.LATC1=0;
       }
       if (umiditate<50)
           LATAbits.LATA4=1;
            
        else 
            LATAbits.LATA4=0;
       
        flag_1000_ms=0;
        TMR1_enable(); 
        state_of_button();
        }
        
        
         
         if (flag_100_ms==1)
        {
            
            Keyboard_Manager();
            
            flag_100_ms==0;
         }
          // flag_directie_read=eeprom_read(0x00);
     command_turn();
     check_status_incubator();
  
       
        
        
        
        
        //TEST VERIFICARE SCRIERE IN EEPROM
    /*
        LCDClear();
        
        if( (supplay_security<200)&& (flag_on==0))
           {
               flag_on=1;
               
             //eeprom_write(0x00,flag_directie);
             write_eeprom_int32(0x07, 1112);
           }
        
        
        if(flag_scriere==0)
        {
            write_eeprom_int32(0x10,9573);
            //eeprom_write(0x03,12);
              flag_scriere=1;
        }
         
       
       // if(flag_citire==0)
       // {
            test_eeprom=read_eeprom_int32(0x10);
            
            //  test_eeprom=eeprom_read(0x03);
         //     flag_citire=1;
      //  }
       LCDWriteString("VAl eprom");
       LCDWriteInt(test_eeprom,4);
       LCDCmd(0xC0);
        LCDWriteString("VAl eprom");
         LCDWriteInt(read_eeprom_int32(0x07),4);
        __delay_ms(1000);
       */
    }
  

        return;  
}

/**
 End of File
*/