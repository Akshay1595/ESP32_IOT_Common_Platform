/** ***************************************************************************
 * @file cmd.h
 * @author Akshay Godase
 * @date 22-09-202
 * @brief header file for the declarations necessary for CMD module
 * ************************************************************************* */
#ifndef CMD_H
#define CMD_H

/** necessary header files for this module */
#include "led.h"
#include "wifi.h"

#define BLE_NAME "ESP32_BLE" ///< name of bluetooth device to pair

extern void cmd_ble_init(void);
extern void cmd_log(char *payload);

extern char pswd[64];
extern char ssid[64];

/*** All commands */
typedef enum cmd_t {
    CMD_AT,
    CMD_PSWD,
    CMD_SSID,
    CMD_CNCT,
    CMD_IS_CNCT,
    CMD_TON,
    CMD_TOFF,
    CMD_ERR
}cmd_s;

#endif /* CMD_H */