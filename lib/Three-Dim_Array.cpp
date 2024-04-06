#include "Three-Dim_Array.h"

ThreeDimensionalArray::ThreeDimensionalArray() {
    length_ = 1;
    width_ = 1;
    depth_ = 1;
    ptr_ = new uint16_t[1];
    bit_ptr_ = new uint8_t[1];
    for (uint32_t i = 0; i < 1; ++i) {
        ptr_[i] = 0;
        bit_ptr_[i] = 0;
    }
}

ThreeDimensionalArray::ThreeDimensionalArray(uint32_t length, uint32_t width, uint32_t depth) : length_(length), width_(width), depth_(depth) {
    if (length_ <= 0) {
        std::cerr << "Undefined behaviour: inaccessible value of length\n";
        exit(1);
    } else if (width_ <= 0) {
        std::cerr << "Undefined behaviour: inaccessible value of width\n";
        exit(1);
    } else if (depth <= 0) {
        std::cerr << "Undefined behaviour: inaccessible value of depth\n";
        exit(1);
    }
    uint32_t array_size = length_ * width_ * depth_;
    ptr_ = new uint16_t[array_size];
    bit_ptr_ = new uint8_t[array_size / 8 + 1];
}

ThreeDimensionalArray::ThreeDimensionalArray(const ThreeDimensionalArray& other) {
    length_ = other.length_;
    width_ = other.width_;
    depth_ = other.depth_;
    uint32_t array_size = length_ * width_ * depth_;
    ptr_ = new uint16_t[array_size];
    uint32_t bit_array_size = (array_size + 7) / 8;
    bit_ptr_ = new uint8_t[bit_array_size];
    for (uint32_t i = 0; i < array_size; ++i) {
        ptr_[i] = other.ptr_[i];
    }
    for (uint32_t i = 0; i < bit_array_size; ++i) {
        bit_ptr_[i] = other.bit_ptr_[i];
    }
}

ThreeDimensionalArray& ThreeDimensionalArray::operator=(const int32_t key) {
    if (key < 0) {
        std::cerr << "Error: This array doesn't accept negative values";
        exit(1);
    }
    if (x_idx == -1 || y_idx == -1 || z_idx == -1) {
        std::cerr << "Error: Index is out of range";
        exit(1);
    }
    SetValue(x_idx, y_idx, z_idx, key);
    x_idx = -1;
    y_idx = -1;
    z_idx = -1;

    return *this;
}

ThreeDimensionalArray& ThreeDimensionalArray::operator[](const uint32_t idx) {
    if (x_idx == -1) {
        x_idx = idx;
    } else if (y_idx == -1) {
        y_idx = idx;
    } else if (z_idx == -1) {
        z_idx = idx;
    }

    return *this;
}

ThreeDimensionalArray::~ThreeDimensionalArray() {
    delete[] ptr_;
    delete[] bit_ptr_;
}

uint32_t ThreeDimensionalArray::GetSize() const {

    return length_ * width_ * depth_;
}

std::pair<uint32_t, uint8_t> ThreeDimensionalArray::GetAdditionalBit(const uint32_t& idx) {

    return (std::make_pair(idx / 8, idx % 8));
}

uint32_t ThreeDimensionalArray::GetCurrentValue(const uint32_t idx) {
    std::pair<uint32_t, uint8_t> additional_bit = this->GetAdditionalBit(idx);

    return (ptr_[idx] + ((bit_ptr_[additional_bit.first] >> additional_bit.second) & 1)) * (UINT16_MAX + 1);
}

void ThreeDimensionalArray::SetCurrentValue(const uint32_t idx, const uint32_t value) {
    std::pair<uint32_t, uint8_t> additional_bit = this->GetAdditionalBit(idx);
    value = value % kMax;
    if (!((value >> 16) & 1)) {
        bit_ptr_[additional_bit.first] = bit_ptr_[additional_bit.first] & (~(1 << additional_bit.second));
    } else {
        bit_ptr_[additional_bit.first] = bit_ptr_[additional_bit.first] | (1 << additional_bit.second);
    }
    ptr_[idx] = value % (UINT16_MAX + 1);
}

uint32_t ThreeDimensionalArray::GetValue(const uint32_t x, const uint32_t y, const uint32_t z) {

    return GetCurrentValue(x * width_ * depth_ + y * depth_ + z);
}

void ThreeDimensionalArray::SetValue(const uint32_t x, const uint32_t y, const uint32_t z, const uint32_t value) {
    SetCurrentValue(x * width_ * depth_ + y * depth_ + z, value);
}

