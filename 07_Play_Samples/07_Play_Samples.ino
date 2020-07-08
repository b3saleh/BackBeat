#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>

File root;

TMRpcm tmrpcm;

void setup() {
  tmrpcm.speakerPin = 9; //Define Speaker Pin
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  
  tmrpcm.volume(7);
  Serial.println("Playing Samples");
  tmrpcm.play("/Samples/K.wav");
  delay(2000);
  tmrpcm.play("/Samples/CHH.wav");
  delay(2000);
  tmrpcm.play("/Samples/S.wav");
  delay(2000);
  tmrpcm.play("/Samples/OHH.wav");
  delay(2000);
  Serial.println("Done Playing Samples");
}

void loop() {
  // nothing happens after setup finishes.
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
