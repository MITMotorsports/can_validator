/*
 * @brief LPC11xx SSP Registers and control functions
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

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/*Set up output clocks per bit for SSP bus*/
void Chip_SSP_SetClockRate(LPC_SSP_T *pSSP, uint32_t clk_rate, uint32_t prescale)
{}

/* SSP Polling Read/Write in blocking mode */
uint32_t Chip_SSP_RWFrames_Blocking(LPC_SSP_T *pSSP, Chip_SSP_DATA_SETUP_T *xf_setup)
{}

/* SSP Polling Write in blocking mode */
uint32_t Chip_SSP_WriteFrames_Blocking(LPC_SSP_T *pSSP, uint8_t *buffer, uint32_t buffer_len)
{}

/* SSP Polling Read in blocking mode */
uint32_t Chip_SSP_ReadFrames_Blocking(LPC_SSP_T *pSSP, uint8_t *buffer, uint32_t buffer_len)
{}

/* Clean all data in RX FIFO of SSP */
void Chip_SSP_Int_FlushData(LPC_SSP_T *pSSP)
{}

/* SSP Interrupt Read/Write with 8-bit frame width */
Status Chip_SSP_Int_RWFrames8Bits(LPC_SSP_T *pSSP, Chip_SSP_DATA_SETUP_T *xf_setup)
{}

/* SSP Interrupt Read/Write with 16-bit frame width */
Status Chip_SSP_Int_RWFrames16Bits(LPC_SSP_T *pSSP, Chip_SSP_DATA_SETUP_T *xf_setup)
{}

/* Set the SSP operating modes, master or slave */
void Chip_SSP_SetMaster(LPC_SSP_T *pSSP, bool master)
{}

/* Set the clock frequency for SSP interface */
void Chip_SSP_SetBitRate(LPC_SSP_T *pSSP, uint32_t bitRate)
{}

/* Initialize the SSP */
void Chip_SSP_Init(LPC_SSP_T *pSSP)
{}

/* De-initializes the SSP peripheral */
void Chip_SSP_DeInit(LPC_SSP_T *pSSP)
{}
