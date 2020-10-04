/*-----------------------------------------------------------------------
     Creator		: Morris chiou
     Sensor		: UV sensor
     File Name		: SENSOR_VEML6070.h
     Function		: SENSOR_VEML6070
     Create Date	: 2017/06/30
---------------------------------------------------------------------- */
#ifndef __VEML6070_HEADER__
#define __VEML6070_HEADER__


/*--------------------------------- Define SLAVE ADDRESS -------------------------------------*/
/*VMEL6070 SLAVE ADDRESS*/
/*Note : if write data -> 0x70 ; read MSB byte -> 0x73 , read LSB byte -> 0x71*/
#define VEML6070_WRITE_ADDRESS 			(0x70)
#define VEML6070_READ_MSB_ADDRESS		(0x73)
#define VEML6070_READ_LSB_ADDRESS		(0x71)
#define VEML6070_ARA_ADDRESS				(0x18)
/*--------------------------------- Define SLAVE ADDRESS -------------------------------------*/


/*--------------------------------- Command Register bit -------------------------------------*/
/* Note : only write data -> address = 0x70 use this Commad register !*/
/* ** bit 7,6 -> 0 ; bit 1 -> 1*/
#define VEML6070_REG_RESERVED				(0x02)

#define VEML6070_REG_ACK 					(1<<5)		/*acknowledge activity setting*/
#define VEML6070_REG_ACL_THD				(1<<4)		/*acknowledge threshold window setting for byte mode usage*/

/*
	integration time setting  with PIN Rset to set REFRESH TIME , see the VEML sepc page.8!
			bit 3		bit 2		Time
			0		0		(1/2)*T
			0		1		1*T
			1		0		2*T
			1		1		4*T
*/
#define VEML6070_REG_IT_0_5T				(0x00)
#define VEML6070_REG_IT_1T					(0x01<<2)
#define VEML6070_REG_IT_2T		       		(0x02<<2)
#define VEML6070_REG_IT_4T					(0x03<<2)

/* shutdown mode setting */
#define VEML6070_REG_SD_ON					(1<<0)		/*1->enable*/
#define VEML6070_REG_SD_OFF				(0<<0)		/*0->disable*/


/*SET refresh time*/
#define VEML6070_REF_TIME	 				(VEML6070_REG_IT_1T)
/*SET VEML6070 ON/OFF*/
#define VEML6070_ON_OFF		 				(VEML6070_REG_SD_OFF)			/*disable shutdown mode*/

/*SET the command ! TO ** VEML6070_CONTROL function ***/
#define VEML6070_COMMAND	  				(VEML6070_REG_RESERVED  | VEML6070_REF_TIME  | VEML6070_ON_OFF )	
/*--------------------------------- Command Register bit -------------------------------------*/


/********************************************** SYSTEM **************************************************/
/*--------------------------------------------------------------------------------------------------*/
/* initial & control  VEML6070*/ 
/* -> use define value : VEML6070_COMMAND*/
CHAR8S VEML6070_CONTROL(CHAR8U command);
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/* Read UV data from VEML6070*/
CHAR8S VEML6070_READ_UV_DATA(INT16U *uv_data);
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/* special I2C protocol . write data to VEML6070*/ 
CHAR8S VEML6070_WRITE_REGISTER(CHAR8U write_data);
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/* special I2C protocol . read data to VEML6070*/ 
CHAR8S VEML6070_READ_DATA(CHAR8U addr,CHAR8U *read_data);
/*--------------------------------------------------------------------------------------------------*/
/********************************************** SYSTEM **************************************************/
#endif		/*#ifndef __VEML6070_HEADER__*/