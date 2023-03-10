#pragma once

#include <functional>
#include <memory>
#include <string_view>
#include <unordered_map>
#include <vector>

class TZipHeader;

class IZipUpdater {
public:
    virtual void Apply(TZipHeader&) const = 0;
    virtual bool Validate(const std::vector<std::string>& args) {
        return args.size() == 0;
    }

    virtual ~IZipUpdater() = default;
};

class TZipUpdaters {
public:
    using TArguments = std::unordered_map<std::string_view, std::function<bool(const std::vector<std::string>&)>>;
    static TArguments SupportedFilters();

    void Create(const std::vector<std::string>& filter);

    void Apply(TZipHeader&) const;
private:
    std::vector<std::unique_ptr<IZipUpdater>> Updaters_;
};
