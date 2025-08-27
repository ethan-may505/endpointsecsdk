#pragma once
#include <mutex>
#ifndef WA_SINGLETON_LOCK_CS
#define WA_SINGLETON_LOCK_CS	std::lock_guard<std::mutex> lock(getCS());
#endif

template<typename T>
class Singleton {
private:
	static T * m_instance;
	static std::mutex mtx;

public:
	inline static T * instance()
	{
		WA_SINGLETON_LOCK_CS;
		if (m_instance == nullptr)
		{
			m_instance = new T();
			((Singleton *)m_instance)->init();
		}
		return m_instance;
	}	
	inline static void destroy()
	{
		if (m_instance != nullptr)
		{
			((Singleton *)m_instance)->deinit();
			delete m_instance;
			m_instance = nullptr;
		}
	}
	Singleton(const Singleton &) = delete;
	Singleton & operator= (const Singleton) = delete;

protected:
	inline static std::mutex & getCS() { return mtx; }
	virtual WAAPI_RETURN init() { return 0; }
	virtual WAAPI_RETURN deinit() { return 0; }
	Singleton() {}
};

template<typename T>
std::mutex Singleton<T>::mtx;
template<typename T>
T * Singleton<T>::m_instance = nullptr;