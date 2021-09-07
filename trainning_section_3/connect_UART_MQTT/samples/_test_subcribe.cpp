#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include <signal.h>
#include "mqtt/async_client.h"

#include <sys/mman.h> /* for mem mapping. */
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <err.h>

#include <dirent.h>
#include <fstream>

/* shared mem */
int shm_fd_sendder = shm_open("broker_to_UART", O_CREAT | O_RDWR, 0666);
int is_err = ftruncate(shm_fd_sendder, 4096);
void *shm_ptr_sendder;

/* mqtt */
const std::string SERVER_ADDRESS("tcp://localhost:1883");
const std::string CLIENT_ID("paho_cpp_async_subcribe");
const std::string TOPIC("My_Topic");
const int	QOS = 0;
const int	N_RETRY_ATTEMPTS = 5;
const char* UART_NAME_PROC = "UART";


int getProcIdByName(std::string procName)
{
    int pid = -1;

    // Open the /proc directory
    DIR *dp = opendir("/proc");
    if (dp != NULL)
    {
        // Enumerate all entries in directory until process found
        struct dirent *dirp;
        while (pid < 0 && (dirp = readdir(dp)))
        {
            // Skip non-numeric entries
            int id = atoi(dirp->d_name);
            if (id > 0)
            {
                // Read contents of virtual /proc/{pid}/cmdline file
                std::string cmdPath = std::string("/proc/") + dirp->d_name + "/cmdline";
                std::ifstream cmdFile(cmdPath.c_str());
                std::string cmdLine;
                std::getline(cmdFile, cmdLine);
                if (!cmdLine.empty())
                {
                    // Keep first cmdline item which contains the program path
                    size_t pos = cmdLine.find('\0');
                    if (pos != std::string::npos)
                        cmdLine = cmdLine.substr(0, pos);
                    // Keep program name only, removing the path
                    pos = cmdLine.rfind('/');
                    if (pos != std::string::npos)
                        cmdLine = cmdLine.substr(pos + 1);
                    // Compare against requested process name
                    if (procName == cmdLine)
                        pid = id;
                }
            }
        }
    }

    closedir(dp);

    return pid;
}



class action_listener : public virtual mqtt::iaction_listener
{
	std::string name_;

	void on_failure(const mqtt::token& tok) override {
		std::cout << name_ << " failure";
		if (tok.get_message_id() != 0)
			std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
		std::cout << std::endl;
	}

	void on_success(const mqtt::token& tok) override {
		std::cout << name_ << " success";
		if (tok.get_message_id() != 0)
			std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
		auto top = tok.get_topics();
		if (top && !top->empty())
			std::cout << "\ttoken topic: '" << (*top)[0] << "', ..." << std::endl;
		std::cout << std::endl;
	}

public:
	action_listener(const std::string& name) : name_(name) {}
};




class callback : public virtual mqtt::callback,
					public virtual mqtt::iaction_listener

{
	
	int nretry_;
	
	mqtt::async_client& cli_;
	
	mqtt::connect_options& connOpts_;
	action_listener subListener_;

	void reconnect() {
		std::this_thread::sleep_for(std::chrono::milliseconds(2500));
		try {
			cli_.connect(connOpts_, nullptr, *this);
		}
		catch (const mqtt::exception& exc) {
			std::cerr << "Error: " << exc.what() << std::endl;
			exit(1);
		}
	}

	// Re-connection failure
	void on_failure(const mqtt::token& tok) override {
		std::cout << "Connection attempt failed" << std::endl;
		if (++nretry_ > N_RETRY_ATTEMPTS)
			exit(1);
		reconnect();
	}

	// (Re)connection success
	// Either this or connected() can be used for callbacks.
	void on_success(const mqtt::token& tok) override {}

	// (Re)connection success
	void connected(const std::string& cause) override {
		std::cout << "\nConnection success" << std::endl;
		std::cout << "\nSubscribing to topic '" << TOPIC << "'\n"
			<< "\tfor client " << CLIENT_ID
			<< " using QoS" << QOS << "\n"
			<< "\nPress Q<Enter> to quit\n" << std::endl;

		cli_.subscribe(TOPIC, QOS, nullptr, subListener_);
	}

	// Callback for when the connection is lost.
	// This will initiate the attempt to manually reconnect.
	void connection_lost(const std::string& cause) override {
		std::cout << "\nConnection lost" << std::endl;
		if (!cause.empty())
			std::cout << "\tcause: " << cause << std::endl;

		std::cout << "Reconnecting..." << std::endl;
		nretry_ = 0;
		reconnect();
	}

	// Callback for when a message arrives.
	void message_arrived(mqtt::const_message_ptr msg) override {   
		shm_ptr_sendder = mmap(0,4096, PROT_WRITE, MAP_SHARED, shm_fd_sendder, 0);
        strcpy((char *)shm_ptr_sendder, msg->to_string().c_str());
		
		/* send signal to the process UART */
		kill(getProcIdByName(UART_NAME_PROC), SIGINT);

		std::cout << "Message arrived" << std::endl;
		std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
		std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;

        if (munmap(0,4096) != 0) {
        	std::cout<< "Unmap Err.\n";
    	}
		
	}

	void delivery_complete(mqtt::delivery_token_ptr token) override {}

public:
	callback(mqtt::async_client& cli, mqtt::connect_options& connOpts)
				: nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription") {}
};





void handler_SIGINT (int signo) {


	/* create a thread */
	/* read Message from UART */	
	int shm_fd_receiver = shm_open("UART_to_broker", O_CREAT | O_RDWR, 0666);
	void *ptr_receiver = mmap(0,4096, PROT_READ, MAP_SHARED, shm_fd_receiver, 0);

	std::cout << "message from UART: " << (char*)ptr_receiver << std::endl;

	if (munmap(0,4096) != 0) {
        std::cout<< "Unmap Err.\n";
    } 
}




/////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{

	signal (SIGINT, handler_SIGINT);
    /* check Err share mem */
    std::cout << "start program\n";
    if (is_err != 0) {
        std::cout << "ftruncate Err.\n";
    }
    if (shm_fd_sendder < 0) {
        std::cout << "open shm file Err.\n";
    }
    if (shm_ptr_sendder == MAP_FAILED) {
        std::cout << "mmap Err: " << strerror(errno) << std::endl ;
    }

	mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);

	mqtt::connect_options connect_options;
	connect_options.set_clean_session(false);
	callback cb(client, connect_options);
	client.set_callback(cb);



	try {
		std::cout << "Connecting to the MQTT server..." << std::flush;
		client.connect(connect_options, nullptr, cb);
	}
	catch (const mqtt::exception& exc) {
		std::cerr << "\nERROR: Unable to connect to MQTT server: '"
			<< SERVER_ADDRESS << "'" << exc << std::endl;
		return 1;
	}

	
	while (std::tolower(std::cin.get()) != 'q');
 
    





    // Disconnect
	try {
		std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
		client.disconnect()->wait();
		std::cout << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc << std::endl;
		return 1;
	}


    

 	return 0;
}