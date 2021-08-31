#ifndef _MQTT_H_
#define _MQTT_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstdint>

class MqttConnection {
private:
    unsigned char *url;
    unsigned char *username;
    unsigned char *passwd;
public:
    MqttConnection(void);
    ~MqttConnection(void);

    void MqttConnectionInit();
};

#endif /* _MQTT_H_ */
