#include <Arduino.h>
#include <EasyINI.h>

// ; i # na pocetku reda oznacavaju komentare
// [x] je Naslov foldera/kategorije
// pocetne i zavrsne beline ne uzimam tj. trimujem i naziv i vrednost - mozda ovo da bude opcija?
// citam fajl od mesta na kojem sam do kraja, pa od kraja do mesta na kojem sam poceo pretragu imena
// testirati: ima li problema ako se u istom skecu vise puta pozove SPIFFS.begin()
// pronaci neki nacin za davanje informacije o mogucim greskama
// sta ako pozovem close, a nisam ni otvorio fajl

void setup()
{
    Serial.begin(115200);

    // EI ei("test.ini", R/W);
    EasyINI ei("/test2.ini");
    // if(ei.Opened()) ...
    if (ei.Opened())
    {
        Serial.println(ei.Size());
        int x = ei.GetInt("one");
        Serial.println(x);
        // float f = ei.ReadFloat("two");
        // bool b = ei.ReadBool("three");
        // char *s = ei.ReadCharArray("four_five");
        // String *str = ei.ReadString("four_five");
    }
    // ei.Close();
    ei.Close();
    Serial.println(ei.Opened());

    while (true)
        delay(100);

    // ...
    // ei.WriteInt("one", 321);
}

void loop()
{
}