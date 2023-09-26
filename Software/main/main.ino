// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).

extern "C" char* char2Matrix(char, char*, int);
extern "C" int getLetterWidth();
extern "C" int getSpaceWidth();
extern "C" int getPunctuationWidth();

#include <Adafruit_NeoPixel.h>
#include <math.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     3   

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT   256  // Neopixel WS2812B (GRB)
#define MTX_HEIGHT  8    // Matrix 8 x 32
#define MTX_WIDTH   (LED_COUNT/MTX_HEIGHT)

// Which pin on the Arduino is connected to the Photo Resistor
#define PHOTO_PIN   0

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

/*----------------------------------------------
 * Typedefs
 *----------------------------------------------*/
typedef enum
{
  INTRO,
  NAME,
  DATE,
  TIME,
  WEIGHT,
  HEIGHT,
  SCROLL
} display_t;

typedef enum
{
  RGB,
  HUE
} color_t;
/*----------------------------------------------
 * Constant Variables
 *----------------------------------------------*/
// Text to Display
const char pageIntro[] = "Arrival:";
const char pageName[] = "John";
const char pageDate[] = "31.12.2023";
const char pageTime[] = "23:59 Uhr";
const char pageWeight[] = "3500 g";
const char pageHeight[] = "53 cm";

// Neopixel Matrix related
const uint16_t amountScroll = 1;              // Amount of times each text is scrolled through matrix before next text
const uint16_t refreshRate = 80;              // [ms], determines speed of text scroll
const uint8_t brightnessMaxValue = 200;       // max. possible brightness is 255, but due to current concerns for the PCB max value must be lower
const uint8_t brightnessMinValue = 2;         // min. brightness in the dark
// Default Color
const color_t colorType = RGB;                // Set color description type (RGB, Hue) for default color
// Defualt Color - RGB
const uint8_t colorR = 0xff;
const uint8_t colorG = 0xff;
const uint8_t colorB = 0xff;
// Default Color Hue
const uint16_t hueDefault = 1150;             // hue value for default color 0.. 65535
const uint8_t saturationDefault = 255;        // saturation of color printed 0.. 255
// Rainbow mode
const bool enableRainbowMode = true;          // enable rainbow mode
const uint16_t colorRainbowInterval = 1111;   // Interval to display text as rainbow (all texts once)
const uint16_t hueChangeRate = 550;           // hue color change rate per column printed 0.. 65535
const uint8_t  saturationRainbow = 225;       // saturation of color during rainbow mode 0.. 255

// Photo Resistor Related
const double refVoltage = 5.0d;               // [V] ADC-Ref Voltage and Arduino logic level
const double adcRes = 1024.0d;                // ADC Resolution
const double Resistor = 100.0d;               // [kOhm] Voltage divider resistor
const double photoResMax = 20000.0d;          // [kOHm], Max value of photo resistor
const uint16_t falseLightCorrFactor = 90;     // Countering false light emmitted from LED matrix
uint8_t matrixBrightAvg[50];                  // Array for average of matrix brightness  

/*----------------------------------------------
 * Global Variables
 *----------------------------------------------*/
bool rainbowMode = false;

/*----------------------------------------------
 * Setup of Hardware
 *----------------------------------------------*/ 
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
}

/*----------------------------------------------
 * Main Function
 *----------------------------------------------*/ 
