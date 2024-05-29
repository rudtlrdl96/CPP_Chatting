#pragma once

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>

// 윈도우 서버 사용을 위한 라이브러리
#pragma comment (lib, "ws2_32") 

class ServerCore
{
public:
	ServerCore();
	~ServerCore();

	ServerCore(const ServerCore& _Other) = delete;
	ServerCore(ServerCore&& _Other) noexcept = delete;
	ServerCore& operator=(const ServerCore& _Other) = delete;
	ServerCore& operator=(ServerCore&& _Other) noexcept = delete;

	// 초기화 함수
	void Initialize(const USHORT portNumber);

	// 패킷 처리 함수
	inline void Update()
	{
	}

	// 서버가 닫혔는지 반환한다
	bool IsCloseServer() const
	{
		return !bIsServerOpen;
	}

protected:

private:
	WSADATA WsaData = {0};
	SOCKET ServerSocket = {0};
	SOCKADDR_IN ServerAddr = {0};

	bool bIsServerOpen = false;

	static const int PORT_NUMBER;
};