#pragma once

template <typename T>
class Singleton
{
private:
	static T *instance;

protected:
	Singleton() = default;
	virtual ~Singleton() = default;

	Singleton(const Singleton &) = delete;
	Singleton &operator=(const Singleton &) = delete;

public:
	static T *GetInstance()
	{
		if (instance == nullptr)
			instance = new T();
		return instance;
	}

	static void DestroyInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	static bool HasInstance()
	{
		return instance != nullptr;
	}
};

// 정적 멤버 변수 초기화
template <typename T>
T *Singleton<T>::instance = nullptr;
