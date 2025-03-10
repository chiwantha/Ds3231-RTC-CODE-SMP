#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

void setup() {
    Serial.begin(115200);
    Wire.begin(4, 5);  // SDA = GPIO4 (D2), SCL = GPIO5 (D1)

    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }

    if (rtc.lostPower()) {
        Serial.println("RTC lost power, setting time...");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

String getTime() {
    DateTime now = rtc.now();
    return String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
}

String getDate() {
    DateTime now = rtc.now();
    return String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());
}

void loop() {
    Serial.println("Time: " + getTime() + "   Date: " + getDate());
    delay(1000);
}
