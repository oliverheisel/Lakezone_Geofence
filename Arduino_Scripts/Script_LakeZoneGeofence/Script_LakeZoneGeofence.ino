// Include necessary libraries for GPS, serial communication, and LCD display handling
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <avr/pgmspace.h>

// Set the pins used by the GPS module
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// Create objects for GPS, serial communication, and the LCD display
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define LED pins
int ROT = 8;
int GELB = 9;
int GRUN = 10;

// Define the number of sides for the large polygon
const uint8_t polySides = 179;

// Large Polygone (150m - 300m zone - yellow)
// Define coordinates of the large polygon stored in flash memory to save RAM
const float polyY[polySides] PROGMEM = {47.35484441901, 47.35661938564, 47.35660047973, 47.35653836329, 47.35643361368, 47.3564259854, 47.35599040283, 47.35596591814, 47.35563905888, 47.35542166978, 47.35532448601, 47.35525983356, 47.3549749567, 47.35496898023, 47.35495365945, 47.35491416211, 47.35484111085, 47.35478720646, 47.35470499341, 47.3546892557, 47.35466721667, 47.35463277867, 47.35456603804, 47.35450975058, 47.35444534194, 47.35436585021, 47.35418257254, 47.3541540482, 47.35415061055, 47.35400733669, 47.35373037352, 47.35369186694, 47.35362231366, 47.35320249251, 47.35316192766, 47.35298077787, 47.35276676118, 47.35236947954, 47.3522092085, 47.35187393507, 47.35163969869, 47.35160230314, 47.35149704822, 47.35147190214, 47.35141707189, 47.35140224625, 47.35139955674, 47.35139019075, 47.3512061502, 47.35114869594, 47.3511503519, 47.35121852197, 47.351234685, 47.35120032563, 47.35115925949, 47.35116985322, 47.35118936369, 47.3511363068, 47.35113277489, 47.35112851758, 47.35109921079, 47.35108571411, 47.35103022737, 47.35104792883, 47.35101697456, 47.35100670666, 47.35099775492, 47.35086883956, 47.35085310291, 47.35078594879, 47.35071965324, 47.35067039137, 47.35064879634, 47.3506501831, 47.35053324626, 47.35045715989, 47.35029918702, 47.35026727942, 47.35022817161, 47.34949568948, 47.34946710819, 47.34940987052, 47.34936236279, 47.34932156796, 47.34915779287, 47.34871467426, 47.34861430212, 47.34838072221, 47.34824231281, 47.34793366345, 47.34790769122, 47.34773332347, 47.34735233236, 47.34733656856, 47.34731910637, 47.34729720225, 47.34727872449, 47.34203610392, 47.34221643031, 47.3422390653, 47.34238777171, 47.3425309534, 47.34298232122, 47.343119967, 47.34331611942, 47.34336869583, 47.34396460986, 47.34416716888, 47.34463653443, 47.34525508951, 47.34538221248, 47.34566792485, 47.34580776891, 47.34586414004, 47.34609013556, 47.34650942108, 47.34652098711, 47.34666231896, 47.34707884469, 47.34708824558, 47.34722449425, 47.34726969354, 47.34762816581, 47.34763324013, 47.34768102519, 47.34792499885, 47.34800523355, 47.34805700272, 47.3482939532, 47.34829120212, 47.34833368262, 47.34835885953, 47.34845655644, 47.34856249004, 47.3486859691, 47.34873232486, 47.34903431852, 47.34910739054, 47.3494589798, 47.34954421638, 47.34969400485, 47.34977558025, 47.34992259931, 47.35015139466, 47.35027148763, 47.35030112767, 47.3503964525, 47.35064280385, 47.35070178474, 47.35076125158, 47.35084829451, 47.35091473284, 47.35121667296, 47.35143678733, 47.35148747352, 47.35157889046, 47.35158610147, 47.3517138114, 47.351828715, 47.3520230905, 47.35203971313, 47.35204425893, 47.35221957297, 47.35225559868, 47.35232687746, 47.35232631647, 47.35247962512, 47.35254230208, 47.35283563339, 47.35325429691, 47.3532709349, 47.35368550918, 47.3537505698, 47.35379031138, 47.35384411023, 47.35428774094, 47.35442051598, 47.35442971511, 47.35484441901}; // X
const float polyX[polySides] PROGMEM = {8.5380774252, 8.546341109, 8.5464245294, 8.5465904664, 8.5466713003, 8.5466713347, 8.546904048, 8.5469247185, 8.5473114632, 8.5473960603, 8.5474248646, 8.5474599215, 8.5477079992, 8.5476949957, 8.5477102439, 8.5477609402, 8.5478245544, 8.5479238919, 8.5480294144, 8.5480552433, 8.5481068541, 8.5481292882, 8.5481475362, 8.5481826208, 8.5482420976, 8.5482971651, 8.5484509607, 8.5484794634, 8.5484818344, 8.5483952473, 8.5483380943, 8.5483251183, 8.5483084488, 8.54830522, 8.5483143025, 8.5483940867, 8.5484069922, 8.5486246948, 8.5487579313, 8.5491519675, 8.5496809796, 8.5498894538, 8.5502100577, 8.5504843221, 8.5507274501, 8.550819132, 8.5508437258, 8.550858076, 8.5514175273, 8.5520332983, 8.5521507364, 8.552733918, 8.5527807937, 8.5528961418, 8.553518549, 8.5537722416, 8.5539011059, 8.5540804409, 8.5540978385, 8.5541674126, 8.5542633298, 8.5543298504, 8.5549702336, 8.5550988442, 8.5552105821, 8.5554174039, 8.55550578, 8.5557809897, 8.5558269859, 8.556113077, 8.5562752139, 8.5564119851, 8.5564548361, 8.5564563493, 8.5566764422, 8.5568617516, 8.5574301861, 8.5580341347, 8.5580757678, 8.5588094827, 8.5588174964, 8.5588492291, 8.5588503723, 8.5588712902, 8.5588343633, 8.5589554169, 8.559009559, 8.5591829049, 8.5592171152, 8.5594184724, 8.5594415246, 8.5594650802, 8.5597016043, 8.5597159246, 8.5597381004, 8.5597516923, 8.5597684966, 8.5399959283, 8.5394753112, 8.5392878658, 8.5391764013, 8.5392508299, 8.5392531521, 8.5392195205, 8.5391820201, 8.5391704144, 8.5390211518, 8.5391000331, 8.5390360177, 8.5387860742, 8.5387101198, 8.5385917955, 8.5385680198, 8.5385447378, 8.5384513552, 8.5381556567, 8.5381383669, 8.5381659935, 8.5380524399, 8.5380475337, 8.5380252212, 8.5380074657, 8.5377807175, 8.5377744766, 8.537753574, 8.5375067423, 8.5376533735, 8.537716408, 8.537915959, 8.5379235142, 8.5379570022, 8.5379706211, 8.5380528987, 8.5380807705, 8.5381475643, 8.5381622979, 8.5382068921, 8.5382055268, 8.5381301111, 8.5380944779, 8.5380175914, 8.5379676227, 8.5378775888, 8.5376917606, 8.5377241511, 8.5377358574, 8.537773526, 8.5378356022, 8.5378422844, 8.5378470817, 8.5378512709, 8.53785206, 8.5378447042, 8.537812658, 8.5377990333, 8.5377941203, 8.5377966701, 8.5378323513, 8.5378560824, 8.5378543887, 8.5378550902, 8.5378542042, 8.5378526765, 8.5378364721, 8.5378319216, 8.5378410173, 8.537861491, 8.5378631697, 8.5380925264, 8.5381996343, 8.5381999769, 8.5381128624, 8.5380662011, 8.538080859, 8.5380895, 8.538052438, 8.5379726783, 8.5379795811, 8.5380774252}; // Y

