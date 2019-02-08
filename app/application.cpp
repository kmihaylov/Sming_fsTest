#include <user_config.h>
#include <SmingCore/SmingCore.h>
#include <SmingCore/Debug.h>

Timer fsTimer;

void saveFile() {
	String fileName = "testFile";
	String fileContents = "Some sample text. Let's make it a little bit longer.";
	fileSetContent( fileName, fileContents );
	debugf("Writing data to spiffs\r\n");
}

void init()
{
	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(true); // Enable debug output to serial
	Serial.commandProcessing(true);

	Debug.setDebug(Serial);
	Debug.initCommand();
	Debug.start();
	Debug.printf("This is the debug output\r\n");

	debugf("trying to mount spiffs at 0x%08x, length %d", 0x100000, SPIFF_SIZE);
	spiffs_mount_manual(0x100000, SPIFF_SIZE);

	fsTimer.initializeMs(1000 , saveFile ).start();
}
