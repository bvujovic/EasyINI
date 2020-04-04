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
    fp.close();
}

int EasyINI::GetInt(const char *name)
{
    //T Serial.println(fp.position());
    char buf[80];
    fp.readBytesUntil('\n', buf, 80);
    size_t n = strlen(name);
    if (strncmp(name, buf, n) == 0)
        return atoi(buf + n + 1);
    else
        return -1;
}

float EasyINI::GetFloat(const char *name)
{
    char buf[80];
    fp.readBytesUntil('\n', buf, 80);
    size_t n = strlen(name);
    if (strncmp(name, buf, n) == 0)
        return atof(buf + n + 1);
    else
        return -1.0;
}

String EasyINI::ProcLine(const char *name)
{
    String line = fp.readStringUntil('\n');
    if (line.startsWith(name))
    {
        size_t n = strlen(name);
        if (line[n] == '=')
            return line.substring(n + 1);
    }
    return "";
}

String EasyINI::GetString(const char *name)
{
    size_t initPos = fp.position();
    String s;
    while (fp.available())
        if (!(s = ProcLine(name)).isEmpty())
            return s;
    fp.seek(0);

    while (fp.position() < initPos)
        if (!(s = ProcLine(name)).isEmpty())
            return s;
    return "";
}

//* Bez for petlje (koja ne treba da utice na rezultat), metoda ne radi!
// char *EasyINI::GetCharArray(const char *name)
// {
//     char buf[80];
//     size_t nBuf = fp.readBytesUntil('\n', buf, 80);
//     Serial.println(buf);
//     Serial.println(nBuf);
//     size_t n = strlen(name);
//     Serial.println(n);
//     if (strncmp(name, buf, n) == 0)
//     {
//         Serial.println("Ne vracam NULL");
//         buf[nBuf - 1] = 0;
//         for (char *p = buf + n + 1; p < buf + nBuf; p++)
//             Serial.println((int)*p);

//         return buf + n + 1;
//     }
//     else
//     {
//         Serial.println("Vracam NULL");
//         return NULL;
//     }
// }