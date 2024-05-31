#pragma once

// C++ Header
#include <assert.h>
#include <string>
#include <string_view>
#include <memory>
#include <atomic>
#include <vector>
#include <functional>
#include <thread>

// OS Header
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>

// Lib Link
// 윈도우 서버 사용을 위한 라이브러리
#pragma comment (lib, "ws2_32") 