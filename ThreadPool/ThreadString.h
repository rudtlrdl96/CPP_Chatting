#pragma once


class ThreadString
{
public:
	static std::string ToUpper(const std::string_view& _Str);

	static std::wstring AnsiToUniCode(const std::string_view& _Text);
	static std::string UniCodeToAnsi(const std::wstring_view& _Text);

	static std::string UniCodeToUTF8(const std::wstring_view& _Text);
	static std::string AnsiToUTF8(const std::string_view& _Text);

	static std::wstring UTF8ToUniCode(const std::string& _UTF8);
	static std::string UTF8ToAnsi(const std::string& _UTF8);
	
private:
	ThreadString();
	~ThreadString();

	ThreadString(const ThreadString& _Other) = delete;
	ThreadString(ThreadString&& _Other) noexcept = delete;
	ThreadString& operator=(const ThreadString& _Other) = delete;
	ThreadString& operator=(ThreadString&& _Other) noexcept = delete;
};

