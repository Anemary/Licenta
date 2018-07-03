
#include <xc.h>
#include "keyboard.h"





void Keyboard_Manager(void)
{
    Check_KeyPressed();
    Check_KeyReleased();
}

void Check_KeyPressed(void)
{
    

    //Check all buttons if any of them are pressed
    
    if((PORTD & BTN_OK_MASK)==0)  //if key is pressed
    {
        if(strKey_Counts.btnOK<3) 
        strKey_Counts.btnOK++; 
    }
    else if(((PORTD & BTN_OK_MASK)!=0)&&(strKey_Counts.btnOK<3))   //if an bouncing effect has been detected reset the button counter
    {
        strKey_Counts.btnOK=0;
    }
    
    
    if((PORTD & BTN_UP_MASK)==0)
    {
        if(strKey_Counts.btnUP<3)
        strKey_Counts.btnUP++;
    }
    else if(((PORTD & BTN_UP_MASK)!=0)&&(strKey_Counts.btnUP<3))  //if an bouncing effect has been detected reset the button counter
    {
        strKey_Counts.btnUP=0;
    }
    
    
    if((PORTD & BTN_DOWN_MASK)==0)
    {
        if(strKey_Counts.btnDOWN<3)
        strKey_Counts.btnDOWN++;
    }
    else if(((PORTD & BTN_DOWN_MASK)!=0)&&(strKey_Counts.btnDOWN<3)) //if an bouncing effect has been detected reset the button counter
    {
        strKey_Counts.btnDOWN=0;
    }
    
    
}

void Check_KeyReleased(void)
{
    
    //Check if any of buttons have been pressed and if they were released
   
    if(((PORTD & BTN_OK_MASK)!=0)&&(strKey_Counts.btnOK==3))  //if key is pressed
    {
        
        strKey_Pressed.btnOK=1;
        strKey_Counts.btnOK=0;
    }
   
    if(((PORTD & BTN_UP_MASK)!=0)&&(strKey_Counts.btnUP==3))  //if key is pressed
    {
        
        strKey_Pressed.btnUP=1; 
        strKey_Counts.btnUP=0;
    }
    if(((PORTD & BTN_DOWN_MASK)!=0)&&(strKey_Counts.btnDOWN==3))  //if key is pressed
    {
        
        strKey_Pressed.btnDOWN=1; 
        strKey_Counts.btnDOWN=0;
    }
}

unsigned char Check_key(unsigned char btn_mask)
{ 
    //returns 1 if the button of the coresponding mask was pressed else will return 0   
  
    unsigned char btn_pressed=0;


    switch(btn_mask)
        {
        case BTN_OK_MASK:
                btn_pressed=strKey_Pressed.btnOK;
//                if(strKey_Pressed.btnOK==1)
                    strKey_Pressed.btnOK=0;
                break;
        
        case BTN_UP_MASK:
                btn_pressed=strKey_Pressed.btnUP;
             //   if(strKey_Pressed.btnUP==1)
                    strKey_Pressed.btnUP=0;
                break;
        case BTN_DOWN_MASK:
                btn_pressed=strKey_Pressed.btnDOWN;
            //    if(strKey_Pressed.btnDOWN==1)
                    strKey_Pressed.btnDOWN=0;
                break;
            default:
                btn_pressed=0;        
        }
    return btn_pressed;
            
}