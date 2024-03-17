#pragma once
#include <iostream>
template <class T>
class TVector
{
protected:
	T* data;      // Указатель на массив шаблонного типа данных
	size_t size;  // Размер массива
	int startInd; // Стартовый индекс
public:
	TVector(size_t size = 10, int startInd = 0) {
		if (size < 0) {
			throw "ERROR";
		}
		this->size = size;
		this->startInd = startInd;
		data = new T[size];
	}
	TVector(const TVector& t) {
		size = t.size;
		startInd = t.startInd;
		data = new T[size];
		for (int i = 0; i < size; i++) {
			data[i] = t.data[i];
		}
	}
	~TVector() {
		delete[] data;
		data = nullptr;
	}

	size_t GetSize() {
		return size;
	}

	int GetStartInd() {
		return startInd;
	}

	T& GetValue(int ind) const {
		return data[ind];
	}

	T& operator[](int ind) {
		if (ind - startInd < 0 || ind - startInd >= size) {
			throw "ERROR";
		}
		return data[ind - startInd];
	}

	bool operator== (const TVector& t) const {
		if (this == &t) return true;
		else {
			if (size != t.size) return false;
			else {
				if (startInd != t.startInd) return false;
				else {
					for (int i = 0; i < size; i++) {
						if (data[i] != t.data[i]) return false;
					}
				}
			}
		}
		return true;
	}

	bool operator!= (const TVector& t) const {
		return !(*this == t);
	}

	TVector& operator=(const TVector& t) {
		if (this == &t) return *this;
		if (size != t.size) {
			T* tmp = data;
			data = new T[t.size];
			size = t.size;
			startInd = t.startInd;
			if (data == nullptr) data = tmp;
		}
		for (int i = 0; i < size; i++) {
			data[i] = t.data[i];
		}
		return *this;
	}

	TVector operator+(const T& elem) const {
		TVector v(*this);
		for (size_t i = 0; i < size; i++) {
			v.data[i] += elem;
		}
		return v;
	}
	TVector operator-(const T& elem) const {
		return this->operator+(-elem);
	}
	TVector operator*(const T& elem) const {
		TVector v(*this);
		for (size_t i = 0; i < size; i++) {
			v.data[i] *= elem;
		}
		return v;
	}

	TVector operator+(const TVector& t) const {
		if (size != t.size) throw "ERROR";
		TVector v(size, startInd);
		for (size_t i = 0; i < size; i++) {
			v.data[i] = data[i] + t.data[i];
		}
	}
	TVector operator-(const TVector& t) const {
		if (size != t.size) throw "ERROR";
		TVector v(size, startInd);
		for (size_t i = 0; i < size; i++) {
			v.data[i] = data[i] - t.data[i];
		}
	}
	
	TVector<T> operator*(const TVector& tv) const {
		if (size != tv.size) throw "ERROR";
		T t();
		for (size_t i = 0; i < size; i++) {
			t += data[i] * tv.data[i];
		}
		return t;
	}

	double getLenght() const {
		double ans = 0;
		for (size_t i = 0; i < size; i++) {
			ans += data[i] * data[i];
		}
		return std::sqrt(ans);
	}

	friend std::ostream& operator<< (std::ostream& out, const TVector& t) {
		for (size_t i = 0; i < t.GetSize(); i++) {
			out << t[i] + " ";
		}
		out << std::endl;
		return out;
	}

	friend std::istream& operator>> (std::istream& in, TVector& t) {

	}
};

