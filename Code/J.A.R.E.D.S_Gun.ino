/*
 * J.A.R.E.D.S Interactive Interface
 * 
 * This sketch contains all of the code to drive the gun hardware, along with the OLED display
 * A quadrature rotary encoder will be used to navigate the display
 * Hardware includes cooling fans, LEDs, buzzer, TMP36 temperature sensors, voltmeter
 * For more information, see *insert GitHub link here*
 * 
 * May 26, 2021
 * G. Carey
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

/*
 * Define I/O pins
 * Declare & initialize global variables
 */

#define buzzerPin 3
#define flywheelPin 5
#define fanPin 6
#define voltmeterPin 8
#define LED_bluePin 9
#define LED_greenPin 10
#define LED_redPin 11

#define encoder_OutputA 2
#define encoder_OutputB 4
#define encoder_Sw 7

#define tempSensorPin1 A0
#define tempSensorPin2 A1

int menuState = 0; // Current state of the GUI
int currentSave; // The current save slot

bool fanMode = false;
bool rgbMode = false;
bool redMode = false;
bool greenMode = false;
bool blueMode = false;

int fanSpeed;
int red, green, blue;
bool voltmeter;
String tempUnits;

int cursorPos = 0; // GUI cursor position, navigated with rotary encoder
int currentStateA; // Current encoder output A state
int previousStateA; // Current encoder output B state
int switchState = 1; // Stores the state of the push switch
int menuItems[] = {2, 7, 6, 4}; // Max cursor positions for the current menu state

