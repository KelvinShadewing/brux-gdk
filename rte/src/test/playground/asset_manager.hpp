#ifndef ASSET_MANAGER
#define ASSET_MANAGER
#include <map>
#include <string>
#include "../../api/sprites.hpp"

class AssetManager{
public:
    std::map<std::string, int> sprites;
    AssetManager() = default;
    void AddSprite(std::string _name, std::string _path, int w, int h);
    void AddSprite(std::string _name, std::string _path);

};

#endif