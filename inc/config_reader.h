#ifndef _CONFIG_READER_H_
#define _CONFIG_READER_H_

#include <list>
#include <fstream>

class ConfigReader {

private:
	std::ifstream m_confFile;
	const std::string m_path;

public:

	ConfigReader(const std::string path);
	~ConfigReader();

	std::pair<bool, std::list<std::string>> getSiteList();
};

#endif /* _CONFIG_READER_H_ */