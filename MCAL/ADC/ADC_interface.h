/*
 * ADC_interface.h
 *
 *  Created on: Sep 20, 2025
 *      Author: uts
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef enum
{
	channel0=0,
	channel1,
	channel2,
	channel3,
	channel4,
	channel5,
	channel6,
	channel7
}channels;
/*can't understand*/
typedef struct
{
	void (*NotificationFunc)(void);
	u8 *ChainChannel;
	u8 size;
	u16 *Result;
}CHAIN;

void ADC_voidInit(void);
void ADC_voidReadChannelSynch(u8 Copy_uuddtChannel,u16 *Copy_u8Reading);
void ADC_voidStratConversionAsynch(u8 Copy_uuddtChannel);
void ADC_voidSetCallBackFunc(u16 *Copy_u8Result,void (*ADC_CopyNotificationFunc)(void));
void ADC_voidStartChainConversion(CHAIN *Copy_chain);

void ADC_voidEnable(void);
void ADC_voidDisable(void);

void ADC_voidINTEnable(void);
void ADC_voidINTDisable(void);



#endif /* ADC_INTERFACE_H_ */
