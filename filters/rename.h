#pragma once

#include "../zip_updater.h"

class TZipRename : public IZipUpdater {
public:
    TZipRename(const std::vector<std::string>& args);
    void Apply(TZipHeader&) const override;

    struct ArgValidator {
        static bool Validate(const std::vector<std::string>& args) {
            return args.size() == 2;
        }
    };

private:
    std::string Limit;
};
