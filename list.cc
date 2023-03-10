#include "argparse.h"
#include "zip_header.h"
#include "zip_updater.h"

#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, const char* argv[]) {
    TArgParser parser(TZipUpdaters::SupportedFilters());
    auto args = parser.Parse(argc, argv);

    if (args.NeedHelp) {
        return 1;
    }

    std::cout << "== " << args.Filename << " ==\n";
    for (const auto& filter : args.Filters) {
        std::cout << "-";
        for (const auto& f : filter)
            std::cout << " " << f;
        std::cout << "\n";
    }
    std::stringstream separator;
    separator << "-- " << std::string(args.Filename.size(), '-') << " --\n\n";
    std::cout << separator.str();

    TZipHeader header;
    header.read_header(std::ifstream(args.Filename));
    header.print_info(std::cout);
    std::cout << separator.str();

    try {
        TZipUpdaters filters;
        for (const auto& filter : args.Filters)
            filters.Create(filter);
        filters.Apply(header);
    } catch (std::exception& e) {
        std:: cout << e.what() << "\n";
        return 1;
    }
    header.print_info(std::cout);
    return 0;
}
