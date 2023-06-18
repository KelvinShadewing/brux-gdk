#include "asset_manager.hpp"

void AssetManager::AddSprite(std::string _name, std::string _path, int w, int h){
    sprites[_name] = BruxAPI::newSprite(_path, w, h, 0, 0, 0, 0);
}