// Define the number of sides for the smaller polygon
const uint8_t polySides2 = 65;

// Small Polygone (300m zone - green)
// Define coordinates of the smaller polygon stored in flash memory
const float polyY2[polySides2] PROGMEM = {47.35003957975, 47.35187943608, 47.35170584389, 47.35154557482, 47.35087503826, 47.35040657514, 47.35034403516, 47.35019731357, 47.35017450461, 47.35010598396, 47.34991474388, 47.34979983818, 47.34980149409, 47.34986971218, 47.34981265115, 47.34981393023, 47.34980644514, 47.34979294878, 47.34970814252, 47.34970335168, 47.34970080635, 47.34966377662, 47.34964804032, 47.3495837662, 47.34952756841, 47.34950108125, 47.34937847984, 47.34930239509, 47.34901099337, 47.34825028019, 47.34814990891, 47.34795373166, 47.3478540691, 47.34753918514, 47.34740552061, 47.34678919099, 47.34256758586, 47.34309363542, 47.34320333704, 47.3433174554, 47.34348995709, 47.34359293565, 47.34395243985, 47.34405508669, 47.34499381991, 47.34561237908, 47.34573927714, 47.34603253966, 47.34617238197, 47.34622890822, 47.34645490526, 47.34679268819, 47.34728373378, 47.34757249041, 47.34761769, 47.34783821631, 47.34799594848, 47.34817583498, 47.3484010904, 47.34844744591, 47.34905143173, 47.34912450378, 47.3498276848, 47.34991292196, 47.35003957975}; // X
const float polyX2[polySides2] PROGMEM = {8.5399408089, 8.5467977485, 8.5468962302, 8.5470294703, 8.5478175497, 8.5488755611, 8.5492242164, 8.5496769513, 8.5499578018, 8.5502616347, 8.5508429681, 8.5520744802, 8.5521919153, 8.5527754944, 8.5536403014, 8.5536709312, 8.5536954288, 8.5537619478, 8.5547407285, 8.5547580222, 8.5548092951, 8.5548883463, 8.5549343417, 8.5552081674, 8.555345609, 8.5554191487, 8.5556499044, 8.5558352113, 8.556883769, 8.5570916119, 8.557145757, 8.5572913528, 8.5573159896, 8.557521426, 8.5575394878, 8.5579221076, 8.5420004053, 8.5412106795, 8.541211248, 8.5411833691, 8.5411503967, 8.5411277323, 8.5410381433, 8.5410781205, 8.5409501236, 8.5407002007, 8.5406243854, 8.5405029448, 8.5404791744, 8.5404558303, 8.5403624552, 8.5401242495, 8.5399903984, 8.539943121, 8.539925367, 8.5397858841, 8.5399187277, 8.5399660632, 8.5400879194, 8.5401026547, 8.5401918651, 8.5401905025, 8.5400396962, 8.5400040658, 8.5399408089}; // Y

