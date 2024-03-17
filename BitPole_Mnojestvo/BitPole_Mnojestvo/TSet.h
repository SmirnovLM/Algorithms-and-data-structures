#pragma once
#include "TBitField.h"
class TSet
{
private:
	TBitField BitField;
	int MaxPower; // максимальная длина множества
public:
	TSet(int mp) : BitField(mp), MaxPower(mp) {}
	TSet(const TBitField& bf) : BitField(bf), MaxPower(bf.GetLength()) {}
	TSet(TSet& set) : BitField(set.BitField), MaxPower(set.MaxPower) {}

	operator TBitField() {
		return TBitField(BitField);
	}

	int GetMaxPower() const {
		return MaxPower;
	}
	int IsMember(int el) const {
		return (BitField.GetBit(el));
	}

	void InsElem(int el) {
		BitField.SetBit(el);
	}

	void DelElem(int el) {
		BitField.ClrBit(el);
	}

	TSet& operator=(const TSet& tmp) {
		if (this == &tmp) {
			return *this;
		}
		else {
			BitField = tmp.BitField;
			MaxPower = tmp.MaxPower;
		}
		return *this;
	}

	int operator== (const TSet& st) {
		return (BitField == st.BitField);
	}

	int operator!= (const TSet& st) {
		return (BitField != st.BitField);
	}

	TSet operator+ (const TSet& st) const {
		TSet tmp(BitField | st.BitField);
		return tmp;
	}
	TSet operator+ (const int el) const {
		TSet tmp(BitField);
		tmp.InsElem(el);
		return tmp;
	}
	TSet operator- (const int el) const {
		TSet tmp(BitField);
		tmp.DelElem(el);
		return tmp;
	}
	TSet operator* (const TSet& st) {
		return TSet(BitField & st.BitField);
	}
	TSet operator~() {
		return(~BitField);
	}
	friend std::ostream& operator<< (std::ostream& out, const TSet& st) {
		out << "{";
		int n = st.GetMaxPower();
		for (int i = 0; i < n; i++) {
			if (st.IsMember(i))
				out << i << (i < n) ? ", " : "";
		}
		out << "}";
		return out;
	}
};

