#include "argparse.h"

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

        result.Filename = *argv++;
        argc--;

        while (argc --> 0) {
            if (**argv == '-') {
                result.Filters.emplace_back();
                result.Filters.back().emplace_back(*argv + 1);
                auto& fname = result.Filters.back().back();
                if (!KnownFilters_.contains(fname)) {
                    throw invalid_argument( "Unsupported filter «" + fname + "»\n");
                    return result;
                }
            } else {
                if (result.Filters.empty()) {
                    throw invalid_argument("Missing a filter name before an argument «"s + *argv + "»\n");
                    return result;
                }
                result.Filters.back().emplace_back(*argv);
            }
            argv++;
        }

        result.NeedHelp = false;
    } catch (exception& x) {
        cout << "Usage: " << argv[0] << " sample.zip -crop 800 600 -gs -blur 0.5\n";
        cout << "Supported filters are:";
        for (const auto& f : KnownFilters_)
            cout << ' ' << f;
        cout << '\n';
    }
    return result;
}

