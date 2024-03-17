//#include <iostream>
//#include "TBitField.h"
//#include "TSet.h"
//int main() {
//
//	//TSet set(10);
//	//TBitField field = (TBitField)set;
//
//	//TBitField A(108);
//	//TBitField B = A;
//	//std::cout << A.GetMemIndex(63) << std::endl;
//	//std::cout << A.GetMemMask(2) << std::endl;
//
//	TBitField C(4);
//	std::cin >> C;
//	std::cout << C;
//
//	TBitField D(4);
//	std::cin >> D;
//	
//	std::cout << D;
//
//	std::cout << (C == D);
//
//}
//
//// Длина массива = 32 бита - 1 uint
//
//// uint16_t a = 0; // 0000 0000 0000 0000 (16)
//// uint16_t* ar = new uint16_t[2]; 
//// 0000 0000 0000 0000 0000 0000 0000 0000 (32)
//// {      ar[0]      } {        ar[1]    }
//
//
//// 0000 0000 0000 0000 = a
//// 0000 0000 0000 0001 = b
//// (a = a | (b << 9)) // (b << 9) - маска конкретного бита

#include <stdio.h>
#include <limits.h>
#include <iostream>

int main()
{
    double matrix[4][4];

    // Составление матрицы пользователем
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = i + j;
        }
    }

    // Печать матрицы
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    double elem = -10000;
    int value;
    for (int i = 0; i < 4; i++) {
        if (matrix[i][1] > elem) {
            elem = matrix[i][1];
            value = i;
        }
    }
    
    std::cout << "max = " << elem << " location: " << value + 1 << " and " << 2;
}