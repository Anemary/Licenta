/* 
 * File:   keyboard.h
 * Author: Nicku
 *
 * Created on 28 noiembrie 2017, 19:44
 */
//BTN_OK==RC2
//BTN_BACK==RC3
//BTN_UP==RD0
//BTN_DOWN==RD1

#ifndef KEYBOARD_H
#define	KEYBOARD_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #define BTN_OK_MASK 0b01000000
    #define BTN_UP_MASK 0b10000000
    #define BTN_DOWN_MASK 0b00100000
    
    volatile struct strKey_Pressed_{
        unsigned char btnOK:1;
        unsigned char btnUP:1;
        unsigned char btnDOWN:1;
    }strKey_Pressed;
   volatile  struct strKey_Released_
    {
        unsigned char btnOK:1;
        unsigned char btnUP:1;
        unsigned char btnDOWN:1;
    }strKey_Released;
   volatile struct strKey_Counts_
    {
        unsigned char btnOK:2;
        unsigned char btnUP:2;
        unsigned char btnDOWN:2;
    }strKey_Counts;
    
   
    
    
    void Check_KeyPressed(void);
    void Check_KeyReleased(void);
    void Keyboard_Manager(void);
    unsigned char Check_key(unsigned char btn_mask);

#ifdef	__cplusplus
}
#endif

#endif	/* KEYBOARD_H */

