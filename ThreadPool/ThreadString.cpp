#include "PrecompileHeader.h"
#include "ThreadString.h"

ThreadString::ThreadString()
{
}

ThreadString::~ThreadString()
{
}

std::string ThreadString::ToUpper(const std::string_view& _Str)
{
	std::string Text = _Str.data();

	for (size_t i = 0; i < Text.size(); i++)
	{
		Text[i] = toupper(Text[i]);
	}

	return Text;
}

std::wstring ThreadString::AnsiToUniCode(const std::string_view& _Text)
{
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0);

	if (0 == Size)
	{
		assert(nullptr);
		return L"";
	}

	std::wstring Result;
	Result.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size);

	if (0 == Size)
	{
		assert(nullptr);
		return L"";
	}

	return Result;
}


std::string ThreadString::UniCodeToAnsi(const std::wstring_view& _Text)
{
	int Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr);

	if (0 == Size)
	{
		assert(nullptr);
		return "";
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		assert(nullptr);
		return "";
	}

	return Result;
}

std::wstring ThreadString::UTF8ToUniCode(const std::string& _UTF8)
{
	std::wstring UniCode;

	int32_t Len = MultiByteToWideChar(
		CP_UTF8,
		0,
		_UTF8.c_str(),
		static_cast<int32_t>(_UTF8.size()),
		nullptr,
		0
	);

	if (0 >= Len)
	{
		return L"";
	}

	UniCode.resize(Len);

	Len = MultiByteToWideChar(
		CP_UTF8,
		0,
		_UTF8.c_str(),
		static_cast<int32_t>(_UTF8.size()),
		&UniCode[0],
		Len
	);

	if (0 >= Len)
	{
		return L"";
	}

	return UniCode;
}

std::string ThreadString::UTF8ToAnsi(const std::string& _UTF8)
{
	std::wstring UniCode = UTF8ToUniCode(_UTF8);
	std::string Return = UniCodeToAnsi(UniCode);
	return Return;
}


std::string ThreadString::UniCodeToUTF8(const std::wstring_view& _Text)
{
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr);

	if (0 == Size)
	{
		assert(nullptr);
		return "";
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		assert(nullptr);
		return "";
	}

	return Result;

}

std::string ThreadString::AnsiToUTF8(const std::string_view& _Text)
{
	std::wstring Unicode = AnsiToUniCode(_Text);
	return UniCodeToUTF8(Unicode.c_str());
}