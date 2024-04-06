#include "../lib/Three-Dim_Array.h"

int main() {
    ThreeDimensionalArray my_array1{2, 2, 2};
    my_array1[1][1][1] = 3;
    std::cout << my_array1[1][1][1] << '\n';
    ThreeDimensionalArray my_array3{2, 2, 2};
    my_array3[1][1][1] = 100;
    std::cout << my_array3[1][1][1] << '\n';
    ThreeDimensionalArray my_array4 = my_array1 + my_array3;
    std::cout << my_array4[1][1][1] << '\n';
    ThreeDimensionalArray my_array2 = my_array1 * 2;
    std::cout << my_array2[1][1][1];
}