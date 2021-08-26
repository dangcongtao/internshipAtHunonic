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

static char key[16], iv[16];
static char m_message_real[MAX_LEN_TCP_MSG];
static int m_message_real_len = 0;
static char tcp_message_to_receive[MAX_LEN_TCP_MSG];
static int len_msg_receive = 0;
static char tcp_message_to_send[MAX_LEN_TCP_MSG];
static uint32_t tcp_msg_len = MAX_LEN_TCP_MSG;
static int have_request_send_tcp = 0;

static void hs_send_device_id(cJSON *jsRoot);
static void hs_get_info_config(cJSON *jsRoot);

typedef enum
{
	TCP_APP_GET_ID = 2,
	TCP_GET_INFOR_CONFIG = 3,
} state_handle_message_mqtt_t;

static hs_handler_t array_handler[] = {
	{hs_send_device_id, TCP_APP_GET_ID},
	{hs_get_info_config, TCP_GET_INFOR_CONFIG},
};

/* {"gateway":2, "device_id":"device_id_here","type":"gateway"} */
static void hs_send_device_id(cJSON *jsRoot)
{
    aes_cbc128_init((uint8_t *)DEFAULT_AES_KEY, (uint8_t *)DEFAULT_AES_IV);
	char respond[MAX_LEN_TCP_MSG] = "{\"gateway\":2, \"device_id\":\"bomayday\",\"type\":\"gateway\"}";
	memset(tcp_message_to_send, 0, MAX_LEN_TCP_MSG);
    uint32_t aes_encrypt_result = aes_cbc128_encrypt((uint8_t *)respond, strlen(respond), (uint8_t*)tcp_message_to_send, (size_t *)&tcp_msg_len);
    if (aes_encrypt_result != AES_SUCCESS) {
        printf("Encode fail,error-code: %d\n", aes_encrypt_result);
        return;
    }

    have_request_send_tcp = 1;
	clear_request_send_udp();
}


/* {"gateway":3,"netkey":"string16char","appkey":"string16char","device_addr":addr} */
static void hs_get_info_config(cJSON *jsRoot)
{
	cJSON *jsKey, *jsIv, *jsDeviceAddress;
    char *netkey = NULL, *appkey = NULL;
	int device_address = 0;

	if (jsRoot == NULL) {
        printf("jsRoot NULL\n");
        return;
    }

	jsKey = cJSON_GetObjectItem(jsRoot, CJSON_KEY_AES_KEY);
	if (jsKey == NULL) {
		printf("jsKey NULL\n");
		return;
	}
	netkey = jsKey->valuestring;
	
	jsIv = cJSON_GetObjectItem(jsRoot, CJSON_KEY_AES_IV);
	if (jsIv == NULL) {
		printf("jsIv NULL\n");
		return;
	}
	appkey = jsIv->valuestring;

	jsDeviceAddress = cJSON_GetObjectItem(jsRoot, CJSON_KEY_DEVICE_ADDRESS);
	if (jsDeviceAddress == NULL) {
		printf("jsDeviceAddress NULL\n");
		return;
	}
	device_address = jsDeviceAddress->valueint;

	strcpy(key, netkey);
	strcpy(iv, appkey);
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
	if (connect_socket < 0)
	{
		printf("accept err: %d\n", connect_socket);
	}
	else
	{
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
			if (aes_cbc128_decrypt((uint8_t *)tcp_message_to_receive, len_msg_receive, (uint8_t *)m_message_real, (size_t *)&m_message_real_len) != AES_SUCCESS) {
				printf("Can not decrypt message\n");
				continue;
			}

			printf("tcp receive buff: %s\n", m_message_real);
			hs_mqtt_handler_msg(m_message_real);

			if (have_request_send_tcp) {
				send(connect_socket, tcp_message_to_send, tcp_msg_len, 0);
				have_request_send_tcp = 0;
			}
		}

		// close(connect_socket);
		// close(listen_socket);

		return 0;
	}
}