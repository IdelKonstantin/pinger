#include "config_reader.h"
#include "pinger.h"

int main(int argc, char** argv) {

	if(argc < 2) {

		std::cerr << "Path to config is not specified..." << std::endl;
		std::cerr << "Usage:\n" << argv[0] << " <path to *.conf>" << std::endl;
		return -1;
	}

	ConfigReader cfgr{argv[1]};
	Pinger png;
	OutFormer of;

	auto confReadResult = cfgr.getSiteList();

	if(!confReadResult.first) {
		std::cerr << "Can't open config file specified..." << std::endl;
		return -2;
	}

	auto requestResults = png.pingThemAll(confReadResult.second);
	std::cout << of.formJson(requestResults) << std::endl;
}