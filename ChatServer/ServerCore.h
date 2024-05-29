#pragma once

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>

// ������ ���� ����� ���� ���̺귯��
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

	// �ʱ�ȭ �Լ�
	void Initialize(const USHORT portNumber);

	// ��Ŷ ó�� �Լ�
	inline void Update()
	{
	}

	// ������ �������� ��ȯ�Ѵ�
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