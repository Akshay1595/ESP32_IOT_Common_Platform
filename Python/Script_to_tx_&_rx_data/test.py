'''
Created on 06-Sep-2020

@summary: This scripts tries to send and receive data
for akshay_trial2 thing created

@author: Akshay Godase
'''
import os

# Import SDK packages
from AWSIoTPythonSDK.MQTTLib import AWSIoTMQTTClient

rx_flag = False
RootCA = "AmazonRootCA1.pem.txt"
private_key = "89da432624-private.pem.key"
certificate = "89da432624-certificate.pem.crt" 
topic = "akshay_trial2_test_rx"

script_dir = os.path.dirname(__file__) #<-- absolute dir the script is in
rel_path = "akshay_trial2/" + RootCA
RootCA = os.path.join(script_dir, rel_path)
rel_path = "akshay_trial2/" + private_key
private_key = os.path.join(script_dir, rel_path)
rel_path = "akshay_trial2/" + certificate
certificate = os.path.join(script_dir, rel_path)

def customCallback(client, userdata, message):
    global rx_flag
    print("Received a new message: ")
    string = message.payload.decode('UTF-8')
    print(string)
    print("from topic: ")
    print(message.topic)
    print("--------------\n\n")
    rx_flag = True

def connect_and_send_rx():
    global RootCA,private_key,certificate,topic,rx_flag
        # For certificate based connection
    myMQTTClient = AWSIoTMQTTClient("akshay_trial2")
    # For Websocket connection
    # myMQTTClient = AWSIoTMQTTClient("myClientID", useWebsocket=True)
    # Configurations
    # For TLS mutual authentication
    myMQTTClient.configureEndpoint("a21w079cqlmaf8-ats.iot.ap-south-1.amazonaws.com", 8883)
    # For Websocket
    # myMQTTClient.configureEndpoint("YOUR.ENDPOINT", 443)
    # For TLS mutual authentication with TLS ALPN extension
    # myMQTTClient.configureEndpoint("YOUR.ENDPOINT", 443)
    myMQTTClient.configureCredentials(RootCA, private_key,certificate)
    # For Websocket, we only need to configure the root CA
    # myMQTTClient.configureCredentials("YOUR/ROOT/CA/PATH")
    myMQTTClient.configureOfflinePublishQueueing(-1)  # Infinite offline Publish queueing
    myMQTTClient.configureDrainingFrequency(2)  # Draining: 2 Hz
    myMQTTClient.configureConnectDisconnectTimeout(10)  # 10 sec
    myMQTTClient.configureMQTTOperationTimeout(5)  # 5 sec

    try:
        myMQTTClient.connect()
        myMQTTClient.publish("akshay_trial2_test", "hello_world", 0)
        myMQTTClient.subscribe(topic, 1, customCallback)
    except:
        print("Connection  failed")
    
    while not rx_flag:
        pass
    
def main():
    global RootCA
    print("HelloWorld")      
    connect_and_send_rx()
    print("done bro")
        
if __name__ == '__main__':
    main()