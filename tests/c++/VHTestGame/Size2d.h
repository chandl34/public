
#ifndef SIZE_2D_C34_H_
#define SIZE_2D_C34_H_

#include "Const.h"


template <typename T> 
class Size2d{
public:
	explicit Size2d(T = 0, T = 0);
	
	T& operator[](size_t);
	const T& operator[](size_t) const;
	
protected:
	T _val[2];
};


// Implementation
template <typename T> 
Size2d<T>::Size2d(T x, T y)
{
	_val[X] = x; 
	_val[Y] = y;
}

template <typename T> 
T& Size2d<T>::operator[](size_t i)
{
	return _val[i];
}

template <typename T> 
const T& Size2d<T>::operator[](size_t i) const
{
	return _val[i];
}


// Non-member functions
template <typename T> 
bool operator<(const Size2d<T>& lhs, const Size2d<T>& rhs)
{
	if(lhs[X] < rhs[X])
		return true;
	else if(lhs[X] == rhs[X]){
		if(lhs[Y] < rhs[Y])
			return true;		
	}
	return false;
}

#endif
