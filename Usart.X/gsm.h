/* 
 * File:   gsm.h
 * Author: Anamaria
 *
 * Created on 01 decembrie 2017, 12:10
 */

#ifndef GSM_H
#define	GSM_H

#ifdef	__cplusplus
extern "C" {
#endif
#define _XTAL_FREQ  18432000
    
   int temp;
    unsigned char RH_byte1;
    
    
void sms_text(void);

void int_gsm(void);

void check_status_incubator(void);

#ifdef	__cplusplus
}
#endif

#endif	/* GSM_H */

