#include <iostream>
#include <cstdint>
#pragma once

const int kMax = (UINT16_MAX + 1) * 2;

class ThreeDimensionalArray {
private:
    uint32_t length_;
    uint32_t width_;
    uint32_t depth_;
    uint16_t* ptr_;
    uint8_t* bit_ptr_;
    int32_t x_idx = -1;
    int32_t y_idx = -1;
    int32_t z_idx = -1;
public:
    ThreeDimensionalArray();

    ThreeDimensionalArray(uint32_t length, uint32_t width, uint32_t depth);

    ThreeDimensionalArray(const ThreeDimensionalArray& other);

    ThreeDimensionalArray& operator=(int32_t key);

    ThreeDimensionalArray& operator[](const uint32_t idx);

    ~ThreeDimensionalArray();

    uint32_t GetSize() const;

    ThreeDimensionalArray operator+(ThreeDimensionalArray& other);

    ThreeDimensionalArray operator-(ThreeDimensionalArray& other);

    ThreeDimensionalArray operator*(int32_t key);

    friend std::ostream& operator<<(std::ostream& stream, ThreeDimensionalArray& arr);

    friend std::istream& operator>>(std::istream& stream, ThreeDimensionalArray& arr);

    static std::pair<uint32_t, uint8_t> GetAdditionalBit(uint32_t &idx);

    uint32_t GetCurrentValue(uint32_t idx);

    void SetCurrentValue(uint32_t idx, uint32_t value);

    uint32_t GetValue(uint32_t x, uint32_t y, uint32_t z);

    void SetValue(uint32_t x, uint32_t y, uint32_t z, uint32_t value);

    operator int();
};