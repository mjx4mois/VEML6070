/*-----------------------------------------------------------------------
     Creator		: Morris chiou
     Sensor		: UV sensor
     File Name		: SENSOR_VEML6070.c
     Function		: SENSOR_VEML6070
     Create Date	: 2017/06/30
---------------------------------------------------------------------- */
#ifndef __VEML6070_FUNCTION__
#define __VEML6070_FUNCTION__

#include <stdio.h>
#include <math.h>
#include <delay.h>
#include <i2c.h>
#include "SENSOR_VEML6070.h"
#include "Porting_Layer.h"

//--------------------------------------------------------------------------------------------------
// initial & control  VEML6070 
// -> use define value : VEML6070_COMMAND
CHAR8S VEML6070_CONTROL(CHAR8U command)
{
		CHAR8S status = 0;
		
		i2c_stop_hang();
    		i2c_stop_hang();
		status = VEML6070_WRITE_REGISTER(command); 
		delay_ms(1);  
		
       	i2c_stop_hang();    
		i2c_stop_hang();	
		return status;
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Read UV data from VEML6070
CHAR8S VEML6070_READ_UV_DATA(INT16U *uv_data)
{

//VEML6070_READ_MSB_ADDRESS 	->	0x71
//VEML6070_READ_LSB_ADDRESS	->	0x73

	CHAR8S status = 0;
	CHAR8U MSB_D = 0,LSB_D = 0;
	INT16U raw_data=0;
	
	i2c_stop_hang();
    	i2c_stop_hang();
			
	status =  VEML6070_READ_DATA(VEML6070_READ_MSB_ADDRESS,&MSB_D);			//read MSB data
	if(status == 1)   
	{
		status = VEML6070_READ_DATA(VEML6070_READ_LSB_ADDRESS,&LSB_D);			//read LSB data
		if(status == 1)
			{
			
			raw_data|= (MSB_D<<8)+(LSB_D<<0);
			
			*uv_data = (INT16U)raw_data;
		//	printf("VEML6070 READ  ok\r\n");
			return 0;		//read ok
			}
		else
			{
		//	printf("VEML6070 READ LSB fail\r\n");
			return -1; 	//read fail
			}
	}
	else 
	{
	//	printf("VEML6070 READ MSB fail\r\n");
		return -1; 	//read fail
	}
	
	i2c_stop_hang();
    	i2c_stop_hang();
		
}
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
// special I2C protocol . write data to VEML6070 
CHAR8S VEML6070_WRITE_REGISTER(CHAR8U write_data)
{
	CHAR8S ack=0,busy=0;
	CHAR8U data ;//= write_data |(1<<1) & (~(0x03<<6));  //bit 7,6 ->0 ; bit 1 ->1 ;

      i2c_stop();
      busy = i2c_start();
      if(busy)
       {
        delay_us(50);
           ack=i2c_write(VEML6070_WRITE_ADDRESS);
           if(ack == 1)
            {
                    ack=i2c_write(data);
                       if(ack == 1)
                       {
                            i2c_stop();
                            delay_us(10);
                            return SWI2C_STATUS_OK;
                       }
                       else
                       {
                        printf("data error\r\n");
                        goto EXIT;
                       }
            }
            else
            {
                printf("address error\r\n");
                goto EXIT;

            }
     }
     else
     {
    EXIT:
         i2c_stop();
         delay_us(10);
         return SWI2C_STATUS_FAIL;
     }

}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// special I2C protocol . read data to VEML6070 
CHAR8S VEML6070_READ_DATA(CHAR8U addr,CHAR8U *read_data)
{

      CHAR8S ack=0,busy=0;

      i2c_stop();
      busy = i2c_start();
      if(busy)
       {
        delay_us(50);
           ack=i2c_write(addr | READ_BIT);
           if(ack == 1)
            {
               *read_data=i2c_read(MASTER_NACK);
               i2c_stop();
               delay_us(10);
               return SWI2C_STATUS_OK;
             }
            else
            {
                printf("address error\r\n");
                goto EXIT;

            }
     }
     else
     {
    EXIT:
         i2c_stop();
         delay_us(10);
         return SWI2C_STATUS_FAIL;
     }

}
//--------------------------------------------------------------------------------------------------


#endif		//#ifndef __VEML6070_FUNCTION__