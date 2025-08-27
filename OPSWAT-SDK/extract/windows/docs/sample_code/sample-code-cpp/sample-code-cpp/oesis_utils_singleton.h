#pragma once
#include <mutex>

#define SINGLETON_LOCK std::unique_lock<std::mutex> lock(getLock());

template<typename T>
class Singleton {
private:
	static T* m_instance;
	static std::mutex m_lock;

public:
	inline static T* instance()
	{
		SINGLETON_LOCK;
		if (m_instance == nullptr)
		{
			m_instance = new T();
			((Singleton*)m_instance)->init();
		}
		return m_instance;
	}
	Singleton(const Singleton&) = delete;
	Singleton& operator= (const Singleton) = delete;

protected:
	inline static std::mutex& getLock() { return m_lock; }
	virtual WAAPI_RETURN init() { return 0; }
	Singleton() {}
};

template<typename T>
std::mutex Singleton<T>::m_lock;
template<typename T>
T* Singleton<T>::m_instance = nullptr;