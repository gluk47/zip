#include "argparse.h"
#include "zip_header.h"
#include "zip_updater.h"

#include <fstream>
#include <iostream>
#include <sstream>

void PrintArguments(const TArgParser::TParsed& args) {
    std::cout << "== " << args.Filename << " ==\n";
    for (const auto& filter : args.Filters) {
        std::cout << "-";
        for (const auto& f : filter)
            std::cout << " " << f;
        std::cout << "\n";
    }
}

int main(int argc, const char* argv[]) {
    TArgParser parser(TZipUpdaters::SupportedFilters());
    auto args = parser.Parse(argc, argv);

    // --help, --usage, -h, -?, /?
    if (args.NeedHelp) {
        // ./image_filter -crop -gs && echo ok
        return 1;
    }
    // -v, --verbose
    PrintArguments(args);

    std::stringstream separator;
    separator << "-- " << std::string(args.Filename.size(), '-') << " --\n\n";
    std::cout << separator.str();

    TZipHeader header;
    header.read_header(std::ifstream(args.Filename));
    header.print_info(std::cout);
    std::cout << separator.str();

    // EAFP
    // ask for forgiveness than for permission
    try {
        TZipUpdaters filters;
        for (const auto& filter : args.Filters)
            filters.Create(filter);
        filters.Apply(header);
    } catch (std::exception& e) {
        std::cout << e.what() << "\n";
        return 1;
    }
    header.print_info(std::cout);
    return 0;
}
