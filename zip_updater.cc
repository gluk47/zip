#include "zip_updater.h"

#include "filters/rename.h"
#include "filters/resize.h"

#include <functional>
#include <memory>
#include <string_view>
#include <unordered_map>

using namespace std;


namespace {

template <typename T>
struct TFilterInfo {
static unique_ptr<IZipUpdater> Create(const vector<string>& s) {
    return make_unique<T>(s);
}

static bool Validate(const vector<string>& s) {
    return T::ArgValidator::Validate(s);
}
};

typedef unique_ptr<IZipUpdater> CreateTypedef(const vector<string>& s);

using TCreate = unique_ptr<IZipUpdater> (*)(const vector<string>&);
using TValidate = bool (*)(const vector<string>&);

// type erasure
using TFuncCreate = std::function<IZipUpdater(const vector<string>&)>;

unordered_map<string, pair<TCreate, TValidate>> Supported = {
    {"rename", make_pair(TFilterInfo<TZipRename>::Create, TFilterInfo<TZipRename>::Validate)},
    {"resize", make_pair(TFilterInfo<TZipResize>::Create, TFilterInfo<TZipResize>::Validate)},
};

/*
for (const vector<string>& filter : filters)
    if (filter[0] == "rename") {
        Updaters_.emplace_back(make_unique<TZipRename>(filter));
    } else if (filter[0] == "resize") {

    }*/

}  // namespace

TZipUpdaters::TArguments TZipUpdaters::SupportedFilters() {
    TArguments names;
    for (const auto& f : Supported)
        names.emplace(f.first, f.second.second);
    return names;
}

void TZipUpdaters::Apply(TZipHeader& zip) const {
    for (const auto& f : Updaters_)
        f->Apply(zip);
}

void TZipUpdaters::Create(const std::vector<std::string>& filter) {
    const auto& i = Supported.find(filter.front());
    if (i == Supported.end())
        throw std::invalid_argument("Unsupported filter " + filter.front());
    Updaters_.push_back(i->second.first(filter));
}


