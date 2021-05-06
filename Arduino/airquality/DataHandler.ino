JsonObject& buildJson(JsonBuffer& jsonBuffer) {
		JsonObject& root = jsonBuffer.createObject();

		JsonArray& analogValues = root.createNestedArray("analog");
		for (int pin = 0; pin < 6; pin++) {
			int value = analogRead(pin);
			analogValues.add(value);
		}

		JsonArray& digitalValues = root.createNestedArray("digital");
		for (int pin = 0; pin < 14; pin++) {
			int value = digitalRead(pin);
			digitalValues.add(value);
		}

		return root;
	}

	void serializeJson_ReadSensorData(const SensorData& data, JsonObject& root)
	{
		root["deviceID"] = data.deviceID;
		root["value1"] = data.value1;
		root["value2"] = data.value2;
		root["digitalValue1"] = data.digitalValue1;
		root["digitalValue2"] = data.digitalValue2;
	}
	