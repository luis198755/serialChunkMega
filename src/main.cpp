#include <Arduino.h>

unsigned long values[] = {
    4294967295, 4294967294, 4294967293, 4294967292,
    4294967291, 4294967290, 4294967289, 4294967288
  };
int numValues = sizeof(values) / sizeof(values[0]);

byte hexArray2[32];
int k=0;



void uLchunck0x00(unsigned long* array, int size) {
  for (int i = 0; i < numValues; i++) {
    // Print the original unsigned long value for reference
    Serial.print("Original value: ");
    Serial.println(array[i]);

    // Extract and print each byte in hexadecimal format
    for (int j = 3; j >= 0; j--) {
      unsigned long mask = 0xFF;
      unsigned long byte = (array[i] >> (j * 8)) & mask;
      Serial.print(j + 1);
      Serial.print(" - 0x");
      if (byte < 16) {
        Serial.print("0"); // Print a leading zero for values less than 0x10
      }
      hexArray2[k] = byte;
      Serial.println(hexArray2[k], HEX);
      k++;

    }
    Serial.println(); // Add a newline for readability
  }
}


void sendChunk(byte* chunk, int chunkSize) {
  Serial.print("Chunk: ");
  for (int i = 0; i < chunkSize; i++) {
    Serial.print("0x");
    if (chunk[i] < 16) {
      Serial.print("0"); // Print leading zero for numbers less than 0x10
    }
    Serial.print(chunk[i], HEX);
    if (i < chunkSize - 1) {
      Serial.print(",");
    }
  }
  Serial.println();
}


void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Example hexadecimal array to send
  byte hexArray[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE, 0xFE, 0xBA, 0xBE, 0xFF};
  int arraySize = sizeof(hexArray);

  uLchunck0x00(values, numValues);
  
  // Define the size of each chunk
  int chunkSize = 2; // Change this to send different chunk sizes
  
  // Send the array in chunks
  for (int i = 0; i < k; i += chunkSize) {
    sendChunk(hexArray2 + i, min(chunkSize, k - i));
    delay(100); // Delay between chunks for readability, adjust as needed
  }

  Serial.print("ok");
}

void loop() {
  
}

