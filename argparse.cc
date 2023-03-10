#include "argparse.h"

#include <cassert>
#include <iostream>

using namespace std;

TArgParser::TParsed TArgParser::Parse(int argc, const char* argv[]) {
    TParsed result;
    try {
        result.NeedHelp = true;
        if (argc < 2) {
            throw invalid_argument("No file name specified as a first argument");
        }

        argc--;
        argv++;

        result.Filename = *argv++; // argv[0]; *(argv + 0)
        argc--;

        while (argc --> 0) {
            if (**argv == '-') {
                result.Filters.emplace_back();
                result.Filters.back().emplace_back(*argv + 1);
                auto& fname = result.Filters.back().back();
                if (!ArgsValidator_.contains(fname)) {
                    throw invalid_argument( "Unsupported filter «" + fname + "»\n");
                    return result;
                }
            } else {
                if (result.Filters.empty()) {
                    throw invalid_argument("Missing a filter name before an argument «"s + *argv + "»\n");
                    return result;
                }
                // 0.6 sigma
                result.Filters.back().emplace_back(*argv);
            }
            argv++;
        }

        for (const auto& f : result.Filters) {
            auto i = ArgsValidator_.find(f[0]);
            assert (i != ArgsValidator_.end());
            if(!i->second(f)) {
                throw std::invalid_argument("Bad arguments for filter «"s + f[0] + "»");
            }
        }

        result.NeedHelp = false;
    } catch (exception& x) {
        cout << "Usage: ./list sample.zip -crop 800 600 -gs -blur 0.5\n";
        cout << "Supported filters are:";
        for (const auto& f : ArgsValidator_)
            cout << ' ' << f.first;
        cout << "\n\n" << x.what() << '\n';
    }
    return result;
}

