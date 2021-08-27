#include "tcp_server.h"

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "cJSON.h"
#include "aes_cbc128.h"
#include "system_typedef.h"
#include "udp_broadcast.h"

#define HS_TCP_PORT 49999
#define MAX_LEN_TCP_MSG    1024

/* database which have to save to file */
static char key[16], iv[16];
static char mqtt_server[128];
static uint32_t mqtt_port;
static char mqtt_user[64];
static char mqtt_pass[64];
static char topic_subscribe[256];
static char topic_publish[256];
static int device_address = 0;

static char m_message_real[MAX_LEN_TCP_MSG];
static int m_message_real_len = 0;
static char tcp_message_to_receive[MAX_LEN_TCP_MSG];
static int len_msg_receive = 0;
static char tcp_message_to_send[MAX_LEN_TCP_MSG];
static uint32_t tcp_msg_len = MAX_LEN_TCP_MSG;
static int have_request_send_tcp = 0;

static void hs_send_device_id(cJSON *jsRoot);
static void hs_get_info_config(cJSON *jsRoot);
static void hs_get_mqtt_server_info(cJSON *jsRoot);
typedef enum
{
	TCP_APP_GET_ID = 2,
	TCP_GET_INFOR_CONFIG = 3,
	TCP_GET_MQTT_SERVER_INFO = 4,
} state_handle_message_mqtt_t;

static hs_handler_t array_handler[] = {
	{hs_send_device_id, TCP_APP_GET_ID},
	{hs_get_info_config, TCP_GET_INFOR_CONFIG},
	{hs_get_mqtt_server_info, TCP_GET_MQTT_SERVER_INFO},
};


static void tcp_send_data(char* raw_message)
{
    /* encode data to send */
	tcp_msg_len = MAX_LEN_TCP_MSG;
	memset(tcp_message_to_send, 0, MAX_LEN_TCP_MSG);
    aes_cbc128_init((uint8_t *)DEFAULT_AES_KEY, (uint8_t *)DEFAULT_AES_IV);
    uint32_t aes_encrypt_result = aes_cbc128_encrypt((uint8_t *)raw_message, strlen(raw_message), (uint8_t*)tcp_message_to_send, (size_t *)&tcp_msg_len);
    if (aes_encrypt_result != AES_SUCCESS) {
        printf("Encode fail,error-code: %d\n", aes_encrypt_result);
        return;
    }

    have_request_send_tcp = 1;
}


/* {"gateway":2, "device_id":"device_id_here","type":"gateway"} */
/* {"id":"00112233445566778899AABBCCDDEEFF"} */
static void hs_send_device_id(cJSON *jsRoot)
{
	char respond[] = "{\"gateway\":2, \"device_id\":\"00112233445566778899AABBCCDDEEFF\",\"type\":\"gateway\"}";
	
	tcp_send_data(respond);

	clear_request_send_udp();
}

/* {"gateway":3,"netkey":"string16char","appkey":"string16char","device_addr":addr} */
static void hs_get_info_config(cJSON *jsRoot)
{
	cJSON *jsKey, *jsIv, *jsDeviceAddress;
    char *netkey = NULL, *appkey = NULL;
	char result = 0;
	char respond[MAX_LEN_TCP_MSG];

	if (jsRoot == NULL) {
        printf("jsRoot NULL\n");
        goto respond_user;
    }

	jsKey = cJSON_GetObjectItem(jsRoot, CJSON_KEY_AES_KEY);
	if (jsKey == NULL) {
		printf("jsKey NULL\n");
		goto respond_user;
	}
	netkey = jsKey->valuestring;
	
	jsIv = cJSON_GetObjectItem(jsRoot, CJSON_KEY_AES_IV);
	if (jsIv == NULL) {
		printf("jsIv NULL\n");
		goto respond_user;
	}
	appkey = jsIv->valuestring;

	jsDeviceAddress = cJSON_GetObjectItem(jsRoot, CJSON_KEY_DEVICE_ADDRESS);
	if (jsDeviceAddress == NULL) {
		printf("jsDeviceAddress NULL\n");
		goto respond_user;
	}

	device_address = jsDeviceAddress->valueint;
	strncpy(key, netkey, strlen(netkey) > sizeof(key) ? sizeof(key) : strlen(netkey));
	strncpy(iv, appkey, strlen(appkey) > sizeof(iv) ? sizeof(iv) : strlen(appkey));
	result = 1;

respond_user:
	memset(respond, 0, MAX_LEN_TCP_MSG);
	sprintf(respond, "{\"gateway\":3,\"result\":%d}", result);
	tcp_send_data(respond);
}

