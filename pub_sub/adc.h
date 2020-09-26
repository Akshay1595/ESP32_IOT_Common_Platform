/** ***************************************************************************
 * @file adc.h
 * @author Akshay Godase
 * @date 22-09-202
 * @brief header file for the declarations necessary for ADC module
* ************************************************************************* */
#ifndef ADC_H
#define ADC_H

#define ADC_1 34 ///< ADC pin 1
#define ADC_2 35 ///< ADC pin 2

extern void adc_read_and_msg(char* data_payload);

#endif /* ADC_H */
