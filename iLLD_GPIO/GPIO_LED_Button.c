/**********************************************************************************************************************
 * \file GPIO_LED_Button.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 *
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are solely in the form of
 * machine-executable object code generated by a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *********************************************************************************************************************/

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "IfxPort.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define LED1 &MODULE_P10, 2  // Digital pin 13 - P10.2
#define SW1  &MODULE_P02, 0  // Digital pin  2 - P02.0

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
// General Purpose Input/Output (GPIO)
void initGPIO(void)
{
    // LED1과 연결된 핀을 출력 모드로 설정
    IfxPort_setPinMode(LED1, IfxPort_Mode_outputPushPullGeneral);

    // SW1과 연결된 핀을 입력 모드로 설정
    IfxPort_setPinMode(SW1, IfxPort_Mode_inputPullUp);
}

// 스위치 상태에 따라 LED를 제어하는 함수
void controlLED(void)
{
    // Pull-up 회로: 스위치를 닫으면 LOW 상태가 됨
    if (IfxPort_getPinState(SW1) == 0)
    {
        IfxPort_setPinState(LED1, IfxPort_State_high);  // LED 켜기
    }
    else
    {
        IfxPort_setPinState(LED1, IfxPort_State_low);  // LED 끄기
    }
}