void loop() {
  char mtxPage[256];    // Matrix to display a text page (max. 42 char if 1 char = 6 columns)
  char *ptrMtxPage = &mtxPage[0];
  int mtxPageLength = 0;
  uint16_t scrollCounter = 0;
  uint16_t colorRainbowCount = 0;
  
  display_t disp = INTRO;
  display_t currentText = INTRO;
  
  while(1)
  {
    // Set brightness of matrix relative to brightness of environment
    strip.setBrightness(getBrightness());
    
    // \NOTE: Switch Case did not work. Certain cases could not be executed!!! Reason still unkown
    if(disp == INTRO)
    {
        // Determine char array size without counting the '\0' 
        int pageCharCount = ((sizeof(pageIntro)-1) / (sizeof(pageIntro[0])));

        // Create matrix page from character string
        mtxPageLength = page2Matrix(&pageIntro[0], pageCharCount, ptrMtxPage);

        disp = SCROLL;
    }

    else if(disp == NAME)
    {
        // Determine char array size without counting the '\0' 
        int pageCharCount = ((sizeof(pageName)-1) / (sizeof(pageName[0])));

        // Create matrix page from character string
        mtxPageLength = page2Matrix(&pageName[0], pageCharCount, ptrMtxPage);

        disp = SCROLL;
    }

    else if(disp == DATE)
    {
        int pageCharCount = ((sizeof(pageDate)-1) / (sizeof(pageDate[0])));
        mtxPageLength = page2Matrix(&pageDate[0], pageCharCount, ptrMtxPage);
        disp = SCROLL;
    }

    else if(disp == TIME)
    {
        int pageCharCount = ((sizeof(pageTime)-1) / (sizeof(pageTime[0])));
        mtxPageLength = page2Matrix(&pageTime[0], pageCharCount, ptrMtxPage);
        disp = SCROLL;
    }

    else if(disp == WEIGHT)
    {
        int pageCharCount = ((sizeof(pageWeight)-1) / (sizeof(pageWeight[0])));
        mtxPageLength = page2Matrix(&pageWeight[0], pageCharCount, ptrMtxPage);
        disp = SCROLL;
    }

    else if(disp == HEIGHT)
    {
        int pageCharCount = ((sizeof(pageHeight)-1) / (sizeof(pageHeight[0])));
        mtxPageLength = page2Matrix(&pageHeight[0], pageCharCount, ptrMtxPage);
        disp = SCROLL;
    }

    else if(disp == SCROLL)
    {
      static int i = MTX_WIDTH-1;
      
      if(i >= 0)
      {
        // Matrix is displayed as a whole on the neopixel baord
        write2Matrix(ptrMtxPage, mtxPageLength, i);
      }
      else
      {
        // Matrix leaves neopixel board on the left and can only be displayed from a certain point on
        write2Matrix((ptrMtxPage-i), (mtxPageLength+i), 0);
      }
      i--;
      
      if(i < -mtxPageLength)
      // Text has left neopixel board completely, therfore text can be repeated
      {
        i = MTX_WIDTH-1;    // Reset text position to first letter rigth edge of matrix
        scrollCounter++;    // Increase scroll counter
        if(scrollCounter >= amountScroll)
        {
          // load new text
          currentText = currentText+1 ;
          if(currentText == SCROLL)
          {
            // No new text -> load first text
            currentText = INTRO;
            
            if((enableRainbowMode == true) && !((++colorRainbowCount) % colorRainbowInterval))
            // set Raibow mode if enabled and counter reached interval
            {
              rainbowMode = true;
            }
            else
            {
              rainbowMode = false;
            }
            
          }
          disp = currentText;
        }
      }
    }
    strip.show();
    delay(refreshRate);
    strip.clear();
  }
}

/*----------------------------------------------
 * Functions
 *----------------------------------------------*/ 
/**
 * Measures Brightness of Environmet and calculates a relative brightness
 * for the LED Matrix in order to be easily readable at any time of the
 * day.
 * 
 * +5V 
 *  ^
 *  |
 * +++
 * | |
 * | |  Resistor 100kOhm
 * | |
 * +++
 *  |
 *  +-----------C Analog in
 *  |
 * +++
 * | |
 * | |  Photo Resistor NSL-19M51
 * | |
 * +++
 *  |
 * -+-
 * GND
 * 
 * @return  brightness value from min to max value
 */
/**
 * Calcualtes Brightenss for neopixel matrix
 */
int getBrightness()
{
  double photoResValue = 0.0d;
  uint8_t brightnessValue = 0;
  uint8_t brightnessValueAvg = 0;
  uint16_t rawValue = analogRead(PHOTO_PIN);   // read voltage divider value
  // calcate voltage on ADC input
  double voltageValue = rawValue*refVoltage/adcRes;

  // calculate photo resistance from ADC value
  photoResValue = (Resistor/((refVoltage/(voltageValue))-1)) * falseLightCorrFactor;

  // calculate brightness of neopixel matrix
  if(photoResValue < 1)
  {
    // remove values so small they cause trouble
    photoResValue = 1;
  }

  //logharitm the value since light is not linear and relativate it
  photoResValue = log10(photoResValue)/log10(photoResMax);

  //invert it, since photo resistor is not proportional
  photoResValue = 1-photoResValue;
  
  // Qantify value
  photoResValue = photoResValue * brightnessMaxValue;

  if(photoResValue < brightnessMinValue)
  {
    // if calculated value is lower than minimum use minimum brightness.
    photoResValue = brightnessMinValue;
  }

  brightnessValue = (int)photoResValue;
  
  //calculate average of brightness of the last 50 values;
  brightnessValueAvg = calcAvg(brightnessValue, &matrixBrightAvg[0], (sizeof(matrixBrightAvg)/sizeof(matrixBrightAvg[0])));

  return ((uint8_t)brightnessValueAvg);
}

