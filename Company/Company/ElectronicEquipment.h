#pragma once
#include <iostream>
#include <iomanip>

class ElectronicEquipment
{
protected:
	std::string name; // Имя устройства
	size_t price;     // Цена устройства
	size_t ram;       // Оперативная память устройства
	size_t ssd;       // Дополнительная память устройства
	size_t weight;    // Вес устройства

	virtual void Print(std::ostream& out) const = 0;

public:
	ElectronicEquipment() = default;
	virtual ~ElectronicEquipment() {}

	ElectronicEquipment(std::string _name, size_t _price, size_t _memory, size_t _ssd, size_t _weight) :
		 name(_name), price(_price), ram(_memory), ssd(_ssd), weight(_weight) {}

	std::string GetName() { return name; }
	size_t GetPrice() { return price; }
	size_t GetRam() { return ram; }
	size_t GetSsd() { return ssd; }
	size_t GetWeight() { return weight; }

	friend std::ostream& operator<<(std::ostream& out, ElectronicEquipment& e) {
		out << "| " << std::setw(20) << std::left << e.name;
		out << "| " << std::setw(15) << std::left << e.price;
		out << "| " << std::setw(10) << std::left << e.ram;
		out << "| " << std::setw(10) << std::left << e.ssd;
		out << "| " << std::setw(15) << std::left << e.weight << "|";
		//e.Print(out);
		return out;
	}

	//virtual ElectronicEquipment* GetCopy() = 0; // Создание Копии
	friend class Warehouse;
};


class Laptop : public ElectronicEquipment
{
protected:
	std::string processor;

	void Print(std::ostream& out) const override {
		out << "Processor: " << processor;
	}

public:
	Laptop() = default;
	Laptop(std::string _name, size_t _price, size_t _memory, size_t _ssd, size_t _weight, std::string p) :
		ElectronicEquipment(_name, _price, _memory, _ssd, _weight), processor(p) {}

	std::string GetNameProcessor() { return processor; }

	/*PElectronicEquipment GetCopy() override {
		return new Laptop(name, price, memory, ssd, weight, processor);
	}*/
};


class Tablet : public ElectronicEquipment 
{
protected:
	double diagonal;

	void Print(std::ostream& out) const override {
		out << "Diagonal: " << diagonal << " inch";
	}

public:
	Tablet() = default;
	Tablet(std::string _name, size_t _price, size_t _memory, size_t _ssd, size_t _weight, float d) :
		ElectronicEquipment(_name, _price, _memory, _ssd, _weight), diagonal(d) {}

	double GetDaigonal() { return diagonal; }

	/*PElectronicEquipment GetCopy() override {
		return new Tablet(name, price, memory, ssd, weight, diagonal);
	}*/
};


class Smartphone : public ElectronicEquipment
{
protected:
	size_t camera;

	void Print(std::ostream& out) const override {
		out << "Camera: " << camera << "MP";
	}

public:
	Smartphone() = default;
	Smartphone(std::string _name, size_t _price, size_t _memory, size_t _ssd, size_t _weight, size_t c) :
		ElectronicEquipment(_name, _price, _memory, _ssd, _weight), camera(c) {}

	size_t GetCameraMP() { return camera; }

	/*PElectronicEquipment GetCopy() override {
		return new Smartphone(name, price, memory, ssd, weight, camera);
	}*/
};


typedef ElectronicEquipment* PElectronicEquipment;
