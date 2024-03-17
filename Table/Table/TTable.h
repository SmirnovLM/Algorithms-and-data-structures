#pragma once
#include "TTabRecord.h"
#include "TDatCom.h"
#define TAB_OK 0       // Код ошибки  
#define TAB_EMPTY -101
#define TAB_FULL -102
#define TAB_NO_RECORD -103
#define TAB_REC_DOUBLE -104
#define TAB_NO_MEMBER -105

// Абстрактный базовый класс, содержащий спецификации методов таблицы
class TTable: public TDatCom
{
protected:
	size_t dataCount;  // Количество Записей в таблице
	size_t efficiency; // Показатель эффективности выполнения операции

public:
	TTable(size_t _dataCount = 0, size_t _efficiency = 0) :
		dataCount(_dataCount), efficiency(_efficiency) {}

	~TTable() {} // Если убрать Виртуал, что будет?

	// Информационные Методы:
	size_t GetDataCount() const { return dataCount; }
	size_t GetEfficiency() const { return efficiency; }
	bool IsEmpty() const { return dataCount == 0; }
	virtual bool IsFull() const = 0;

	// Методы Доступа к записям:
	virtual TKey GetKey() const = 0;         // Получить значение ключа текущей записи
	virtual PTDatValue GetValue() const = 0; // Получить указатель на значение текущей записи

	// Методы обработки таблицы:
	virtual PTDatValue FindRecord(const TKey key) = 0;                     // Поиск записи по значению ключа
	virtual bool InsertRecord(const TKey key, const PTDatValue value) = 0; // Вставка записи в таблицу
	virtual void DeleteRecord(const TKey key) = 0;                         // Удаление запии
	
	// Навигация (Итератор):
	virtual int Reset() = 0;            // Установить текущую позицию на первую запись
	virtual int IsTabEnded() const = 0; // Проверка завершения таблицы
	virtual int GoNext() = 0;           // Перемещение текущей позиции на следующую запись
	// (=1 после применения для последней записи таблицы)

	friend std::ostream& operator<<(std::ostream& out, TTable& table) {
		for (table.Reset(); !table.IsTabEnded(); table.GoNext()) {
			out << "KEY: " << table.GetKey();
			for (int i = 0; i < 25 - table.GetKey().length(); i++) out << " ";

			out << "VALUE: " << *table.GetValue();
			out	<< std::endl;
		}
		return out;
	}
};

