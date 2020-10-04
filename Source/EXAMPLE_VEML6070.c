/*-----------------------------------------------------------------------
     Creator :Morris chiou
     Sensor      : UV sensor
     File Name   : EXAMPLE_VEML6070.c
     Function    : EXAMPLE_VEML6070
     Create Date : 2017/06/30
---------------------------------------------------------------------- */

#include <mega32a.h>
#include <stdio.h>
#include <delay.h>
#include <math.h>
#include <i2c.h>
#include <alcd.h>
#include <datatype_Layer.h>
#include <swi2c_Layer.h>
#include <SENSOR_VEML6070.h>

void  EXAMPLE_VEML6070(void);


void  EXAMPLE_VEML6070(void)
{
	CHAR8S status = 0;
	CHAR8U run = 1;
	CHAR8U uva_slave;
	INT16U uv_data;
		
		printf("-------------------- UV VEML6070 --------------------\r\n");


		/*first run to set mode!*/
		if(run==1)
		{
			status =  VEML6070_READ_DATA((VEML6070_ARA_ADDRESS),&uva_slave);
			/*initial & control VEML6070 , enable VEML6070 sensor*/
			/*if change any parameter -> define  VEML6070_COMMAND*/
			status = VEML6070_CONTROL(VEML6070_COMMAND);  
			if(status!=1)
			{
				printf("VEML6070 set mode fail !\r\n");
			}
			else
			{
				printf("VEML6070 set mode success !\r\n");
			}
			run=0;	

		       /*power on delay 200ms*/
			delay_ms(200);
		}

		while(1)
		{		
		
			/*if change any parameter -> define  VEML6070_COMMAND*/
			//status = VEML6070_CONTROL(VEML6070_COMMAND);   
			//if(status!=0) printf("VEML6070 set mode fail !\r\n");
			
			i2c_stop_hang();
    			i2c_stop_hang();
				
			status = VEML6070_READ_UV_DATA(&uv_data); 
			if(status!=0) 
			{
				printf("VEML6070 set mode fail !\r\n");
			}
			else 
			{
				printf("VEML6070 UV data = %d\r\n", uv_data);
			}

			
			//VEML6070_READ_DATA(0x30,&uva_slave);
			/*Rset =270k , if set 1T -> delay 125mS */
			//delay_ms(70);
	
			delay_ms(180);
			//i2c_stop_hang();
    			i2c_stop_hang();

			status =  VEML6070_READ_DATA((VEML6070_ARA_ADDRESS),&uva_slave);

			//i2c_stop_hang();
    			i2c_stop_hang();
			/*
				UV RANGE
				Extreme ; Very High ; High ; Moderate ; Low
				see VEML6070 application note & Rset & refresh time!
			*/
			if(uv_data<=560)
			{
				printf("LOW\r\n");
			}
			else if(uv_data>560 && uv_data<=1120)
			{
				printf("MID\r\n");
			}
			else if(uv_data>1121 && uv_data<=1494)
			{
				printf("HIGH\r\n"); 
			}
			else if(uv_data>1495 && uv_data<=2054)
			{
				printf("VHIGH\r\n");    
			}
			else if(uv_data>2055)
			{
				printf("EXT!!\r\n"); 	
			}


			/* show uv data */
			lcd_gotoxy(0,0);
	            	lcd_putsf("UV data:");     
   			
			lcd_putchar(48+(uv_data/1000)%10);
			lcd_putchar(48+(uv_data/100)%10);
			lcd_putchar(48+(uv_data/10)%10);
			lcd_putchar(48+(uv_data)%10);

			/* show UV level */
			lcd_gotoxy(0,1);
			lcd_putsf("UI LEVEL:");     
			if(uv_data<=560)lcd_putsf("LOW ");
			else if(uv_data>560 && uv_data<=1120)lcd_putsf("MID "); 
			else if(uv_data>1121 && uv_data<=1494)lcd_putsf("HIGH"); 
			else if(uv_data>1495 && uv_data<=2054)lcd_putsf("VHIGH");    
			else if(uv_data>2055)lcd_putsf("EXT!"); 	

				
		}
		
		printf("-------------------- UV VEML6070 --------------------\r\n");
	
}
