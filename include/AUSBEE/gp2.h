/**
 ********************************************************************
 * @file    encoder.h
 * @author  David BITONNEAU <david.bitonneau@gmail.com>
 * @author  Fabien DEPRAETRE
 * @version V1.2
 * @date    14-May-2015
 * @brief   Encoders driver definition file.
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
 * <h2><centor>&copy;  Copyright 2013-2015 (C) EIRBOT </center></h2>
 ********************************************************************
 */
#ifndef GP2_H
#define GP2_H


#include "AUSBEE/device.h"

#include <stdint.h>

#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_adc.h>


typedef struct
{
  GPIO_TypeDef* GPIOx;
  uint32_t GPIO_Pin;
  ADC_TypeDef* ADCx;
  uint8_t ADC_Channel;
  uint16_t value;

}ausbee_GP2;

void ausbee_init_struct_GP2(ausbee_GP2* GP2, uint8_t GP2_number);
void ausbee_init_GP2(ausbee_GP2* GP2);
uint16_t ausbee_read_GP2(ausbee_GP2* GP2);

#endif // GP2_H
