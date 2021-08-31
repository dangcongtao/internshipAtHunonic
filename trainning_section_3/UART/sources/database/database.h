#ifndef _Database_H_
#define _Database_H_

#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <cctype>
#include <cstdint>

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  /*File Control Definition*/
#include <errno.h>  /*Error number definition*/

#include <m_log.h>

#define DB_FILENAME_LEN     30
#define DB_CHECKSUM         0x474E5544

typedef struct
{
    uint32_t checksum;
} DeviceInform_t;

class Database {
private:
    static Database *dbInstance;

    int fd;
    bool dbRequestSync;
    char fileName[DB_FILENAME_LEN];
    DeviceInform_t deviceInform;

    Database(void) {}
    Database(const char* db_filename)
    {
        fd = -1;
        dbRequestSync = false;
        memset(&deviceInform, 0, sizeof(DeviceInform_t));
        memset(fileName, 0, DB_FILENAME_LEN);
        sprintf(fileName, "%s", db_filename);
    }

public:

    virtual ~Database(void);
    static Database* getInstance(const char*  db_file);

    bool getRequestSync(void);
    void setRequestSync(void);
    void resetRequestSync(void);
    int Load(void);
    int Sync(void);
};

#endif /* _Database_H_ */
