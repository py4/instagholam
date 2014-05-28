#ifndef CVECTOR_H_
#define CVECTOR_H_
#include <vector>
#include <Poco/Thread.h>

template <class T>
class cvector : public std::vector<T>
{
public:
	void push_back(const T& t)
	{
		mutex.lock();
		std::vector<T>::push_back(t);
		mutex.unlock();
	}

	T& operator[](int n)
	{
		mutex.lock();
		return std::vector<T>::operator[](n);
		mutex.unlock();
	}

	cvector() {}
	cvector(const cvector<T>& t)
	{
		for(int i = 0; i < t.size(); i++)
			std::vector<T>::push_back(operator[](i));
	}

	Poco::Mutex mutex;
};

#endif