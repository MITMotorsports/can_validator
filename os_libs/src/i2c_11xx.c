/*
 * @brief LPC11xx I2C driver
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

#if !defined(CHIP_LPC110X)

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Control flags */
#define I2C_CON_FLAGS (I2C_CON_AA | I2C_CON_SI | I2C_CON_STO | I2C_CON_STA)
#define LPC_I2Cx(id)      ((i2c[id].ip))
#define SLAVE_ACTIVE(iic) (((iic)->flags & 0xFF00) != 0)

/* I2C common interface structure */
struct i2c_interface {
	LPC_I2C_T *ip;		/* IP base address of the I2C device */
	CHIP_SYSCTL_CLOCK_T clk;	/* Clock used by I2C */
	I2C_EVENTHANDLER_T mEvent;	/* Current active Master event handler */
	I2C_EVENTHANDLER_T sEvent;	/* Slave transfer events */
	I2C_XFER_T *mXfer;	/* Current active xfer pointer */
	I2C_XFER_T *sXfer;	/* Pointer to store xfer when bus is busy */
	uint32_t flags;		/* Flags used by I2C master and slave */
};

/* Slave interface structure */
struct i2c_slave_interface {
	I2C_XFER_T *xfer;
	I2C_EVENTHANDLER_T event;
};

/* I2C interfaces */
static struct i2c_interface i2c[I2C_NUM_INTERFACE] = {
	{LPC_I2C, SYSCTL_CLOCK_I2C, Chip_I2C_EventHandler, NULL, NULL, NULL, 0}
};

static struct i2c_slave_interface i2c_slave[I2C_NUM_INTERFACE][I2C_SLAVE_NUM_INTERFACE];

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Chip event handler interrupt based */
void Chip_I2C_EventHandler(I2C_ID_T id, I2C_EVENT_T event)
{}

/* Chip polling event handler */
void Chip_I2C_EventHandlerPolling(I2C_ID_T id, I2C_EVENT_T event)
{}

/* Initializes the LPC_I2C peripheral with specified parameter */
void Chip_I2C_Init(I2C_ID_T id)
{}

/* De-initializes the I2C peripheral registers to their default reset values */
void Chip_I2C_DeInit(I2C_ID_T id)
{}

/* Set up clock rate for LPC_I2C peripheral */
void Chip_I2C_SetClockRate(I2C_ID_T id, uint32_t clockrate)
{}

/* Get current clock rate for LPC_I2C peripheral */
uint32_t Chip_I2C_GetClockRate(I2C_ID_T id)
{}

/* Set the master event handler */
int Chip_I2C_SetMasterEventHandler(I2C_ID_T id, I2C_EVENTHANDLER_T event)
{}

/* Get the master event handler */
I2C_EVENTHANDLER_T Chip_I2C_GetMasterEventHandler(I2C_ID_T id)
{}

/* Transmit and Receive data in master mode */
int Chip_I2C_MasterTransfer(I2C_ID_T id, I2C_XFER_T *xfer)
{}

/* Master tx only */
int Chip_I2C_MasterSend(I2C_ID_T id, uint8_t slaveAddr, const uint8_t *buff, uint8_t len)
{}

/* Transmit one byte and receive an array of bytes after a repeated start condition is generated in Master mode.
 * This function is useful for communicating with the I2C slave registers
 */
int Chip_I2C_MasterCmdRead(I2C_ID_T id, uint8_t slaveAddr, uint8_t cmd, uint8_t *buff, int len)
{}

/* Sequential master read */
int Chip_I2C_MasterRead(I2C_ID_T id, uint8_t slaveAddr, uint8_t *buff, int len)
{}

/* Check if master state is active */
int Chip_I2C_IsMasterActive(I2C_ID_T id)
{}

/* State change handler for master transfer */
void Chip_I2C_MasterStateHandler(I2C_ID_T id)
{}

/* Setup slave function */
void Chip_I2C_SlaveSetup(I2C_ID_T id,
						 I2C_SLAVE_ID sid,
						 I2C_XFER_T *xfer,
						 I2C_EVENTHANDLER_T event,
						 uint8_t addrMask)
{}

/* I2C Slave event handler */
void Chip_I2C_SlaveStateHandler(I2C_ID_T id)
{}

/* Disable I2C device */
void Chip_I2C_Disable(I2C_ID_T id)
{
	LPC_I2Cx(id)->CONCLR = I2C_I2CONCLR_I2ENC;
}

/* State change checking */
int Chip_I2C_IsStateChanged(I2C_ID_T id)
{}

#endif /* !defined(CHIP_LPC110X) */
