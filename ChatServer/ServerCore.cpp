#include "PrecompileHeader.h"
#include "ServerCore.h"

#include <iostream>
#include <assert.h>

#include "ThreadPool/IOCPThreadPool.h"

const int ServerCore::PORT_NUMBER = 10;

ServerCore::ServerCore()
{
}

ServerCore::~ServerCore()
{
}

void ServerCore::Initialize(const USHORT portNumber)
{
	// IOCP 스레드 풀 생성
	IOCPThreadPool::CreateThreadPool("Server Thread", 0);

	if (0 != WSAStartup(MAKEWORD(2, 2), &WsaData))
	{
		std::cout << "Fail WSAStartup!!! \n";
		assert(nullptr);
		return;
	}

	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	ServerAddr.sin_port = portNumber;
		
	bind(ServerSocket, reinterpret_cast<const SOCKADDR*>(&ServerAddr), sizeof(ServerAddr));
	listen(ServerSocket, SOMAXCONN);

	// 서버 열림
	bIsServerOpen = true;
}

void ServerCore::Update()
{
}