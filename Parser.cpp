#include "Parser.hpp"

t_conf *Parser::parseConf(const std::string &filename) {
	t_conf			*conf;
	std::ifstream	in;
	std::string		line;
	std::string		directive;
	std::string		value;

	conf = new(t_conf);

	in.open(filename);

	while (std::getline(in, line)) {
		std::stringstream stream(line);

		stream >> directive >> value;

		if (directive == "listen") {
			conf->listen = std::stoi(value);
		}
	}

	return conf;
}
