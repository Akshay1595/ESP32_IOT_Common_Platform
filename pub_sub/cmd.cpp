/** ***************************************************************************
 * @file cmd.cpp
 * @author Akshay Godase
 * @date 22-09-202
 * @brief This module takes care of bluetooth initialization.
 * Bluetooth in this project is used to accept the SSID and password for wifi
 * connection. 
 * ***************************************************************************/

#include "BluetoothSerial.h"
#include "cmd.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

/** Bluetooth module object */
BluetoothSerial SerialBT;

/** Commands that can be input with bluetooth */
char commands_input[][32] = {
    "AT?",
    "AT+PSWD=",
    "AT+SSID=",
    "AT+CNCT",
    "AT+IS_CNCT?",
    "AT+TON",
    "AT+TOFF"
};

/** ***************************************************************************
 * @brief This interface disables bluetooth. Since bluetooth has accepted
 * the SSID and Password
**************************************************************************** */
static inline void cmd_disable_bluetooth(void) {
	SerialBT.end();
}


/** ***************************************************************************
 * @brief This interface gets SSID and password with bluetooth
**************************************************************************** */
static void cmd_get_ssid_pswd(void) {
	while((strlen(ssid) == 0) || (strlen(pswd) == 0))
	{
		Serial.print("Waiting for SSID and password from bluetooth name :");
		Serial.println(BLE_NAME);
		delay(5000);
	}
	Serial.println("Got SSID and password as");
	Serial.println(ssid);
	Serial.println(pswd);

	Serial.println("Disconnecting Bluetooth!");
	cmd_disable_bluetooth();
}

/** ***************************************************************************
 * @brief This interface generate response to AT command
**************************************************************************** */
static inline void cmd_on_AT(void) {
  cmd_log("OK!");
}

/** ***************************************************************************
 * @brief This interface is called in response to password command
 * @param buffer of command
**************************************************************************** */
static void cmd_on_AT_PSWD(char *buff) {
    char payload[32] = {};  

    strcpy(pswd,buff+strlen(commands_input[CMD_PSWD]));
    sprintf(payload,"Password set to = %s",pswd);
    
    cmd_log(payload);
}

/** ***************************************************************************
 * @brief This interface is called in response to SSID command
 * @param buff : data buffer of received message
**************************************************************************** */
static void cmd_on_AT_SSID(char *buff) {
    char payload[32] = {};

    strcpy(ssid,buff+strlen(commands_input[CMD_SSID]));
    sprintf(payload,"SSID set to %s\n",ssid);

  cmd_log(payload);
}

/** ***************************************************************************
 * @brief This interface is called in response to IS_CNCT command which informs
 * if WIFI is connected or not
**************************************************************************** */
static void cmd_AT_IS_CNCT(void) {
  char payload[32] = {};
    if(wifi_check_status()) {
    	strcpy(payload,"WIFI connected!");
    	cmd_log(payload);
    } else {
    	strcpy(payload,"WIFI not connected!");
    	cmd_log(payload);
    }
}

/** ***************************************************************************
 * @brief This interface is called in response to TON command 
 * which turns on LED
**************************************************************************** */
static void cmd_on_AT_TON(void) {
	cmd_log("Turning ON LED\n");
	led_set_MSG_rcvd_pin();
}

/** ***************************************************************************
 * @brief This interface is called in response to TOFF command 
 * which turns off LED
**************************************************************************** */
static void cmd_on_AT_TOFF(void) {
    cmd_log("Turning OFF LED\n");
    led_reset_MSG_rcvd_pin();
}

/** ***************************************************************************
 * @brief This interface is returns error response for invalid command
**************************************************************************** */
static inline void cmd_on_AT_ERR(void) {
    cmd_log("Error!\n");
}


/** ***************************************************************************
 * @brief Handler to handle command received.
 * @param buff : data buffer of received message
**************************************************************************** */
static void cmd_handler(char* buff)
{
    int cmd;
    char *ptr = NULL;
    for (cmd=0;cmd<CMD_ERR;cmd++) {
        ptr = strstr(buff,commands_input[cmd]);
        if(ptr) {
                break;
        }
    }

    switch(cmd) {
    case CMD_AT:
        cmd_on_AT();
        break;

    case CMD_PSWD:
        cmd_on_AT_PSWD(buff);
        break;

    case CMD_SSID:
        cmd_on_AT_SSID(buff);
        break;

    case CMD_CNCT:
        wifi_init();
        break;

    case CMD_IS_CNCT:
        cmd_AT_IS_CNCT();
        break;

    case CMD_TON:
        cmd_on_AT_TON();
        break;

    case CMD_TOFF:
        cmd_on_AT_TOFF();
        break;

    default:
        cmd_on_AT_ERR();
        break;
    }
}

/** ***************************************************************************
 * @brief Callback to handle message received by bluetooth
 * @param buffer : data buffer of received message
 * @param size : size of message received
**************************************************************************** */
static void cmd_ble_callback(const uint8_t *buffer, size_t size) {
  char string[64] = {};
  strcpy(string,(char *)buffer);
  string[size] =  0;
  cmd_handler(string);
}

/** ***************************************************************************
 * @brief This interface is for initialization of bluetooth.
 * This interface waits for input from bluetooth device.
**************************************************************************** */
void cmd_ble_init(void) {
  Serial.println("Initializing Bluetooth!\n");
  SerialBT.begin(BLE_NAME); //Bluetooth device name
  SerialBT.onData(cmd_ble_callback);
  Serial.println("The device started, now you can pair it with bluetooth!");
  cmd_get_ssid_pswd();
}


/** ***************************************************************************
 * @brief Logging interface to print the 
 * buffer data on serial monitor and returns on bluetooth terminal
 * 
 * @param payload : buffer to print the data
**************************************************************************** */
void cmd_log(char *payload){
  Serial.println(payload);
  SerialBT.write((const uint8_t*)payload,strlen(payload));
}
