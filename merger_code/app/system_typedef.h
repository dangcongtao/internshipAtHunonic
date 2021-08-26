#ifndef CJSON_KEYWORD_H__
#define CJSON_KEYWORD_H__

#define CJSON_KEY_TYPE          "gateway"
#define CJSON_KEY_AES_KEY       "netkey"
#define CJSON_KEY_AES_IV        "appkey"
#define CJSON_KEY_ACTION        "action"
#define CJSON_KEY_ACT_ID        "act_id"
#define CJSON_KEY_USER_ID       "u"
#define CJSON_KEY_MAC_ADDRESS   "mac"
#define CJSON_KEY_DEVICE_ID     "device_id"
#define CJSON_KEY_DEVICE_ADDRESS "device_addr"
#define CJSON_KEY_TIME          "time"
#define CJSON_KEY_URL           "url"
#define CJSON_KEY_IP            "ip"
#define CJSON_KEY_SSID          "ssid"
#define CJSON_KEY_PASS          "pass"
#define CJSON_KEY_PO            "po" /* power-on state */
#define CJSON_KEY_INDEX         "index"
#define CJSON_KEY_LOCK          "lock"
#define CJSON_KEY_T_ACT         "t_ac1"
#define CJSON_KEY_T_C           "t_c"
#define CJSON_KEY_BACKUP        "backup"

/* JSON KEY USE FOR CONFIGURATION PROCESSING */
#define CJSON_KEY_SERVER        "server"
#define CJSON_KEY_S_PORT        "port"
#define CJSON_KEY_S_USER        "su"
#define CJSON_KEY_S_PASS        "sp"
#define CJSON_KEY_TOPIC_PUB     "pub"
#define CJSON_KEY_TOPIC_SUB     "sub"

#define DEFAULT_AES_KEY "0000000000000000"
#define DEFAULT_AES_IV  "0000000000000000"

#define SIZEOF_ARRAY(array) (sizeof(array_handler) / sizeof(array_handler[0]))

typedef enum {
    SYSTEM_STARTUP = 0,
    SYSTEM_ACTIVE_NORMAL,
    SYSTEM_HANDLER_OTA
} state_machine_t;

typedef enum {
    CH1_ON = 1,
    CH1_OFF = 2,
    CH2_ON = 3,
    CH2_OFF = 4,
    CH3_ON = 5,
    CH3_OFF = 6,
    CH4_ON = 7,
    CH4_OFF = 8,
} switch_action_t;

typedef enum
{
    SRC_ACTION_USER = 0,
    SRC_ACTION_ALARM = 2,
} src_action_t;

typedef enum
{
    RESULT_SUCCESS = 1,
} result_t;


typedef enum
{
    LOW = 0,
    HIGH = !LOW,
} state_t;


#endif /* CJSON_KEYWORD_H__ */