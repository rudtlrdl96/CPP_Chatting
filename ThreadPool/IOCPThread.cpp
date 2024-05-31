#include "PrecompileHeader.h"
#include "IOCPThread.h"
#include "ThreadString.h"

IOCPThread::IOCPThread()
{
}

IOCPThread::IOCPThread(std::string threadName, std::function<void()> callBack)
{
	CreateThread(threadName, callBack);
}

IOCPThread::~IOCPThread()
{
	Join();
}

void IOCPThread::CreateThread(std::string_view threadName, std::function<void()> callBack)
{
	CallBack = callBack;
	Thread = std::thread(ThreadBaseFunction, this, threadName);
}

void IOCPThread::Join()
{
	if (nullptr == CallBack)
	{
		return;
	}

	Thread.join();
	CallBack = nullptr;
}

void IOCPThread::ThreadBaseFunction(IOCPThread* thread, std::string_view threadName)
{
	std::wstring WThreadName = ThreadString::AnsiToUniCode(threadName);
	SetThreadDescription(GetCurrentThread(), WThreadName.c_str()); // GetCurrentThreadId() : �츮�� ������ ��û�ϸ� ������� �츮 �����忡 id�� �ο�
	thread->CallBack();
}
