 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Ebraheem Ali
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif
   
  STATIC const Port_ConfigType * Port_ChannelIndex = NULL_PTR;
  STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;
  
/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pin configuration:
*              - Setup the pin as Digital GPIO pin
*              - Setup the direction of the GPIO pin
*              - Provide initial value for o/p pin
*              - Setup the internal resistor for i/p pin
************************************************************************************/
void Port_Init(const Port_ConfigType * ConfigPtr )
{
    uint8 Pin_index;
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 delay = 0;
    
#if(PORT_DEV_ERROR_DETECT == STD_ON)
    if(NULL_PTR == ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_INIT_SID,PORT_E_PARAM_CONFIG);
    }
    else
#endif
    {
        Port_ChannelIndex = ConfigPtr;
        Port_Status = PORT_INITIALIZED;
    }
    
    for(Pin_index = 0; Pin_index < PORT_NUM_OF_CONFIGURED_PORT_PINS; Pin_index++)
    {
        switch(Port_ChannelIndex->PortPin[Pin_index]->PortId)
        {
            case  PORT_A_ID_0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                     break;
            case  PORT_B_ID_1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                     break;
            case  PORT_C_ID_2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                     break;
            case  PORT_D_ID_3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                     break;
            case  PORT_E_ID_4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                     break;
            case  PORT_F_ID_5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                     break;
        }
        
        /* Enable clock for PORT and allow time for clock to start*/
        SYSCTL_REGCGC2_REG |= (1<<Port_ChannelIndex->PortPin[Pin_index]->PortId);
        delay = SYSCTL_REGCGC2_REG;
        
        if( ((Port_ChannelIndex->PortPin[Pin_index]->PortId == 3) && (Port_ChannelIndex->PortPin[Pin_index]->PortPinId == 7)) || ((Port_ChannelIndex->PortPin[Pin_index]->PortId == 5) && (Port_ChannelIndex->PortPin[Pin_index]->PortPinId == 0)) ) /* PD7 or PF0 */
        {
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        }
        else if( (Port_ChannelIndex->PortPin[Pin_index]->PortId == 2) && (Port_ChannelIndex->PortPin[Pin_index]->PortPinId <= 3) ) /* PC0 to PC3 */
        {
            /* Do Nothing ...  this is the JTAG pins */
            continue;
        }
        else
        {
            /* Do Nothing ... No need to unlock the commit register for this pin */
        }
        
        if(Port_ChannelIndex->PortPin[Pin_index]->PortPinInitialMode == PORT_PIN_MODE_DIO)
        {
            /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId);      
           
            /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId);            
           
            /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_ChannelIndex->PortPin[Pin_index]->PortPinId * 4)); 
            
            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId); 
        }
        else if(Port_ChannelIndex->PortPin[Pin_index]->PortPinInitialMode == PORT_PIN_MODE_ADC)
        {
          /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
          SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId);
          
          /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId);
          
          /* Clear the PMCx bits for this pin */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_ChannelIndex->PortPin[Pin_index]->PortPinId * 4)); 
            
        }
        else /* Another mode */
        {
          /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId);

          /* Set the PMCx bits for this pin */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ((Port_ChannelIndex->PortPin[Pin_index]->PortPinInitialMode & 0x0000000F) << (Port_ChannelIndex->PortPin[Pin_index]->PortPinId * 4));        
          
          /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId); 
        }
        
        if(Port_ChannelIndex->PortPin[Pin_index]->PortPinDirection == PORT_PIN_OUT)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSETI:\Courses\EmbeddedSystem\ARM\__workspace\LED_CONTROL_PROJECT\Src\MCAL\GPIO\Port.h) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            
            if(Port_ChannelIndex->PortPin[Pin_index]->PortPinLevelValue == STD_HIGH)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
            }
            else
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
            }
        }
        else if(Port_ChannelIndex->PortPin[Pin_index]->PortPinDirection == PORT_PIN_IN)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
            
            if(Port_ChannelIndex->PortPin[Pin_index]->PortPinResistorValue == PULL_UP_ACTIVE)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
            }
            else if(Port_ChannelIndex->PortPin[Pin_index]->PortPinResistorValue == PULL_DOWN_ACTIVE)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
            }
            else
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_ChannelIndex->PortPin[Pin_index]->PortPinId);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
            }
        }
        else
        {
            /* Do Nothing */
        }
        
   }
}


#if(PORT_SET_PIN_DIRECTION_API == STD_ON)
/******************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): PortPinIndex      - PortPin Strcture index in the array if pointer to strcture *PortPin[43].
*		   PortPinDirection  - PortPin direction (IN/OUT).	
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the direction of the portpin.
*******************************************************************************/
 void Port_SetPinDirection(Port_PinType PortPinIndex,Port_PinDirectionType PortPinDirection)
 {
#if(PORT_DEV_ERROR_DETECT == STD_ON)
     if(PortPinIndex >= PORT_NUM_OF_CONFIGURED_PORT_PINS)
     {
          /* Trigger a Development error if the user tries to access with a non configured PortPin */
          Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_DIRECTION_SID,PORT_E_PARAM_PIN);
     }
     else 
     {    /* Do nothing */      }
     
     if(Port_Status != PORT_INITIALIZED)
     {
          /* Trigger a Development error if the user tries to use the Port_SetPinDirection API before initialize the Port Driver */
          Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_DIRECTION_SID,PORT_E_UNINIT);
     }
     else
     {    /* Do nothing */      }
     
     if(Port_ChannelIndex->PortPin[PortPinIndex]->PortPinDirectionChangeable == STD_OFF)
     {    
          /* Trigger a Development error if User tries to change the direction in the run-time, While it's configured unchangeable */
          Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_DIRECTION_SID,PORT_E_DIRECTION_UNCHANGEABLE);
     }
     else
     {    /* Do nothing */      }