/* {"gateway":4, "server": "server", "port": port, "user": "mqtt_user", "pass":"mqtt_pass", "pub": "topicPub", "sub":"topincSub"} */
/* {"gateway":4, "result": RESULT_CODE, "devkey": "stringbase64"} */
static void hs_get_mqtt_server_info(cJSON *jsRoot)
{
	cJSON *jsServer, *jsPort;
	cJSON *jsUser, *jsPass;
	cJSON *jsPub, *jsSub;
	char *server = NULL;
	uint32_t port = 8;
	char* user = NULL, *pass = NULL;
	char* topic_pub = NULL, *topic_sub = NULL;
	char respond[MAX_LEN_TCP_MSG];
	int result = 0;

	if (jsRoot == NULL) {
		printf("jsRoot NULL\n");
		goto respond_user;
	}

	jsServer = cJSON_GetObjectItem(jsRoot, CJSON_KEY_MQTT_SERVER);

	if (jsServer == NULL) {
		printf("jsServer NULL\n");
		goto respond_user;
	}
	server = jsServer->valuestring;

	jsPort = cJSON_GetObjectItem(jsRoot, CJSON_KEY_MQTT_PORT);
	if (jsPort == NULL) {
		printf("jsPort NULL\n");
		goto respond_user;
	}
	port = jsPort->valueint;

	jsUser = cJSON_GetObjectItem(jsRoot, CJSON_KEY_MQTT_USER);
	if (jsUser == NULL) {
		printf("jsUser NULL\n");
		goto respond_user;
	}
	user = jsUser->valuestring;

	jsPass = cJSON_GetObjectItem(jsRoot, CJSON_KEY_MQTT_PASS);
	if (jsPass == NULL) {
		printf("jsPass NULL\n");
		goto respond_user;
	}
	pass = jsPass->valuestring;

	jsSub = cJSON_GetObjectItem(jsRoot, CJSON_KEY_TOPIC_SUB);
	if (jsSub == NULL) {
		printf("topic_sub NULL\n");
		goto respond_user;
	}
	topic_sub = jsSub->valuestring;

	jsPub = cJSON_GetObjectItem(jsRoot, CJSON_KEY_TOPIC_PUB);
	if (jsPub == NULL) {
		printf("topic_pub NULL\n");
		goto respond_user;
	}
	topic_pub = jsPub->valuestring;
	
	mqtt_port = port;
	strncpy(mqtt_server, server, strlen(server));
	strncpy(mqtt_user, user, strlen(user));
	strncpy(mqtt_pass, pass, strlen(pass));
	strncpy(topic_publish, topic_pub, strlen(topic_pub));
	strncpy(topic_subscribe, topic_sub, strlen(topic_sub));
	result = 1;

	udp_send_data("{\"gateway\":5}");

respond_user:
	memset(respond, 0, MAX_LEN_TCP_MSG);
	sprintf(respond, "{\"gateway\":4,\"result\":%d, \"devkey\": \"%s\"}", result, "mGmemBcYCyedvKcr");
	tcp_send_data(respond);
}

static void hs_mqtt_handler_msg(char *json)
{
	cJSON *jsRoot = cJSON_Parse(json);
	if (!jsRoot)
		return;

	cJSON *jsType = cJSON_GetObjectItem(jsRoot, CJSON_KEY_TYPE);

	if (jsType == NULL)
	{
		printf("Get JSON type mqtt message fail\n");
		cJSON_Delete(jsRoot);
		return;
	}

	uint32_t i = 0;
	for (; i < SIZEOF_ARRAY(array_handler); i++)
	{
		if (array_handler[i]._cmd_number == jsType->valueint)
		{
			printf("jump to handler\n");
			array_handler[i]._handler(jsRoot);
		}
	}

	cJSON_Delete(jsRoot);
}

void *tcp_thread(void *args)
{
	(void)args;

	int listen_socket = -1;
	int connect_socket = -1, opt = 1, err = 0;
	struct sockaddr_in server_addr;
	int address_len = 0;
	uint32_t aes_ret = 0;

	memset(&server_addr, 0, sizeof(server_addr));

	/* create socket succes */
	listen_socket = socket(AF_INET, SOCK_STREAM, 0);

	/* check setsockopt */
	err = setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	if (err < 0)
	{
		printf("setsock Err: %d\n", err);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(HS_TCP_PORT);
	printf("server IP:%s\n", inet_ntoa(server_addr.sin_addr));

	/* bind sucess */
	err = bind(listen_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (err != 0)
	{
		printf("bind Err: %d", err);
	}

	/* create a queue */
	printf("listening...\n");
	listen(listen_socket, 10);

	address_len = sizeof(server_addr);
	connect_socket = accept(listen_socket, (struct sockaddr *)&server_addr, (socklen_t *)&address_len);
	if (connect_socket < 0) {
		printf("accept err: %d\n", connect_socket);
	} else {
		printf("connected \n");
	}

	memset(tcp_message_to_receive, 0, MAX_LEN_TCP_MSG);

	while (1)
	{
		len_msg_receive = read(connect_socket, &tcp_message_to_receive, 1024);

		if (len_msg_receive > 0) {
			/* decode data */
			memset(m_message_real, 0, sizeof(m_message_real));
			m_message_real_len = MAX_LEN_TCP_MSG;

			aes_cbc128_init((uint8_t *)DEFAULT_AES_KEY, (uint8_t *)DEFAULT_AES_IV);
			aes_ret = aes_cbc128_decrypt((uint8_t *)tcp_message_to_receive, len_msg_receive,
										(uint8_t *)m_message_real, (size_t *)&m_message_real_len);
			if (aes_ret != AES_SUCCESS) {
				printf("Can not decrypt message\n");
				continue;
			}

			printf("tcp receive buff: %s\n", m_message_real);
			hs_mqtt_handler_msg(m_message_real);
		}

		if (have_request_send_tcp) {
			int bytes_sent = send(connect_socket, tcp_message_to_send, tcp_msg_len, 0);
			printf ("Bytes sent: %d\n", bytes_sent);
			have_request_send_tcp = 0;
		}
		// close(connect_socket);
		// close(listen_socket);
	}
		return 0;
}