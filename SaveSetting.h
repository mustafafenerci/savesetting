/**
 * @file       SaveSetting.h
 * @author     Mustafa Fenerci	mustafafenercieem@gmail.com
 * @date       Sep 2020
 * @brief	   Written to save settings to EEPROM.   
 * @version    1.0
 */


#ifndef SAVE_SETTING_H
#define SAVE_SETTING_H

#include "Arduino.h"
#include <EEPROM.h>

	class SaveSetting
	{
	  public:
		/*
			@brief  Constructor for SaveSetting
			@param  size -> Size of data to be saved
		*/
		SaveSetting(int size);	
		SaveSetting();
		/*
			@brief  Start SaveSetting
			@return If successful return 1
		*/			
		bool begin();
		/*
			@brief  
			@param  incoming ->	Data to be recorded
			@return If successful return 1
		*/		
		bool write(String incoming);
		/*
			@brief  
			@return  Send the read data
		*/	
		String read();
		/*
			@brief  Erase all memory where data was written.		
		*/	
		void clear();
		/*
			@brief  
			@return  Sends the size of the current data
		*/	
		uint16_t length();
		/*
			@brief  
			@return  Sends total used memory
		*/	
		uint16_t totalLength();
	  private:
		int _size; 				//< Size of data generated
		int _data_size_adress;  //< Address of the size of generated data
		int _len;				//< The length of data coming with 'incoming'
		int _first_adress;		//< Starting address of generated data
		String _outgoing;		//<	Data sent after reading
	};
	extern SaveSetting Memory;

#endif