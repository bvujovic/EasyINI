#include <Arduino.h>
#include <EasyINI.h>

// testirati: ima li problema ako se u istom skecu vise puta pozove SPIFFS.begin()
// sta ako pozovem close, a nisam ni otvorio fajl
// pronaci neki nacin za davanje informacije o mogucim greskama
// mozda staviti u destruktor Close? (ako je fajl prethodno otvoren)

EasyINI ei("/testx.ini");

void setup()
{
    Serial.begin(115200);
    Serial.println("\n");

    ulong ms = millis();
    ei.Open(EasyIniFileMode::Read);
    //if (ei.Open(EasyIniFileMode::Read))
    {
        Serial.println(ei.GetFloat("two", 5.99));
        Serial.println(ei.GetInt("three", 3));
        Serial.println(ei.GetInt("one", 1));
        Serial.println(ei.GetAll());
        Serial.println(ei.GetString("str", "bleja"));
        ei.Close();
    }
    Serial.println(millis() - ms);
    delay(2000);

    if (ei.Open(EasyIniFileMode::Write))
    {
        ei.SetFloat("two", 10.55);
        ei.SetInt("three", 125);
        ei.SetInt("ones", 100);
        ei.SetString("str", "Azuki");
        ei.Close();
    }    
    Serial.println("End.");

    while (true)
        delay(100);
}

void loop()
{
}