/**
 * \file
 *
 * \brief User board configuration template
 *
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

//Clock
#define FOSC0           16000000                                //!< Osc0 frequency: Hz.
#define OSC0_STARTUP    AVR32_SCIF_OSCCTRL0_STARTUP_2048_RCOSC  //!< Osc0 startup time: RCOsc periods.

#define BOARD_OSC0_HZ           16000000
#define BOARD_OSC0_STARTUP_US   2000
#define BOARD_OSC0_IS_XTAL      true
#define BOARD_OSC32_HZ          32768
#define BOARD_OSC32_STARTUP_US  71000
#define BOARD_OSC32_IS_XTAL     true


//SDRAM 

//! Part header file of used SDRAM(s).
#define SDRAM_PART_HDR  "mt48lc16m16a2tg7e/mt48lc16m16a2tg7e.h"

//! Data bus width to use the SDRAM(s) with (16 or 32 bits; always 16 bits on
//! UC3).
#define SDRAM_DBW       16

//USB


/*! \name USB Definitions
 */
//! @{
//! Multiplexed pin used for USB_ID: AVR32_USBC_ID_x.
//! To be selected according to the AVR32_USBC_ID_x_PIN and
//! AVR32_USBC_USB_ID_FUNCTION definitions from <avr32/uc3cxxxx.h>.
#define USB_ID                             AVR32_USBC_ID_

//! Multiplexed pin used for USB_VBOF: AVR32_USBC_VBOF_x.
//! To be selected according to the AVR32_USBC_VBOF_x_PIN and
//! AVR32_USBC_USB_VBOF_FUNCTION definitions from <avr32/uc3cxxxx.h>.
#define USB_VBOF                           AVR32_USBC_VBOF

//! Active level of the USB_VBOF output pin.
# define USB_VBOF_ACTIVE_LEVEL       LOW

//! USB overcurrent detection pin.
# define USB_OVERCURRENT_DETECT_PIN  AVR32_PIN_PB7



//LEDs
//! Number of LEDs.
#define LED_COUNT   6

/*! \name GPIO Connections of LEDs
 */
//! @{
#define LED_MOTOR	AVR32_PIN_PB12
#define LED2_GPIO   AVR32_PIN_PB17
#define LED3_GPIO   AVR32_PIN_PB18
#define LED4_GPIO   AVR32_PIN_PB27
#define LED5_GPIO   AVR32_PIN_PB28
#define LED6_GPIO   AVR32_PIN_PB29

#define LED2_SET {gpio_set_gpio_pin(LED2_GPIO);}
#define LED3_SET {gpio_set_gpio_pin(LED3_GPIO);}
#define LED4_SET {gpio_set_gpio_pin(LED4_GPIO);}
#define LED5_SET {gpio_set_gpio_pin(LED5_GPIO);}
#define LED6_SET {gpio_set_gpio_pin(LED6_GPIO);}
#define LEDMOTOR_SET {gpio_set_gpio_pin(LED_MOTOR);}

#define LED2_CLR {gpio_clr_gpio_pin(LED2_GPIO);}
#define LED3_CLR {gpio_clr_gpio_pin(LED3_GPIO);}
#define LED4_CLR {gpio_clr_gpio_pin(LED4_GPIO);}
#define LED5_CLR {gpio_clr_gpio_pin(LED5_GPIO);}
#define LED6_CLR {gpio_clr_gpio_pin(LED6_GPIO);}
#define LEDMOTOR_CLR {gpio_clr_gpio_pin(LED_MOTOR);}


//Motors
#define MOTOR_0_STBY	AVR32_PIN_PB08
#define MOTOR_0_IN1		AVR32_PIN_PB09
#define MOTOR_0_IN2		AVR32_PIN_PB10
#define MOTOR_0_PWM		AVR32_PIN_PB11

#define MOTOR_1_STBY	AVR32_PIN_PB16
#define MOTOR_1_IN1		AVR32_PIN_PB15
#define MOTOR_1_IN2		AVR32_PIN_PB14
#define MOTOR_1_PWM		AVR32_PIN_PB13

//PWM
// #  define M0_PWM_L_PIN             AVR32_PWM_PWML_0_1_PIN
// #  define M0_PWM_L_FUNCTION        AVR32_PWM_PWML_0_1_FUNCTION
#  define M0_PWM_H_PIN             AVR32_PWM_PWMH_1_1_PIN
#  define M0_PWM_H_FUNCTION        AVR32_PWM_PWMH_1_1_FUNCTION
#  define M0_PWM_CHANNEL_ID        1
#  define M1_PWM_H_PIN             AVR32_PWM_PWMH_2_2_PIN
#  define M1_PWM_H_FUNCTION        AVR32_PWM_PWMH_2_2_FUNCTION
#  define M1_PWM_CHANNEL_ID        2

