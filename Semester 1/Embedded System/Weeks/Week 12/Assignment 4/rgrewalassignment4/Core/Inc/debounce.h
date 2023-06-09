/*
 * debounce.h
 *
 *  Created on: Mar 31, 2023
 *      Author: rajka
 */

#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

void deBounceInit(int16_t pin, char port, int8_t mode);
GPIO_PinState deBounceReadPin(int16_t pin, char port, int8_t stableInterval);

#endif /* INC_DEBOUNCE_H_ */
