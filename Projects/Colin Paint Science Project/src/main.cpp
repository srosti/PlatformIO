#include <DHT_U.h>
#include <DHT.h>

/*****************************************
 * Colin's Science Fair Project.
 * I2C 4-line Display http://wiki.sunfounder.cc/index.php?title=I2C_LCD2004
 * 4 DHT11 Temp/HumiditySensors
 * 
 * Display the temperature of each sensor on separate lines
/********************************/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <dht.h>

dht DHT;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

double fahrenheit(double celsius) {
 return celsius * 1.8 + 32;
}

float getTemp(int pin) {
  
  int chk =  DHT.read11(pin);
  
  Serial.print("Read sensor: ");
  switch (chk)
  {
    case DHTLIB_OK: 
       Serial.println("OK"); 
       Serial.println(pin);
       break;
    case DHTLIB_ERROR_CHECKSUM: 
       Serial.println("Checksum error"); 
       return 0;
    case DHTLIB_ERROR_TIMEOUT: 
      Serial.println("Time out error"); 
      return 0;
    default: 
      Serial.println("Unknown error"); 
      return 0;
  }

  float temp = fahrenheit(DHT.temperature);
  Serial.println(temp);

  return temp;
}

void updateDisplay(int line, int pin) {
 
    float temp = getTemp(pin);
    if (temp > 0) {
      lcd.setCursor (14, line );            
      lcd.print(temp);
    }

}

void setup()
{
  Serial.begin(115200);
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
  
  lcd.setCursor ( 0, 0 );            // go to the top left corner
  lcd.print("Black   Temp:");
  lcd.setCursor ( 0, 1 );            // go to the 2nd row
  lcd.print("Dk-Grey Temp:"); // pad with spaces for centering
  lcd.setCursor ( 0, 2 );            // go to the third row
  lcd.print("Lt-Grey Temp:"); // pad string with spaces for centering
  lcd.setCursor ( 0, 3 );            // go to the fourth row
  lcd.print("White   Temp:");
}

void loop() 
{

  int pin = 10;
  int line = 0;
  float temp;

  pin = 10;
  line = 0;
  updateDisplay(line, pin);
  
  pin = 9;
  line = 1;
  updateDisplay(line, pin);
  
  pin = 8;
  line = 2;
  updateDisplay(line, pin);

  pin = 7;
  line = 3;
  updateDisplay(line, pin);

  delay(1000);


}