#pragma once

#include <string>
#include <unordered_set>
#include <vector>

// using Lean Mean C++ Option Parser
// https://optionparser.sourceforge.net/index.html
// https://github.com/hepcatjk/optionparser

class TArgParser {
public:
    struct TParsed {
        std::string Filename;
        std::vector<std::vector<std::string>> Filters;
        bool NeedHelp = false;
    };

    TArgParser(std::unordered_set<std::string_view> known_filters)
    : KnownFilters_(known_filters)
    {}

    TParsed Parse(int argc, const char* argv[]);

private:
    const std::unordered_set<std::string_view> KnownFilters_;
};
