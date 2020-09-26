/** ***************************************************************************
 * @file wifi.cpp
 * @author Akshay Godase
 * @date 22-09-202
 * @brief WIFI module has all necessary definitions for WIFI initializations
 * ************************************************************************* */

#include "wifi.h"

/** Saves MAC ID */
byte mac[6];

/** WIFI SSID */
char ssid[64] = {};
/** WIFI Password */
char pswd[64] = {};

/** ***************************************************************************
 * @brief This interface prints MAC ID of WIFI connected.
**************************************************************************** */
static void wifi_print_mac_string(void)
{
  char mac_Id[128];
	WiFi.macAddress(mac);
	snprintf(mac_Id, sizeof(mac_Id), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	Serial.print(mac_Id);
}

/** ***************************************************************************
 * @brief This function returns the status of WIFI connection.
 * @return true : WIFI connected
 * false : WIFI not connected
**************************************************************************** */
bool wifi_check_status(void)
{
  if (WiFi.status() == WL_CONNECTED)  {
    Serial.println("WiFi is connected!\n");
    led_set_WIFI_pin();
    return true;
  } else {
    Serial.println("WiFi is disconnected!\n");
    led_reset_WIFI_pin();
    return false;
  }
}

/** ***************************************************************************
 * @brief This function initialize WIFI connection
**************************************************************************** */
void wifi_init(void) {
	/** reset WIFI LED */
	led_reset_WIFI_pin();
	led_reset_status_pin();
	delay(10);

	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, pswd);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	randomSeed(micros());

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	led_set_WIFI_pin();
	wifi_print_mac_string();
}
