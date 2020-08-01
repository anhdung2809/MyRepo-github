/*****************************************************************************
  *Ten Tep          :     lcd16x2.h
  *Ngay             :     14/03/2014
  *Tac Gia          :     MinhHa R&D Team
  *Cong Ty          :     MinhHaGroup
  *Webside          :     mcu.banlinhkien.vn
  *Phien Ban        :     V1.0
  *Tom Tat          :     Dinh nghia cac ham giao tiep LCD16x2
  ******************************************************************************
  * Chu Y : Phai dinh nghia cac chan su dung cho LCD16X2 vao file main.h
  * Vi Du :                                       
   // khai bao chan LCD16x2 TREN KIT AVR V2
   #define     LCD16X2_RS     PORTB_1         
   #define     LCD16X2_RW     PORTC_2          
   #define     LCD16X2_EN     PORTC_3          
   #define     LCD16X2_D4     PORTD_4          
   #define     LCD16X2_D5     PORTD_5          
   #define     LCD16X2_D6     PORTD_6          
   #define     LCD16X2_D7     PORTD_7                            
  ******************************************************************************
**/
/*********************************** VI DU ************************************
   // khai bao 1 mang ki tu dung cho LCD16X2
   uint8_t str[16]; 
   // cac tham bien khac
   uint8_t Do_am;
   //Khoi tao LCD16X2
   LCD16X2_Init();
   // hien thi 1 chuoi ki tu
   sprintf(str,"BanLinhKien.Vn");
   LCD16X2_Puts(str);             
   sprintf(str,"Do Am: %u",Do_am);  
   LCD16X2_Gotoxy(0,1);
   LCD16X2_Puts(str);
*******************************************************************************/
#include "lcd16x2.h"

#if (__LCD16X2_H!=14032014)
    #error "Include Sai File lcd16x2.h"
#endif

#include "DEF_STM32.h"
#include "stm32f10x.h"
#include "delay.h"
/*------------------------------------------------------------------------------
Noi Dung    :   Gui tin hieu Enable den LCD16X2.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
 -------------------------------------------------------------------------------*/

void LCD16X2_Enable(void)
{
	LCD16X2_EN=1;
	delay_us(3);
	LCD16X2_EN=0;
	delay_us(50); 
}

/*------------------------------------------------------------------------------
Noi Dung    :   Gui 4 bit du lieu den LCD16X2.
Tham Bien   :   Data: 4 bit thap cua Data chua 4 bit du lieu can gui.
Tra Ve      :   Khong.
 -------------------------------------------------------------------------------*/

void LCD16X2_Send4Bit(uint8_t Data)
{
	LCD16X2_D4=((Data&0x01)==0x01);
	LCD16X2_D5=((Data&0x02)==0x02);
	LCD16X2_D6=((Data&0x04)==0x04);
	LCD16X2_D7=((Data&0x08)==0x08);
}

/*------------------------------------------------------------------------------
Noi Dung    :   Gui 1 byte du lieu den LCD16X2.
Tham Bien   :   command: lenh can ghi
Tra Ve      :   Khong.
vi du       :   LCD16X2_SendCommand (0x01);
 -------------------------------------------------------------------------------*/

void LCD16X2_SendCommand(uint8_t Command)
{
	LCD16X2_Send4Bit(Command>>4);   /* Gui 4 bit cao */
	LCD16X2_Enable() ;
	LCD16X2_Send4Bit(Command);      /* Gui 4 bit thap*/
	LCD16X2_Enable() ;
}

/*------------------------------------------------------------------------------
Noi Dung    :   Khoi tao LCD16X2.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
 -------------------------------------------------------------------------------*/
 
void LCD16X2_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
/*________________________________ OUTPUT ___________________________________*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9 ;	         		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	LCD16X2_Send4Bit(0x00);
	delay_ms(20);
	LCD16X2_RS=0;
	LCD16X2_RW=0;
	LCD16X2_Send4Bit(0x03);
	LCD16X2_Enable();
	delay_ms(5);
	LCD16X2_Enable();
	delay_us(100);
	LCD16X2_Enable();
	LCD16X2_Send4Bit(0x02);
	LCD16X2_Enable();
	LCD16X2_SendCommand( 0x28);        // giao thuc 4 bit, hien thi 2 hang, ki tu 5x7
	LCD16X2_SendCommand( 0x0c);        // cho phep hien thi man hinh
	LCD16X2_SendCommand( 0x06);        // tang ID, khong dich khung hinh
	LCD16X2_Clear();                   // xoa toan bo khung hinh
}

/*------------------------------------------------------------------------------
Noi Dung    :   Thiet lap vi tri con tro LCD16X2.
Tham Bien   :   x: vi tri cot cua con tro. x = 0 - 15.
                y: vi tri hang cua con tro. y= 0,1.
Tra Ve      :   Khong.
Vi du       :   LCD16X2_Gotoxy(0,0);
 -------------------------------------------------------------------------------*/
 
void LCD16X2_Gotoxy(uint8_t  x, uint8_t  y)
{
	uint8_t  address;
	if(!y)
		address = (0x80+x);
	else
		address = (0xC0+x);
	delay_ms(1);
	LCD16X2_SendCommand(address);
	delay_ms(5);
}

/*------------------------------------------------------------------------------
Noi Dung    :   Xoa noi dung hien thi tren LCD16X2.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
 -------------------------------------------------------------------------------*/
 
void LCD16X2_Clear(void)
{
	LCD16X2_SendCommand(0x01);  
	delay_ms(5);
}

/*------------------------------------------------------------------------------
Noi Dung    :   Viet 1 ki tu len LCD16X2.
Tham Bien   :   Data  :   Gia tri ki tu can hien thi.
Tra Ve      :   Khong.
 -------------------------------------------------------------------------------*/
void LCD16X2_PutChar(uint8_t Data)
{
	LCD16X2_RS=1;
	LCD16X2_SendCommand( Data );
	LCD16X2_RS=0;
}

/*------------------------------------------------------------------------------
Noi Dung    :   Viet 1 chuoi ki tu len LCD16X2.
Tham Bien   :   *s    :   chuoi du lieu can hien thi.
Tra Ve      :   Khong.
 -------------------------------------------------------------------------------*/
void LCD16X2_Puts(uint8_t *s)
{
	while (*s)
	{
		LCD16X2_PutChar(*s);
		s++;
	}
}
/*------------------------------KET THUC FILE-------------------------------
 ______________________________MinhHa R&D Temp______________________________*/




