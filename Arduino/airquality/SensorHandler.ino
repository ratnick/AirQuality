
void setupSensor() {
	Serial.print("\nSensor name = ");
	Serial.println(sensorData.deviceID);

	switch (wifiDevice.sensorType) {
		case CoSensor_MQ7:
			SetupCoSensor_MQ7();
			break;
	}
	ReadI2CAddresses();
}

void SetupCoSensor_MQ7()
{
	//GetSensorResistorValue();  // execute this one only once for each sensor to deduct R0

	Serial.println("SetupCoSensor_MQ7");
	pinMode(ANALOG_IN_PIN, INPUT);//sets the pin as an input to the arduino
	Serial.println("SetupCoSensor_MQ7 a");
	pinMode(DIGITAL_IN_PIN, INPUT);//sets the pin as an output of the arduino
	Serial.println("SetupCoSensor_MQ7 b");

}

void readSensor() {
	switch (wifiDevice.sensorType) {
	case CoSensor_MQ7:
		readCoSensor_MQ7();
		break;
	}
}

void readCoSensor_MQ7()
{
	// https://www.teachmemicro.com/use-mq-7-carbon-monoxide-sensor/

	float sensor_volt = 0;
	float RS_gas = 0;
	float ratio = 0;
	float sensorValue = 0;
	float ppm = 0;
	const float R0 = 0.57; // found via the function GetSensorResistorValue below


	for (int i = 0; i<900; i++) {
		sensorValue = analogRead(ANALOG_IN_PIN);
		sensor_volt = sensorValue / 1024 * 5.0;
		RS_gas = (5.0 - sensor_volt) / sensor_volt;
		ratio = RS_gas / R0; //Replace R0 with the value found using the sketch above
		ppm = 100 * pow(log10(40) / log10(0.09), ratio);


		Serial.print("PPM: ");
		Serial.println(ppm);
		sensorData.value1 = ppm;
		delay(100);
	}

	sensorData.digitalValue1 = digitalRead(DIGITAL_IN_PIN);

	Serial.print("\readCoSensor_MQ7: value1 (ppm) = ");
	Serial.print(sensorData.value1);
	Serial.print(", digitalValue1 (threshold) = ");
	Serial.println(sensorData.digitalValue1);

}

void ReadI2CAddresses() {

	Serial.println("Scanning for attached I2C devices ...");
	byte count = 0;

	Wire.begin();
	for (byte i = 8; i < 120; i++)
	{
		Wire.beginTransmission(i);
		if (Wire.endTransmission() == 0)
		{
			Serial.print("Found address: ");
			Serial.print(i, DEC);
			Serial.print(" (0x");
			Serial.print(i, HEX);
			Serial.println(")");
			count++;
			delay(1);  // maybe unneeded?
		} 
	} 
	Serial.print("Found ");
	Serial.print(count, DEC);
	Serial.println(" device(s).");
} 

void GetSensorResistorValue() {
	// https://www.teachmemicro.com/use-mq-7-carbon-monoxide-sensor/
	float sensor_volt;
	float RS_air;
	float R0;
	float sensorValue;
	int iMax = 100;

	//pinMode(A1, OUTPUT);//sets the pin as an input to the arduino
	pinMode(ANALOG_IN_PIN, INPUT);//sets the pin as an input to the arduino

	while (true) {

		//analogWrite(A1, 1023);
		//delay(60000);

		for (int i = 0; i<iMax; i++) {
			sensorValue = sensorValue + analogRead(ANALOG_IN_PIN);
			delay(900);
		}

		sensorValue = sensorValue / iMax;

		sensor_volt = sensorValue / 1024 * 5.0;
		RS_air = (5.0 - sensor_volt) / sensor_volt;
		R0 = RS_air / (26 + (1 / 3));

		Serial.print("R0 = ");
		Serial.println(R0);
		delay(1000);
	}
}