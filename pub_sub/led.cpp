/** ***************************************************************************
 * @file led.cpp
 * @author Akshay Godase
 * @date 22-09-202
 * @brief LED module is used to configure the LEDs connected.
 * Function declarations to set or reset LEDs.
 * ************************************************************************* */

#include <Arduino.h>
#include "led.h"

/** status maintaining flags */
bool msg_rcvd_led = LED_LOW;
bool status_led = LED_LOW;

/** ****************************************************************************
 * @brief This interface will toggle status pin.
 * It checks flag   status_led and toggles the status LED
***************************************************************************** */
void led_toggle_status_pin(void) {
  if (status_led == LED_LOW){
		led_set_status_pin();
		status_led = LED_HIGH;
  }
  else {
	  led_reset_status_pin();
	  status_led = LED_LOW;
  }
}


/** ***************************************************************************
 * @brief Toggle interface to toggle msg_received pin
 *
 * @return none
 *************************************************************************** */
void led_toggle_pin(void)
{
  if (msg_rcvd_led == LED_LOW){
	  led_set_MSG_rcvd_pin();
	  msg_rcvd_led = LED_HIGH;
  }
  else {
	  led_reset_MSG_rcvd_pin();
	  msg_rcvd_led = LED_LOW;
  }
}

/** ***************************************************************************
 * @brief Initialization sequence to configure all LEDs
 *
 * @return none
 *************************************************************************** */
void led_setup(void)
{
	pinMode(WIFI_CONNECTED_PIN, OUTPUT);
	pinMode(AWS_CLIENT_CONNECTED,  OUTPUT);
	pinMode(MSG_RCVD,OUTPUT);
	pinMode(STATUS_LED,OUTPUT);
	led_reset_WIFI_pin();
	led_reset_AWS_connected_pin();
	led_reset_MSG_rcvd_pin();
	led_reset_status_pin();
}
