/** ***************************************************************************
 * @file aws.cpp
 * @author Akshay Godase
 * @date 22-09-202
 * @brief AWS module to configure send and receive messages from AWS cloud
 * ************************************************************************* */

#include <Arduino.h>
#include <PubSubClient.h>
#include "SPIFFS.h"
#include "aws.h"

/** Strings to maintain certificates */
String Read_rootca;
String Read_cert;
String Read_privatekey;

/** pointers to print certificates */
char* pRead_rootca;
char* pRead_cert;
char* pRead_privatekey;

WiFiClientSecure espClient;
PubSubClient client(espClient);

/** ***************************************************************************
 * @brief callback function getting called whenever message received from AWS
 * thing
 *
 * @param topic from which data is getting received
 * @param payload message received
 * @param length of message received
 *
 * @return none
 *************************************************************************** */
static void aws_callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i = 0; i < length; i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println();
	/** Toggle the led once message is received */
	led_toggle_pin();
}

/** ***************************************************************************
 * @brief function will print all the certificates read from SPIFF
 *
 * @return none
 *************************************************************************** */
static void aws_print_certificates(void)
{
	pRead_rootca = (char *)malloc(sizeof(char) * (Read_rootca.length() + 1));
	strcpy(pRead_rootca, Read_rootca.c_str());

	pRead_cert = (char *)malloc(sizeof(char) * (Read_cert.length() + 1));
	strcpy(pRead_cert, Read_cert.c_str());

	pRead_privatekey = (char *)malloc(sizeof(char) * (Read_privatekey.length() + 1));
	strcpy(pRead_privatekey, Read_privatekey.c_str());
	
	Serial.println("================================================================================================");
	Serial.println("Certificates that passing to espClient Method");
	Serial.println();
	Serial.println("Root CA:");
	Serial.write(pRead_rootca);
	Serial.println("================================================================================================");
	Serial.println();
	Serial.println("Cert:");
	Serial.write(pRead_cert);
	Serial.println("================================================================================================");
	Serial.println();
	Serial.println("privateKey:");
	Serial.write(pRead_privatekey);
	Serial.println("================================================================================================");
}

/** ****************************************************************************
 * @brief function will read all the certificates read from SPIFF
 * these certificates are necessary for AWS client connection.
 * @return none
 **************************************************************************** */
static void aws_read_certificates(void)
{
	if (!SPIFFS.begin(true)) {
		Serial.println("An Error has occurred while mounting SPIFFS");
	return;
	}

	//Root CA File Reading.
	File file2 = SPIFFS.open("/AmazonRootCA1.pem", "r");
	if (!file2) {
		Serial.println("Failed to open file for reading");
		return;
	}
	Serial.println("Root CA File Content:");
	while (file2.available()) {
	Read_rootca = file2.readString();
		Serial.println(Read_rootca);
	}

	// Cert file reading
	File file4 = SPIFFS.open("/89da432624-certificate.pem.crt", "r");
	if (!file4) {
		Serial.println("Failed to open file for reading");
		return;
	}
	Serial.println("Cert File Content:");
	while (file4.available()) {
		Read_cert = file4.readString();
		Serial.println(Read_cert);
	}

	//Privatekey file reading
	File file6 = SPIFFS.open("/89da432624-private.pem.key", "r");
	if (!file6) {
		Serial.println("Failed to open file for reading");
		return;
	}
	Serial.println("privateKey File Content:");
	while (file6.available()) {
		Read_privatekey = file6.readString();
		Serial.println(Read_privatekey);
	}
	/** print all the certificates after read from SPIFFs */
	aws_print_certificates();
}

/** ***************************************************************************
 * @brief This function will be called whenever AWS client is disconnected to
 * reconnect again
 * @return none
 *************************************************************************** */
static void aws_reconnect(void) {
  // Loop until we're reconnected
  while (!client.connected()) {
	/** Reset the LED for indication */
	led_reset_AWS_connected_pin();
	led_reset_status_pin();

	/** WIFI connection needs to be intact
	 *  so verify WIFI first */
	Serial.println("Check Wifi status first!");
	if(!wifi_check_status()) {
	  wifi_init();
	  delay(2000);
    }
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(MQTT_TOPIC, "hello world");
      // ... and resubscribe
      client.subscribe(MQTT_GET_DATA_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  /** Set the LED for indication */
  led_set_AWS_connected_pin();
}

/** ***************************************************************************
 * @brief This function will be called after certificates are read from SPIFFS.
 * It will configure according to certificate data.
 *
 * @return none
 *************************************************************************** */
static void aws_configure_client(void)
{
	espClient.setCACert(pRead_rootca);
	espClient.setCertificate(pRead_cert);
	espClient.setPrivateKey(pRead_privatekey);
	client.setServer(MQTT_SERVER, MQTT_PORT);
	client.setCallback(aws_callback);
	delay(2000);
}

/** ***************************************************************************
 * @brief Function to publish on AWS cloud configured.
 * @param payload : pointer to message to be sent
 * @return none
 *************************************************************************** */
void aws_publish(char *payload){
    client.publish(MQTT_TOPIC,payload);
}

/** ***************************************************************************
 * @brief Function to ensure if AWS client is connected.
 * If not connected reconnect it.
 * @return none
 *************************************************************************** */
void aws_check_if_connected(void){
	if (!client.connected()) {
		aws_reconnect();
	}
	client.loop();
}

/** ***************************************************************************
 * @brief Function will initialize all the necessary components for AWS
 *************************************************************************** */
void aws_init(void)
{
	aws_read_certificates();
	aws_configure_client();
	aws_reconnect();
}
