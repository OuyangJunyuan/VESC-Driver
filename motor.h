#ifndef MOTOR_WTR_H 
#define MOTOR_WTR_H

#include "usart.h"



typedef enum {
COMM_FW_VERSION = 0,
COMM_JUMP_TO_BOOTLOADER,
COMM_ERASE_NEW_APP,
COMM_WRITE_NEW_APP_DATA,
COMM_GET_VALUES,
COMM_SET_DUTY,
COMM_SET_CURRENT,
COMM_SET_CURRENT_BRAKE,
COMM_SET_RPM,
COMM_SET_POS,
COMM_SET_DETECT,
COMM_SET_SERVO_POS,
COMM_SET_MCCONF,
COMM_GET_MCCONF,
COMM_GET_MCCONF_DEFAULT,
COMM_SET_APPCONF,
COMM_GET_APPCONF,
COMM_GET_APPCONF_DEFAULT,
COMM_SAMPLE_PRINT,
COMM_TERMINAL_CMD,
COMM_PRINT,
COMM_ROTOR_POSITION,
COMM_EXPERIMENT_SAMPLE,
COMM_DETECT_MOTOR_PARAM,
COMM_DETECT_MOTOR_R_L,
COMM_DETECT_MOTOR_FLUX_LINKAGE,
COMM_DETECT_ENCODER,
COMM_DETECT_HALL_FOC,
COMM_REBOOT,
COMM_ALIVE,
COMM_GET_DECODED_PPM,
COMM_GET_DECODED_ADC,
COMM_GET_DECODED_CHUK,
COMM_FORWARD_CAN,
COMM_SET_CHUCK_DATA,
COMM_CUSTOM_APP_DATA
} COMM_PACKET_ID;
typedef enum {
FAULT_CODE_NONE = 0,
FAULT_CODE_OVER_VOLTAGE,
FAULT_CODE_UNDER_VOLTAGE,
FAULT_CODE_DRV8302,
FAULT_CODE_ABS_OVER_CURRENT,
FAULT_CODE_OVER_TEMP_FET,
FAULT_CODE_OVER_TEMP_MOTOR,
FAULT_CODE_END
} mc_fault_code;


typedef struct
{
	UART_HandleTypeDef *huartn;
	void(*comm)(COMM_PACKET_ID id,float value);
}VESC_HandleTypeDef;


typedef struct
{

	uint8_t error_code;
	uint8_t controller_id;
	
	float duty;
	float pos_now;
	float rpm_electrical;
	int32_t tachometer;
	int32_t tachometer_abs;
	float current_motor;
	float current_input;
	float voltage_input;
	
	float id;
	float iq;
	float temp_fet;
	float temp_motor;
	float A_hours_draw;
	float A_hours_charge;
	float Watt_hours_draw;
	float Watt_hours_charge;
}MOTOR_PROPERTY;


	

typedef struct
{
	VESC_HandleTypeDef vesc;
	MOTOR_PROPERTY property;
}MOTOR_HandleTypeDef;
typedef struct
{
	void (*init)(void);
	void (*duty)(MOTOR_HandleTypeDef *hmotor,float _duty);
	void (*current)(MOTOR_HandleTypeDef *hmotor,float _current);
	void (*rpm)(MOTOR_HandleTypeDef *hmotor,float _rpm);
	void (*pos)(MOTOR_HandleTypeDef *hmotor,float _pos);
	void (*request_new_data)(MOTOR_HandleTypeDef *hmotor);
}MOTOR_SET;



void send_commands(VESC_HandleTypeDef *hvesc, const COMM_PACKET_ID id,float value);

extern MOTOR_SET COMMOND;
extern MOTOR_HandleTypeDef hmotor1;
extern MOTOR_HandleTypeDef hmotor2;
extern MOTOR_HandleTypeDef hmotor3;
extern MOTOR_HandleTypeDef hmotor4;



#endif
