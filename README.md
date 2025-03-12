# TC275

Infineon AURIX™ TC275 보드와 Easy Module Shield V1를 활용한 기초 프로젝트

<br>

## Projects

|   Name   | Abstract                                        | Base Example                                                                                                                                       |
| :------: | :---------------------------------------------- | :------------------------------------------------------------------------------------------------------------------------------------------------- |
| **ADC**  | 아날로그 신호(가변저항) 측정                    | [ADC_Background_Scan_1_KIT_TC275_LK](https://github.com/Infineon/AURIX_code_examples/tree/master/code_examples/ADC_Background_Scan_1_KIT_TC275_LK) |
| **ERU**  | 스위치로 외부 인터럽트를 발생시켜 LED 제어      | [ERU_Interrupt_1_KIT_TC275_LK](https://github.com/Infineon/AURIX_code_examples/tree/master/code_examples/ERU_Interrupt_1_KIT_TC275_LK)             |
| **GPIO** | 스위치 상태에 따라 LED 제어                     | [GPIO_LED_Button_1_KIT_TC275_LK](https://github.com/Infineon/AURIX_code_examples/tree/master/code_examples/GPIO_LED_Button_1_KIT_TC275_LK)         |
| **PWM**  | ADC 값에 따라 PWM 신호를 생성하여 LED 밝기 조절 | [GTM_TOM_PWM_1_KIT_TC275_SB](https://github.com/Infineon/AURIX_code_examples/tree/master/code_examples/GTM_TOM_PWM_1_KIT_TC275_SB)                 |
| **STM**  | STM 인터럽트를 활용하여 작업 스케줄러 구현      | [STM_Interrupt_1_KIT_TC275_SB](https://github.com/Infineon/AURIX_code_examples/tree/master/code_examples/STM_Interrupt_1_KIT_TC275_SB)             |

- 접두사 `iLLD_`가 붙은 프로젝트는 [iLLD(Infineon Low Level Driver)](https://www.infineon.com/aurix-expert-training/TC27D_iLLD_UM_1_0_1_16_0.chm)를 사용함

<br>

## Prerequisites

- [AURIX™ Development Studio](https://softwaretools.infineon.com/tools/com.ifx.tb.tool.aurixide)
- AURIX™ TC275 보드 ([KIT_AURIX_TC275_ARD_SB](https://www.infineon.com/cms/en/product/evaluation-boards/kit_aurix_tc275_ard_sb/))
- Easy Module Shield V1

<br>

## Usage

1. AURIX™ Development Studio 실행
2. **File** > **New** > **New AURIX Project** 선택
3. Target Device 선택 (hitex ShieldBuddy, KIT_AURIX_TC275_ARD_SB, TC27xTP_D-Step)

   <img src="https://dydi59svggub9.cloudfront.net/tc275/target-device.png" alt="Select target device" width="600">

4. 프로젝트 생성
5. 소스 파일과 헤더 파일을 프로젝트 디렉터리에 복사

   - KIT_AURIX_TC275_LITE 보드를 사용하는 경우, 코드에 정의(`#define`)되어 있는 핀 할당을 하드웨어 구성에 맞게 변경해 주어야 함

6. 프로젝트를 빌드하고 보드에 플래시하여 실행
