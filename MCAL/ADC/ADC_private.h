/*
 * ADC_private.h
 *
 *  Created on: Sep 20, 2025
 *      Author: uts
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADC_MASK 0b11100000
#define ADC_TIMEOUT 50000

#define ADMUX  *((volatile u8 *)(0x27))
#define ADLAR 5
#define REFS0 6
#define REFS1 7

#define ADCSRA *((volatile u8 *)(0x26))
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE  3
#define ADIF  4
#define ADATE 5
#define ADSC  6
#define ADEN  7

#define ADC    *((volatile u16*)(0x24))
#define SFIOR  *((volatile u8 *)(0x50))

#define AREF 0
#define AVCC 1
#define INTERNAL 2
/*Adjustment*/
#define RIGHT_ADJUSTMENT 0
#define LEFT_ADJUSTMENT 1
/*ADC Status*/
#define ADC_ENABLE  1
#define ADC_DISABLE 0
/*ADC Interrupt Status*/
#define ADCINT_ENABLE  1
#define ADCINT_DISABLE 0
/*ADC States */
#define IDLE 1
#define BUSY 0
/*ISR States*/
#define SINGLE_CHANNEL_ASYNCH 0
#define CHAIN_CHANNEL_ASYNCH 1


#endif /* ADC_PRIVATE_H_ */
