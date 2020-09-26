/** ***************************************************************************
 * @file aws.h
 * @author Akshay Godase
 * @date 22-09-202
 * @brief header file for the declarations necessary for AWS module
 * ************************************************************************* */

#ifndef AWS_H
#define AWS_H

// required libraries
#include "led.h"
#include "wifi.h"

#define MQTT_TOPIC "akshay_trial2_test" ///< topic to send message
#define MQTT_GET_DATA_TOPIC "akshay_trial2_test_rx" ///< topic to receive message
#define MQTT_SERVER "a21w079cqlmaf8-ats.iot.ap-south-1.amazonaws.com" ///< AWS end point of AWS thing
#define MQTT_PORT 8883 ///< port for communication

// function declarations
extern void aws_init(void);
extern void aws_check_if_connected();
extern void aws_publish(char *payload);

#endif /* AWS.h */
