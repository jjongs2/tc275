/**********************************************************************************************************************
 * \file ERU_Interrupt.c
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
#include "ERU_Interrupt.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define ISR_PRIORITY_SCUERU_INT0 40  // 인터럽트 우선순위

#define LED1 &MODULE_P10, 2         // Digital pin 13 - P10.2
#define REQ6 &IfxScu_REQ6_P02_0_IN  // Digital pin  2 - P02.0

/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/
static ERUconfig g_ERUconfig;  // ERU 설정 구조체

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
// 벡터 테이블에 ISR 등록
IFX_INTERRUPT(SCUERU_Int0_Handler, 0, ISR_PRIORITY_SCUERU_INT0);

// Interrupt Service Routine (ISR)
void SCUERU_Int0_Handler(void)
{
    IfxPort_setPinState(LED1, IfxPort_State_toggled);  // LED 토글
}

// General Purpose Input/Output (GPIO)
void initGPIO(void)
{
    // LED1 핀을 출력 모드로 설정
    IfxPort_setPinMode(LED1, IfxPort_Mode_outputPushPullGeneral);
}

// External Request Unit (ERU)
void initERU(void)
{
    // 입력 설정
    g_ERUconfig.reqPin       = REQ6;
    g_ERUconfig.inputChannel = (IfxScuEru_InputChannel)g_ERUconfig.reqPin->channelId;

    // SW1 핀을 입력 모드로 설정 + 입력 신호 선택
    IfxScuEru_initReqPin(g_ERUconfig.reqPin, IfxPort_InputMode_pullUp);

    // 에지 감지 설정
    IfxScuEru_enableFallingEdgeDetection(g_ERUconfig.inputChannel);

    // 트리거 펄스 활성화
    IfxScuEru_enableTriggerPulse(g_ERUconfig.inputChannel);

    // 출력 채널 설정
    g_ERUconfig.outputChannel = IfxScuEru_OutputChannel_0;
    g_ERUconfig.triggerSelect = IfxScuEru_InputNodePointer_0;
    IfxScuEru_connectTrigger(g_ERUconfig.inputChannel, g_ERUconfig.triggerSelect);

    // 인터럽트 게이팅 패턴 설정
    IfxScuEru_setInterruptGatingPattern(g_ERUconfig.outputChannel, IfxScuEru_InterruptGatingPattern_alwaysActive);

    // 서비스 요청 설정
    g_ERUconfig.src = &MODULE_SRC.SCU.SCU.ERU[(int)g_ERUconfig.outputChannel % 4];
    IfxSrc_init(g_ERUconfig.src, IfxSrc_Tos_cpu0, ISR_PRIORITY_SCUERU_INT0);
    IfxSrc_enable(g_ERUconfig.src);
}
