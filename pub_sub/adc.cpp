/** ***************************************************************************
 * @file adc.cpp
 * @author Akshay Godase
 * @date 22-09-202
 * @brief This module handles ADC data reading function
 * ************************************************************************* */

#include <Arduino.h>
#include "adc.h"

/** ***************************************************************************
 * @brief This interface will read ADC values and fill the buffer
 * with message consisting these ADC values
 * @param data_payload : data buffer to be filled with ADC value string
**************************************************************************** */
void adc_read_and_msg(char* data_payload)
{
  uint16_t value_adc_1 = 0,value_adc_2=0;
  value_adc_1 = analogRead(ADC_1);
  value_adc_2 = analogRead(ADC_2);
  sprintf( data_payload, "adc_1 = %u adc_2 = %u",value_adc_1,value_adc_2);
}
