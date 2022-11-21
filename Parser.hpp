#ifndef WEBSERV_PARSER_HPP
#define WEBSERV_PARSER_HPP

#include <iostream>
#include <fstream>
#include <sstream>


typedef struct s_conf {
	int	listen;
}	t_conf;


class Parser {
public:
	static t_conf*	parseConf(const std::string& filename);
};


#endif //WEBSERV_PARSER_HPP
