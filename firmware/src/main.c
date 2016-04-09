#include "board.h"

// -------------------------------------------------------------
// Macro Definitions

#define CCAN_BAUD_RATE 1000000 					// Desired CAN Baud Rate
#define UART_BAUD_RATE 57600 					// Desired UART Baud Rate

#define BUFFER_SIZE 8

#define STATUS_LED_PERIOD 200

// -------------------------------------------------------------
// Static Variable Declaration

extern volatile uint32_t msTicks;

static CCAN_MSG_OBJ_T msg_obj; 					// Message Object data structure for manipulating CAN messages
static RINGBUFF_T can_rx_buffer;				// Ring Buffer for storing received CAN messages
static CCAN_MSG_OBJ_T _rx_buffer[BUFFER_SIZE]; 	// Underlying array used in ring buffer

static bool can_error_flag;
static uint32_t can_error_info;

// -------------------------------------------------------------
// Helper Functions

/**
 * Delay the processor for a given number of milliseconds
 * @param ms Number of milliseconds to delay
 */
void _delay(uint32_t ms) {
	uint32_t curTicks = msTicks;
	while ((msTicks - curTicks) < ms);
}

// -------------------------------------------------------------
// CAN Driver Callback Functions

/*	CAN receive callback */
/*	Function is executed by the Callback handler after
    a CAN message has been received */
void CAN_rx(uint8_t msg_obj_num) {
	// LED_On();
	/* Determine which CAN message has been received */
	msg_obj.msgobj = msg_obj_num;
	/* Now load up the msg_obj structure with the CAN message */
	LPC_CCAN_API->can_receive(&msg_obj);
	if (msg_obj_num == 1) {
		RingBuffer_Insert(&can_rx_buffer, &msg_obj);
	}
}

/*	CAN transmit callback */
/*	Function is executed by the Callback handler after
    a CAN message has been transmitted */
void CAN_tx(uint8_t msg_obj_num) {
	msg_obj_num = msg_obj_num;
}

/*	CAN error callback */
/*	Function is executed by the Callback handler after
    an error has occurred on the CAN bus */
void CAN_error(uint32_t error_info) {
	can_error_info = error_info;
	can_error_flag = true;
}

// -------------------------------------------------------------
// Interrupt Service Routines


// -------------------------------------------------------------
// Main Program Loop

int main(void)
{

	//---------------
	// Initialize UART Communication
	Board_UART_Init(UART_BAUD_RATE);
	Board_UART_Println("Started up");

	//---------------
	// Initialize SysTick Timer to generate millisecond count
	if (Board_SysTick_Init()) {
		Board_UART_Println("Failed to Initialize SysTick. ");
		// Unrecoverable Error. Hang.
		while(1);
	}

	//---------------
	// Initialize GPIO and LED as output
	Board_LEDs_Init();
	Board_LED_On(LED0);

	//---------------
	// Initialize CAN  and CAN Ring Buffer

	RingBuffer_Init(&can_rx_buffer, _rx_buffer, sizeof(CCAN_MSG_OBJ_T), BUFFER_SIZE);
	RingBuffer_Flush(&can_rx_buffer);

	Board_CAN_Init(CCAN_BAUD_RATE, CAN_rx, CAN_tx, CAN_error);

	// For your convenience.
	// typedef struct CCAN_MSG_OBJ {
	// 	uint32_t  mode_id;
	// 	uint32_t  mask;
	// 	uint8_t   data[8];
	// 	uint8_t   dlc;
	// 	uint8_t   msgobj;
	// } CCAN_MSG_OBJ_T;

	msg_obj.msgobj = 1;
	msg_obj.mode_id = 0x000;
	msg_obj.mask = 0x000;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	can_error_flag = false;
	can_error_info = 0;

	uint8_t status_led_state = 1;
	uint32_t status_led_time = msTicks;

	while (1) {
		if (!RingBuffer_IsEmpty(&can_rx_buffer)) {
			Board_LED_On(LED3);
			CCAN_MSG_OBJ_T temp_msg;
			RingBuffer_Pop(&can_rx_buffer, &temp_msg);
			Board_UART_PrintNum(temp_msg.mode_id, 16, false);
			Board_UART_Print("\t");
			Board_UART_PrintNum(temp_msg.dlc, 10, false);

			int i = 0;
			for (i = 0; i < temp_msg.dlc; i++) {
				Board_UART_Print("\t");
				Board_UART_PrintNum(temp_msg.data[i], 16, false);
			}

			Board_UART_Println("");
			Board_LED_Off(LED3);
		}	

		if (can_error_flag) {
			can_error_flag = false;
			Board_UART_Print("CAN Error: 0b");
			Board_UART_PrintNum(can_error_info, 2, true);
		}

		if (msTicks - status_led_time > STATUS_LED_PERIOD) {
			status_led_time = msTicks;
			status_led_state = 1 - status_led_state;
			Board_LED_Set(LED0, status_led_state);
		}
	}
}
