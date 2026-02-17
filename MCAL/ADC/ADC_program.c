/*
 * ADC_program.c
 *
 *  Created on: Sep 20, 2025
 *      Author: uts
 */
#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"

#include"DIO_private.h"
#include"DIO_config.h"
#include"DIO_interface.h"

#include"ADC_private.h"
#include"ADC_config.h"
#include"ADC_interface.h"

#include"../GIE/GIE_private.h"
#include"../GIE/GIE_interface.h"
static u16 *ADC_pvGlobalResult=NULL;
static void (*ADC_pvGlobalNotificationFunc)(void)=NULL;
static u8 ADC_u8State=IDLE;
/*chain*/
static u8 ADC_u8ISRState ;//ISR (start conversion Asych & start chain conversion)
static u8 ADC_u8Index;
static u8 ADC_SizeOfChain;
static u8 *ADC_puChainchannel;


void ADC_voidInit(void)
{
	/* Select Reference Voltage  */
    #if(REFERENCE_VOLTAGE==AREF)
	CLR_BIT(ADMUX,REFS1);
	CLR_BIT(ADMUX,REFS0);
    #elif(REFERENCE_VOLTAGE==AVCC)
    CLR_BIT(ADMUX,REFS1);
	SET_BIT(ADMUX,REFS0);
    #elif(REFERENCE_VOLTAGE==INTERNAL)
    SET_BIT(ADMUX,REFS1);
	SET_BIT(ADMUX,REFS0);
    #endif
	/* Select Adjustment */
    #if(AJUSTMENT==RIGHT_ADJUSTMENT)
	CLR_BIT(ADMUX,ADLAR);
    #elif(AJUSTMENT==LEFT_ADJUSTMENT)
	SET_BIT(ADMUX,ADLAR);
    #endif

	/* Select PreScaler  */
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS0);


	/* Enable ADC */
    #if(ADC_STATUS==ADC_ENABLE)
	ADC_voidEnable();
    #elif(ADC_STATUS==ADC_DISABLE)
	ADC_voidDisable();
    #else
    #error "ADC STATUS ERROR CONFIG"
    #endif
	/*Enable Interrupt*/
    #if(ADCINT_STATUS==ADCINT_ENABLE)
	ADC_voidINTEnable();
    #elif(ADC_STATUS==ADCINT_DISABLE)
	ADC_voidINTDisable();
    #else
    #error "ADC INT STATUS ERROR CONFIG"
    #endif
}
void ADC_voidEnable(void)
{
	SET_BIT(ADCSRA,ADEN);

}
void ADC_voidDisable(void)
{
	CLR_BIT(ADCSRA,ADEN);

}

void ADC_voidINTEnable(void)
{
	SET_BIT(ADCSRA,ADIE);
	GIE_voidEnable();


}
void ADC_voidINTDisable(void)
{
	CLR_BIT(ADCSRA,ADIE);
}

void ADC_voidReadChannelSynch(channels Copy_uddtChannel,u16 *Copy_u8Reading)
{
	u16 TimeOut_Counter=NULL;
	u8 ADC_u8State=IDLE;
	if(ADC_u8State==IDLE)
	{
		ADC_u8State=BUSY;
		/* Select the Channel */
		ADMUX&=ADC_MASK;
		ADMUX|=Copy_uddtChannel;

		/* Start Conversion */
		SET_BIT(ADCSRA,ADSC);

		/* Polling on the ADC Flag */
		while(!GET_BIT(ADCSRA,ADIF)&&TimeOut_Counter<ADC_TIMEOUT)
		{
			TimeOut_Counter++;
		}
		if(GET_BIT(ADCSRA,ADIF)!=NULL)
		{
			/* Clear Flag */
			SET_BIT(ADCSRA,ADIF);
			/*store the conversion result*/
			*Copy_u8Reading=ADC;
	    }

	}
	ADC_u8State=IDLE;

	}
void ADC_voidStratConversionAsynch(u8 Copy_uddtChannel)
{

	if(ADC_u8State==IDLE)
	{
		ADC_u8State=BUSY;
		/* Select the Channel */
		ADMUX&=ADC_MASK;
		ADMUX|=Copy_uddtChannel;
		/* Start Conversion */
		SET_BIT(ADCSRA,ADSC);
        /*enable ADC Interrupt*/
		ADC_voidINTEnable();
	}
}
void ADC_voidSetCallBackFunc(u16 *Copy_u8Result,void (*ADC_CopyNotificationFunc)(void))
{
	ADC_pvGlobalResult=Copy_u8Result;

	ADC_pvGlobalNotificationFunc=ADC_CopyNotificationFunc;
}

void ADC_voidStartChainConversion(CHAIN *Copy_chain)
{
	if(ADC_u8State==IDLE)
	{
		ADC_u8State=BUSY;
		ADC_u8ISRState=CHAIN_CHANNEL_ASYNCH;
		ADC_u8Index=0;
		/*Local->Global*/
        ADC_SizeOfChain=Copy_chain->size;
		ADC_puChainchannel=Copy_chain->ChainChannel;
		ADC_pvGlobalResult=Copy_chain->Result;
		ADC_pvGlobalNotificationFunc=Copy_chain->NotificationFunc;
		/*select the channels of the chain*/
		ADMUX&=ADC_MASK;
		ADMUX|=ADC_puChainchannel[ADC_u8Index];

		/*start conversion*/
		SET_BIT(ADCSRA,ADSC);//Start conversion first sensor and go to convert next sensor
		/*enable interrupt*/
		ADC_voidINTEnable();


	}

}

void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	if((ADC_u8ISRState==SINGLE_CHANNEL_ASYNCH)&&(ADC_pvGlobalNotificationFunc!=NULL)){
		ADC_u8State=IDLE;
		ADC_pvGlobalNotificationFunc();
		ADC_voidINTDisable();
	}
	/*Start chain conversion */
	else
	{
		/*next sensor in chain*/
		ADC_u8Index++;
		if(ADC_u8Index==ADC_SizeOfChain)
		{
			/*ADC IDLE*/
			ADC_u8State=IDLE;
			/*set callback Func*/
			ADC_pvGlobalNotificationFunc();
			/*disable interrupt*/
			ADC_voidINTDisable();

		}
		else
		{
			/*select the next channel of chain*/
			ADMUX&=ADC_MASK;
			ADMUX|=ADC_puChainchannel[ADC_u8Index];
			/*start conversion*/
			SET_BIT(ADCSRA,ADSC);
		}




	}


}


