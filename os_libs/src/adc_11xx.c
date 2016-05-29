/*
 * @brief LPC11xx A/D conversion driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "chip.h"

#if !defined(CHIP_LPC1125)

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Get the number of clock for a full conversion */
STATIC INLINE uint8_t getFullConvClk(void)
{
}

/* Get divider value */
STATIC uint8_t getClkDiv(bool burstMode, uint32_t adcRate, uint8_t clks)
{
}

/* Set start mode for ADC */
void setStartMode(LPC_ADC_T *pADC, uint8_t start_mode)
{}

/* Get the ADC value */
Status readAdcVal(LPC_ADC_T *pADC, uint8_t channel, uint16_t *data)
{}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initialize the ADC peripheral and the ADC setup structure to default value */
void Chip_ADC_Init(LPC_ADC_T *pADC, ADC_CLOCK_SETUP_T *ADCSetup)
{}

/* Shutdown ADC */
void Chip_ADC_DeInit(LPC_ADC_T *pADC)
{}

/* Get the ADC value */
Status Chip_ADC_ReadValue(LPC_ADC_T *pADC, uint8_t channel, uint16_t *data)
{}

/* Get ADC Channel status from ADC data register */
FlagStatus Chip_ADC_ReadStatus(LPC_ADC_T *pADC, uint8_t channel, uint32_t StatusType)
{}

/* Enable/Disable interrupt for ADC channel */
void Chip_ADC_Int_SetChannelCmd(LPC_ADC_T *pADC, uint8_t channel, FunctionalState NewState)
{}

/* Select the mode starting the AD conversion */
void Chip_ADC_SetStartMode(LPC_ADC_T *pADC, ADC_START_MODE_T mode, ADC_EDGE_CFG_T EdgeOption)
{}

/* Set the ADC Sample rate */
void Chip_ADC_SetSampleRate(LPC_ADC_T *pADC, ADC_CLOCK_SETUP_T *ADCSetup, uint32_t rate)
{}

/* Set the ADC accuracy bits */
void Chip_ADC_SetResolution(LPC_ADC_T *pADC, ADC_CLOCK_SETUP_T *ADCSetup, ADC_RESOLUTION_T resolution)
{}

/* Enable or disable the ADC channel on ADC peripheral */
void Chip_ADC_EnableChannel(LPC_ADC_T *pADC, ADC_CHANNEL_T channel, FunctionalState NewState)
{}

/* Enable burst mode */
void Chip_ADC_SetBurstCmd(LPC_ADC_T *pADC, FunctionalState NewState)
{}

/* Read the ADC value and convert it to 8bits value */
Status Chip_ADC_ReadByte(LPC_ADC_T *pADC, ADC_CHANNEL_T channel, uint8_t *data)
{}

#endif /* !defined(CHIP_LPC1125) */
