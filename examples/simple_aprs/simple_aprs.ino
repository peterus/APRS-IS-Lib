#include <WiFiMulti.h>
#include <APRS-IS.h>

#include "settings.h"

WiFiMulti WiFiMulti;
APRS_IS aprs_is(USER, PASS, TOOL, VERS);

void setup()
{
	Serial.begin(115200);
	Serial.println("simple APRS-IS test");

	WiFiMulti.addAP(WIFI_NAME, WIFI_KEY);
	Serial.print("Waiting for WiFi");

	while(WiFiMulti.run() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(500);
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	delay(500);
}

void loop()
{
	if(WiFiMulti.run() != WL_CONNECTED)
	{
		Serial.println("WiFi not connected!");
		delay(1000);
		return;
	}
	if(!aprs_is.connected())
	{
		Serial.print("connecting to server: ");
		Serial.print(SERVER);
		Serial.print(" on port: ");
		Serial.println(PORT);
		if(!aprs_is.connect(SERVER, PORT, FILTER))
		{
			Serial.println("Connection failed.");
			Serial.println("Waiting 5 seconds before retrying...");
			delay(5000);
			return;
		}
		Serial.println("Connected to server!");
	}
	if(aprs_is.available() > 0)
	{
		Serial.println(aprs_is.getMessage());
	}
}
