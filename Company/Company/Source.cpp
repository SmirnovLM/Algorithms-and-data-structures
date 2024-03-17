#include <iostream>
#include "Warehouse.h"

//customer
void Customer(size_t l, size_t t, size_t s, Warehouse* wr) {
	std::cout << "\nrequest: " << l << " " << t << " " << s << "\n";
	size_t ll = l, tt = t, ss = s;
	if (ll > wr->GetSizeOfLaptops() || tt > wr->GetSizeOfTablets() || ss > wr->GetSizeOfSmartphones()) {
		std::cout << "Error, because Warehouse: ";
		std::cout << wr->GetSizeOfLaptops() << " " << wr->GetSizeOfTablets() << " " << wr->GetSizeOfSmartphones() << "\n\n";
	}
	else {
		wr->Delete(ll, tt, ss);
		std::cout << "\n";
	}
}

int main() {
	Warehouse* wr = new Warehouse;
	wr->Insert(new Smartphone("name", 112, 12, 12, 12, 12));
	wr->Insert(new Tablet("name", 1112, 12, 12, 12, 12.2));
	wr->Insert(new Laptop("name", 11112, 12, 12, 12, "Intel"));

	wr->Insert(new Smartphone("name", 112, 12, 12, 12, 12));
	wr->Insert(new Tablet("name", 1112, 12, 12, 12, 12.2));
	wr->Insert(new Laptop("name", 11112, 12, 12, 12, "Intel"));

	wr->Insert(new Smartphone("name", 112, 12, 12, 12, 12));
	wr->Insert(new Tablet("name", 1112, 12, 12, 12, 12.2));
	wr->Insert(new Laptop("name", 11112, 12, 12, 12, "Intel"));
	

	std::cout << *wr;
	// 
	//Customer(1, 1, 1, wr);

	//std::cout << *wr;
		
	return 0;
}