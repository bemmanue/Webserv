#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "Parser.hpp"

void	startServer(t_conf* conf) {
	int sockfd;

	// Создаем сокет
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		strerror(errno);
		exit(0);
	}

	struct sockaddr_in address = {};
	int addrlen = sizeof(address);
	const int PORT = conf->listen;

	memset((char *)&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);

	// Привязываем сокет к попту и адресу
	if (bind(sockfd,(struct sockaddr *)&address,sizeof(address)) < 0) {
		strerror(errno);
		exit(0);
	}

	// Начинаем прослушивание
	if (listen(sockfd, 3) < 0) {
		strerror(errno);
		exit(EXIT_FAILURE);
	}

	while(1) {
		std::cout << "Waiting for new connection" << std::endl;

		// Принимаем входящее соединение
		int new_socket;
		if ((new_socket = accept(sockfd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
			strerror(errno);
			exit(EXIT_FAILURE);
		}

		// Читаем данные из сокета и печатаем их
		char buffer[1024] = {0};
		int valread = read(new_socket, buffer, 1024);
		printf("%s\n", buffer);
		if (valread < 0) {
			printf("No bytes are there to read");
		}

		// Записываем данные их нового сокета
		char hello[] = "Hello from the server\n";
		write(new_socket, hello, strlen(hello));

		close(new_socket);
	}
}

int main(int argc, char *argv[]) {
	t_conf* conf;

	if (argc != 2) {
		std::cout << "Provide configuration file as argument" << std::endl;
		exit(0);
	}

	conf = Parser::parseConf(argv[1]);
	if (!conf) {
		std::cout << "Error parsing configuration file" << std::endl;
		exit(0);
	}
	std::cout << conf->listen << std::endl;

	startServer(conf);

	return 0;
}
