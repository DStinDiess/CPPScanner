#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

bool port_is_open(const std::string& target, int port) {
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd <= 0) {
		std::cerr << "Failed to create socket" << std::endl;
	}

	struct sockaddr_in address, serv_addr;
	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	int err = inet_pton(AF_INET, target.c_str(), &serv_addr.sin_addr);
	if (err <= 0) {
		std::cerr << "Failed to convert address" << std::endl;
	}

	err = connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	int error_code;
	socklen_t error_code_size = sizeof(error_code);
	getsockopt(socket_fd, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);

	return (error_code != 0);
}


int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "Usage: cppscaner [ip_address]" << std::endl;
		return 1;
	}

	std::string target = argv[1];
	std::vector<int> open_ports;

	for (int i = 1; i < 1025; ++i) {
		int result = port_is_open(target, i) ? 1 : 0;	
		if (result) open_ports.push_back(i);
	}

	if (open_ports.size()) {
		std::cout << "Open ports on " << target << ": " << std::endl;

		for (auto port : open_ports)
			std::cout << "\t" << port << std::endl;
	} else {
		std::cout << "There are no open ports on " << target << std::endl;
	}

	return 0;
}
