# ESP32_&_AWS_based_Common_IOT_Platform
This project is made to provide common platform for IOT solution with ESP32.
This code connects with AWS thing and publishes MQTT messages to AWS cloud.
Also this code is able  to get message from AWS thing and based on message it can take an action.

![Diagram of Project](https://github.com/Akshay1595/ESP32_IOT_Common_Platform/blob/master/Documentation/diagram_of_Common_IOT_platform.jpg)

###Features:

1. Firmware can be modified to read sensor data
2. Firmware can be updated with OTA feature
3. Firwmare works with AT commands need to be sent from AWS cloud
4. Modular and well documented firmware which provide simple functionality to add command and action for user
5. Python script running at user's AWS EC2 remote machine which collects data and store it.
6. Based on computational logic which can be modified any time user can make send command to ESP32 and take an action
7. Python script can be modified anytime based on requirement
8. Also firmware can be updated if requirements changes with OTA feature.
9. WiFi credentials can be configured with android app and bluetooth

Code accepts wifi credentials with Bluetooth. Install Serial Bluetooth Terminal app in users mobile phone.
Terminal should input command with
AT+SSID=<ssid of your wifi>
AT+PSWD=<password of your wifi>

Once valid credentials are received, firmware will disconnect bluetooth.
If valid credentials are not received, it will keep on waiting for valid
credentials.

After connection to wifi it will start sending messages to cloud. Message will
have ADC data of configured ADC pins.

Once connected to WIFI, connect to same wifi with your laptop. 
Change the firmware upload port to IP address of wifi showed ESP32 board
and upload the new sketch for OTA.

### Reference video for OTA:
https://www.youtube.com/watch?v=1pwqS_NUG7Q

### Reference Video for AWS code:
https://www.youtube.com/watch?v=c4gEKQIHK4g&t=379s

### Referrence for Bluetooth code:
please refer the library of BluetoothSerial