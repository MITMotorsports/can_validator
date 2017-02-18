#include "chip.h"
#include "sysinit.h"
#include "can.h"

#include <string.h>

const uint32_t OscRateIn = 0;

/*****************************************************************************
 * Private types/enumerations/variables/macros
 ****************************************************************************/

#define LED0 2, 8
#define LED1 2, 10


volatile uint32_t msTicks;

#define UART_RX_BUFFER_SIZE 8
static char uart_rx_buf[UART_RX_BUFFER_SIZE];
static CCAN_MSG_OBJ_T msg_obj;

#ifdef DEBUG_ENABLE
	static char temp_str[10];
	#define DEBUG_Print(str) Chip_UART_SendBlocking(LPC_USART, str, strlen(str))
	#define DEBUG_Println(str) {DEBUG_Print(str); DEBUG_Print("\r\n");}
	#define DEBUG_PrintNum(num, base) {itoa(num, temp_str, base); DEBUG_Print(temp_str);}
	#define DEBUG_Write(str, count) Chip_UART_SendBlocking(LPC_USART, str, count)
#else
	#define DEBUG_Print(str)
	#define DEBUG_Println(str)
	#define DEBUG_PrintNum(num, base)
	#define DEBUG_Write(str, count) 
#endif

/*****************************************************************************
 * Private functions
 ****************************************************************************/

void SysTick_Handler(void) {
	msTicks++;
}

static void LED_Init(uint8_t port, uint8_t pin) {
	Chip_GPIO_WriteDirBit(LPC_GPIO, port, pin, true);
	Chip_GPIO_SetPinState(LPC_GPIO, port, pin, false);

}

static void LED_Write(uint8_t port, uint8_t pin, uint8_t val) {
	Chip_GPIO_SetPinState(LPC_GPIO, port, pin, val);
}


int main(void)
{
	SysTick_Config (TicksPerMS);

	LPC_SYSCTL->CLKOUTSEL = 0x03; 		// Main CLK (Core CLK) Out
	LPC_SYSCTL->CLKOUTUEN = 0x00; 		// Toggle Update CLKOUT Source
	LPC_SYSCTL->CLKOUTUEN = 0x01;
	while(!(LPC_SYSCTL->CLKOUTUEN & 0x1)); // Wait until updated
	LPC_SYSCTL->CLKOUTDIV = 0x04; 		// No division

	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_1, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_OPENDRAIN_EN)); /*CLKOUT*/

	//---------------
	//UART
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_6, (IOCON_FUNC1 | IOCON_MODE_INACT));/* RXD */
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_7, (IOCON_FUNC1 | IOCON_MODE_INACT));/* TXD */

	Chip_UART_Init(LPC_USART);
	Chip_UART_SetBaud(LPC_USART, UART_BAUD);
	Chip_UART_ConfigData(LPC_USART, (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS));
	Chip_UART_SetupFIFOS(LPC_USART, (UART_FCR_FIFO_EN | UART_FCR_TRG_LEV2));
	Chip_UART_TXEnable(LPC_USART);
	//---------------

	CAN_Init(500000);

	DEBUG_Print("Started up\n\r");

	LED_Init(LED0);
	LED_Init(LED1);

	LED_Write(LED0, true);


	uint32_t reset_can_peripheral_time;
    const uint32_t can_error_delay = 1000;
    bool reset_can_peripheral = false;

    CAN_ERROR_T ret;

	while (1) {
		uint8_t count;
		if ((count = Chip_UART_Read(LPC_USART, uart_rx_buf, UART_RX_BUFFER_SIZE)) != 0) {
				DEBUG_Write(uart_rx_buf, count);
				if (uart_rx_buf[0] == 'a') {
					msg_obj.msgobj = 1;
					msg_obj.mode_id = 0x618;
					msg_obj.dlc = 7;
					msg_obj.data[0] = (1 << 7);
					msg_obj.data[1] = 10 >> 8;
					msg_obj.data[2] = 10 & 0xFF;
					msg_obj.data[3] = 0;
					msg_obj.data[4] = 0;
					msg_obj.data[5] = 0;
					msg_obj.data[6] = 0;

					ret = CAN_TransmitMsgObj(&msg_obj);
                    if(ret != NO_CAN_ERROR) {
                        DEBUG_Print("CAN Error (Tx): ob");
					    DEBUG_PrintNum(ret, 2);
                        DEBUG_Println("");
                    }
				}
		}

		// if (msTicks - last_count > 1000) {
		// 	last_count = msTicks;
		// 	DEBUG_Print("PING\r\n");
		// }


        if(reset_can_peripheral && msTicks > reset_can_peripheral_time) {
            DEBUG_Print("Attempting to reset CAN peripheral...\r\n ");
            CAN_ResetPeripheral();
            CAN_Init(500000);
            DEBUG_Print("Reset CAN peripheral. \r\n ");
            reset_can_peripheral = false;
        }

	    ret = CAN_Receive(&msg_obj);
        if(ret == NO_RX_CAN_MESSAGE) {
            // DEBUG_Print("No CAN message received...\r\n");
        } else if(ret == NO_CAN_ERROR) {
            // DEBUG_Print("Recieved data ");
            // Print_Buffer(rx_msg.data, rx_msg.dlc);
            // DEBUG_Print(" from ");
            // itoa(rx_msg.mode_id, str, 16);
            // DEBUG_Print(str);
            // DEBUG_Print("\r\n");
            DEBUG_Print("0x");
            DEBUG_PrintNum(msg_obj.mode_id, 16);
            DEBUG_Print(" ");
            DEBUG_PrintNum(msg_obj.dlc, 10);
            int i;
            for (i = 0; i < msg_obj.dlc; i++) {
            	DEBUG_Print(" 0x");
            	DEBUG_PrintNum(msg_obj.data[i], 16);
            }
            DEBUG_Println("");
        } else {
            DEBUG_Print("CAN Error: ");
            DEBUG_PrintNum(ret, 2)
            DEBUG_Println("");

            reset_can_peripheral = true;
            reset_can_peripheral_time = msTicks + can_error_delay;
        }
	}
}
