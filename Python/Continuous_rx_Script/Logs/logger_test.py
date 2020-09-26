import logging
import time

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

my_logger = get_logger()
my_logger.info("Hello_World = %d"%23)