#include <EasyINI.h>

EasyINI::EasyINI(const char *fileName)
{
    SPIFFS.begin();
    this->fileName = fileName;
}

bool EasyINI::Open(EasyIniFileMode mode)
{
    fp = SPIFFS.open(fileName, mode == EasyIniFileMode::Read ? "r" : "w");
    if (!fp)
        Serial.println("Where's the file?");
    return fp;
}

char *EasyINI::ProcLineNum(const char *name, char *buf, size_t n)
{
    fp.readBytesUntil(EINI_ROW_SEP, buf, EINI_BUF_LEN);
    if (strncmp(name, buf, n) == 0 && buf[n] == EINI_VAL_SEP)
        return buf + n + 1;
    return NULL;
}

int EasyINI::GetInt(const char *name, int def)
{
    size_t initPos = fp.position();
    size_t n = strlen(name);
    char buf[EINI_BUF_LEN];
    char *p;

    while (fp.available())
        if ((p = ProcLineNum(name, buf, n)))
            return atoi(p);
    fp.seek(0);

    while (fp.position() < initPos)
        if ((p = ProcLineNum(name, buf, n)) != NULL)
            return atoi(p);

    return def;
}

float EasyINI::GetFloat(const char *name, float def)
{
    size_t initPos = fp.position();
    size_t n = strlen(name);
    char buf[EINI_BUF_LEN];
    char *p;

    while (fp.available())
        if ((p = ProcLineNum(name, buf, n)))
            return atof(p);
    fp.seek(0);

    while (fp.position() < initPos)
        if ((p = ProcLineNum(name, buf, n)) != NULL)
            return atof(p);

    return def;
}

String EasyINI::ProcLineString(const char *name)
{
    String line = fp.readStringUntil(EINI_ROW_SEP);
    if (line.startsWith(name))
    {
        size_t n = strlen(name);
        if (line[n] == EINI_VAL_SEP)
            return line.substring(n + 1);
    }
    return EINI_DEF_STR;
}

String EasyINI::GetString(const char *name, String def)
{
    size_t initPos = fp.position();
    String s;
    while (fp.available())
        if (!(s = ProcLineString(name)).isEmpty())
            return s;
    fp.seek(0);

    while (fp.position() < initPos)
        if (!(s = ProcLineString(name)).isEmpty())
            return s;
    return def;
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

String EasyINI::GetAll()
{
    fp.seek(0);
    return fp.readString();
}

void EasyINI::SetInt(const char *name, int val) { PRINT_TO_FILE }

void EasyINI::SetFloat(const char *name, float val) { PRINT_TO_FILE }

void EasyINI::SetString(const char *name, const char *val) { PRINT_TO_FILE }