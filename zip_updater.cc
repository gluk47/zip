#include "zip_updater.h"

#include "filters/rename.h"
#include "filters/resize.h"

#include <functional>

using namespace std;


namespace {
template <typename T>
unique_ptr<IZipUpdater> Create(const vector<string>& s) {
    return make_unique<T>(s);
}

using TCreate = unique_ptr<IZipUpdater> (*)(const vector<string>& s);

unordered_map<string, TCreate> Supported = {
    {"rename", Create<TZipRename>},
    {"resize", Create<TZipResize>},
};

}  // namespace

std::unordered_set<std::string_view> TZipUpdaters::SupportedFilters() {
    std::unordered_set<std::string_view> names;
    for (const auto& f : Supported)
        names.emplace(f.first);
    return names;
}


void TZipUpdaters::Apply(TZipHeader& zip) const {
    for (const auto& f : Updaters_)
        f->Apply(zip);
}

void TZipUpdaters::Create(const std::vector<std::string>& filter) {
    const auto& i = Supported.find(filter.front());
    if (i == Supported.end())
        throw std::runtime_error("Unsupported filter " + filter.front());
    Updaters_.push_back(i->second(filter));
}


