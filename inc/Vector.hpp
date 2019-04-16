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
		Vector();
		Vector(const T& aX);
		Vector(const T& aX, const T& aY, const T& aZ);

		T GetX() const;
		T GetY() const;
		T GetZ() const;

		void SetX(const T& aX);
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
		T		  GetMaxDot	 (const Vector<T>& aVector) const;
		T		  DotProduct(const Vector<T> aVector1, const Vector<T> aVector2) const;
		T		  Length() const;
		bool	  IsZero() const;
		Vector<T> Abs();


				
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

	typedef Vector<float> VectorF;
}


template<typename T>
rt::Vector<T>::Vector()
	: myX(0.0f)
	, myY(0.0f)
	, myZ(0.0f)
{
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

template <typename T>
void rt::Vector<T>::SetX(const T& aX)
{
	myX = aX;
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

template<typename T>
T
rt::Vector<T>::GetMaxDot(const rt::Vector<T>& aVector) const
{
	T dotProduct = *this * aVector;
	if (dotProduct < 0.f)
		return 0.f;

	return dotProduct;
}

template<typename T>
T
rt::Vector<T>::DotProduct(const rt::Vector<T> aVector1, const rt::Vector<T> aVector2) const
{
	return aVector1.myX * aVector2.myX + aVector1.myY * aVector2.myY + aVector1.myZ * aVector2.myZ;
}

template<typename T>
T
rt::Vector<T>::Length() const
{
	return std::sqrt((myX * myX) + (myY * myY) + (myZ * myZ));
}

template <typename T>
bool rt::Vector<T>::IsZero() const
{
	if ((int)myX == 0 && (int)myY == 0 && (int)myZ == 0) 
		return true;

	return false;
}

template <typename T>
rt::Vector<T> rt::Vector<T>::Abs()
{
	myX = abs(myX);
	myY = abs(myY);
	myZ = abs(myZ);

	return *this;
}