ThreeDimensionalArray ThreeDimensionalArray::operator+(const ThreeDimensionalArray& other) {
    if (length_ != other.length_ || width_ != other.width_ || depth_ != other.depth_) {
        std::cerr << "Undefined behaviour: inaccessible dimensions\n";
        if (length_ != other.length_) {
            std::cerr << "Value of the first length is " << length_ << " and value of the second length is " << other.length_ << '\n';
        }
        if (width_ != other.width_) {
            std::cerr << "Value of the first width is " << length_ << " and value of the second width is " << other.length_ << '\n';
        }
        if (depth_ != other.depth_) {
            std::cerr << "Value of the first depth is " << depth_ << " and value of the second depth is " << other.depth_ << '\n';
        }
        exit(1);
    }
    ThreeDimensionalArray result{length_, width_, depth_};
    for (uint32_t i = 0 ; i < result.GetSize(); ++i) {
        std::pair<uint32_t, uint8_t> additional_bit = this->GetAdditionalBit(i);
        uint32_t current_idx_sum = ptr_[i] + ((bit_ptr_[additional_bit.first] >> additional_bit.second) & 1) * kMax + other.ptr_[i] + ((other.bit_ptr_[additional_bit.first] >> additional_bit.second) & 1) * kMax;
        result.SetCurrentValue(i, current_idx_sum);
    }

    return result;
}

ThreeDimensionalArray ThreeDimensionalArray::operator-(const ThreeDimensionalArray& other) {
    if (length_ != other.length_ || width_ != other.width_ || depth_ != other.depth_) {
        std::cerr << "Undefined behaviour: inaccessible dimensions\n";
        if (length_ != other.length_) {
            std::cerr << "Value of the first length is " << length_ << " and value of the second length is " << other.length_ << '\n';
        }
        if (width_ != other.width_) {
            std::cerr << "Value of the first width is " << length_ << " and value of the second width is " << other.length_ << '\n';
        }
        if (depth_ != other.depth_) {
            std::cerr << "Value of the first depth is " << depth_ << " and value of the second depth is " << other.depth_ << '\n';
        }
        exit(1);
    }
    ThreeDimensionalArray result{length_, width_, depth_};
    for (uint32_t i = 0 ; i < result.GetSize(); ++i) {
        std::pair<uint32_t, uint8_t> additional_bit = this->GetAdditionalBit(i);
        uint32_t current_idx_dif = ptr_[i] + ((bit_ptr_[additional_bit.first] >> additional_bit.second) & 1) * kMax - other.ptr_[i] - ((other.bit_ptr_[additional_bit.first] >> additional_bit.second) & 1) * kMax;
        result.SetCurrentValue(i, current_idx_dif);
    }

    return result;
}

ThreeDimensionalArray ThreeDimensionalArray::operator*(int32_t key) {
    if (key < 0) {
        std::cerr << "Error: This array doesn't accept negative values";
        exit(1);
    }
    ThreeDimensionalArray result{length_, width_, depth_};
    for (uint32_t i = 0 ; i < result.GetSize(); ++i) {
        std::pair<uint32_t, uint8_t> additional_bit = this->GetAdditionalBit(i);
        uint32_t current_idx_multi = (ptr_[i] + ((bit_ptr_[additional_bit.first] >> additional_bit.second) & 1) * kMax) * key;
        result.SetCurrentValue(i, current_idx_multi);
    }

    return result;
}

std::ostream& operator<<(std::ostream& stream, const ThreeDimensionalArray& arr) {
    if (arr.x_idx == -1 || arr.y_idx == -1 || arr.z_idx == -1) {
        for (uint32_t i = 0; i < arr.length_; ++i) {
            for (uint32_t j = 0; j < arr.width_; ++j) {
                for (uint32_t k = 0; k < arr.depth_; ++k) {
                    uint32_t curr_idx = i * arr.width_ * arr.depth_ + j * arr.depth_ + k;
                    std::pair<uint32_t, uint8_t> additional_bit = arr.GetAdditionalBit(curr_idx);
                    uint32_t position = ((arr.bit_ptr_[additional_bit.first] >> additional_bit.second) & 1) * (UINT16_MAX + 1);
                    std::cout << (arr.ptr_[curr_idx] + position) << ' ';
                }
                std::cout << '\n';
            }
            std::cout << '\n';
        }
        arr.x_idx = -1;
        arr.y_idx = -1;
        arr.z_idx = -1;

        return stream;
    } else {
        uint32_t curr_idx = arr.x_idx * arr.width_ * arr.depth_ + arr.y_idx * arr.depth_ + arr.z_idx;
        std::pair<uint32_t, uint8_t> additional_bit = arr.GetAdditionalBit(curr_idx);
        uint32_t position = ((arr.bit_ptr_[additional_bit.first] >> additional_bit.second) & 1) * (UINT16_MAX + 1);
        std::cout << (arr.ptr_[curr_idx] + position);
        arr.x_idx = -1;
        arr.y_idx = -1;
        arr.z_idx = -1;

        return stream;
    }
}

std::istream& operator>>(std::istream& stream, const ThreeDimensionalArray& arr) {
    for (uint32_t i = 0; i < arr.GetSize(); ++i) {
        uint32_t value;
        stream >> value;
        arr.SetCurrentValue(i, value);
    }

    return stream;
}

ThreeDimensionalArray::operator int() {
    uint32_t curr_idx = x_idx * width_ * depth_ + y_idx * depth_ + z_idx;
    std::pair<uint32_t, uint8_t> additional_bit = GetAdditionalBit(curr_idx);
    uint32_t position = ((bit_ptr_[additional_bit.first] >> additional_bit.second) & 1) * (UINT16_MAX + 1);
    x_idx = -1;
    y_idx = -1;
    z_idx = -1;

    return static_cast<int>(ptr_[curr_idx] + position);
}