/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Ebraheem Ali
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif


const Port_ConfigType Port_PinConfigSet = {
  {
      /* PORT_A Pins configuration */
      &(Port_PinConfigType){PORT_A_ID_0,PORT_PIN_0,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_A_ID_0,PORT_PIN_1,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_A_ID_0,PORT_PIN_2,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_A_ID_0,PORT_PIN_3,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_A_ID_0,PORT_PIN_4,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_A_ID_0,PORT_PIN_5,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_A_ID_0,PORT_PIN_6,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_A_ID_0,PORT_PIN_7,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      /* PORT_B Pins configuratoin */
      &(Port_PinConfigType){PORT_B_ID_1,PORT_PIN_0,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_B_ID_1,PORT_PIN_1,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_B_ID_1,PORT_PIN_2,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_B_ID_1,PORT_PIN_3,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_B_ID_1,PORT_PIN_4,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_B_ID_1,PORT_PIN_5,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_B_ID_1,PORT_PIN_6,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_B_ID_1,PORT_PIN_7,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      /* PORT_C Pins configuration */
      &(Port_PinConfigType){PORT_C_ID_2,PORT_PIN_0,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_C_ID_2,PORT_PIN_1,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_C_ID_2,PORT_PIN_2,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_C_ID_2,PORT_PIN_3,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_C_ID_2,PORT_PIN_4,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_C_ID_2,PORT_PIN_5,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_C_ID_2,PORT_PIN_6,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_C_ID_2,PORT_PIN_7,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      /* PORT_D Pins configuration */
      &(Port_PinConfigType){PORT_D_ID_3,PORT_PIN_0,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_D_ID_3,PORT_PIN_1,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_D_ID_3,PORT_PIN_2,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_D_ID_3,PORT_PIN_3,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_D_ID_3,PORT_PIN_4,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_D_ID_3,PORT_PIN_5,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_D_ID_3,PORT_PIN_6,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_D_ID_3,PORT_PIN_7,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      /* PORT_E Pins configuration */
      &(Port_PinConfigType){PORT_E_ID_4,PORT_PIN_0,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_E_ID_4,PORT_PIN_1,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_E_ID_4,PORT_PIN_2,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_E_ID_4,PORT_PIN_3,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_E_ID_4,PORT_PIN_4,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_E_ID_4,PORT_PIN_5,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},

      /* PORT_F Pins configuration */
      &(Port_PinConfigType){PORT_F_ID_5,PORT_PIN_0,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_F_ID_5,PORT_PIN_1,PORT_PIN_MODE_DIO,PORT_PIN_OUT,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_F_ID_5,PORT_PIN_2,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_F_ID_5,PORT_PIN_3,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,OFF,STD_ON,STD_ON},
      &(Port_PinConfigType){PORT_F_ID_5,PORT_PIN_4,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_LEVEL_LOW,PULL_UP_ACTIVE,STD_ON,STD_ON}
  }
};