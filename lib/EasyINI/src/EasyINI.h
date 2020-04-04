#include <FS.h>

// ...
class EasyINI
{
private:
    File fp;


public:
    String ProcLine(const char *);
    EasyINI(const char *fileName);

    bool Opened() { return fp; }
    void Close();
    // Size of the file.
    size_t Size() const { return fp.size(); }

    int GetInt(const char *);
    float GetFloat(const char *);
    // char *GetCharArray(const char *);
    String GetString(const char *);
};
