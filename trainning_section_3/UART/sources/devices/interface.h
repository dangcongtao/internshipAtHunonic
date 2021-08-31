#ifndef _IDevice_H_
#define _IDevice_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstdint>

class IDevice {
private:
    unsigned char *url;
    unsigned char *username;
    unsigned char *passwd;
public:
    IDevice(void);
    ~IDevice(void);

    void IDeviceInit();
};

#endif /* _IDevice_H_ */