//Macros
#define M0_STANDBY		{gpio_clr_gpio_pin(MOTOR_0_STBY);}
#define M0_GO			{gpio_set_gpio_pin(MOTOR_0_STBY);}
#define M0_IN1_SET		{gpio_set_gpio_pin(MOTOR_0_IN1);}
#define M0_IN2_SET		{gpio_set_gpio_pin(MOTOR_0_IN2);}
#define M0_IN1_CLR		{gpio_clr_gpio_pin(MOTOR_0_IN1);}
#define M0_IN2_CLR		{gpio_clr_gpio_pin(MOTOR_0_IN2);}
#define M0_PWM_HIGH		{gpio_set_gpio_pin(MOTOR_0_PWM);}
#define M0_PWM_LOW		{gpio_clr_gpio_pin(MOTOR_0_PWM);}
	
#define M1_STANDBY		{gpio_clr_gpio_pin(MOTOR_1_STBY);}
#define M1_GO			{gpio_set_gpio_pin(MOTOR_1_STBY);}
#define M1_IN1_SET		{gpio_set_gpio_pin(MOTOR_1_IN1);}
#define M1_IN2_SET		{gpio_set_gpio_pin(MOTOR_1_IN2);}
#define M1_IN1_CLR		{gpio_clr_gpio_pin(MOTOR_1_IN1);}
#define M1_IN2_CLR		{gpio_clr_gpio_pin(MOTOR_1_IN2);}
#define M1_PWM_HIGH		{gpio_set_gpio_pin(MOTOR_1_PWM);}
#define M1_PWM_LOW		{gpio_clr_gpio_pin(MOTOR_1_PWM);}	
//SD Card

#define SD_MMC_SPI_MEM_CNT          1
#define SD_MMC_0_CD_GPIO            AVR32_PIN_PB26
#define SD_MMC_0_CD_DETECT_VALUE    1
#define SD_MMC_0_WP_GPIO            AVR32_PIN_PD30
#define SD_MMC_0_WP_DETECT_VALUE    0
#define SD_MMC_SPI_0_CS             0

// Keep it for SD MMC stack ASF V1.7
#define SD_MMC_CARD_DETECT_PIN      SD_MMC_0_CD_GPIO
#define SD_MMC_WRITE_PROTECT_PIN    SD_MMC_0_WP_GPIO
#define SD_MMC_SPI_NPCS             SD_MMC_SPI_0_CS

#define SD_MMC_SPI                  (&AVR32_SPI1)
#define SD_MMC_SPI_SCK_PIN          AVR32_SPI1_SCK_0_1_PIN
#define SD_MMC_SPI_SCK_FUNCTION     AVR32_SPI1_SCK_0_1_FUNCTION
#define SD_MMC_SPI_MISO_PIN         AVR32_SPI1_MISO_0_1_PIN
#define SD_MMC_SPI_MISO_FUNCTION    AVR32_SPI1_MISO_0_1_FUNCTION
#define SD_MMC_SPI_MOSI_PIN         AVR32_SPI1_MOSI_0_1_PIN
#define SD_MMC_SPI_MOSI_FUNCTION    AVR32_SPI1_MOSI_0_1_FUNCTION
#define SD_MMC_SPI_NPCS_PIN         AVR32_SPI1_NPCS_0_2_PIN
#define SD_MMC_SPI_NPCS_FUNCTION    AVR32_SPI1_NPCS_0_2_FUNCTION
//! \brief PBA clock frequency (Hz)
#define PBA_HZ                FOSC0

//! \brief Number of bytes in the receive buffer when operating in slave mode
#define BUFFERSIZE            64


#define AVR32_PDCA_CHANNEL_USED_RX AVR32_PDCA_PID_SPI1_RX
#define AVR32_PDCA_CHANNEL_USED_TX AVR32_PDCA_PID_SPI1_TX

#define AVR32_PDCA_CHANNEL_SPI_RX 0 // In the example we will use the pdca channel 0.
#define AVR32_PDCA_CHANNEL_SPI_TX 1 // In the example we will use the pdca channel 1.

//USART

#define DBG_USART                   (&AVR32_USART2)
#define DBG_USART_RX_PIN           AVR32_USART2_RXD_0_1_PIN
#define DBG_USART_RX_FUNCTION      AVR32_USART2_RXD_0_1_FUNCTION
#define DBG_USART_TX_PIN           AVR32_USART2_TXD_0_1_PIN
#define DBG_USART_TX_FUNCTION      AVR32_USART2_TXD_0_1_FUNCTION
#define DBG_USART_IRQ               AVR32_USART2_IRQ
#define DBG_USART_IRQ_GROUP         AVR32_USART2_IRQ_GROUP
#define DBG_USART_SYSCLK            SYSCLK_USART2
#define DBG_USART_BAUDRATE			57600


// static const usart_options_t USART_OPTIONS =
// 	{
// 		.baudrate     = 57600,
// 		.charlength   = 8,
// 		.paritytype   = USART_NO_PARITY,
// 		.stopbits     = USART_1_STOPBIT,
// 		.channelmode  = USART_NORMAL_CHMODE
// 	};


#endif // CONF_BOARD_H
