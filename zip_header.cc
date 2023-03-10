#include "zip_header.h"

#include <iomanip>
#include <iostream>

/// variadic template
// template<typename T...>
// void print_vector(const vector<T>& data, ostream&) {}

// accumulate(1,2,3)
// accumulate(1,2.0,3)
// accumulate(1,2,"3",4.0)

template<typename... T>
auto accumulate(T&&... args) -> decltype((args + ...)) {
    return (args + ...);
}

// 0x1234 -> 34 12
void TZipHeader::read_header(std::istream& str) {
    std::apply([&](auto&&... args){
        (
            str.read(reinterpret_cast<char*>(&args), sizeof(args)),
            ...
        );
    }, fixed_binary_header);
    read_file_name(str);
}

void TZipHeader::read_file_name(std::istream& str) {
    file_name.resize(fname_length);
    str.read(file_name.data(), fname_length);
}

void TZipHeader::print_info(std::ostream& str) const {
    str << "Zip file version " << version << "\n"
        << "Compression method: " << method << "\n"
        << "Size (bytes): " << uncompressed_size << " -> " << compressed_size << " (deflated to "
        << std::fixed << std::setprecision(2) << (compressed_size * 100. / uncompressed_size) << "%)\n"
        << "File name: «" << file_name << "»\n";
}