/**
 * Adds value to Array and calculates the Avg for the given array of given size
 * 
 * @param value         value that is added to array
 * @param avgArray      pointer to array holding all values for average
 * @param sizeArray     size of avg array
 * 
 * @return int          avgValue
 */
int calcAvg (uint8_t value, uint8_t *avgArray, uint8_t sizeArray)
{
  static uint8_t arrayIterator = 0;
  uint8_t i;
  int32_t summe = 0;

  *(avgArray + arrayIterator) = value;

  arrayIterator++;
  if(arrayIterator >= sizeArray)
  {
    arrayIterator = 0;
  }

  for(i = 0; i < sizeArray; i++)
  {
    summe += *(avgArray + i);
  }
  return ((uint8_t)(summe/sizeArray));
}


/**
 * Writes a certain number of colums to the matrix at given startPosition
 * 
 * @param char *matrix      matrix containing the columns that are written on the neopixel board
 * @param int columns       amount of columns to write
 * @param int startColumn   position of first columns to be written
 *  
 * @return int              column index of next available empty column
 */ 
int write2Matrix(char *matrix, int matrixWidth, int startColumn)
{
  int x;      // column on neopixel matrix (whole)
  int i = 0;  // iterator for width of matrix that shall be printed
  
  // Write at column x
  for(x = startColumn, i = 0; i < matrixWidth; x++, i++)
  {
    int y;
    /** 
     *  Hardware (Matrix) requires even columns (0,2,4,...) to be written from top down
     *  and odd columns (1,3,5,...) to be written from bottom up
     *  
     *   0 1 2 3 4
     *  +- - - - ->x
     *  |0 7 0 7 0
     *  |1 6 1 6 1
     *  |2 5 2 5 2
     *  |3 4 3 4 3
     *  |4 3 4 3 4
     *  |5 2 5 2 5
     *  |6 1 6 1 6
     *  |7 0 7 0 7
     *  y
     */

    //Write at column x, row y
    for(y = 0; y < MTX_HEIGHT; y++)
    {
      if(((matrix[i] >> y) & 1) == 1)
      {
        uint32_t color = 0x00000000;
        uint8_t saturation = saturationDefault;
        static uint16_t hue = hueDefault;
        
        // Determine in which color type the color shall be set
        switch(colorType)
        {
          case HUE:
            color = strip.ColorHSV(hue, saturation, 255);
            break;
          case RGB:
          defualt:
            color = ((((uint32_t)colorR & 0x000000ff) << 16) |
                    (((uint32_t)colorG & 0x000000ff) << 8) |
                    ((uint32_t)colorB & 0x0000000ff));
        }

        // Pixel of column x and row y shall be set
        // Set colors
        if (rainbowMode == true)
        {
          hue += hueChangeRate;
          saturation = saturationRainbow;
          color = strip.ColorHSV(hue, saturation, 255);
        }
        
        if(x%2 > 0)
        {
          // Odd column - print bottom up
          strip.setPixelColor(((x*MTX_HEIGHT)+(MTX_HEIGHT-1-y)), color);
        }
        else
        {
          // Even column - print top down
          strip.setPixelColor(((x*MTX_HEIGHT)+y), color);
        }
      }
      
    }
  }
  return x+1;
}

/**
 * Builds a matrix for a provided page
 * Page is a string of charachters
 * 
 * @param char *page      char string(a.k.a. page) for conversion
 * @param int charCount   amount of characters in page 
 * @param char *matrix    pixel matrix for page
 * 
 * @return int            length of matrix page in columns
 */
int page2Matrix(char *page, int charCount, char *matrix)
{
  int i;
  int mtxLength = 0;
  
  for(i = 0; i < charCount; i++)
  {
    switch(*(page+i))
    {
      case ' ':
        // character is a ' '
        char2Matrix(*(page+i), (matrix+mtxLength), getSpaceWidth());
        mtxLength += getSpaceWidth();
        break;
      case '.':
      case ':':
        // character is a '.' or ':'
        char2Matrix(*(page+i), (matrix+mtxLength), getPunctuationWidth());
        mtxLength += getPunctuationWidth();
        break;
      default:
        // for all other characters
        char2Matrix(*(page+i), (matrix+mtxLength), getLetterWidth());
        mtxLength += getLetterWidth();
    }
  }
  return mtxLength;
}
