/* 
 * File:   step_motor.h
 * Author: Anamaria
 *
 * Created on 01 decembrie 2017, 13:07
 */

#ifndef STEP_MOTOR_H
#define	STEP_MOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define _XTAL_FREQ  18432000


#define PIN1 LATCbits.LATC0
#define PIN2 LATCbits.LATC3
#define PIN3 LATCbits.LATC4
#define PIN4 LATCbits.LATC5
#define PIN1_direction TRISCbits.TRISC0
#define PIN2_direction TRISCbits.TRISC3
#define PIN3_direction TRISCbits.TRISC4
#define PIN4_direction TRISCbits.TRISC5
    
    
    
int flag_directie;
void turn_egs(void);
void command_turn(void);

#ifdef	__cplusplus
}
#endif

#endif	/* STEP_MOTOR_H */

