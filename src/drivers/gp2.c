/**
 ********************************************************************
 * @file    gp2.c
 * @author  Fabien DEPRAETRE <depraetref@gmail.com>
 * @version V1.1
 * @date    10-Mai-2015
 * @brief   This file provides functions for reading GP2 values
 ********************************************************************
 * @attention
 *
 * This file is part of LIBAUSBEE.
 * 
 * LIBAUSBEE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * LIBAUSBEE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with LIBAUSBEE.  If not, see <http://www.gnu.org/licenses/>.
 *
 * <h2><centor>&copy;  Copyright 2013-2014 (C) EIRBOT </center></h2>
 ********************************************************************
 */

/* Includes */
#include <AUSBEE/gp2.h>

/*
 * ADC 1 -> PF3
 * ADC 2 -> PF4
 * ADC 3 -> PF5
 * ADC 4 -> PF10
 * ADC 5 -> PC4
 * ADC 6 -> PC5
 * ADC 7 -> PB0
 * ADC 8 -> PB1
 *
 * */


void ausbee_init_struct_GP2(ausbee_GP2* GP2,uint8_t GP2_number)
{

  switch(GP2_number)
  {
    case 1:
      GP2->GPIOx = GPIOF;
      GP2->ADCx = ADC3;
      GP2->GPIO_Pin = 3;
      GP2->ADC_Channel = ADC_Channel_9;
      break;
    case 2:
      GP2->GPIOx = GPIOF;
      GP2->ADCx = ADC3;
      GP2->GPIO_Pin = 4;
      GP2->ADC_Channel = ADC_Channel_14;
      break;
    case 3:
      GP2->GPIOx = GPIOF;
      GP2->ADCx = ADC3;
      GP2->GPIO_Pin = 5;
      GP2->ADC_Channel = ADC_Channel_15;
      break;
    case 4:
      GP2->GPIOx = GPIOF;
      GP2->ADCx = ADC3;
      GP2->GPIO_Pin = 10;
      GP2->ADC_Channel = ADC_Channel_8;
      break;
    case 5:
      GP2->GPIOx = GPIOC;
      GP2->ADCx = ADC1;// ADC12 sur datasheet
      GP2->GPIO_Pin = 4;
      GP2->ADC_Channel = ADC_Channel_12;
      break;
    case 6:
      GP2->GPIOx = GPIOC;
      GP2->ADCx = ADC1;
      GP2->GPIO_Pin = 5;
      GP2->ADC_Channel = ADC_Channel_15;
      break;
    case 7:
      GP2->GPIOx = GPIOB;
      GP2->ADCx = ADC1;
      GP2->GPIO_Pin = 0;
      GP2->ADC_Channel = ADC_Channel_8;
      break;
    case 8:
      GP2->GPIOx = GPIOB;
      GP2->ADCx = ADC1;
      GP2->GPIO_Pin = 1;
      GP2->ADC_Channel = ADC_Channel_9;
      break;
    default:
      break;
  }
  GP2->value = 0;
}
void ausbee_init_GP2(ausbee_GP2* GP2)
{

  // Structure nécessaire pour l'initialisation de l'ADC

  GPIO_InitTypeDef      GPIO_InitStruct;
  ADC_InitTypeDef       ADC_InitStruct;
  ADC_CommonInitTypeDef ADC_CommonInitStruct;


  // Activation de la clock sur l'adc correspondant à la demande
  if(GP2->ADCx == ADC1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
  else if (GP2->ADCx == ADC2)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
  else
  {
    if ( GP2->ADCx == ADC3)
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE);
  }

  // Activation de la clock sur le port de GPIO correspondante

  if(GP2->GPIOx == GPIOB)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
  else if(GP2->GPIOx == GPIOC)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
  else
  {
    if(GP2->GPIOx == GPIOF)
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
  }

  GPIO_InitStruct.GPIO_Pin = GP2->GPIO_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;// désactive les pull up et pull down pour ne pas fausser la valeur de la mesure
  GPIO_Init(GP2->GPIOx, &GPIO_InitStruct);
  // Initialisation de l'adc
  ADC_CommonInitStruct.ADC_Mode             = ADC_Mode_Independent;// mode indépendant
  ADC_CommonInitStruct.ADC_Prescaler        = ADC_Prescaler_Div4;// divise la fréquence d'horloge par 4 ( pour la vitesse de calcul de l'adc
  ADC_CommonInitStruct.ADC_DMAAccessMode    = ADC_DMAAccessMode_Disabled;// pas d'accès DMA
  ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;

  ADC_CommonInit(&ADC_CommonInitStruct);



  ADC_InitStruct.ADC_ContinuousConvMode   = DISABLE;
  ADC_InitStruct.ADC_ScanConvMode         = DISABLE;
  ADC_InitStruct.ADC_Resolution           = ADC_Resolution_8b;// résolution 8 bits
  ADC_InitStruct.ADC_ExternalTrigConv     = ADC_ExternalTrigConvEdge_None;
  ADC_InitStruct.ADC_DataAlign            = ADC_DataAlign_Right;
  ADC_InitStruct.ADC_NbrOfConversion      = 1;// 1 conversion à la fois
  ADC_Init(GP2->ADCx,&ADC_InitStruct);

  ADC_Cmd(GP2->ADCx,ENABLE);
 
}

void ausbee_read_GP2(ausbee_GP2* GP2)
{

  uint8_t unblock = 1;

  ADC_RegularChannelConfig(GP2->ADCx, GP2->ADC_Channel, 1, ADC_SampleTime_56Cycles);

  // Start the conversion
  ADC_SoftwareStartConv(GP2->ADCx);

  // Wait until conversion completion
  while((ADC_GetFlagStatus(GP2->ADCx, ADC_FLAG_EOC) == RESET));// && unblock != 0xFF)
  {
//    unblock = (unblock<<1) +1;
  }

  GP2->value = ADC_GetConversionValue(GP2->ADCx);

}

uint16_t ausbee_GP2_get_value(ausbee_GP2* GP2)
{
  return GP2->value;
}
/*
void ausbee_get_distance_GP2(ausbee_GP2* GP2)
{

}
*/

