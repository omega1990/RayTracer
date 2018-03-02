#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace rt
{
	template <typename T>
	class Vector
	{
	public:
		Vector(const T& aX);
		Vector(const T& aX, const T& aY, const T& aZ);

		T GetX() const;
		T GetY() const;
		T GetZ() const;

		void SetZ(const T& aZ);
		void SetY(const T& aY);

		
		Vector<T> operator*  (const T& aScalar)			const;
		T operator*			 (const Vector<T>& aVector)	const;
		Vector<T> operator/  (const T& aScalar)			const;
		Vector<T> operator/  (const Vector<T>& aVector)	const;
		Vector<T> operator+  (const T& aScalar)			const;
		Vector<T> operator+  (const Vector<T>& aVector)	const;
		Vector<T> operator+= (const Vector<T>& aVector)	const;
		Vector<T> operator-  (const T& aScalar)			const;
		Vector<T> operator-  (const Vector<T>& aVector)	const;
		Vector<T> Cross		 (const Vector<T>& aVector) const;
		Vector<T> Normalize() const;
				
		friend std::ostream& operator<< (std::ostream& aOs, const Vector<T>& aV)
		{
			aOs << aV.myX << " " << aV.myY << " " << aV.myZ;
			return aOs;
		}

	private:
		T myX;
		T myY; 
		T myZ;
	};

}

template<typename T>
rt::Vector<T>::Vector(
	const T& aX)
	: myX(aX)
{
}

template<typename T>
rt::Vector<T>::Vector(
	const T& aX,
	const T& aY,
	const T& aZ)
	: myX(aX)
	, myY(aY)
	, myZ(aZ)
{
}

template<typename T>
T
rt::Vector<T>::GetX() const
{
	return myX;
}

template<typename T>
T
rt::Vector<T>::GetY() const
{
	return myY;
}

template<typename T>
T
rt::Vector<T>::GetZ() const
{
	return myZ;
}

template<typename T>
void rt::Vector<T>::SetZ(const T& aZ)
{
	myZ = aZ;
}


template<typename T>
void rt::Vector<T>::SetY(const T& aY)
{
	myY = aY;
}


template<typename T>
rt::Vector<T>
rt::Vector<T>::operator*(const T & aScalar) const
{
	return Vector<T>(myX * aScalar, myY * aScalar, myZ * aScalar);
}

template<typename T>
T
rt::Vector<T>::operator*(
	const Vector<T>& aVector) const
{
	return myX * aVector.myX + myY * aVector.myY + myZ * aVector.myZ;
}

template<typename T>
rt::Vector<T>
rt::Vector<T>::operator/(
	const T & aScalar) const
{
	return Vector<T>(myX / aScalar, myY / aScalar, myZ / aScalar);
}

template<typename T>
rt::Vector<T>
rt::Vector<T>::operator/(
	const Vector<T>& aVector) const
{
	return Vector<T>(myX / aVector.myX, myY / aVector.myY, myZ / aVector.myZ);
}

template<typename T>
rt::Vector<T>
rt::Vector<T>::operator+(
	const T & aScalar) const
{
	return Vector<T>(myX + aScalar, myY + aScalar, myZ + aScalar);
}

template<typename T>
rt::Vector<T>
rt::Vector<T>::operator+(
	const Vector<T>& aVector) const
{
	return Vector<T>(myX + aVector.myX, myY + aVector.myY, myZ + aVector.myZ);
}

template<typename T>
rt::Vector<T>
rt::Vector<T>::operator+=(
	const Vector<T>& aVector) const
{
	// TODO: Implement this
	return Vector<T>(myX);
}

template<typename T>
rt::Vector<T>
rt::Vector<T>::operator-(
	const T & aScalar) const
{
	return Vector<T>(myX - aScalar, myY - aScalar, myZ - aScalar);
}

template<typename T>
rt::Vector<T>
rt::Vector<T>::operator-(
	const Vector<T>& aVector) const
{
	return Vector<T>(myX - aVector.myX, myY - aVector.myY, myZ - aVector.myZ);
}

template<typename T>
rt::Vector<T>
rt::Vector<T>::Cross(
	const Vector<T>& aVector) const
{
	auto x = myY * aVector.myZ - myZ * aVector.myY;
	auto y = myZ * aVector.myX - myX * aVector.myZ;
	auto z = myX * aVector.myY - myY * aVector.myX;

	return Vector<T>(x, y, z);
}

template<typename T>
rt::Vector<T> 
rt::Vector<T>::Normalize() const
{
	auto length = sqrt(myX*myX + myY*myY + myZ*myZ);

	auto x = myX / length;
	auto y = myY / length;
	auto z = myZ / length;

	return Vector<T>(x, y, z);
}
