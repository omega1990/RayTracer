#pragma once

template <typename T>
class Singleton
{
public:
	static T& GetInstance()
	{
		static T instance;
		return instance;
	}
protected:
	Singleton() {};

public:
	Singleton(const Singleton&) = delete;
	void operator=(const Singleton&) = delete;

};