/*
 * OV7670.c
 *
 * Created: 15/02/2013 13:12:12
 *  Author: hslovett
 */ 


#include <asf.h>
#include "CustomDevices/CustomDevices.h"
#include "stdio.h"
// Camera
// #include "CustomDevices/OV7670.h"
// I2C Mux
// #include "CustomDevices/PCA9542A.h"
// MotorDriver
// /*#include "CustomDevices/MotorDriver.h"*/
// SDCard
// #include "CustomDevices/SD_Card.h"

__attribute__((__interrupt__)) static void VSYNC0_Handler (void)
{
	//print_dbg("\n\rVSYNC0 Detected!");
	eic_clear_interrupt_line(&AVR32_EIC, VSYNC_0_LINE);
	//VSYNC_0_DISABLE_INTERRUPT;
	switch(OV7670_Status.VSYNC0_State)
	{
		case(TAKE_PHOTO):
			FIFO_0_WEN_SET;
			OV7670_Status.VSYNC0_State = TAKING_PHOTO;
			break;
			
		case(TAKING_PHOTO):
			FIFO_0_WEN_CLR;
			OV7670_Status.VSYNC0_State = TAKEN_PHOTO;
			break;
		
		case (TAKEN_PHOTO):
			FIFO_0_WEN_CLR;
			break;
			
		case(IDLE):
		default:
			VSYNC_0_DISABLE_INTERRUPT;
			FIFO_0_WEN_CLR;
			OV7670_Status.VSYNC0_State = IDLE;
			break;
	}
}

