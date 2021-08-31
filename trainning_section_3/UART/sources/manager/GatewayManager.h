#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstdint>

class GatewayManager {
private:
    unsigned char *url;
    unsigned char *username;
    unsigned char *passwd;
public:
    GatewayManager(void);
    ~GatewayManager(void);

    void GatewayManagerInit();
};

#endif /* _MANAGER_H_ */
