#include "resize.h"

#include "../zip_header.h"

bool TZipResize::ArgValidator::Validate(const std::vector<std::string>& args) {
    if (args.size() != 3) {
        throw std::invalid_argument("resize filter requires exactly two arguments (uncompressed size, compressed size)");
    }
    try {
        std::stoi(args[1]);
        std::stoi(args[2]);
    } catch (std::invalid_argument& x) {
        throw std::invalid_argument("resize filter: failure parsing arguments: " + args[1] + " " + args[2] + ": " + x.what());
    }
    return true;
}


TZipResize::TZipResize(const std::vector<std::string>& args) {
    if (args.size() != 3) {
        throw std::invalid_argument("resize filter requires exactly two arguments (uncompressed size, compressed size)");
    }
    try {
        Uncompressed = std::stoi(args[1]);
        Compressed = std::stoi(args[2]);
    } catch (std::invalid_argument& x) {
        throw std::invalid_argument("resize filter: failure parsing arguments: " + args[1] + " " + args[2] + ": " + x.what());
    }
}

void TZipResize::Apply(TZipHeader& zh) const {
    zh.uncompressed_size = Uncompressed;
    zh.compressed_size = Compressed;
}
