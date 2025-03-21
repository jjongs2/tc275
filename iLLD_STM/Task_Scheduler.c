/**********************************************************************************************************************
 * \file Task_Scheduler.c
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

#include "Task_Scheduler.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define LED1 &MODULE_P10, 2  // Digital pin 13 - P10.2

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
uint32   g_counter1ms;  // 1ms 카운터
TaskFlag g_taskFlags;   // 작업 실행 준비 상태를 나타내는 플래그 집합

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
static void excuteTask1ms(void);
static void excuteTask10ms(void);
static void excuteTask100ms(void);
static void excuteTask1000ms(void);

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
// General Purpose Input/Output (GPIO)
void initGPIO(void)
{
    // LED1 핀을 출력 모드로 설정
    IfxPort_setPinMode(LED1, IfxPort_Mode_outputPushPullGeneral);
}

// 작업 스케줄링 함수
void excuteTasks(void)
{
    // 플래그 값에 따라 작업 실행
    if (g_taskFlags.isTask1msReady)
    {
        g_taskFlags.isTask1msReady = FALSE;
        excuteTask1ms();
    }

    if (g_taskFlags.isTask10msReady)
    {
        g_taskFlags.isTask10msReady = FALSE;
        excuteTask10ms();
    }

    if (g_taskFlags.isTask100msReady)
    {
        g_taskFlags.isTask100msReady = FALSE;
        excuteTask100ms();
    }

    if (g_taskFlags.isTask1000msReady)
    {
        g_taskFlags.isTask1000msReady = FALSE;
        excuteTask1000ms();
    }
}

static void excuteTask1ms(void)
{
    // 작업 없음
}

static void excuteTask10ms(void)
{
    // 작업 없음
}

static void excuteTask100ms(void)
{
    // 작업 없음
}

static void excuteTask1000ms(void)
{
    IfxPort_setPinState(LED1, IfxPort_State_toggled);  // LED 토글
}