__attribute__((__interrupt__)) static void VSYNC1_Handler (void)
{
	//print_dbg("\n\rVSYNC1 Detected!");
	eic_clear_interrupt_line(&AVR32_EIC, VSYNC_1_LINE);
	//VSYNC_1_DISABLE_INTERRUPT;
		switch(OV7670_Status.VSYNC1_State)
		{
			case(TAKE_PHOTO):
			FIFO_1_WEN_SET;
			OV7670_Status.VSYNC1_State = TAKING_PHOTO;
			break;
			
			case(TAKING_PHOTO):
			FIFO_1_WEN_CLR;
			OV7670_Status.VSYNC1_State = TAKEN_PHOTO;
			break;
			
			case (TAKEN_PHOTO):
			FIFO_1_WEN_CLR;
			break;
			
			case(IDLE):
			default:
			VSYNC_1_DISABLE_INTERRUPT;
			FIFO_1_WEN_CLR;
			OV7670_Status.VSYNC1_State = IDLE;
			break;
		}
}
unsigned char Write_Reg(unsigned char Register, unsigned char Data)
{
	/*	I2C Traffic Generated:
	 *	S | OV_7670 + W | A | RegID | A | Data | A | P |
	 */
	uint8_t Buff[2] = {Register, Data};
	int status = twim_write(&AVR32_TWIM0, &Buff, 2, OV7670_ADDR, false);
	return status;
}
unsigned char Read_Reg(unsigned char Register, unsigned char *Data)
{
	/*	I2C Traffic Generated:
	 *	S	|	OV_ADDR + W	| A | RegID | A | P |
	 *	S	|	OV_ADDR + R | A | Data	|~A | P |
	 */
	unsigned char Buff[2] = {Register, 0};
	int status = twim_write(&AVR32_TWIM0, &Buff, 1, OV7670_ADDR, false);
	if(status != STATUS_OK)
		return status;
		
	status = twim_read(&AVR32_TWIM0, &Buff, 1, OV7670_ADDR, false);
	*Data = Buff[0];
	
	return status;
	
}
void OV7670_Init()
{
	
	//Check Cameras Exist
	PCA9542A_Chan_Sel(I2C_CHANNEL_0);
	if (twim_probe(&AVR32_TWIM0, OV7670_ADDR) == STATUS_OK)
		OV7670_Status.Camera_0_Found = true;
	else
		OV7670_Status.Camera_0_Found = false;
		
	PCA9542A_Chan_Sel(I2C_CHANNEL_1);
	if (twim_probe(&AVR32_TWIM0, OV7670_ADDR) == STATUS_OK)
		OV7670_Status.Camera_1_Found = true;
	else
		OV7670_Status.Camera_1_Found = false;
		
	
	//Iniialise Cameras
	if(OV7670_Status.Camera_0_Found)
	{
		PCA9542A_Chan_Sel(I2C_CHANNEL_0);
		//Reset Camera
		if(STATUS_OK != Write_Reg(OV_COM7, 0x80))
		{
			print_dbg("\n\rCamera Reset Fail");
			OV7670_Status.Camera_0_Error = true;
			OV7670_Status.Error = true;
			//return FAIL;
		}
		delay_ms(10); //wait for Camera to reset
		for (int i = 0; i < SETTINGS_LENGTH; i++)
		{
			if(STATUS_OK != Write_Reg(default_settings[i][0], default_settings[i][1]))
			{
				print_dbg("\n\rCamera Initialise Fail");
				//return FAIL;
				OV7670_Status.Camera_0_Error = true;	
				OV7670_Status.Error = true;	
				break;
			}
			delay_ms(1);
		}	
	}
	if(OV7670_Status.Camera_1_Found)
	{
		PCA9542A_Chan_Sel(I2C_CHANNEL_1);

		//Reset Camera
		if(STATUS_OK != Write_Reg(OV_COM7, 0x80))
		{
			print_dbg("\n\rCamera Reset Fail");
			OV7670_Status.Camera_1_Error = true;
			OV7670_Status.Error = true;
			//return FAIL;
		}
		delay_ms(10); //wait for Camera to reset
		for (int i = 0; i < SETTINGS_LENGTH; i++)
		{
			if(STATUS_OK != Write_Reg(default_settings[i][0], default_settings[i][1]))
			{
				print_dbg("\n\rCamera Initialise Fail");
				//return FAIL;
				OV7670_Status.Camera_1_Error = true;
				OV7670_Status.Error = true;				
				break;
			}
			delay_ms(1);
		}
	}
	PCA9542A_Chan_Sel(NO_SELECT);
	
	//Initialise VSYNC Interrupts
	eic_options_t eic_options;
	eic_options.eic_mode = EIC_MODE_EDGE_TRIGGERED;
	eic_options.eic_edge = EIC_EDGE_FALLING_EDGE;
	eic_options.eic_async = EIC_SYNCH_MODE;
	eic_options.eic_line = VSYNC_1_LINE;
	//eic_options.eic_line = VSYNC_0_LINE;
	
	Disable_global_interrupt();
	gpio_enable_module_pin(VSYNC_1_PIN, VSYNC_1_FUNCTION);
	gpio_enable_module_pin(VSYNC_0_PIN, VSYNC_0_FUNCTION);
	
	gpio_enable_pin_pull_up(VSYNC_1_PIN); //Enable pull up as it is a low level interrupt
	gpio_enable_pin_pull_up(VSYNC_0_PIN);
	//Initialise EIC
	eic_init(&AVR32_EIC, &eic_options, 1);
	eic_options.eic_line = VSYNC_0_LINE;
	eic_init(&AVR32_EIC, &eic_options, 1);
	
	INTC_register_interrupt(&VSYNC1_Handler, AVR32_EIC_IRQ_1, AVR32_INTC_INT0);
	INTC_register_interrupt(&VSYNC0_Handler, AVR32_EIC_IRQ_4, AVR32_INTC_INT0);
	//Enable interrupt on VSYNC1
	eic_enable_line(&AVR32_EIC, VSYNC_1_LINE);
	eic_enable_line(&AVR32_EIC, (VSYNC_0_LINE));
 	VSYNC_1_ENABLE_INTERRUPT;
 	VSYNC_0_ENABLE_INTERRUPT;
	
	FIFO_Init();
	//Enable_global_interrupt();
	
}
void FIFO_Init()
{
	//Disable both outputs
	FIFO_0_nOE_SET
	FIFO_1_nOE_SET
	
	//Reset Buffer 0
	FIFO_0_WRST_CLR;
	FIFO_0_RCLK_CLR;
	FIFO_0_nRRST_SET;
	FIFO_0_WEN_CLR;
	delay_us(10);
	FIFO_0_RCLK_SET;
	delay_us(10);
	FIFO_0_RCLK_CLR;
	FIFO_0_nRRST_CLR;
	delay_us(10);
	FIFO_0_RCLK_SET;
	delay_us(10);
	FIFO_0_RCLK_CLR;
	FIFO_0_nRRST_SET;
	delay_us(10);
	FIFO_0_WRST_SET;
	
	//Reset Buffer 1
	FIFO_1_WRST_CLR;
	FIFO_1_RCLK_CLR;
	FIFO_1_nRRST_SET;
	FIFO_1_WEN_CLR;
	delay_us(10);
	FIFO_1_RCLK_SET;
	delay_us(10);
	FIFO_0_RCLK_CLR;
	FIFO_1_nRRST_CLR;
	delay_us(10);
	FIFO_1_RCLK_SET;
	delay_us(10);
	FIFO_1_RCLK_CLR;
	FIFO_1_nRRST_SET;
	delay_us(10);
	FIFO_1_WRST_SET;
}

