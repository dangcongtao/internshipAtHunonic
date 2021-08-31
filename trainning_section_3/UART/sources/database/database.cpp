#include "database.h"

const char* TAG = "Database";

Database* Database::dbInstance = nullptr; 

Database::~Database()
{

}

Database* Database::getInstance(const char*  db_file)
{
    if (nullptr == dbInstance) {
        dbInstance = new Database(db_file);
    }
    return dbInstance;
}

bool Database::getRequestSync(void)
{
    return this->dbRequestSync;
}

void Database::setRequestSync(void)
{
    this->dbRequestSync = true;
}

void Database::resetRequestSync(void)
{
    this->dbRequestSync = false;
}

int Database::Load()
{
    int ret = -1;

    this->fd = open(this->fileName, O_RDWR | O_CREAT | O_SYNC, 0666);
    if (fd < 0) {
        m_printf(TAG, "open database file %s failed, errno: %d\n", this->fileName, errno);
        return -1;
    }

    ret = read(fd, &this->deviceInform, sizeof(this->deviceInform));
    if (ret < 0) {
        m_printf(TAG, "read database file %s failed, errno: %d\n", this->fileName, errno);
        close(fd);
        return -1;
    }

    if (this->deviceInform.checksum != DB_CHECKSUM) {
        m_printf(TAG, "checksum error, checksum: %x, expect checksum: %x\n", this->deviceInform.checksum, DB_CHECKSUM);
        this->deviceInform.checksum = DB_CHECKSUM;
        setRequestSync();
    } else {
        m_printf(TAG, "checksum ok, checksum: %x\n", this->deviceInform.checksum);
    }

    close(fd);

    return 0;
}

int Database::Sync()
{
    int ret = -1;

    this->fd = open(this->fileName, O_RDWR | O_CREAT | O_SYNC, 0666);
    if (fd < 0) {
        m_printf(TAG, "open database file %s failed, errno: %d\n", this->fileName, errno);
        return -1;
    }

    ret = write(this->fd, &this->deviceInform, sizeof(this->deviceInform));
    if (ret < 0) {
        m_printf(TAG, "write database file %s failed, errno: %d\n", this->fileName, errno);
        close(fd);
        return -1;
    }

    close(fd);
    
    return 0;
}