void setup() {
  Serial.begin(9600);
  
  // Define I/O pins as input/output
  pinMode(buzzerPin, OUTPUT);
  pinMode(flywheelPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(voltmeterPin, OUTPUT);
  pinMode(LED_bluePin, OUTPUT);
  pinMode(LED_greenPin, OUTPUT);
  pinMode(LED_redPin, OUTPUT);
  
  pinMode(encoder_OutputA, INPUT_PULLUP);
  pinMode(encoder_OutputB, INPUT_PULLUP);
  pinMode(encoder_Sw, INPUT);
  
  pinMode(tempSensorPin1, INPUT);
  pinMode(tempSensorPin2, INPUT);

  // Initialize the state of output A
  previousStateA = digitalRead(encoder_OutputA);

  // Initialize the display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  
  // Loading screen
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("      J.A.R.E.D.S");
  display.println("      Interactive");
  display.println("       Interface");
  display.display();

  // Set to the last saved slot and load settings
  //ginitEEPROM();
  currentSave = EEPROM.read(0);
  loadSettings(currentSave);
  
  delay(1000);

  // Load the main menu screen
  renderGraphics();
}

void loop() {
  switch(encoderInput())
  {
    Default:
      break;
    case 0:
      if(cursorPos > 0 && !fanMode && !rgbMode)
      {
        cursorPos--;
        renderGraphics();
      }
      else if(fanMode && fanSpeed > 0)
      {
        fanSpeed -= 5;
        analogWrite(fanPin, fanSpeed);
        renderGraphics();
      } else if(redMode && red > 0)
      {
        red -= 15;
        setRGB(red, green, blue);
        renderGraphics();
      } else if(greenMode && green > 0)
      {
        green -= 15;
        setRGB(red, green, blue);
        renderGraphics();
      } else if(blueMode && blue > 0)
      {
        blue -= 15;
        setRGB(red, green, blue);
        renderGraphics();
      }
      break;
    case 1:
      if(cursorPos < menuItems[menuState]-1 && !fanMode && !rgbMode)
      {
        cursorPos++;
        renderGraphics();
      }
      else if(fanMode && fanSpeed < 255)
      {
        fanSpeed += 5;
        analogWrite(fanPin, fanSpeed);
        renderGraphics();
      } else if(redMode && red < 255)
      {
        red += 15;
        setRGB(red, green, blue);
        renderGraphics();
      } else if(greenMode && green < 255)
      {
        green += 15;
        setRGB(red, green, blue);
        renderGraphics();
      } else if(blueMode && blue < 255)
      {
        blue += 15;
        setRGB(red, green, blue);
        renderGraphics();
      }
      break;
    case 2:
      switch(menuState)
      {
        case 0:
          switch(cursorPos)
          {
            case 0:
              menuState = 1;
              cursorPos = 0;
              renderGraphics();
              break;
            case 1:
              menuState = 2;
              cursorPos = 0;
              renderGraphics();
              break;
          }
          break;
        case 1:
          switch(cursorPos)
          {
            case 0:// Adjust fan speed
              if(fanMode)
              {
                fanMode = false;
                renderGraphics();
              }
              else
                fanMode = true;
              break;
            case 1:// Toggle voltmeter
              if(voltmeter)
                voltmeter = false;
              else
                voltmeter = true;
              digitalWrite(voltmeterPin, voltmeter);
              renderGraphics();
              break;
            case 2:// Set LED RGB values
              menuState = 3;
              cursorPos = 0;
              renderGraphics();
              break;
            case 3:// Change temperature from celsius to fahrenheit
              if(tempUnits.equals("Celsius"))
                tempUnits = "Fahrenheit";
              else
                tempUnits = "Celsius";
              renderGraphics();
              break;
            case 4:// Load current save with default values
              loadDefaults();
              break;
            case 5:// Cancel changes
              loadSettings(currentSave);
              cursorPos = 0;
              menuState = 0;
              renderGraphics();
              break;
            case 6:// Save changes
              saveSettings(currentSave);
              cursorPos = 0;
              menuState = 0;
              renderGraphics();
              break;
          }
          break;
        case 2:
        {
          switch(cursorPos)
          {
            case 0:
              currentSave = 0;
              loadSettings(currentSave);
              menuState = 0;
              cursorPos = 0;
              renderGraphics();
              break;
            case 1:
              currentSave = 1;
              loadSettings(currentSave);
              menuState = 0;
              cursorPos = 0;
              renderGraphics();
              break;
            case 2:
              currentSave = 2;
              loadSettings(currentSave);
              menuState = 0;
              cursorPos = 0;
              renderGraphics();
              break;
            case 3:
              currentSave = 3;
              loadSettings(currentSave);
              menuState = 0;
              cursorPos = 0;
              renderGraphics();
              break;
            case 4:
              loadDefaults();
              for(int i = 1; i <= 3; i++)
                saveSettings(i);
              break;
            case 5:
              menuState = 0;
              cursorPos = 0;
              renderGraphics();
              break;
          }
        }
        case 3:
          switch(cursorPos)
          {
            case 0:// Red
              if(rgbMode)
              {
                rgbMode = false;
                redMode = false;
              }
              else
              {
                if(menuState == 3) // Error
                {
                  rgbMode = true;
                  redMode = true;
                }
              }
              break;
            case 1:// Green
              if(rgbMode)
              {
                rgbMode = false;
                greenMode = false;
              }
              else
              {
                rgbMode = true;
                greenMode = true;
              }
              break;
            case 2:// Blue
              if(rgbMode)
              {
                rgbMode = false;
                blueMode = false;
              }
              else
              {
                rgbMode = true;
                blueMode = true;
              }
              break;
            case 3:// Back
              menuState = 1;
              cursorPos = 2;
              renderGraphics();
              break;
          }
          break;
      }
      break;
  }
}

void setValues()
{
  analogWrite(fanPin, fanSpeed);
  digitalWrite(voltmeterPin, voltmeter);
  setRGB(red, green, blue);
}

void loadDefaults()
{
  fanSpeed = 255;
  voltmeter = true;
  red = 255;
  green = 255;
  blue = 255;
  tempUnits = "Celsius";
  
  setValues();
}

/*
 * Load saved settings
 *          Param
 * int save: the specified save slot to load
 */
void loadSettings(int save)
{
  switch(save)
  {
    Default:
      fanSpeed = 255;
      voltmeter = true;
      red = 255;
      green = 255;
      blue = 255;
      tempUnits = "Celsius";
      
      setValues();
      break;
    case 0:// Load default values
      fanSpeed = 255;
      voltmeter = true;
      red = 255;
      green = 255;
      blue = 255;
      tempUnits = "Celsius";
      
      setValues();
      break;
    case 1:// Save 1
      fanSpeed = EEPROM.read(1);
      voltmeter = EEPROM.read(2);
      red = EEPROM.read(3);
      green = EEPROM.read(4);
      blue = EEPROM.read(5);
      if(EEPROM.read(6) == 0)
        tempUnits = "Celsius";
      else
        tempUnits = "Fahrenheit";

        setValues();
        EEPROM.write(0, 1);
      break;
    case 2:// Save 2
      fanSpeed = EEPROM.read(7);
      voltmeter = EEPROM.read(8);
      red = EEPROM.read(9);
      green = EEPROM.read(10);
      blue = EEPROM.read(11);
      if(EEPROM.read(12) == 0)
        tempUnits = "Celsius";
      else
        tempUnits = "Fahrenheit";

      setValues();
        EEPROM.write(0, 2);
      break;
    case 3:// Save 3
      fanSpeed = EEPROM.read(13);
      voltmeter = EEPROM.read(14);
      red = EEPROM.read(15);
      green = EEPROM.read(16);
      blue = EEPROM.read(17);
      if(EEPROM.read(18) == 0)
        tempUnits = "Celsius";
      else
        tempUnits = "Fahrenheit";

      setValues();
        EEPROM.write(0, 3);
      break;
  }
}

/*
 * Load saved settings
 *          Param
 * int save: the specified save slot to overwrite
 */
void saveSettings(int save)
{
  switch(save)
  {
    case 0:// Save to save 1
      EEPROM.write(1, fanSpeed);
      EEPROM.write(2, voltmeter);
      EEPROM.write(3, red);
      EEPROM.write(4, green);
      EEPROM.write(5, blue);
      if(tempUnits.equals("Celsius"))
        EEPROM.write(6, 0);
      else
        EEPROM.write(6, 1);

      currentSave = 1;
      EEPROM.write(0, 1);
      break;
    case 1:// Save 1
      EEPROM.write(1, fanSpeed);
      EEPROM.write(2, voltmeter);
      EEPROM.write(3, red);
      EEPROM.write(4, green);
      EEPROM.write(5, blue);
      if(tempUnits.equals("Celsius"))
        EEPROM.write(6, 0);
      else
        EEPROM.write(6, 1);
      break;
    case 2:// Save 2
      EEPROM.write(7, fanSpeed);
      EEPROM.write(8, voltmeter);
      EEPROM.write(9, red);
      EEPROM.write(10, green);
      EEPROM.write(11, blue);
      if(tempUnits.equals("Celsius"))
        EEPROM.write(12, 0);
      else
        EEPROM.write(12, 1);
      break;
    case 3:// Save 3
      EEPROM.write(13, fanSpeed);
      EEPROM.write(14, voltmeter);
      EEPROM.write(15, red);
      EEPROM.write(16, green);
      EEPROM.write(17, blue);
      if(tempUnits.equals("Celsius"))
        EEPROM.write(18, 0);
      else
        EEPROM.write(18, 1);
      break;
  }
}

/*
 * Reads the encoder input
 * Returns
 * 0: Counter-clockwise rotation
 * 1: Clockwise rotation
 * 2: Switch
 */
int encoderInput()
{
  // Read the current state of output A
  currentStateA = digitalRead(encoder_OutputA);

  // If the current state of output A is different from the previous state of output A, indicates a pulse
  if(currentStateA != previousStateA)
  {
    // Counter-Clockwise rotation
    if(digitalRead(encoder_OutputB) != currentStateA)
    {
      // Update the previous state of output A to the current state of output A
      previousStateA = currentStateA;
      return 0;
    }
    else
    {
      previousStateA = currentStateA;
      return 1;
    }
  }
  previousStateA = currentStateA;
  
  /*
   * Switch has been pressed
   * switchState is checked to ensure only one pulse is recorded
   */
  if(digitalRead(encoder_Sw) == LOW && switchState == 1)
  {
    switchState = 0;
    return 2;
  }
  else if(digitalRead(encoder_Sw) == HIGH)
  {
    switchState = 1;
  }

  // No input
  return -1;
}

/*
 * Updates the GUI
 */
void renderGraphics()
{
  int relativeCursorPos;// Cursor position relative to the display
  
  display.setCursor(0,0);
  display.clearDisplay();
  
  switch(menuState)
  {
    case 0:// Main menu
      display.println("  Settings");
      if(currentSave == 0)
        display.println("  Load Settings: Default");
      else if(currentSave == 1)
        display.println("  Load Settings: Save 1");
      else if(currentSave == 2)
        display.println("  Load Settings: Save 2");
      else if(currentSave == 3)
        display.println("  Load Settings: Save 3");
      display.setCursor(0, (cursorPos+2)*8);
      display.print(">");
      break;
    case 1:// Settings
      relativeCursorPos = cursorPos;
    
      String tempFanSpeed = "";
      tempFanSpeed += map(fanSpeed, 0, 255, 0, 100);
    
      display.println("       Settings");
      if(cursorPos == 3)
      {
        display.setCursor(0,0);
        display.clearDisplay();
        relativeCursorPos -= 1;
      }
      display.println("  Fan Speed: " + tempFanSpeed + "%");
      if(cursorPos == 4)
      {
        display.setCursor(0,0);
        display.clearDisplay();
        relativeCursorPos -= 2;
      }
      if(voltmeter)
        display.println("  Voltmeter: On");
      else
        display.println("  Voltmeter: Off");
      if(cursorPos >= 5)
      {
        display.setCursor(0,0);
        display.clearDisplay();
        relativeCursorPos -= 3;
      }
      display.println("  RGB");
      display.println("  Temp: " + tempUnits);
      display.println("  Reset to Default");
      display.println("  Cancel        Save");
      if(cursorPos < 6)
        display.setCursor(0, (relativeCursorPos+1)*8);
      else
        display.setCursor(85, (relativeCursorPos)*8);
      display.print(">");
      break;
  }

  if(menuState == 2)
  {
    relativeCursorPos = cursorPos;
    
    display.println("     Load Settings");
    if(cursorPos == 3)
    {
      display.setCursor(0,0);
      display.clearDisplay();
      relativeCursorPos -= 1;
    }
    display.println("  Default");
    if(cursorPos == 4)
    {
      display.setCursor(0,0);
      display.clearDisplay();
      relativeCursorPos -= 2;
    }
    display.println("  Save 1");
    if(cursorPos == 5)
    {
      display.setCursor(0,0);
      display.clearDisplay();
      relativeCursorPos -= 3;
    }
    display.println("  Save 2");
    display.println("  Save 3");
    display.println("  Clear Saves");
    display.println("  Back");
    display.setCursor(0, (relativeCursorPos+1)*8);
    display.print(">");
  }
  else if(menuState == 3)
  {
    String r;
    String g;
    String b;
    
    r += red;
    g += green;
    b += blue;
    
    display.println("  Red  : " + r);
    display.println("  Green: " + g);
    display.println("  Blue : " + b);
    display.println("  Back");
    display.setCursor(0, cursorPos*8);
    display.print(">");
  }
  
  display.setTextColor(WHITE, BLACK);
  
  float temp1 = analogRead(tempSensorPin1);
  float temp2 = analogRead(tempSensorPin2);

  float v1 = temp1 * 5.0 / 1023.0;
  float v2 = temp2 * 5.0 / 1023.0;

  float tempC1 = (v1 - 0.5) * 100;
  float tempC2 = (v2 - 0.5) * 100;

  String tempFinal1 = "";
  String tempFinal2 = "";

  tempFinal1 += tempC1;
  tempFinal2 += tempC2;
  
  display.display();
}

/*
 * Customize LED RGB levels using PWM signal
 */
void setRGB(int red, int green, int blue)
{
  analogWrite(LED_redPin, red);
  analogWrite(LED_greenPin, green);
  analogWrite(LED_bluePin, blue);
}

/*
 * Run code only on first start-up
 */
void initEEPROM()
{
  EEPROM.write(0, 0);
  
  for(int i = 0; i < 3; i++)
  {
    EEPROM.write(1+(i*6), 255);
    EEPROM.write(2+(i*6), 1);
    EEPROM.write(3+(i*6), 255);
    EEPROM.write(4+(i*6), 255);
    EEPROM.write(5+(i*6), 255);
    EEPROM.write(6+(i*6), 0);
  }
}
