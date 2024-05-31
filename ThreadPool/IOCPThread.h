#pragma once


class IOCPThread
{
public:
	IOCPThread();
	IOCPThread(std::string threadName, std::function<void()> callBack);
	~IOCPThread();

	IOCPThread(const IOCPThread& _Other) = delete;
	IOCPThread(IOCPThread&& _Other) noexcept = delete;
	IOCPThread& operator=(const IOCPThread& _Other) = delete;
	IOCPThread& operator=(IOCPThread&& _Other) noexcept = delete;

	void CreateThread(std::string_view threadName, std::function<void()> callBack);
	void Join();

protected:

private:
	static void ThreadBaseFunction(IOCPThread* thread, std::string_view threadName);

	std::thread Thread;
	std::function<void()> CallBack;
};