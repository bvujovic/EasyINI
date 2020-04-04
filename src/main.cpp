#include <Arduino.h>
#include <EasyINI.h>

// ; i # na pocetku reda oznacavaju komentare
// [x] je Naslov foldera/kategorije
// pocetne i zavrsne beline ne uzimam tj. trimujem i naziv i vrednost - mozda ovo da bude opcija?
// citam fajl od mesta na kojem sam do kraja, pa od kraja do mesta na kojem sam poceo pretragu imena
// testirati: ima li problema ako se u istom skecu vise puta pozove SPIFFS.begin()
// sta ako pozovem close, a nisam ni otvorio fajl
// pronaci neki nacin za davanje informacije o mogucim greskama

void setup()
{
    Serial.begin(115200);
    Serial.println();

    //* EI ei("test.ini", R/W);
    EasyINI ei("/test2.ini");
    if (ei.Opened())
    {
        // Serial.println(ei.Size());
        // int x = ei.GetInt("one");
        int x = ei.GetInt("one");
        Serial.println(x);
        // float f = ei.ReadFloat("two");
        Serial.println(ei.GetFloat("two"));
        // bool b = ei.GetBool("three");
        bool b = ei.GetInt("three");
        Serial.println(b);
        // char *s = ei.GetCharArray("four_five");
        String s = ei.GetString("s");
        Serial.println(s);
        s = ei.GetString("str");
        Serial.println(s);
        s = ei.GetString("fsfsf");
        Serial.println(s);
        s = ei.GetString("four_five");
        Serial.println(s);
    }
    ei.Close();

    while (true)
        delay(100);

    // ...
    // ei.WriteInt("one", 321);
}

void loop()
{
}