#endif
     
     volatile uint32* PortGpio_Ptr = NULL_PTR;
     switch(Port_ChannelIndex->PortPin[PortPinIndex]->PortId)
     {
            case  PORT_A_ID_0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                     break;
            case  PORT_B_ID_1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                     break;
            case  PORT_C_ID_2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                     break;
            case  PORT_D_ID_3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                     break;
            case  PORT_E_ID_4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                     break;
            case  PORT_F_ID_5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                     break;
     }
     
     /* Skip changes if PortPinIndex is the index of PC0-PC3   */
     if((Port_ChannelIndex->PortPin[PortPinIndex]->PortId == PORT_C_ID_2) && (Port_ChannelIndex->PortPin[PortPinIndex]->PortPinId <= PORT_PIN_3))
     {
            /* Do nothing ... it is a JTAG pins */
            return;
     }
     else if(Port_ChannelIndex->PortPin[PortPinIndex]->PortPinDirection == PORT_PIN_OUT)
     {
            /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIR_REG_OFFSET),Port_ChannelIndex->PortPin[PortPinIndex]->PortPinId);
     }
     else if(Port_ChannelIndex->PortPin[PortPinIndex]->PortPinDirection == PORT_PIN_IN)
     {
            /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIR_REG_OFFSET),Port_ChannelIndex->PortPin[PortPinIndex]->PortPinId);
     }
     else
     {
            /* Do nothing */
     }
 }
#endif
 
                     
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
#if (PORT_VERSION_INFO_API == STD_ON)

void Port_GetVersionInfo(Std_VersionInfoType* versionInfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versionInfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
	}
	else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versionInfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versionInfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versionInfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versionInfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versionInfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
}
                     
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
void Port_SetPinMode(Port_PinType PortPinIndex,Port_PinModeType pinMode)
{
#if(PORT_DEV_ERROR_DETECT == STD_ON)
    if(PORT_INITIALIZED != Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_MODE_SID,PORT_E_UNINIT);
    }
    else
    {   /* Do nothing    */    }
    if(Port_ChannelIndex->PortPin[PortPinIndex]->PortPinModeChangeable == STD_OFF)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_MODE_SID,PORT_E_MODE_UNCHANGEABLE);
    }
    else
    {   /* Do nothing    */    }
    if(Port_ChannelIndex->PortPin[PortPinIndex]->PortPinId >= PORT_NUM_OF_CONFIGURED_PORT_PINS)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_MODE_SID,PORT_E_PARAM_PIN);
    }
    else
    {   /* Do nothing   */      }
#endif
    
    volatile uint32* PortGpio_Ptr = NULL_PTR;
     switch(Port_ChannelIndex->PortPin[PortPinIndex]->PortId)
     {
            case  PORT_A_ID_0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                     break;
            case  PORT_B_ID_1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                     break;
            case  PORT_C_ID_2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                     break;
            case  PORT_D_ID_3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                     break;
            case  PORT_E_ID_4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                     break;
            case  PORT_F_ID_5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                     break;
     }
     
     /* Skip changes if PortPinIndex is the index of PC0-PC3   */
     if((Port_ChannelIndex->PortPin[PortPinIndex]->PortId == PORT_C_ID_2) && (Port_ChannelIndex->PortPin[PortPinIndex]->PortPinId <= PORT_PIN_3))
     {
            /* Do nothing ... it is a JTAG pins */
            return;
     }
     else if(Port_ChannelIndex->PortPin[PortPinIndex]->PortPinInitialMode == PORT_PIN_MODE_DIO)
     {
            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this PortPin */
            SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),Port_ChannelIndex->PortPin[PortPinIndex]->PortPinId);
            
            /* Clear the corresponding bit in the GPIOAMSEL register to disable digital functionality on this PortPin */
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_ChannelIndex->PortPin[PortPinIndex]->PortPinId);
            
            /* Clear the PMCx bits for this pin */
            *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_CTL_REG_OFFSET)&=~(0x0000000F << (4*Port_ChannelIndex->PortPin[PortPinIndex]->PortPinId));
            
            /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET),Port_ChannelIndex->PortPin[PortPinIndex]->PortPinId);
     }
     else if(Port_ChannelIndex->PortPin[PortPinIndex]->PortPinInitialMode == PORT_PIN_MODE_ADC)
     {
             /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this PortPin */
            SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_ChannelIndex->PortPin[PortPinIndex]->PortPinId);

            /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this PortPin */
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),Port_ChannelIndex->PortPin[PortPinIndex]->PortPinId);
            
            /* Clear the PMCx bits for this pin */
            *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_CTL_REG_OFFSET)&=~(0x0000000F << (4*Port_ChannelIndex->PortPin[PortPinIndex]->PortPinId));
            
            /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET),Port_ChannelIndex->PortPin[PortPinIndex]->PortPinId);
     }
     else /*    Another Mode       */
     {
            /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_ChannelIndex->PortPin[PortPinIndex]->PortPinId);
                    
            /* Set the PMCx bits for this pin */
            *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ((pinMode & 0x0000000F) << 4 * Port_ChannelIndex->PortPin[PortPinIndex]->PortPinId);
            
            
     }
}
#endif
                    
