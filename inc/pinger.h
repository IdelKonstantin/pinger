#ifndef _PINGER_H_
#define _PINGER_H_

#include <list>
#include <vector>
#include <iostream>

#include <sstream>
#include <curl/curl.h>

#include "program_timer.h"
#include "nlohmann.h"

namespace pinger {

	struct pingResult {
		
		bool OK{false};
		std::string errorMessage;
		std::string sitePath;
		double siteExecTime{0.0};
		size_t bitesRecieved{0};
	};
};

class CURLWorker {

private:

	CURL* m_curl;
	std::stringstream m_ss;
	long m_httpCode{0};
	char* m_contentType;

	Timer m_timer;

private:
    
	static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);
	size_t Write(void *buffer, size_t size, size_t nmemb);

public:

	CURLWorker(); 
	~CURLWorker();

	pinger::pingResult Execute(const std::string& url);
};


class Pinger {

private:
	CURLWorker m_client;

public:
	std::vector<pinger::pingResult> pingThemAll(const std::list<std::string> sitesList);
};

class OutFormer {

public:
	std::string formJson(const std::vector<pinger::pingResult>& results);
};

#endif /* _PINGER_H_ */