#include <FS.h>

// ...
class EasyINI
{
private:
    File fp;

public:
    EasyINI(const char *fileName);

    bool Opened() { return fp; }
    void Close();
    // Size of the file.
    size_t Size() const { return fp.size(); }

    int GetInt(const char *);
};
