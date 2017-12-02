/* 
 * File:   dht11.h
 * Author: Anamaria
 *
 * Created on 01 decembrie 2017, 12:41
 */

#ifndef DHT11_H
#define	DHT11_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _XTAL_FREQ  18432000
unsigned char  Check, T_byte1, T_byte2,
                RH_byte2, Ch ;
unsigned char  Temp, RH, Sum ; 
 int umiditate;
 
void StartSignal(void);

void CheckResponse(void);

char ReadData(void);           //used for DHT11

void DHT_result(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DHT11_H */