unsigned long previousMillis = 0; // will store the last time LED was updated
const long interval = 700; // interval at which to blink (milliseconds) when no gps
unsigned long lastLedOnMillis = 0; // will store the last time any LED was on (when there was an GPS signal)
const long ledOffInterval = 2000; // interval to check if LEDs are off (milliseconds) all colors, when no gps
const long fastBlinkInterval = 200; // interval blinking, when over the speed limit

// Setup function to initialize hardware
void setup() {
  pinMode(ROT, OUTPUT);
  pinMode(GELB, OUTPUT);
  pinMode(GRUN, OUTPUT);

  Serial.begin(9600);
  ss.begin(GPSBaud);
  lcd.init();
  lcd.backlight();
}

// Main loop function
void loop() {
  static bool ledState = LOW;
  unsigned long currentMillis = millis();

  // Check if data is available from the GPS
  if (ss.available() > 0) {
    // Decode GPS data
    if (gps.encode(ss.read())) {
      // Check if GPS location is updated
      if (gps.location.isUpdated()) {
        // Determine if the current location is within the defined polygons
        bool inLargePolygon = pointInPolygon(gps.location.lng(), gps.location.lat(), polyX, polyY, polySides);
        bool inSmallPolygon = pointInPolygon(gps.location.lng(), gps.location.lat(), polyX2, polyY2, polySides2);
        // Calculate the speed in km/h
        double speedKmH = gps.speed.kmph();

        // Determine the appropriate LED to control based on location and speed
        int ledPin = ROT; // Default to outside both polygons
        bool shouldBlink = speedKmH > 10;
        long currentInterval = interval; // Use normal interval by default

        // Set LED behavior based on the location
        if (inSmallPolygon) {
          ledPin = GRUN;
          shouldBlink = speedKmH > 40;
        } else if (inLargePolygon) {
          ledPin = GELB;
        }

        // Use faster blinking interval if over speed limit
        if (shouldBlink) {
          currentInterval = fastBlinkInterval;
        }

        // Reset all LEDs before setting the new state
        digitalWrite(ROT, LOW);
        digitalWrite(GELB, LOW);
        digitalWrite(GRUN, LOW);

        // Manage LED blinking based on timing and condition
        if (shouldBlink) {
          if (currentMillis - previousMillis >= currentInterval) {
            previousMillis = currentMillis;
            ledState = !ledState;
            digitalWrite(ledPin, ledState);
          }
        } else {
          digitalWrite(ledPin, HIGH);
        }

        // Update last time any LED was on
        lastLedOnMillis = currentMillis;

        // Update LCD with current GPS coordinates
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Lat:");
        lcd.print(gps.location.lat(), 6);
        lcd.setCursor(0, 1);
        lcd.print("Lng:");
        lcd.print(gps.location.lng(), 6);
      }
    }
  }

  // Check if LEDs have been off for more than 2 seconds
  if (currentMillis - lastLedOnMillis >= ledOffInterval) {
    // Flash all LEDs
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(ROT, ledState);
      digitalWrite(GELB, ledState);
      digitalWrite(GRUN, ledState);
    }
  }
}


// Function to determine if a point is inside a polygon
bool pointInPolygon(float x, float y, const float *polyX, const float *polyY, int polySides) {
  bool oddNodes = false;
  int j = polySides - 1;
  for (int i = 0; i < polySides; i++) {
    float xi = pgm_read_float_near(&polyX[i]);
    float yi = pgm_read_float_near(&polyY[i]);
    float xj = pgm_read_float_near(&polyX[j]);
    float yj = pgm_read_float_near(&polyY[j]);
    if ((yi < y && yj >= y) || (yj < y && yi >= y)) {
      oddNodes ^= (xi + (y - yi) / (yj - yi) * (xj - xi) < x);
    }
    j = i;
  }
  return oddNodes;
}
