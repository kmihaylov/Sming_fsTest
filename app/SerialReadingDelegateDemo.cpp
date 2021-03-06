/*
 * SerialReadingDelegateDemo.cpp
 */

#include "SerialReadingDelegateDemo.h"

//*** Example of global callback routine
void onDataCallback(Stream& stream, char arrivedChar, unsigned short availableCharsCount)
{
	// Note: we're using the global Serial here, but it may not be the same port as stream
	Serial.printf(_F("Char: %d, Count: %d\r\n"), (uint8_t)arrivedChar, availableCharsCount);
}

void echoCallback(Stream& stream, char arrivedChar, unsigned short availableCharsCount)
{
	stream.write(arrivedChar);
}

void SerialReadingDelegateDemo::begin(HardwareSerial& serial)
{
	this->serial = &serial;
	serial.setCallback(StreamDataReceivedDelegate(&SerialReadingDelegateDemo::onData, this));
	debugf("hwsDelegateDemo instantiated, waiting for data");
}

void SerialReadingDelegateDemo::onData(Stream& stream, char arrivedChar, unsigned short availableCharsCount)
{
	/*
	serial->print(_F("Class Delegate Demo Time = "));
	serial->print(micros());
	serial->print(_F(" char = 0x"));
	serial->print(String(arrivedChar, HEX)); // char hex code
	serial->print(_F(" available = "));
	serial->println(availableCharsCount);
*/
	numCallback++;

	if(arrivedChar == '\n') // Lets show data!
	{
	//	serial->println(_F("<New line received>"));
		// Read the string into a line
		String line;
		line.reserve(availableCharsCount);
		while(availableCharsCount--) {
			char cur = stream.read();
			charReceived++;
			serial->print(cur);
			if(cur != '\n' && cur != '\r') {
				line += cur;
			}
		}
		serial->println();

		if(callback) {
			callback(line);
		}
	}
}
