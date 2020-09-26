/** ***************************************************************************
 * @file wifi.h
 * @author Akshay Godase
 * @date 22-09-202
 * @brief header file for the declarations necessary for WIFI module
 * ************************************************************************* */

#ifndef WIFI_H
#define WIFI_H

#include <WiFiClientSecure.h>
#include "led.h"

/// function declarations
extern void wifi_init(void);
extern bool wifi_check_status(void);

#endif
