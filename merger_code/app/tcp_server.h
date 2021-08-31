#ifndef _M_TCP_H_
#define _M_TCP_H_

#include "cJSON.h"
#include <stdint.h>

typedef void (*hs_message_handler_t)(cJSON *jsRoot);

typedef struct {
    hs_message_handler_t _handler;
    int                 _cmd_number;
} hs_handler_t;


void* tcp_thread (void* args);

#endif /* _M_TCP_H_ */