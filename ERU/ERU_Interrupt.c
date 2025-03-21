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
#include "IfxPort_bf.h"
#include "IfxScuEru.h"
#include "IfxSrc.h"
#include "IfxSrc_bf.h"

#include "ERU_Interrupt.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define ISR_PRIORITY_SCUERU_INT0 40  // 인터럽트 우선순위

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
// 벡터 테이블에 ISR 등록
IFX_INTERRUPT(SCUERU_Int0_Handler, 0, ISR_PRIORITY_SCUERU_INT0);

// Interrupt Service Routine (ISR)
void SCUERU_Int0_Handler(void)
{
    P10_OMR.U = (IFX_P_OMR_PS2_MSK << IFX_P_OMR_PS2_OFF) | (IFX_P_OMR_PCL2_MSK << IFX_P_OMR_PCL2_OFF);  // LED 토글
}

// General Purpose Input/Output (GPIO)
void initGPIO(void)
{
    // LED1 핀을 출력 모드로 설정
    P10_IOCR0.U &= ~(IFX_P_IOCR0_PC2_MSK << IFX_P_IOCR0_PC2_OFF);
    P10_IOCR0.U |= (MyPort_Mode_outputPushPullGeneral << IFX_P_IOCR0_PC2_OFF);

    // SW1 핀을 입력 모드로 설정
    P02_IOCR0.U &= ~(IFX_P_IOCR0_PC0_MSK << IFX_P_IOCR0_PC0_OFF);
    P02_IOCR0.U |= (MyPort_Mode_inputPullUp << IFX_P_IOCR0_PC0_OFF);
}

// External Request Unit (ERU)
void initERU(void)
{
    // 입력 신호 선택
    SCU_EICR1.U &= ~(IFX_SCU_EICR_EXIS1_MSK << IFX_SCU_EICR_EXIS1_OFF);
    SCU_EICR1.U |= (Ifx_RxSel_c << IFX_SCU_EICR_EXIS1_OFF);

    // 에지 감지 설정
    SCU_EICR1.U |= (IFX_SCU_EICR_FEN1_MSK << IFX_SCU_EICR_FEN1_OFF);

    // 트리거 펄스 활성화
    SCU_EICR1.U |= (IFX_SCU_EICR_EIEN1_MSK << IFX_SCU_EICR_EIEN1_OFF);

    // 출력 채널 설정
    SCU_EICR1.U &= ~(IFX_SCU_EICR_INP1_MSK << IFX_SCU_EICR_INP1_OFF);
    SCU_EICR1.U |= (IfxScuEru_InputNodePointer_0 << IFX_SCU_EICR_INP1_OFF);

    // 인터럽트 게이팅 패턴 설정
    SCU_IGCR0.U &= ~(IFX_SCU_IGCR_IGP0_MSK << IFX_SCU_IGCR_IGP0_OFF);
    SCU_IGCR0.U |= (IfxScuEru_InterruptGatingPattern_alwaysActive << IFX_SCU_IGCR_IGP0_OFF);

    // 서비스 요청 우선순위 설정
    SRC_SCU_SCU_ERU0.U &= ~(IFX_SRC_SRCR_SRPN_MSK << IFX_SRC_SRCR_SRPN_OFF);
    SRC_SCU_SCU_ERU0.U |= (ISR_PRIORITY_SCUERU_INT0 << IFX_SRC_SRCR_SRPN_OFF);

    // 서비스 요청 활성화
    SRC_SCU_SCU_ERU0.U |= (IFX_SRC_SRCR_SRE_MSK << IFX_SRC_SRCR_SRE_OFF);

    // 서비스 제공자 설정
    SRC_SCU_SCU_ERU0.U &= ~(IFX_SRC_SRCR_TOS_MSK << IFX_SRC_SRCR_TOS_OFF);
    SRC_SCU_SCU_ERU0.U |= (IfxSrc_Tos_cpu0 << IFX_SRC_SRCR_TOS_OFF);
}
