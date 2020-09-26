/** ***************************************************************************
 * @file led.h
 * @author Akshay Godase
 * @date 22-09-202
 * @brief header file for the declarations necessary for LED module
 * ************************************************************************* */

#ifndef LED_H
#define LED_H

#define LED_LOW false
#define LED_HIGH true

#define STATUS_LED            17 ///< Status LED
#define WIFI_CONNECTED_PIN    5  ///< WiFi connected LED pin = 5
#define AWS_CLIENT_CONNECTED  18 ///< AWS Client connected LED pin = 4
#define MSG_RCVD              19 ///< Message received from client

/// function declarations
extern void led_setup(void);
extern void led_toggle_pin(void);
extern void led_toggle_status_pin(void);

/** ***************************************************************************
 * @brief This interface resets status LED
**************************************************************************** */
inline void led_reset_status_pin() {
  digitalWrite(STATUS_LED,LOW);
}

/** ***************************************************************************
 * @brief This interface sets status LED
**************************************************************************** */
inline void led_set_status_pin() {
  digitalWrite(STATUS_LED,HIGH);
}

/** ***************************************************************************
 * @brief This interface sets WIFI pin
**************************************************************************** */
inline void led_set_WIFI_pin() {
	digitalWrite(WIFI_CONNECTED_PIN, HIGH);
}

/** ***************************************************************************
 * @brief This interface resets WIFI LED
**************************************************************************** */
inline void led_reset_WIFI_pin() {
	digitalWrite(WIFI_CONNECTED_PIN, LOW);
}

/** ***************************************************************************
 * @brief This interface sets AWS_CONNECTED LED
**************************************************************************** */
inline void led_set_AWS_connected_pin() {
	digitalWrite(AWS_CLIENT_CONNECTED, HIGH);
}

/** ***************************************************************************
 * @brief This interface resets AWS_CONNECTED LED
**************************************************************************** */
inline void led_reset_AWS_connected_pin() {
	digitalWrite(AWS_CLIENT_CONNECTED, LOW);
}

/** ***************************************************************************
 * @brief This interface sets MSG RCVD LED
**************************************************************************** */
inline void led_set_MSG_rcvd_pin() {
	digitalWrite(MSG_RCVD, HIGH);
}

/** ***************************************************************************
 * @brief This interface resets MSG RCVD LED
**************************************************************************** */
inline void led_reset_MSG_rcvd_pin() {
	digitalWrite(MSG_RCVD, LOW);
}

#endif /* LED_H */
