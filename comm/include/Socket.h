#pragma once
#include "General.h"
#ifdef _WIN32
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
#else
#endif
static WSADATA g_socket_wsadata;
class Socket
{
private:
	sockaddr_in sockaddr;
	SOCKET socket = NULL;
public:
	typedef enum :short {
		TCP,
		UDP
	}NetWorkType;
	//初始化套接字库
	static bool Init() {
		if (g_socket_wsadata.wVersion == 0) {
			int code = !WSAStartup(MAKEWORD(2, 2), &g_socket_wsadata);
			return code;
		}
		else if (g_socket_wsadata.wVersion != 0) {
			return true;
		}
		return false;
	}
	//清理
	static void Cleanup() {
		::WSACleanup();
		g_socket_wsadata.wVersion = 0;
	}
	static std::vector<std::string> GetIpByName(const std::string&hostname) {
		Init();
		std::vector<std::string> ipList;
		char           szHostname[100];
		HOSTENT   *pHostEnt;
		int             nAdapter = 0;
		struct       sockaddr_in   sAddr;
		Init();
		struct hostent *host = ::gethostbyname(hostname.c_str());
		for (int i = 0; host&&host->h_addr_list[i]; i++)
		{
			char* ip = inet_ntoa(*(struct in_addr*)host->h_addr_list[i]);
			ipList.push_back(ip);
		}
		return ipList;
	}
	size_t Port = 0;
	std::string Address;
	NetWorkType WorkType;
	int Receive(char* outBuf, size_t recvLen, int flags = 0) const;
	bool Connect(const std::string& ip, size_t port);
	bool Bind(const std::string & ip, size_t port);
	bool Listen(int backlog = 0);
	Socket Accep() const;
	int Write(const char* buff, int size)const;
	void Close() const;
	Socket(NetWorkType type = NetWorkType::TCP);
	Socket(SOCKET socket);
	virtual ~Socket();
};