void FIFO_Reset(uint8_t CameraID)
{
	FIFO_0_nOE_SET;
	FIFO_1_nOE_SET;
	if(CameraID & CAMERA_LEFT)
	{
		FIFO_0_WRST_CLR;
		FIFO_0_nRRST_CLR;
		FIFO_0_RCLK_SET;
		FIFO_0_RCLK_CLR;
		FIFO_0_nRRST_SET;
		FIFO_0_WRST_SET;
	}
	if(CameraID & CAMERA_RIGHT)
	{
		FIFO_1_WRST_CLR;
		FIFO_1_nRRST_CLR;
		FIFO_1_RCLK_SET;
		FIFO_1_RCLK_CLR;
		FIFO_1_nRRST_SET;
		FIFO_1_WRST_SET;
	}
	
}

int TakePhoto(uint8_t Cameras)
{
	VSYNC_0_ENABLE_INTERRUPT;
	VSYNC_1_ENABLE_INTERRUPT;
	//Only want to take pictures on cameras found
	if(((OV7670_Status.VSYNC0_State != IDLE) || !OV7670_Status.Camera_0_Found) && ((OV7670_Status.VSYNC1_State != IDLE) || !OV7670_Status.Camera_1_Found))
		return CAMERAS_BUSY; //wait for cameras to be idle if they are found
	
	if(Cameras & CAMERA_LEFT)
		OV7670_Status.VSYNC0_State = TAKE_PHOTO;
		
	if(Cameras & CAMERA_RIGHT)
		OV7670_Status.VSYNC1_State = TAKE_PHOTO;
	
	return TAKING_PHOTO;
	
}

bool Photos_Ready(void)
{
	int status = 0;
	if(OV7670_Status.Camera_0_Found == true) //If camera is there
	{ 
		if(OV7670_Status.Camera_0_Error == false)//and has no errors
		{
			if(OV7670_Status.VSYNC0_State == TAKEN_PHOTO)
			{
				status |= 1; //camera0 has taken photo
			}
		}
		else
			status |= 1;
	}
	else
		status |= 1;		
		
	if(OV7670_Status.Camera_1_Found == true) //If camera is there
	{
		if(OV7670_Status.Camera_1_Error == false)//and has no errors
		{
			if(OV7670_Status.VSYNC1_State == TAKEN_PHOTO)
			{
				status |= 1; //camera0 has taken photo
			}
		}
		else
		status |= 1;
	}
	else
		status |= 1;
		
	if(status)
		return true;
	else
		return false;
}



