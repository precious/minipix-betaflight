/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 */

#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM3, CH3, PB0,  TIM_USE_PPM,   0, 0), // PPM input

    DEF_TIM(TIM1, CH1, PE9,  TIM_USE_MOTOR, 0, 0), // Motor 1
    DEF_TIM(TIM1, CH2, PE11, TIM_USE_MOTOR, 0, 0), // Motor 2
    DEF_TIM(TIM1, CH3, PE13, TIM_USE_MOTOR, 0, 0), // Motor 3
    DEF_TIM(TIM1, CH4, PE14, TIM_USE_MOTOR, 0, 0), // Motor 4
};
