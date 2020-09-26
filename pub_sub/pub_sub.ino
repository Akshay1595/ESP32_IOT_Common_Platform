/** ***************************************************************************
 * @file pub_sub.ino
 * @author Akshay Godase
 * @date 22-09-2020
 *
 * @brief This is the main file where code starts execution.
 * This project is working on ESP32 code compiled on
 * Arduino IDE platform.
 * ESP32 is used to collect and send data to cloud.
 * Cloud server will collect the data and take a
 * decision based on computing logic.
 *************************************************************************** */

// header file which has all the necessary headers
#include "my_header.h"

/** Buffer to  maintain the message to be translated to cloud */
char payload[BUFFER_LEN];
/** lastMsg will maintain the time stamp of last message  */
long lastMsg = 0;

/** ***************************************************************************
 * This is the setup function
 * where all initializations are done
 * @param none
 *************************************************************************** */
void setup(void) {
	Serial.setDebugOutput(true);
	Serial.begin(115200);
	led_setup();
	cmd_ble_init();
	wifi_init();
	delay(1000);
	aws_init();
	setupOTA("Akshay_ESP32");
	Serial.println("All Setup Done!\n");
}

/** ***************************************************************************
 * This is the loop function
 * which will loop continuously
**************************************************************************** */
void loop(void) { 
	// Step 1: check if client is connected
	aws_check_if_connected();
	
	long now = millis();
	// This condition will check if loop is not idle from 2 seconds
	if (now - lastMsg > 2000) {
		lastMsg = now;

		adc_read_and_msg(payload);
		Serial.print("Publish message: ");
		Serial.println(payload);
		// Step 2: publish the message

		aws_publish(payload);
	}              
	delay(100); // wait for a second

	// Step 3: Toggle the LED for indication to end user
	led_toggle_status_pin();
	
	// Step  : Check for OTA update
	ArduinoOTA.handle();
}
