 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Ebraheem Ali
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Ebraheem Ali's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* port Module Id */
#define PORT_MODULE_ID    (124U)

/* port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/* Number of pins in a port */
#define NUMBER_OF_PORT_PINS	  (Port_PinType)(8)

/* 
 * Symbolic names of Port pins in a MCU(TM4C123GH6PM)
 */
#define PORT_PIN_0	(Port_PinType)(0)	
#define PORT_PIN_1	(Port_PinType)(1)	
#define PORT_PIN_2	(Port_PinType)(2)	
#define PORT_PIN_3	(Port_PinType)(3)	
#define PORT_PIN_4	(Port_PinType)(4)	
#define PORT_PIN_5	(Port_PinType)(5)	
#define PORT_PIN_6	(Port_PinType)(6)	
#define PORT_PIN_7	(Port_PinType)(7)	

/*
 * PORT IDs of MCU ports
 */
#define PORT_A_ID_0       (uint8)(0)
#define PORT_B_ID_1       (uint8)(1)
#define PORT_C_ID_2       (uint8)(2)
#define PORT_D_ID_3       (uint8)(3)
#define PORT_E_ID_4       (uint8)(4)
#define PORT_F_ID_5       (uint8)(5)

/*
 * Definitions for the level of PortPin
 */
#define PORT_PIN_LEVEL_LOW      (STD_LOW)
#define PORT_PIN_LEVEL_HIGH     (STD_HIGH)


/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Dio Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Dio_Cfg.h and Dio.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Dio_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_Cfg.h and Dio.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Dio_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port Init API */
#define PORT_INIT_SID				(uint8)0x00
 
/* Service ID for Port Set Pin Direction API */
#define PORT_SET_PIN_DIRECTION_SID		(uint8)0x01
 
/* Service ID for Port Get Version Info API */
#define PORT_GET_VERSION_INFO_SID		(uint8)0x03
 
/* Service ID for Port Set Pin Mode API */
#define PORT_SET_PIN_MODE_SID			(uint8)0x04
 
 /*****************************************************************************
 *                      DET Error Codes                                       *
 ******************************************************************************/
 /* DET code for Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN			(uint8)0x0A
 
 /* DET code for PortPin is not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE	        (uint8)0x0B

/* DET code API Port_Init service called with wrong parameter */ 
#define PORT_E_PARAM_CONFIG			(uint8)0x0C

/* DET code API Port_SetPinMode service called when mode is unchangeable or wrong mode entered */
#define PORT_E_INVALID_MODE			(uint8)0x0D  /* for wrong mode */
#define PORT_E_MODE_UNCHANGEABLE		(uint8)0x0E  /* for mode unchangeable */

/* DET code API service called without module initialization */
#define PORT_E_UNINIT				(uint8)0x0F

/* DET code APIs called with a NULL pointer */
#define PORT_E_PARAM_POINTER			(uint8)0x10

/******************************************************************************
 *                              Module Data Types                             *
 ******************************************************************************/
/* Type defining the symbolic name of a Port Pin */
typedef uint8 Port_PinType;

/* Description: Enum type for defining the direction of the Port Pin */
typedef enum
{
	PORT_PIN_IN,   /* configure port pin as input */
	PORT_PIN_OUT   /* configure port pin as output */
}Port_PinDirectionType;

/* Description: Enum type for defining the internal resistor of the Port Pin */
typedef enum
{
    OFF,	/* unactivate internal resistor */
    PULL_UP_ACTIVE,PULL_DOWN_ACTIVE
}Port_InternalResistorType;

/*
 * Description: Enum containing the PortPin Modes Symbolic names
 */
typedef enum
{
  PORT_PIN_MODE_DIO,               
  PORT_PIN_MODE_SPI,       
  PORT_PIN_MODE_CAN,        
  PORT_PIN_MODE_PWM,        
  PORT_PIN_MODE_LIN,        
  PORT_PIN_MODE_ICU,       
  PORT_PIN_MODE_MEM,       
  PORT_PIN_MODE_DIO_WDG,   
  PORT_PIN_MODE_DIO_GPT,   
  PORT_PIN_MODE_ADC
}Port_PinModeType;

/* 
 *	Description: 
 *		-> It's a container in the configuration tool has some parameters that configure an individual
 *		   PortPin.
 *              -> Structure to configure each individual port pin:
 *	1. the direction of port pin --> INPUT or OUTPUT
 *      2. the internal resistor --> Disable, Pull up or Pull down
 *      3. the initial value of port pin level in output case -> high or low
 *      4. port pin's Mode -> DIO, SPI, .... ,Analog
 *      5. pin direction changeability -> ON or OFF
 *      6. pin mode changeability -> ON or OFF
 *	7. initial pin mode -> DIO,ADC,SPI,...,ANALOG
 */
typedef struct
{
    uint8 PortId;	/* configure port number */
    Port_PinType PortPinId;	/* this value will be assigned to the symbolic name derived from the PortPin container short name */
    Port_PinModeType PortPinInitialMode;	/* PortPin mode from mode list used with Port_Init function */
    Port_PinDirectionType PortPinDirection; /* specific direction of the pin */
    uint8 PortPinLevelValue;	/* Pin level initial value */
    Port_InternalResistorType PortPinResistorValue; /* Activation of the internal resistor (OFF,PULL_UP,PULL_DOWN) */
    uint8 PortPinModeChangeable;		/* Pin mode changeable during run-time (STD_ON, STD_OFF) */
    uint8 PortPinDirectionChangeable;	/* Pin direction changeable during run-time (STD_ON, STD_OFF) */
}Port_PinConfigType;

/* 
 * Description : -> PortContainer collecting the PortPin.
 *		 -> contains an included container named PortPin.
 * 		 -> structure that is required for initialization API */
typedef struct{
	/* array of pointers to a configuration structure to optimize memory storage */
    Port_PinConfigType PortPin[PORT_NUM_OF_CONFIGURED_PORT_PINS];
}Port_ConfigType;

/******************************************************************************
 *                      Function Prototypes                                   *
 ******************************************************************************/
/******************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: non-reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to initiate the port driver.
*******************************************************************************/
 void Port_Init(const Port_ConfigType* ConfigPtr);
 
#if(PORT_SET_PIN_DIRECTION_API == STD_ON)
/******************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): PortPinNum        - PortPin ID number
*		   PortPinDirection  - PortPin direction (IN/OUT).	
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the direction of the portpin.
*******************************************************************************/
 void Port_SetPinDirection(Port_PinType PortPinNum,Port_PinDirectionType PortPinDirection);
#endif
 
#if(PORT_SET_PIN_MODE_API == STD_ON)
/******************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): PortPinIndex   - PortPin ID number
*		   PortPinMode  - New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function for setting the port pin mode API.
*******************************************************************************/ 
  void Port_SetPinMode(Port_PinType PortPinIndex,Port_PinModeType pinMode);
#endif
 
#if(PORT_VERSION_INFO_API == STD_ON)
/******************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: non-reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versionInfo	- Pointer to where to store the version information of this module.
* Return value: None
* Description: Function for returning the version information of the module.
*******************************************************************************/ 
  void Port_GetVersionInfo(Std_VersionInfoType* versionInfo);
#endif
   
 /*****************************************************************************
 *                       External Variables                                   *
 ******************************************************************************/
 
 /* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_PinConfigSet;

#endif /* PORT_H */