bool Store_Both_Images()
{
	if(Photos_Ready() == false)
		return false;
	
	Store_Image_1();
	FIFO_Reset(CAMERA_RIGHT);
	
	Store_Image_0();
	FIFO_Reset(CAMERA_LEFT);
	
	return true;
}
void Store_Image_0()
{ 
	int i,j;
	//Image0
	//make file
	//delete file if it exits already
	char Filename_buff[15];
	i = 0;
	while(1)
	{
		nav_filelist_reset();
		sprintf(&Filename_buff, Image0Name, i++);
		if(nav_filelist_findname((FS_STRING)Filename_buff, false))
		{
			//nav_setcwd((FS_STRING)Image0Name, true, false);
// 			print_dbg("\n\r File Exists");
// 			print_dbg(&Filename_buff);
			//nav_file_del(false);
		}
		else
		{
			break;
		}
	}	
	nav_file_create((FS_STRING)Filename_buff);//create file
	
	file_open(FOPEN_MODE_W);
	//write bitmap headers
	file_write_buf(BMPHeader, BMPHEADERSIZE);
	file_write_buf(DIBHead, DIBHEADERSIZE);
	
	//read and write image data
	//Image0
	//reset read pointer
	FIFO_0_nRRST_CLR;
	FIFO_0_RCLK_SET;

	FIFO_0_RCLK_CLR;
	FIFO_0_nRRST_SET;
	
	//enable output
	FIFO_0_nOE_CLR;
	uint8_t buffer[WIDTH * 2];
	
	for(j = 0; j < HEIGHT; j++)
	{
		for(i = 0; i < WIDTH*2; i+=2)
		{
			FIFO_0_RCLK_SET;
			buffer[i+1] = ((AVR32_GPIO.port[1].pvr) & 0xFF);//CAMERA_INPUT;
			FIFO_0_RCLK_CLR;
			FIFO_0_RCLK_SET;
			buffer[i] = ((AVR32_GPIO.port[1].pvr) & 0xFF);//CAMERA_INPUT;
			FIFO_0_RCLK_CLR;
		}
		file_write_buf(&buffer, WIDTH * 2);
	}
	FIFO_0_nOE_SET;
	file_close();

	
}

void Store_Image_1()
{
	int i, j;
	uint8_t buffer[WIDTH * 2];
	char Filename_buff[15];
	i = 0;
	//make file
	//delete file if it exits already
	nav_filelist_reset();
	while(1)
	{
		sprintf(&Filename_buff, Image1Name, i++);
		if(nav_filelist_findname((FS_STRING)Filename_buff, false))
		{
			//nav_setcwd((FS_STRING)Image1Name, true, false);
			//print_dbg("\n\rImage1.bmp File Exists");
			//nav_file_del(false);
		}
		else
		{
			break;
		}
	}	
	nav_file_create((FS_STRING)Filename_buff);//create file
	file_open(FOPEN_MODE_W);
	//write bitmap headers
	file_write_buf(BMPHeader, BMPHEADERSIZE);
	file_write_buf(DIBHead, DIBHEADERSIZE);
	//Image1
	//reset read pointer
	FIFO_1_nRRST_CLR;
	FIFO_1_RCLK_SET;

	FIFO_1_RCLK_CLR;
	FIFO_1_nRRST_SET;
	
	//enable output
	FIFO_1_nOE_CLR;
	/*uint8_t buffer[WIDTH * 2];*/
	
	for(j = 0; j < HEIGHT; j++)
	{
		for(i = 0; i < WIDTH*2; i+=2)
		{
			FIFO_1_RCLK_SET;
			buffer[i+1] = ((AVR32_GPIO.port[1].pvr) & 0xFF);//CAMERA_INPUT;
			FIFO_1_RCLK_CLR;
			delay_us(1);
			FIFO_1_RCLK_SET;
			buffer[i] = ((AVR32_GPIO.port[1].pvr) & 0xFF);//CAMERA_INPUT;
			FIFO_1_RCLK_CLR;
		}
		file_write_buf(&buffer, WIDTH * 2);
	}
	FIFO_1_nOE_SET;//disable output
	file_close();
}