#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

class TZipHeader;

class IZipUpdater {
public:
    virtual void Apply(TZipHeader&) const = 0;
    virtual ~IZipUpdater() = default;
};

class TZipUpdaters {
public:
    static std::unordered_set<std::string_view> SupportedFilters();

    void Create(const std::vector<std::string>& filter);

    void Apply(TZipHeader&) const;
private:
    std::vector<std::unique_ptr<IZipUpdater>> Updaters_;
};
