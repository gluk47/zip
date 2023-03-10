#pragma once

#include "../zip_updater.h"

class TZipResize : public IZipUpdater {
public:
    TZipResize(const std::vector<std::string>& args);

    struct ArgValidator {
        static bool Validate(const std::vector<std::string>& args);
    };

    void Apply(TZipHeader&) const override;

private:
    uint32_t Uncompressed;
    uint32_t Compressed;
};
