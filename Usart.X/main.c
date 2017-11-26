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
char line1[] = " ";  //use for umiditi
char line2[]=  " "; //used for temperature

unsigned char  Check, T_byte1, T_byte2,
                RH_byte1, RH_byte2, Ch ;
 unsigned char  Temp, RH, Sum ; 
 int temp;
 int umiditate;
/*
                         Main application
 */

//FUNCTII PENTRU LCD

enum State_machine{
                  rot_eggs,
                  display_lcd,
                  read_hum,
                  read_temp,
                  send_sms,
                  set_heater,
                  none
                  };

void turn_egs()
{
    static unsigned char step_index;
    static unsigned int step_nr=1;
    //while (step_nr<300)   //in functie de valoarea pusa v-om sti cat se
                      //roteste motorul 
                      //steps = Number of steps in One Revolution  * Gear ratio  
                      //steps= (360°/5.625°)*64"Gear ratio" = 64 * 64 =4096 
       //{
        
        if((step_nr<1000)&&(flag_10_ms==1))
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

                flag_10_ms=0;
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

            flag_10_ms=0;
            }
        }
        else if(step_nr==1000)
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
    char smstext[]="";
    char umid[]="";
   static int sms_index=0;
    
        printf("AT+CSCS=\"GSM\"");
        putch(0x0d);
       __delay_ms(200);
         printf("AT+CMGS=\"0757494823\"");
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
/*
void sms_text()
{
    char smstext[]="";
    char umid[]="";
   static int sms_index=0;
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
        sprintf(smstext," Temper=%d      ", temp);
         printf(smstext);
        sprintf(umid," Umid=%d        ",RH_byte1);
        printf(umid);
        putch(26);
        putch(0x0d);
        sms_index++;
        }
        else if  (sms_index==3)
        {
            sms_index=0;
            flag_A=0;
            flag_B=0;
        }
       
        }
        flag_4000_ms==0;
}   
*/
void int_gsm()
{
    
   static int sms1_index;
   while(sms1_index<5)
   {
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


void StartSignal()
{
 TRISDbits.TRISD2 = 0;    //Configure RD0 as output
 PORTDbits.RD2 = 0;    //RD0 sends 0 to the sensor
 __delay_ms(18);
 PORTDbits.RD2 = 1;    //RD0 sends 1 to the sensor
 __delay_us(30);
 TRISDbits.TRISD2 = 1;    //Configure RD0 as input
  }

void CheckResponse()
 {
 Check = 0;
 __delay_us(40);
 if (PORTDbits.RD2  == 0){
 __delay_us(80);
 if (PORTDbits.RD2  == 1)   Check = 1;   __delay_us(40);}
 }
 
 
 char ReadData()           //used for DHT11
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
 
 void DHT_result()
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
            sprintf(line2,"Um=%d",x);
            
}
 
 
void main(void)
{
    char x=0;
    
    // initialize the device
    SYSTEM_Initialize();
    TRISCbits.TRISC2=0; // set as output for the sourse of heater
    ADC_StartConversion();
    PIN1_direction=0;  //pini folositi pentru control motorului pentru intoarcerea oualor
    PIN2_direction=0;
    PIN3_direction=0;
    PIN4_direction=0;
    //TRISB = 0b00000000; // Set RB0-7 as digital output
    //TRISD = 0x00;   //set as output
    ANSELD=ANSELD & 0b11100000; //RD0-RD4 setam ca pini digitali folositi pentru LCD si senzorul digital DHT11
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:
   // LATDbits.LATD1=0;
   // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
   
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
  // INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
   // INTERRUPT_PeripheralInterruptDisable();
    
    char incubator_state=none;
    TRISDbits.TRISD2 = 1;   //for the senzor dht11
   
    flag_directie=1;
    int_gsm();
    
    //TRISB=0;
    //TRISD=0;
    //ANSELB=0;
    //ANSELD=0;
    float volt;
    LCDInit(1);
    
    LCDClear();
    
    while (1)
    {
       // __delay_ms(300);
         if (flag_1000_ms==1)
        {
         TMR1_disable();
         StartSignal();
         CheckResponse();
        if(Check == 1)
        {
            DHT_result();
        //    send_command_byte(0x01); // Clear display
            ;
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
        
        
        
        if (flag_G==1)
        {
           if (flag_N==1)
            {
         
            turn_egs();
            
             }
               
        }
        
        if (flag_A==1)
        {
           if (flag_B==1)
            {
               
               sms_text();
            
     
             }
               
        }
        
        
       
       
        
       
        
    }
      
    
        return;
}

/**
 End of File
*/