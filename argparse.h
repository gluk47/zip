#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

// using Lean Mean C++ Option Parser
// https://optionparser.sourceforge.net/index.html
// https://github.com/hepcatjk/optionparser

// C getopt
// getoptpb (protobuf)
// sample.zip -crop 800 600 -gs

// ./binary -l -x -s
// ./binary -lxs
// ./binary --line --except --size

class TArgParser {
public:
    // &TClass::* -> obj.*func_ptr
    using TArgValidator = std::function<bool(const std::vector<std::string>&)>;

    struct TParsed {
        std::string Filename;
        std::vector<std::vector<std::string>> Filters;
        bool NeedHelp = false;
    };

    TArgParser(std::unordered_map<std::string_view, TArgValidator> validators)
    : ArgsValidator_(validators)
    {}

    TParsed Parse(int argc, const char* argv[]);

private:
    const std::unordered_map<std::string_view, TArgValidator> ArgsValidator_;
};
