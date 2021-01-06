#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

const char *SERVER = "localhost";
const int PORT = 1234;

int main(int argc, char *argv[])
{
	WORD WRequiredVersion;
	WSADATA WData;
	SOCKET SSocket;
	int nBytes;
	struct sockaddr_in stServerAddr;
	struct hostent *lpstServerEnt;
	char cbBuf[1024];

	WRequiredVersion = MAKEWORD(2, 0);
	WSAStartup(WRequiredVersion, &WData);
	lpstServerEnt = gethostbyname(SERVER);
	SSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	stServerAddr.sin_family = AF_INET;
	memcpy(&stServerAddr.sin_addr.s_addr, lpstServerEnt->h_addr, lpstServerEnt->h_length);
	stServerAddr.sin_port = htons(PORT);
	connect(SSocket, (struct sockaddr *)&stServerAddr, sizeof(struct sockaddr));

	send(SSocket, "GET / HTTP1.0\n\n", 16, 0);

	nBytes = recv(SSocket, cbBuf, sizeof(cbBuf), 0);
	cbBuf[nBytes] = '\x0';
	printf("Data from SERVER [%s]:\t%s", SERVER, cbBuf);
	closesocket(SSocket);
	WSACleanup();
	return 0;
}
