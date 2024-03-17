#pragma once
#include <iostream>

typedef unsigned int TELEM; // Синоним unsigned int -> TELEM (32 бита)

class TBitField
{
private:
	// Хранение битов
	TELEM* pMem; // Память для представления битового поля
	int MemLen;  // к-во эл-тов рМем для представления битового поля
	int BitLen;  // Длина битового поля - макс кол. бит

	// Возврат номер pMem, в котором находиться индекс элемента массива (100 - 4)
	int GetMemIndex(const int n) const;
	// Возвращение побитовой маски
	TELEM GetMemMask(const int n) const;

public:
	// Прием количество бит в контейнер
	TBitField(int memLen);
	TBitField(const TBitField& bf);
	~TBitField();

	// Доступ к битам
	int GetLength() const;         // Возврат количества доступных битов
	void SetBit(const int n);      // Установка конкретного бита в массиве (контейнере)
	void ClrBit(const int n);      // Очистка значения конкретного бита
	int GetBit(const int n) const; // Возврат значения отпределенного бита

	// Перегрузка операторов сравнения
	int operator ==(const TBitField& bf) const;
	int operator !=(const TBitField& bf) const;

	// Оператор присваивания
	TBitField& operator =(const TBitField& bf);

	// Конъюнкция |
	TBitField& operator |(const TBitField& bf) const;

	// Дизъюнкция &
	TBitField& operator &(const TBitField& bf);

	// Отрицание ~
	TBitField& operator ~() const;

	// COUT, CIN
	friend std::istream& operator >>(std::istream& in, TBitField& a);
	friend std::ostream& operator <<(std::ostream& out, const TBitField& a);
};

