#include <SmingCore/Debug.h>
#include <SmingCore/SmingCore.h>
#include <application.h>
#include <user_config.h>
#include "SerialReadingDelegateDemo.h"
//#include "Services/CommandProcessing/CommandProcessingIncludes.h"

SerialReadingDelegateDemo delegateDemoClass;

String fileName = "test123456";
String fileContents = "0123456789";

Timer fsTimer;

void delayedMount() {
	debugf("trying to mount spiffs at 0x%08x, length %d", 0x100000, SPIFF_SIZE);
	spiffs_mount_manual(0x100000, SPIFF_SIZE);
}
void init()
{
	Serial.begin(SERIAL_BAUD_RATE, SERIAL_8N1, SERIAL_FULL);
	Debug.setDebug(Serial);
	Serial.systemDebugOutput(true); // Enable debug output to serial
	Serial.commandProcessing(true);

	delegateDemoClass.begin(Serial);
	delegateDemoClass.onCommand(handleCommand);

	fsTimer.initializeMs( 10000 , delayedMount ).startOnce();

}

void saveFile(int iterations = 0)
{
	int bytes = 0;
	int i;
	for(i = 0; i < iterations; i++) {
		bytes += fileSetContent(fileName, fileContents);
		debugf("Bytes written to fs: %d", bytes);
	}
}

void handleCommand(const String& command)
{
	String first = command.substring(0, 4);
	String second = command.substring(5,10);
	Serial.printf( "Full cmd is: %s\r\n" , command.c_str());
	Serial.printf( "Cmd1: %s, cmd2: %s\r\n" , first.c_str() , second.c_str() );
	if(first.equalsIgnoreCase(_F("save"))) {
		if(second.toInt() > 0) {
			saveFile(second.toInt());
		}
	} else {
		//Serial.printf(_F("Try typing: save [N] - [N] is integer\r\n"));
	}
}
