#include <xc.h>
#include "lcd_hd44780_pic16.h"
#include "step_motor.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/eusart.h"



void turn_egs(void)
{ 

    //while (step_nr<300)   //in functie de valoarea pusa v-om sti cat se
                      //roteste motorul 
                      //steps = Number of steps in One Revolution  * Gear ratio  
                      //steps= (360°/5.625°)*64"Gear ratio" = 64 * 64 =4096 
       //{
    
     while((step_nr<350))
         {
      
            if(flag_directie==1)
            {
                  
      
                check_PowerSupply();                
                step_nr++;
                
                PIN4=1;//pin0
                PIN3=0;//pin3
                PIN2=0; //pin4
                PIN1=0;  ///pin5
                 __delay_ms(5);

                check_PowerSupply(); 
                PIN4=0;
                PIN3=1;
                PIN2=0;
                PIN1=0;
                 __delay_ms(5);
                 
                check_PowerSupply();                 
                PIN4=0;
                PIN3=0;
                PIN2=1;
                PIN1=0;
                 __delay_ms(5);

                check_PowerSupply(); 
                PIN4=0;
                PIN3=0;
                PIN2=0;
                PIN1=1;
                __delay_ms(5); 

                
            }
             if(flag_directie==0)
            {
               /* 
                if( (supplay_security<200))
                    { 
                      write_eeprom_int32(0x10, step_nr);
                      
                      eeprom_write(0x00,flag_directie);
                      
              
                      
                      
                      
                    }   
                   */  
                step_nr++;
                check_PowerSupply(); 
                PIN1=1;//pin0
                PIN2=0;//pin3
                PIN3=0; //pin4
                PIN4=0;  ///pin5                
                __delay_ms(5);
                
                check_PowerSupply(); 
                PIN1=0;
                PIN2=1;
                PIN3=0;
                PIN4=0;
                __delay_ms(5);
                
                check_PowerSupply();  
                PIN1=0;
                PIN2=0;
                PIN3=1;
                PIN4=0;
                __delay_ms(5);
                
                check_PowerSupply(); 
                PIN1=0;
                PIN2=0;
                PIN3=0;
                PIN4=1;
                __delay_ms(5);
                
                
                
                
                
                

                
            
            }  
     }
                check_PowerSupply();  
                PIN1=0;//pin0
                PIN2=0;//pin3
                PIN3=0; //pin4
                PIN4=0;  ///pin5
           if(step_nr==350)
           {
            flag_N=0;
            flag_G=0;
            step_nr=0;
          
           }

        if(flag_directie==1)
            {
                flag_directie=0;
            }
            else if(flag_directie==0)
            {
                flag_directie=1;
            }
            
             eeprom_write(0x00,flag_directie);  //save the value of flag_directie just in case a reset occurs
             write_eeprom_int32(0x01, step_nr);
}

void command_turn(void)
{
if (flag_G==1)
        {
           if (flag_N==1)
            {
        //  flag_directie=eeprom_read(0x00);
        //  step_nr=read_eeprom_int32(0x10);
          LCD_Init_apdatat();
          LCDWriteString(" Intoarcere oua!");
          turn_egs();
        //  eeprom_write(0x00,flag_directie);
             }
               
         }     



}
