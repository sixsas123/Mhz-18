#include "Mhz-18b.h"

int readCO2UART() {
	
  byte cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79}; // byte array witch requests seansor to do measurments
  byte response[9]; // byte array for response from sensor
  
  Serial1.write(cmd, 9); //request PPM CO2

  // clear the buffer
  memset(response, 0, 9);
  int i = 0;

  while (Serial1.available() == 0) {

    delay(1000);
    i++;
  }
  
  // If data is available in Serial1 buffer
  if (Serial1.available() > 0) {
    Serial1.readBytes(response, 9);
  }
  // print out the response in hexa
  for (int i = 0; i < 9; i++) {
    Serial.print(String(response[i], HEX));
    Serial.print("   ");
  }
  Serial.println("");


  // ppm calculation
  int ppm_uart = 256 * (int)response[2] + response[3];
  Serial.print("PPM UART: ");

  // status
  byte status = response[5];
  Serial.print("Status? ");
  Serial.println(status);
  // 0x40 status OK
  if (status == 0x40) {
    Serial.println("Status OK");
  }
  Serial.println();
  return ppm_uart;
}
