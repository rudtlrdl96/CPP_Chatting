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
// ������ ���� ����� ���� ���̺귯��
#pragma comment (lib, "ws2_32") 