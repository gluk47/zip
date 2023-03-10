#pragma once

#include <cctype>
#include <iosfwd>
#include <string>
#include <tuple>

class TZipHeader {
public:
    void read_header(std::istream& str);
    void read_header(std::istream&& str) {
        read_header(str);
    }
    void read_file_name(std::istream& str);

    void print_info(std::ostream& str) const;

    std::tuple<
        uint32_t,

        uint16_t,
        uint16_t,
        uint16_t,
        uint16_t,
        uint16_t,

        uint32_t,
        uint32_t,
        uint32_t,

        uint16_t,
        uint16_t
    > fixed_binary_header;

    uint16_t& version = std::get<1>(fixed_binary_header);
    uint16_t& method  = std::get<3>(fixed_binary_header);
    uint16_t& mtime   = std::get<4>(fixed_binary_header);
    uint16_t& mdate   = std::get<5>(fixed_binary_header);
    uint32_t& compressed_size = std::get<7>(fixed_binary_header);
    uint32_t& uncompressed_size = std::get<8>(fixed_binary_header);
    std::string file_name;

private:
    uint16_t& fname_length = std::get<9>(fixed_binary_header);
};
