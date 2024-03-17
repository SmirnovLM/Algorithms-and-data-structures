#pragma once
#include "TVector.h"
template <class T>

class TMatrix : public TVector<TVector<T>>
{
public:
	TMatrix(int size = 10) : TVector<TVector<T>>(size) {
		for (size_t i = 0; i < size; i++) {
			this->data[i] = TVector<T>(size - i, i);
		}
	}
	TMatrix(const TMatrix& m): TVector<TVector<T>>(m) { }
	TMatrix(const TVector<TVector<T>>& v): TVector<TVector<T>>(v) { }

	bool operator==(const TMatrix& m) const {
		if (this == &m) return true;
		else {
			if (this->size != m.size) return false;
			else {
				for (size_t i = 0; i < this->size; i++) {
					if (this->data[i] != m.data[i]) return false;
				}
			}
		}
		return true;
	}
	bool operator!=(const TMatrix& m) const {
		return !(*this == m);
	}

	TMatrix& operator=(const TMatrix& m) {
		if (this != &m) {
			if (this->size != m.size) {
				delete[] this->data;
				this->data = new TVector<T>[m.size];
			}
			this->size = m.size;
			for (size_t i = 0; i < this->size; i++) {
				this->data[i] = m.data[i];
			}
		}
		return *this;
	}

	TMatrix operator+(const TMatrix& m) const {
		return TVector<TVector<T>>::operator+(m);
	}
	TMatrix operator-(const TMatrix& m) const {
		return TVector<TVector<T>>::operator-(m);
	}
	TMatrix operator*(const TMatrix& m) const {
		if (this->size != m.size) throw "ERROR";
		TMatrix tmp(this->size);
		for (size_t i = 0; i < this->size; i++)
		{
			for (size_t j = i; j < this->size; j++)
			{
				tmp.data[i][j] = T();
				for (size_t k = i; k <= j; k++)
					tmp.data[i][j] += this->data[i][k] * m.data[k][j];
			}
		}
		return tmp;
	}

	friend std::ostream& operator<< (std::ostream& out, const TMatrix& m) {
		for (size_t i = 0; i < m.size; i++) {
			out << m.data[i];
		}
		out << std::endl;
		return out;
	}
};

