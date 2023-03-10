#pragma once

#include "../zip_updater.h"

class TZipRename : public IZipUpdater {
public:
    TZipRename(const std::vector<std::string>& args);
    void Apply(TZipHeader&) const override;

private:
    std::string Limit;
};
