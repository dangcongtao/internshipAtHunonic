#ifndef _LOG_H_
#define _LOG_H_

void m_log_init(const char* logFile);
void m_printf(const char* tag, const char* format, ...);

#define m_log(...) m_printf(__FUNCTION__, __VA_ARGS__)

#endif // _LOG_H_