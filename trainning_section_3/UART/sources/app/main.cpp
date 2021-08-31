#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "mqtt.h"
#include "m_log.h"
#include "database.h"
#include "interface.h"
#include "uart.h"

static const char *TAG = "MAIN";
static int synctask_pid = -1, mqtt_task_pid = -1, uart_task_pid = -1;

static void sync_task(void)
{
	m_printf(TAG, "sync_task");

	Database *database = Database::getInstance("database.txt");
	if (database == NULL) {
		m_printf(TAG, "database init failed");
		exit(-1);
	}

	int ret = database->Load();
	if (ret != 0) {
		m_printf(TAG, "database load failed");
		exit(-1);
	}

	while (1) {
		if (database->getRequestSync()) {
			m_printf(TAG, "Have request sync database");

			ret = database->Sync();
			if (ret != 0) {
				m_printf(TAG, "database Sync failed");
				exit(-1);
			} else {
				m_printf(TAG, "database Sync success");
			}

			database->resetRequestSync();
		}
		usleep(1000);
	}
}

static void mqtt_task(void)
{
	/* run 2 thread used for Tx and Rx */
}


static void uart_task(void)
{
	/* run 2 thread used for Tx and Rx */
}


void *thread_to_turn_on_led (void *){
	/* UartConnection::UartSetAttribute(11, 0, 8, 1, 0); */
}

int main(void)
{
	/* init debugger */
	m_log_init("log.txt");

	/* task synchronize database */
	synctask_pid = fork();
	if (synctask_pid < 0) {
			m_printf(TAG, "Create sync task fail");
	}
	else if (!synctask_pid) { /* child */
		m_printf(TAG, "Create sync task success");
		sync_task();
	}
	else { /* parent */
		/* create mqtt uart */
		mqtt_task_pid = fork();

		if (mqtt_task_pid < 0) {
			m_printf(TAG, "Create mqtt task fail");
		}
		else if (!mqtt_task_pid) { /* child */
			m_printf(TAG, "Create mqtt task success");
			mqtt_task();
		}
		else { /* parent */
			/* create task uart */
			uart_task_pid = fork();
			if (uart_task_pid < 0) {
				m_printf(TAG, "Create uart task fail");
			}
			else if (!uart_task_pid) { /* child */
				m_printf(TAG, "Create uart task success");
				uart_task();
			}
			else { /* parent */
				/* wait for child process */
				wait(NULL);
				wait(NULL);
				wait(NULL);
			}
		}
	}
	
 	return 0;
}

