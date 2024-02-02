#include "config_reader.h"

ConfigReader::ConfigReader(const std::string path) : m_path(path) {}

std::pair<bool, std::list<std::string>> ConfigReader::getSiteList() {

	m_confFile.open(m_path); 

	if(!m_confFile.is_open()) {
		return {false, {}};
	}

	std::list<std::string> sitesList{};

	std::string site;
	while (std::getline(m_confFile, site)) {
		sitesList.push_back(site);
	}

	return {true, sitesList};
}

ConfigReader::~ConfigReader() {

	if(m_confFile.is_open()) {
		m_confFile.close();
	}
}