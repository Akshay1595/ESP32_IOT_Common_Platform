# Smart Solution
This project is made to provide common platform for IOT solution with ESP32.
This code connects with AWS thing and publishes MQTT messages to AWS cloud.
Also this code is able  to get message from AWS thing and based on message it can take an action.

### Reference Video for AWS code:
https://www.youtube.com/watch?v=c4gEKQIHK4g&t=379s

Code accepts wifi credentials with Bluetooth. Install Serial Bluetooth Terminal app in users mobile phone.
Terminal should input command with
AT+SSID=<ssid of your wifi>
AT+PSWD=<password of your wifi>

### Referrence for Bluetooth code:
please refer the library of BluetoothSerial

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