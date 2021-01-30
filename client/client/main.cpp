#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>

//连接WS2_32库
#pragma comment(lib,"WS2_32.lib")
#pragma warning(disable:4996)

int main()
{
	//初始化WS2_32.dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 0);
	WSAStartup(sockVersion, &wsaData);

	//创建套接字
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		printf("Failed socket\n");
		WSACleanup();
		return 0;
	}

	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(10010);
	servAddr.sin_addr.S_un.S_addr = inet_addr("192.168.6.130");

	//连接服务器
	int retC = connect(s, (sockaddr*)&servAddr, sizeof(servAddr));
	if (retC == -1)
	{
		printf("failed connect\n");
		WSACleanup();
		return 0;
	}

	char sendBuf[256] = { 0 };
	char recvBuf[256] = { 0 };
	int n = 0;
	while (1)
	{
		memset(sendBuf, 0, sizeof(sendBuf));
		memset(recvBuf, 0, sizeof(recvBuf));
		printf("please input send message!\n");
		scanf("%s", sendBuf);
		send(s, sendBuf, strlen(sendBuf), 0);
		n = recv(s, recvBuf, sizeof(recvBuf), 0);
		if (n == 0)
		{
			printf("client exit connected\n");
			break;
		}
		else
		{
			printf("server message:%s\n", recvBuf);
		}
	}
	closesocket(s);
	WSACleanup();


	

	system("pause");
}

