#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Sprite.h"
class SpriteLoader
{
public:
    Sprite Load(std::string path) {
        std::vector<std::string> data;
        std::ifstream stream(path);
        while (!stream.eof()) {
            std::string s;
            std::getline(stream, s);
            data.push_back(s);
        }
        Sprite result;
        result.SetData(data);
        return result;
    }
};

