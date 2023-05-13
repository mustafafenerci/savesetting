/**
 * @file       SaveSetting.h
 * @author     Mustafa Fenerci	mustafafenercieem@gmail.com
 * @date       Sep 2020
 * @brief	   Written to save settings to EEPROM. For ESP32 or ESP8266 
 * @version    1.0
 */


#include "Arduino.h"
#include "SaveSetting.h"


int last_memory_address = 0;

SaveSetting::SaveSetting(int size)
{
	_size = size; 	

	if(last_memory_address == 0) //< To use address 0
	{
		_first_adress = 0; 
		_data_size_adress = _size;	
		last_memory_address = _size; 
	}		
	else
	{
		_first_adress = last_memory_address + 1; 
		_data_size_adress = last_memory_address + _size + 1; 
		last_memory_address = last_memory_address + _size + 1; 
	}
	
}

SaveSetting::SaveSetting()
{
	//
}

bool SaveSetting::begin()
{
	EEPROM.begin(last_memory_address+1);
	return 1;
}

uint16_t SaveSetting::length()
{
	return EEPROM.read(_data_size_adress);	
}

uint16_t SaveSetting::totalLength()
{
	return (last_memory_address + 1);
}

bool SaveSetting::write(String incoming) //< ğ, Ğ, ç, Ç, ş, Ş, ü, Ü, ö, Ö, ı, İ > occupies two places when it is
{

	incoming.trim(); //< Discard the blanks
	_len = incoming.length();
	
/* 	Serial.println("Write incoming          :" + incoming);
	Serial.println("Write first address     :" + String(_first_adress));
	Serial.println("Write data size address :" + String(_data_size_adress));
	Serial.println("Write size              :" + String(_size));
	Serial.println("Write len               :" + String(_len)); */
	
	if(_len > _size) _len = _size; //< if the incoming data exceeds the maximum size 
	EEPROM.write(_data_size_adress,_len); 
	int ixd_incoming = 0;
	for(int ixd = _first_adress; ixd < _len + _first_adress; ixd++)
	{
		EEPROM.write(ixd,incoming[ixd_incoming]);
		ixd_incoming++;
	}	
	
	if(EEPROM.commit())
	{
		
		//Serial.println("yazma başarılı.");
		return 1;
	}
	else
	{
		
		//Serial.println("yazma başarısız.");
		return 0;
	}		
	
}

String SaveSetting::read()
{

	_len = EEPROM.read(_data_size_adress);
	_outgoing = "";
	for(int ixd = _first_adress; ixd < _len + _first_adress; ixd++)
	{
		_outgoing += char(EEPROM.read(ixd));
		
	}
	
/* 	Serial.println("Read first address     :" + String(_first_adress));
	Serial.println("Read data size address :" + String(_data_size_adress));
	Serial.println("Read size              :" + String(_size));
	Serial.println("Read len               :" + String(_len));
	Serial.println("Read outgoing          :" + _outgoing); */
	
	return _outgoing;
}

void SaveSetting::clear()
{
	EEPROM.write(_data_size_adress,0); 
	for(int ixd = _first_adress; ixd < _size + _first_adress; ixd++)
	{
		EEPROM.write(ixd,0XFF);
	}	
	EEPROM.commit();  
}

SaveSetting Memory;