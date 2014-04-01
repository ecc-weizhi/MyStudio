#ifndef _MATRIX_4_BY_4
#define _MATRIX_4_BY_4

template <class T>
class Matrix4By4{
private:
	T value[16];

public:
	Matrix4By4()
	{
		for(int i=0; i<16; i++)
			value[i] = 0;
	}
	Matrix4By4(T v0, T v1, T v2, T v3, 
			   T v4, T v5, T v6, T v7,
			   T v8, T v9, T v10, T v11,
			   T v12, T v13, T v14, T v15)
	{
		value[0] = v0;
		value[1] = v1;
		value[2] = v2;
		value[3] = v3;

		value[4] = v4;
		value[5] = v5;
		value[6] = v6;
		value[7] = v7;

		value[8] = v8;
		value[9] = v9;
		value[10] = v10;
		value[11] = v11;

		value[12] = v12;
		value[13] = v13;
		value[14] = v14;
		value[15] = v15;
	}
	~Matrix4By4(){}

	/** 
	 * Overloading arithmetric operator (+, -, *). Division is not overloaded as
	 * it is unclear what matrix division means.
	 **/
	Matrix4By4<T> operator + (const Matrix4By4<T> rhs)
	{
		Matrix4By4<T> sum(*this);

		for(int i=0; i<16; i++)
			sum.value[i] += rhs.value[i];

		return sum;
	}
	Matrix4By4<T> operator - (const Matrix4By4<T> rhs)
	{
		Matrix4By4<T> difference(*this);

		for(int i=0; i<16; i++)
			difference.value[i] -= rhs.value[i];

		return difference;
	}
	Matrix4By4<T> operator * (const Matrix4By4<T> rhs)
	{
		Matrix4By4<T> product(*this);

		product.value[0] = value[0] * rhs.value[0] + value[1] * rhs.value[4] + value[2] * rhs.value[8] + value[3] * rhs.value[12];
		product.value[1] = value[0] * rhs.value[1] + value[1] * rhs.value[5] + value[2] * rhs.value[9] + value[3] * rhs.value[13];
		product.value[2] = value[0] * rhs.value[2] + value[1] * rhs.value[6] + value[2] * rhs.value[10] + value[3] * rhs.value[14];
		product.value[3] = value[0] * rhs.value[3] + value[1] * rhs.value[7] + value[2] * rhs.value[11] + value[3] * rhs.value[15];

		product.value[4] = value[4] * rhs.value[0] + value[5] * rhs.value[4] + value[6] * rhs.value[8] + value[7] * rhs.value[12];
		product.value[5] = value[4] * rhs.value[1] + value[5] * rhs.value[5] + value[6] * rhs.value[9] + value[7] * rhs.value[13];
		product.value[6] = value[4] * rhs.value[2] + value[5] * rhs.value[6] + value[6] * rhs.value[10] + value[7] * rhs.value[14];
		product.value[7] = value[4] * rhs.value[3] + value[5] * rhs.value[7] + value[6] * rhs.value[11] + value[7] * rhs.value[15];

		product.value[8] = value[8] * rhs.value[0] + value[9] * rhs.value[4] + value[10] * rhs.value[8] + value[11] * rhs.value[12];
		product.value[9] = value[8] * rhs.value[1] + value[9] * rhs.value[5] + value[10] * rhs.value[9] + value[11] * rhs.value[13];
		product.value[10] = value[8] * rhs.value[2] + value[9] * rhs.value[6] + value[10] * rhs.value[10] + value[11] * rhs.value[14];
		product.value[11] = value[8] * rhs.value[3] + value[9] * rhs.value[7] + value[10] * rhs.value[11] + value[11] * rhs.value[15];

		product.value[12] = value[12] * rhs.value[0] + value[13] * rhs.value[4] + value[14] * rhs.value[8] + value[15] * rhs.value[12];
		product.value[13] = value[12] * rhs.value[1] + value[13] * rhs.value[5] + value[14] * rhs.value[9] + value[15] * rhs.value[13];
		product.value[14] = value[12] * rhs.value[2] + value[13] * rhs.value[6] + value[14] * rhs.value[10] + value[15] * rhs.value[14];
		product.value[15] = value[12] * rhs.value[3] + value[13] * rhs.value[7] + value[14] * rhs.value[11] + value[15] * rhs.value[15];

		return product;
	}
	Matrix4By4<T> operator += (const Matrix4By4<T> rhs)
	{
		for(int i=0; i<16; i++)
			value[i] += rhs.value[i];

		return *this;
	}
	Matrix4By4<T> operator -= (const Matrix4By4<T> rhs)
	{
		for(int i=0; i<16; i++)
			value[i] -= rhs.value[i];

		return *this;
	}
	Matrix4By4<T> operator *= (const Matrix4By4<T> rhs)
	{
		Matrix4By4<T> product(*this);

		product.value[0] = value[0] * rhs.value[0] + value[1] * rhs.value[4] + value[2] * rhs.value[8] + value[3] * rhs.value[12];
		product.value[1] = value[0] * rhs.value[1] + value[1] * rhs.value[5] + value[2] * rhs.value[9] + value[3] * rhs.value[13];
		product.value[2] = value[0] * rhs.value[2] + value[1] * rhs.value[6] + value[2] * rhs.value[10] + value[3] * rhs.value[14];
		product.value[3] = value[0] * rhs.value[3] + value[1] * rhs.value[7] + value[2] * rhs.value[11] + value[3] * rhs.value[15];

		product.value[4] = value[4] * rhs.value[0] + value[5] * rhs.value[4] + value[6] * rhs.value[8] + value[7] * rhs.value[12];
		product.value[5] = value[4] * rhs.value[1] + value[5] * rhs.value[5] + value[6] * rhs.value[9] + value[7] * rhs.value[13];
		product.value[6] = value[4] * rhs.value[2] + value[5] * rhs.value[6] + value[6] * rhs.value[10] + value[7] * rhs.value[14];
		product.value[7] = value[4] * rhs.value[3] + value[5] * rhs.value[7] + value[6] * rhs.value[11] + value[7] * rhs.value[15];

		product.value[8] = value[8] * rhs.value[0] + value[9] * rhs.value[4] + value[10] * rhs.value[8] + value[11] * rhs.value[12];
		product.value[9] = value[8] * rhs.value[1] + value[9] * rhs.value[5] + value[10] * rhs.value[9] + value[11] * rhs.value[13];
		product.value[10] = value[8] * rhs.value[2] + value[9] * rhs.value[6] + value[10] * rhs.value[10] + value[11] * rhs.value[14];
		product.value[11] = value[8] * rhs.value[3] + value[9] * rhs.value[7] + value[10] * rhs.value[11] + value[11] * rhs.value[15];

		product.value[12] = value[12] * rhs.value[0] + value[13] * rhs.value[4] + value[14] * rhs.value[8] + value[15] * rhs.value[12];
		product.value[13] = value[12] * rhs.value[1] + value[13] * rhs.value[5] + value[14] * rhs.value[9] + value[15] * rhs.value[13];
		product.value[14] = value[12] * rhs.value[2] + value[13] * rhs.value[6] + value[14] * rhs.value[10] + value[15] * rhs.value[14];
		product.value[15] = value[12] * rhs.value[3] + value[13] * rhs.value[7] + value[14] * rhs.value[11] + value[15] * rhs.value[15];

		*this = product;
		return *this;
	}

	/**
	 * Overloading of other shorthand operator.
	 **/
	T& operator [] (unsigned int index)
	{
		return value[index];
	}
	Matrix4By4<T> operator = (const Matrix4By4<T> rhs)
	{
		for(int i=0; i<16; i++)
			value[i] = rhs.value[i];

		return *this;
	}
	bool operator == (const Matrix4By4<T> rhs)
	{
		bool isEquivalent = true;

		for(int i=0; i<16; i++)
		{
			if(!value[i] == rhs.value[i])
				isEquivalent = false;
		}
		return isEquivalent;
	}
	bool operator != (const Matrix4By4<T> rhs)
	{
		return !(*this == rhs);
	}
};

#endif