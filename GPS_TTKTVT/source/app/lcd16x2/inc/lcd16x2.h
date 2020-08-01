/*****************************************************************************
  *Ten Tep          :     lcd16x2.h
  *Ngay             :     14/03/2014
  *Tac Gia          :     MinhHa R&D Team
  *Cong Ty          :     MinhHaGroup
  *Webside          :     mcu.banlinhkien.vn
  *Phien Ban        :     V1.0
  *Tom Tat          :     Khai bao cac ham giao tiep LCD16x2
  ******************************************************************************
  * Chu Y        :   Phai dinh nghia cac chan su dung cho LCD16X2 vao file main.h
  * Vi Du        : 
  
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
#ifndef __LCD16X2_H
#define __LCD16X2_H    14032014

#include <stdint.h>

/*________________________________ GPIO B____________________________________*/
#define LCD16X2_D4    PORTB_3
#define LCD16X2_D5    PORTB_4
#define LCD16X2_D6    PORTB_5
#define LCD16X2_D7    PORTB_6
/*________________________________ GPIO B ____________________________________*/
#define	LCD16X2_RS    PORTB_7
#define	LCD16X2_RW    PORTB_8
#define	LCD16X2_EN    PORTB_9
/*------------------------------------------------------------------------------
Noi Dung    :   Gui tin hieu Enable den LCD16X2.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
 -------------------------------------------------------------------------------*/
 
void LCD16X2_Enable(void);

/*------------------------------------------------------------------------------
Noi Dung    :   Gui 4 bit du lieu den LCD16X2.
Tham Bien   :   Data: 4 bit thap cua Data chua 4 bit du lieu can gui.
Tra Ve      :   Khong.
 -------------------------------------------------------------------------------*/

void LCD16X2_Send4Bit(uint8_t Data);
/*------------------------------------------------------------------------------
Noi Dung    :   Gui 1 byte du lieu den LCD16X2.
Tham Bien   :   command: lenh can ghi
Tra Ve      :   Khong.
vi du       :   LCD16X2_SendCommand (0x01);
 -------------------------------------------------------------------------------*/

void LCD16X2_SendCommand(uint8_t Command);

/*------------------------------------------------------------------------------
Noi Dung    :   Khoi tao LCD16X2.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
 -------------------------------------------------------------------------------*/
 
void LCD16X2_Init(void);
 
/*------------------------------------------------------------------------------
Noi Dung    :   Thiet lap vi tri con tro LCD16X2.
Tham Bien   :   x: vi tri cot cua con tro. x = 0 - 15.
                y: vi tri hang cua con tro. y= 0,1.
Tra Ve      :   Khong.
Vi du       :   LCD16X2_Gotoxy(0,0);
 -------------------------------------------------------------------------------*/
 
void LCD16X2_Gotoxy(uint8_t x,uint8_t y);

/*------------------------------------------------------------------------------
Noi Dung    :   Xoa noi dung hien thi tren LCD16X2.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
 -------------------------------------------------------------------------------*/
 
void LCD16X2_Clear(void);

/*------------------------------------------------------------------------------
Noi Dung    :   Viet 1 ki tu len LCD16X2.
Tham Bien   :   Data  :   Gia tri ki tu can hien thi.
Tra Ve      :   Khong.
 -------------------------------------------------------------------------------*/
 
void LCD16X2_PutChar(uint8_t Data);
 
/*------------------------------------------------------------------------------
Noi Dung    :   Viet 1 chuoi ki tu len LCD16X2.
Tham Bien   :   *s    :   chuoi du lieu can hien thi.
Tra Ve      :   Khong.
 -------------------------------------------------------------------------------*/
 
void LCD16X2_Puts(uint8_t *s);

#endif
/*------------------------------KET THUC FILE-------------------------------
 ______________________________MinhHa R&D Temp______________________________*/


