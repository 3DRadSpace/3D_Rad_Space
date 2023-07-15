#include "IAsset.hpp"

Engine3DRadSpace::Content::IAsset::IAsset(const unsigned id, const std::type_info& info, const std::string &path, const std::string &name):
    _id(id),
    Path(path),
    Type(info),
    Name(name)
{
    if(name.empty())
    {
        Name = std::filesystem::path(path).stem().string();
    }
}

unsigned Engine3DRadSpace::Content::IAsset::ID()
{
    return _id;
}
