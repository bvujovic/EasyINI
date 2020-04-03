#include <EasyINI.h>

EasyINI::EasyINI(const char *fileName)
{
    SPIFFS.begin();
    fp = SPIFFS.open(fileName, "r");
    if (!fp)
        Serial.println("Nema fajla.");
}

void EasyINI::Close()
{
    //B if (Opened())
    fp.close();
}

int EasyINI::GetInt(const char *name)
{
    Serial.println(fp.position());
    char buf[80];
    size_t read = fp.readBytesUntil('\n', buf, 80);
    Serial.println(buf);
    size_t n = strlen(name);
    //todo ...
    
    return 111;
}