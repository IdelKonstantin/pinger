#include "pinger.h"

size_t CURLWorker::write_data(void *buffer, size_t size, size_t nmemb, void *userp) {

	return static_cast<CURLWorker*>(userp)->Write(buffer,size,nmemb);
}

size_t CURLWorker::Write(void *buffer, size_t size, size_t nmemb) {

	m_ss.str(std::string());
	m_ss.write((const char*)buffer,size*nmemb);
	return size*nmemb;
}


CURLWorker::CURLWorker() : m_curl(curl_easy_init()) {}

CURLWorker::~CURLWorker() {

	if (m_curl) {
		curl_easy_cleanup(m_curl);
	} 
}

pinger::pingResult CURLWorker::Execute(const std::string& url) {

	m_ss.str(std::string());

	CURLcode res;
	curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);

	m_timer.reset();

	res = curl_easy_perform(m_curl);

	if (res != CURLE_OK) {
		return pinger::pingResult{false, curl_easy_strerror(res), url, 0.0, 0};
	}

	return pinger::pingResult{true, "", url, m_timer.elapsed(), m_ss.str().size()};
}

std::vector<pinger::pingResult> Pinger::pingThemAll(const std::list<std::string> sitesList) {

	std::vector<pinger::pingResult> res{};
	
	for(const auto& site : sitesList) {
		res.push_back(m_client.Execute(site));
	}

	return res;		
}

std::string OutFormer::formJson(const std::vector<pinger::pingResult>& results) {

	nlohmann::json responceJson;

	for(const auto& result : results) {

		auto [status, errorMessage, url, time, size] = result;
		responceJson[url] = {{"success", status}, {"error", errorMessage}, {"exec.time", time}, {"data size", size}};
	}

	return responceJson.dump(4).c_str();
}