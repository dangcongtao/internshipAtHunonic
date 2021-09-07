#include <iostream>
#include <string>
#include <mqtt/async_client.h>
#include <mqtt/topic.h>


const std::string SERV_ADDR = "127.0.0.1";
const std::string CLIENT_ID = "abc";
const std::string PERSIST_DIR = { "./persist" };
const mqtt::string TOPIC_NAME = "My_Topic";
const std::string PAYLOAD = "payLoad1/Payload2";
const int QoS =0;
const int PACKET_ID = 123;
const bool DUP_FLAG = false;
const bool RETAIN_FLAG = false;
const int	N_RETRY_ATTEMPTS = 5;


int main (int argc, char *argv[])
{

	mqtt::async_client client(SERV_ADDR, CLIENT_ID);

	mqtt::connect_options connect_option;
	mqtt::connect_options_builder buider = mqtt::connect_options_builder();
	connect_option = buider.finalize();

	client.connect(connect_option)->wait();

	std::cout << "sending message\n";
	mqtt::message_ptr message = mqtt::make_message(TOPIC_NAME,PAYLOAD);
	client.publish(message);

	client.disconnect()->wait();
    return 0;
}