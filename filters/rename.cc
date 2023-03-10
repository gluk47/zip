#include "rename.h"

#include "../zip_header.h"

TZipRename::TZipRename(const std::vector<std::string>& args) {
    if (args.size() != 2) {
        throw std::invalid_argument("crop filter requires exactly one argument");
    }
    Limit = args[1];
}

void TZipRename::Apply(TZipHeader& zh) const {
    zh.file_name = Limit;
}
