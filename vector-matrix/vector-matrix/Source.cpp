#include <iostream>
#include "TVector.h"
#include "TMatrix.h"

int main() {
    const int size1 = 3;
    TMatrix<int> m1(size1);
    for (int i = 0; i < size1; i++) {
        for (int j = i; j < size1; j++) {
            m1[i][j] = 1;
        }
    }
    TMatrix<int> m2(size1);
    for (int i = 0; i < size1; i++) {
        for (int j = i; j < size1; j++) {
            if (i == j) {
                m2[i][j] = 1;
            }
            else
            {
                m2[i][j] = 0;
            }
        }
    }
    TMatrix<int> m3(size1);
    m3 = m1 * m2;

    for (int i = 0; i < 3; i++) {
        for (int j = i; j < 3; j++) {
            std::cout << m3[i][j] << " ";
        }
        std::cout << std::endl;
    }
	return 0;
}