/**************************************************
 ** The RTE signal blackboard (autogenerated)
 **************************************************/

#ifndef RTE_SIGNALPOOL_H
#define RTE_SIGNALPOOL_H


/* Generated signal classes */
#include "adc_signal.h"
#include "pwm_signal.h"
#include "gpio_signal.h"
#include "lcd_signal.h"


/* Generated objects */

/* Input signal for joystick position (ADC), range -100..100 */
extern ADC_t JOYSTICK_signal;

/* Output Signal for engine speed (PWM), range 0..255 */
extern PWM_t ENGINE_signal;

/* Output Signal for brake light (GPIO), range 0..1 */
extern GPIO_t BRAKELIGHT_signal;

/* Output Signal to lcd */
extern LCD_t LCD_signal;

/** Central Timertick function 
 *  must be called every 10ms 
 **/  
void RTE_timertick();


#endif