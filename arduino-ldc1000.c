#include "SPI.h" // include arduino SPI library

const int CSB = 10; // chip select bit for Arduino Uno


void setup() 
{
  Serial.begin(9600);
  // start SPI library/ activate BUS
  SPI.begin();
 
  pinMode(CSB, OUTPUT);  
}

void loop() 
{
  unsigned int val = 0;
  byte READ = 0x80; // MSB = 1 which is a 'read' bit
  byte reg = 0x04; // register address
  
  
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0); // CPOL = 0 and CPH = 0 mode 3 also works
  SPI.setClockDivider(SPI_CLOCK_DIV4); // set SCLK @ 4MHz, LDC1000 max is 4MHz DIV2 also works
  
  // begin data transfer
  digitalWrite(CSB, LOW);
  byte data_2_send = READ + reg;
  SPI.transfer(data_2_send);
  val = SPI.transfer(0x00);
  
  // prints 8 bit decimal value between 0 and 255 found in desired register
  Serial.println(val);
  
  // end data transfer
  digitalWrite(CSB, HIGH);
    
  delay(500);
                 
}