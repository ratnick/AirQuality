const char DEVICE_ID[] = "CO Sensor";            
const char displayTitle1[] = "CO concentration"; 
const char metricUnit1[] = "%";
const char displayTitle2[] = "Threshold exceededn/a";
const char metricUnit2[] = "0/1";
const int lowerLimit1 = 0;
const int upperLimit1 = 20;                  
const int lowerLimit2 = 0;
const int upperLimit2 = 0;
const int  proposedSampleFreq = 5000; 

enum SensorType {
	CoSensor_MQ7
};
SensorType SENSORTYPE = CoSensor_MQ7;          

IPAddress hostIPaddress = (0xFFFFFFFF);

const time_t DS_INIT_VALUE = 3;
time_t deepSleepPeriod = DS_INIT_VALUE; // sec   NOTE: This is the initial value. It is modified via CMD_GOTO_DEEP_SLEEP 
struct {
	uint32_t crc32;
	int deepSleepPeriod;
} rtcData;


// Pins on WeMos D1 Mini
const int SPI_CS = 16; 
const int LED_PIN = D4;

const int ANALOG_IN_PIN = A0;//the AOUT pin of the CO sensor goes into analog pin A0 of the arduino
const int DIGITAL_IN_PIN = D8;//the DOUT pin of the CO sensor goes into digital pin D8 of the arduino

enum LedState {
  LED_Off,
  LED_On
};

enum SensorMode {
  None,
  Bmp180Mode,
  DhtShieldMode
};

enum BoardType {
  NodeMCU,
  WeMos,
  SparkfunThing,
  Other
};

struct SensorData {
	const char* deviceID = DEVICE_ID;
	float value1;
	float value2;
	int digitalValue1;
	int digitalValue2;
};
// size = max nbr of elements in SensorData
#define SENSORDATA_JSON_SIZE (JSON_OBJECT_SIZE(15))  

struct DeviceConfig {
  int WifiIndex = 0;
  unsigned long LastWifiTime = 0;
  int WiFiConnectAttempts = 0;
  int wifiPairs = 1;
  String ssid;
  String pwd;
  BoardType boardType = Other;            // OperationMode enumeration: NodeMCU, WeMos, SparkfunThing, Other
  SensorMode sensorMode = None;           // OperationMode enumeration: DemoMode (no sensors, fakes data), Bmp180Mode, Dht11Mode
  unsigned int deepSleepSeconds = 0;      // Number of seconds for the ESP8266 chip to deepsleep for.  GPIO16 needs to be tied to RST to wake from deepSleep http://esp8266.github.io/Arduino/versions/2.0.0/doc/libraries.html
  SensorType sensorType = SENSORTYPE;
};

