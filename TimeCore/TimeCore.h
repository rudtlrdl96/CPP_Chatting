#pragma once


class TimeCore
{
public:
	TimeCore();
	~TimeCore();

	TimeCore(const TimeCore& _Other) = delete;
	TimeCore(TimeCore&& _Other) noexcept = delete;
	TimeCore& operator=(const TimeCore& _Other) = delete;
	TimeCore& operator=(TimeCore&& _Other) noexcept = delete;

protected:

private:

};