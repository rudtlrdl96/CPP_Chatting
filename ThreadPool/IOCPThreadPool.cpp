#include "PrecompileHeader.h"
#include "IOCPThreadPool.h"
#include "IOCPThread.h"

std::vector<std::shared_ptr<IOCPThread>> IOCPThreadPool::ThreadPool;
size_t IOCPThreadPool::ThreadCount = 0;

std::atomic_bool IOCPThreadPool::bIsRun = false;
HANDLE IOCPThreadPool::IOCPHandle = nullptr;
std::atomic_int IOCPThreadPool::RunningThreadCount = 0;

IOCPThreadPool::IOCPThreadPool()
{
}

IOCPThreadPool::~IOCPThreadPool()
{
	bIsRun = false;

	while (RunningThreadCount)
	{
		// 쓰레드 깨우는 함수
		if (
			FALSE ==
			PostQueuedCompletionStatus(IOCPHandle, static_cast<DWORD>(ThreadWorkType::Destroy), 0, nullptr)
			)
		{
			assert(nullptr && "Fail Call IOCPThreadPool Destroy Command.");
		}

		Sleep(0);
	}
}

void IOCPThreadPool::CreateThreadPool(std::string_view threadName, size_t poolSize)
{
	if (true == bIsRun)
	{
		assert(nullptr && "It's already Created...");
		return;
	}

	ThreadCount = poolSize;

	if (0 == ThreadCount)
	{
		SYSTEM_INFO Info;
		GetSystemInfo(&Info);
		ThreadCount = (Info.dwNumberOfProcessors * 2) + 1;
	}

	IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, ThreadCount);

	if (nullptr == IOCPHandle)
	{
		assert(nullptr && "Fail Create IOCP Handle...");
	}

	RunningThreadCount = ThreadCount;
	ThreadPool.resize(ThreadCount);

	std::string Space = " ";

	for (size_t i = 0; i < ThreadCount; i++)
	{
		// 스레드 생성 함수
		ThreadPool[i] = std::make_shared<IOCPThread>();
		ThreadPool[i]->CreateThread(threadName.data() + Space + std::to_string(i), std::bind(ThreadPoolFunction, ThreadPool[i].get(), IOCPHandle));
	}
}

void IOCPThreadPool::RunWork(std::function<void(IOCPThread*)> work)
{
	ThreadWork* NewWork= new ThreadWork();
	NewWork->Function = work;
	PostQueuedCompletionStatus(IOCPHandle, static_cast<DWORD>(ThreadWorkType::Work), reinterpret_cast<unsigned __int64>(NewWork), nullptr);
}

void IOCPThreadPool::ThreadPoolFunction(IOCPThread* thread, HANDLE IOCPHandle)
{
	DWORD Byte;
	ULONG_PTR PtrKey;
	LPOVERLAPPED OverLapped = nullptr;

	while (true == bIsRun)
	{
		GetQueuedCompletionStatus(IOCPHandle, &Byte, &PtrKey, &OverLapped, INFINITE);

		ThreadWorkType WorkType = static_cast<ThreadWorkType>(Byte);

		switch (WorkType)
		{
		case ThreadWorkType::Work:
		{
			ThreadWork* WorkPtr = reinterpret_cast<ThreadWork*>(PtrKey);

			if (nullptr != WorkPtr->Function)
			{
				WorkPtr->Function(thread);
			}

			delete WorkPtr;
			break;
		}
		case ThreadWorkType::Destroy:
			--RunningThreadCount;
			return;
		default:
			break;
		}
	}
}