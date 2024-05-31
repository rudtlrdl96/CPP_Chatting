#pragma once

class IOCPThread;

class IOCPThreadPool
{
private:
	enum class ThreadWorkType
	{
		Work = -2,
		Destroy = -1,
	};

	class ThreadWork
	{
	public:
		std::function<void(IOCPThread*)> Function;
	};
public:
	// (poolSize = 0) -> (SystemInfo ProcessorsCount * 2) + 1
	static void CreateThreadPool(std::string_view threadName, size_t poolSize);
	static void RunWork(std::function<void(IOCPThread*)> work);

protected:

private:
	static std::vector<std::shared_ptr<IOCPThread>> ThreadPool;
	static size_t ThreadCount;

	static std::atomic_bool bIsRun;
	static HANDLE IOCPHandle;

	static std::atomic_int RunningThreadCount;
	static void ThreadPoolFunction(IOCPThread* thread, HANDLE IOCPHandle);

private:
	IOCPThreadPool();
	~IOCPThreadPool();

	IOCPThreadPool(const IOCPThreadPool& _Other) = delete;
	IOCPThreadPool(IOCPThreadPool&& _Other) noexcept = delete;
	IOCPThreadPool& operator=(const IOCPThreadPool& _Other) = delete;
	IOCPThreadPool& operator=(IOCPThreadPool&& _Other) noexcept = delete;
};