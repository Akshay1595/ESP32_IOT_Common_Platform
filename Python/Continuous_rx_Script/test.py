'''
Created on 06-Sep-2020

@summary: This scripts tries to send and receive data
for akshay_trial2 thing created

@author: Akshay Godase
'''
import os
import sys 

# Import SDK packages
from AWSIoTPythonSDK.MQTTLib import AWSIoTMQTTClient
import logging
import time
from sys import stdout

myMQTTClient = None
my_logger = None

RootCA = "AmazonRootCA1.pem.txt"
private_key = "89da432624-private.pem.key"
certificate = "89da432624-certificate.pem.crt" 
topic = "akshay_trial2_test"
msg_count = 0

script_dir = os.path.dirname(__file__) #<-- absolute dir the script is in
rel_path = "certificates/" + RootCA
RootCA = os.path.join(script_dir, rel_path)
rel_path = "certificates/" + private_key
private_key = os.path.join(script_dir, rel_path)
rel_path = "certificates/" + certificate
certificate = os.path.join(script_dir, rel_path)

def get_logger():
    list_time = time.ctime().split(' ')
    time_string = list_time[3].split(':')[0] + '_' + list_time[3].split(':')[1] + '_' + list_time[3].split(':')[2]
    date_string =  list_time[1] + '_' + list_time[2]  +  '_' + list_time[4]
    day = list_time[0]
    file_name = day + '_' + date_string + '_' + time_string + '.log'
    logging.basicConfig(level=logging.INFO,
                        format='%(asctime)s - %(message)s',
                        datefmt='%d-%m-%Y %H:%M:%S',
                        filename="Logs\\" + file_name,
                        filemode='w')
    logger = logging.getLogger()
    stdout_handler = logging.StreamHandler(sys.stdout) # this line will print on terminal
    logger.addHandler(stdout_handler)
    return logger

def customCallback(client, userdata, message):
    global msg_count,my_logger
    my_logger.info("Received new message: ")
    string = message.payload.decode('UTF-8')
    my_logger.info(string)
    my_logger.info("from topic: "  + message.topic)
    msg_count += 1
    my_logger.info("Now Message count = %d"%msg_count)
    my_logger.info("-"*40)
    
def connect_and_send_rx():
    global RootCA,private_key,certificate,topic,myMQTTClient,my_logger
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
        myMQTTClient.connect(5)
        myMQTTClient.publish("akshay_trial2_test_rx", "hello_world", 0)
        myMQTTClient.subscribe(topic, 1, customCallback)
    except:
        my_logger.info("Connection  failed")
    
def main():
    global myMQTTClient,my_logger
    my_logger = get_logger()
    my_logger.info("-"*80)
    my_logger.info("Jay Shri Ram! Logging started at %s"%time.ctime())      
    my_logger.info("-"*80)
    connect_and_send_rx()
    my_logger.info("Connection done bro! now keep on receiving messages")
    while True:
        pass
        
if __name__ == '__main__':
    main()