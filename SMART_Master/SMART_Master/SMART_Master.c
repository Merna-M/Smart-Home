/*
 * SMART_Master.c
 *
 * Created: 7/19/2023 12:50:46 PM
 *  Author: MERNA
 */ 


/** Libraries **/
#include "STD_types.h"
/** MCAL **/
#include "EEPROM_interface.h"
#include "SPI_interface.h"
#include "TMR0_interface.h"
/** HAL **/
#include "LCD_interface.h"
#include "KYP_interface.h"

#define F_CPU 8000000UL
#include "util/delay.h"

#define SMART_GUEST_PW_ADDR		0x100
#define SMART_ADMIN_PW_ADDR		0x110
#define PASSWORD_SIZE			4
#define TRAILS_NUMBER			3
#define TRIAL_STOP				10
#define SESSION_TIME_OUT		10


/* Global Variables */
uint16 TMR0_counter = 0;


void TMR0_ISR(void)
{
	TMR0_counter++;
}


int main(void)
{
	uint8 button = NOT_PRESSED;
	uint8 user_pw[PASSWORD_SIZE];
	sint8 i , check=0 , trials = TRAILS_NUMBER;
	uint8 time_check_flag = 0;
	uint8 user_current_status;
	uint8 mode;
	LCD_vInit();
	KYP_vInit();
	SPI_vInit();
	TMR0_vInit();
	TMR0_COMP_SetCallBack(TMR0_ISR);
	
	
	
	LCD_vSendString("   Welcome To");
	LCD_vMoveCursor(2,1);
	LCD_vSendString("   SMART HOME");
	_delay_ms(2000);
	LCD_vClearScreen();
	if(EEPROM_vREAD(SMART_ADMIN_PW_ADDR)==EEPROM_ADDRESS_EMPTY)
	{
		LCD_vSendString("Set Admin PW:");
		LCD_vMoveCursor(2,1);
		for(i=0 ; i<PASSWORD_SIZE ; i++)
		{
			do{
				button = KYP_u8CheckPress();
				_delay_ms(150);
			}
			while(button == NOT_PRESSED);
			LCD_vSendData(button);
			_delay_ms(100);
			LCD_vMoveCursor(2,1+i);
			LCD_vSendData('*');
			EEPROM_vWrite(SMART_ADMIN_PW_ADDR+i,button);
		}
		_delay_ms(150);
		LCD_vClearScreen();
		LCD_vSendString("Admin PW is set");
		_delay_ms(500);
		LCD_vClearScreen();
		
		LCD_vSendString("Set Guest PW:");
		LCD_vMoveCursor(2,1);
		for(i=0 ; i<PASSWORD_SIZE ; i++)
		{
			do{
				button = KYP_u8CheckPress();
				_delay_ms(150);
			}
			while(button == NOT_PRESSED);
			LCD_vSendData(button);
			_delay_ms(100);
			LCD_vMoveCursor(2,1+i);
			LCD_vSendData('*');
			EEPROM_vWrite(SMART_GUEST_PW_ADDR+i,button);
		}			
		_delay_ms(150);
		LCD_vClearScreen();
		LCD_vSendString("Guest PW is set");
		_delay_ms(500);
		LCD_vClearScreen();
	}
    while(1)
    {
		LCD_vClearScreen();
        LCD_vSendString("Choose Mode:");
		LCD_vMoveCursor(2,1);
		LCD_vSendString("1:Admin  2:Guest");
		do{
			mode = KYP_u8CheckPress();
			_delay_ms(150);
		}
		while(mode != '1' && mode != '2');
		_delay_ms(150);
		LCD_vClearScreen();
		do{
			LCD_vSendString("Enter Password:");
			LCD_vMoveCursor(2,1);
			for(i=0 ; i<PASSWORD_SIZE ; i++)
			{
				do{
					button = KYP_u8CheckPress();
					_delay_ms(150);
				}
				while(button == NOT_PRESSED);
				LCD_vSendData(button);
				_delay_ms(100);
				LCD_vMoveCursor(2,1+i);
				LCD_vSendData('*');
				user_pw[i]=button;
			}
			check = 0;
			for(i=0 ; i<PASSWORD_SIZE ; i++)
			{
				if(mode == '1' && user_pw[i]!=EEPROM_vREAD(SMART_ADMIN_PW_ADDR+i))
				{
					check = 1;
				}
				else if(mode == '2' && user_pw[i]!=EEPROM_vREAD(SMART_GUEST_PW_ADDR+i))
				{
					check = 1;
				}
			}
			LCD_vClearScreen();
			if(check == 1)
			{
				LCD_vSendString("Wrong Password");
				LCD_vMoveCursor(2,1);
				trials--;
				LCD_vSendNumber(trials);
				LCD_vSendString(" Trials Left");
				_delay_ms(1000);
				LCD_vClearScreen();
			}
		}
		while(check == 1 && trials>0);
		LCD_vClearScreen();
		if(check == 1)
		{
			LCD_vSendString("Try Again in ");
			LCD_vSendNumber(TRIAL_STOP);
			LCD_vMoveCursor(2,1);
			LCD_vSendString("Seconds");
			TMR0_counter = 0;
			while(TMR0_counter < (TRIAL_STOP*100))
			{
				LCD_vMoveCursor(1,14);
				LCD_vSendNumber(TRIAL_STOP-(TMR0_counter/100));
				LCD_vSendString("   ");
				_delay_ms(100);
			}
			LCD_vClearScreen();
		}
		else
		{
			if(mode == '1')
			{
				LCD_vSendString("Welcome Admin!");
				_delay_ms(1000);
			}
			else if(mode == '2')
			{
				LCD_vSendString("Welcome Guest!");
				_delay_ms(1000);
			}
			TMR0_counter = 0;
			while(TMR0_counter<(SESSION_TIME_OUT*100))
			{
				check = 0; trials = TRAILS_NUMBER;
				if(mode == '1')
				{
					LCD_vClearScreen();
					LCD_vSendString("Choose an Option");
					_delay_ms(1000);
					LCD_vClearScreen();
					LCD_vSendString("1:ROOM1  2:ROOM2");
					LCD_vMoveCursor(2,1);
					LCD_vSendString("3:ROOM3  4:MORE");
					
					button = NOT_PRESSED;
					TMR0_counter=0;
					do
					{
						if(button != NOT_PRESSED)
						{
							LCD_vClearScreen();
							LCD_vSendString("Enter from 1->4");
							_delay_ms(1000);
							LCD_vClearScreen();
							LCD_vSendString("1:ROOM1  2:ROOM2");
							LCD_vMoveCursor(2,1);
							LCD_vSendString("3:ROOM3  4:MORE");
						}
						button = KYP_u8CheckPress();
						_delay_ms(150);
					} while (button != '1' && button != '2' && button != '3' && button !='4' && TMR0_counter<(SESSION_TIME_OUT*100));
					if(TMR0_counter>=(SESSION_TIME_OUT*100))
					{
						LCD_vClearScreen();
						LCD_vSendString("Session TimedOut");
						_delay_ms(1000);
						LCD_vClearScreen();
					}
					else if(button == '4')
					{
						LCD_vClearScreen();
						LCD_vSendString("1:FAN1   2:FAN2");
						LCD_vMoveCursor(2,1);
						LCD_vSendString("3:GARAGE 4:More");
						button = NOT_PRESSED;
						TMR0_counter=0;
						do
						{
							if(button != NOT_PRESSED)
							{
								LCD_vClearScreen();
								LCD_vSendString("Enter from 1->4");
								_delay_ms(1000);
								LCD_vClearScreen();
								LCD_vSendString("1:FAN1   2:FAN2");
								LCD_vMoveCursor(2,1);
								LCD_vSendString("3:GARAGE 4:More");
							}
							button = KYP_u8CheckPress();
							_delay_ms(150);
						} while (button != '1' && button != '2' && button != '3' && button!='4' && TMR0_counter<(SESSION_TIME_OUT*100));
						if(TMR0_counter>=(SESSION_TIME_OUT*100))
						{
							LCD_vClearScreen();
							LCD_vSendString("Session TimedOut");
							_delay_ms(1000);
							LCD_vClearScreen();
						}
						else if(button>='1' && button<='3')
						{
							SPI_u8Tranceiver(button+3);
							time_check_flag = button+3-48;
							user_current_status = (button+3-49)*2;
						}
						else if(button == '4')
						{
							LCD_vClearScreen();
							LCD_vSendString("1:Chng Admin PW");
							LCD_vMoveCursor(2,1);
							LCD_vSendString("2:chng Guest PW");
							button = NOT_PRESSED;
							TMR0_counter=0;
							do
							{
								if(button != NOT_PRESSED)
								{
									LCD_vClearScreen();
									LCD_vSendString("Enter from 1 or 2");
									_delay_ms(1000);
									LCD_vClearScreen();
									LCD_vSendString("1:Chng Admin PW");
									LCD_vMoveCursor(2,1);
									LCD_vSendString("2:chng Guest PW");
								}
								button = KYP_u8CheckPress();
								_delay_ms(150);
							} while (button != '1' && button != '2' && TMR0_counter<(SESSION_TIME_OUT*100));
							if(TMR0_counter>=(SESSION_TIME_OUT*100))
							{
								LCD_vClearScreen();
								LCD_vSendString("Session TimedOut");
								_delay_ms(1000);
								LCD_vClearScreen();
							}
							else if(button == '1')
							{
								LCD_vClearScreen();
								LCD_vSendString("New Password:");
								LCD_vMoveCursor(2,1);
								for(i=0 ; i<PASSWORD_SIZE ; i++)
								{
									do{
										button = KYP_u8CheckPress();
										_delay_ms(150);
									}
									while(button == NOT_PRESSED);
									LCD_vSendData(button);
									_delay_ms(100);
									LCD_vMoveCursor(2,1+i);
									LCD_vSendData('*');
									EEPROM_vWrite(SMART_ADMIN_PW_ADDR+i,button);
								}
								_delay_ms(150);
								LCD_vClearScreen();
								LCD_vSendString("Admin PW is set");
								_delay_ms(700);
								LCD_vClearScreen();
								TMR0_counter = 100*SESSION_TIME_OUT;
							}
							else if(button == '2')
							{
								LCD_vClearScreen();
								LCD_vSendString("New Password:");
								LCD_vMoveCursor(2,1);
								for(i=0 ; i<PASSWORD_SIZE ; i++)
								{
									do{
										button = KYP_u8CheckPress();
										_delay_ms(150);
									}
									while(button == NOT_PRESSED);
									LCD_vSendData(button);
									_delay_ms(100);
									LCD_vMoveCursor(2,1+i);
									LCD_vSendData('*');
									EEPROM_vWrite(SMART_GUEST_PW_ADDR+i,button);
								}
								_delay_ms(150);
								LCD_vClearScreen();
								LCD_vSendString("Guest PW is set");
								_delay_ms(700);
								LCD_vClearScreen();
								TMR0_counter = 100*SESSION_TIME_OUT;
							}
						}
					}
					else if(button>='1' && button<='3')
					{
						SPI_u8Tranceiver(button);
						time_check_flag = button-48;
						user_current_status = (button-49)*2;
					}
				}
				else if(mode == '2') // guest
				{
					LCD_vClearScreen();
					LCD_vSendString("Choose an Option");
					_delay_ms(1000);
					LCD_vClearScreen();
					LCD_vSendString("1:ROOM1  2:ROOM2");
					LCD_vMoveCursor(2,1);
					LCD_vSendString("3:ROOM3");
					button = NOT_PRESSED;
					TMR0_counter=0;
					do
					{
						if(button != NOT_PRESSED)
						{
							LCD_vClearScreen();
							LCD_vSendString("Enter from 1->3");
							_delay_ms(1000);
							LCD_vClearScreen();
							LCD_vSendString("1:ROOM1  2:ROOM2");
							LCD_vMoveCursor(2,1);
							LCD_vSendString("3:ROOM3");
						}
						button = KYP_u8CheckPress();
						_delay_ms(150);
					} while (button != '1' && button != '2' && button != '3' && TMR0_counter<(SESSION_TIME_OUT*100));
					if(TMR0_counter>=(SESSION_TIME_OUT*100))
					{
						LCD_vClearScreen();
						LCD_vSendString("Session TimedOut");
						_delay_ms(1000);
						LCD_vClearScreen();
					}
					else
					{
						SPI_u8Tranceiver(button);
						time_check_flag = button-48;
						user_current_status = (button-49)*2;
					}
				}
				if(time_check_flag != 0)
				{
					if(time_check_flag>=1 && time_check_flag<=3)
					{
						LCD_vClearScreen();
						LCD_vSendString("     ROOM_");
						LCD_vSendNumber(time_check_flag);
						LCD_vMoveCursor(2,1);
						LCD_vSendString("1:ON     2:OFF");
					}
					else if(time_check_flag==4 || time_check_flag ==5)
					{
						LCD_vClearScreen();
						LCD_vSendString("      FAN_");
						LCD_vSendNumber(time_check_flag-3);
						LCD_vMoveCursor(2,1);
						LCD_vSendString("1:ON     2:OFF");
					}
					else if(time_check_flag ==6)
					{
						LCD_vClearScreen();
						LCD_vSendString("      GARAGE");
						LCD_vMoveCursor(2,1);
						LCD_vSendString("Status: ");
						button = SPI_u8Tranceiver('a');
						if(button == 'E')
						{
							LCD_vSendString("Empty");
						}
						else if(button == 'B')
						{
							LCD_vSendString("Busy");
						}
						_delay_ms(1000);
					}
					if(time_check_flag !=6)
					{
						TMR0_counter=0;
						do
						{
							button = KYP_u8CheckPress();
							_delay_ms(150);
						} while (button != '1' && button != '2' && TMR0_counter<(SESSION_TIME_OUT*100));
						if(TMR0_counter>=(SESSION_TIME_OUT*100))
						{
							LCD_vClearScreen();
							LCD_vSendString("Session TimedOut");
							_delay_ms(1000);
							LCD_vClearScreen();
						}
						else if(button == '1')
						{
							SPI_u8Tranceiver('N');
						}
						else if(button == '2')
						{
							SPI_u8Tranceiver('F');
							user_current_status ++;
						}
						if((user_current_status/2)>=0 && (user_current_status/2)<=2)
						{
							LCD_vMoveCursor(2,1);
							LCD_vSendString("ROOM_");
							LCD_vSendNumber((user_current_status/2)+1);
						}
						else if((user_current_status/2)==3 || (user_current_status/2)==4)
						{
							LCD_vMoveCursor(2,1);
							LCD_vSendString("FAN_");
							LCD_vSendNumber((user_current_status/2)-2);
						}
						if(user_current_status%2==0)
						{
							LCD_vSendString(" ON                ");
							_delay_ms(1000);
							LCD_vClearScreen();
						}
						else
						{
							LCD_vSendString(" OFF                ");
							_delay_ms(1000);
							LCD_vClearScreen();
						}
					}
					time_check_flag = 0;
				}
			}
		}									
    }
}