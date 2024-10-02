#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Sprite.h"
#include <algorithm>

class SpriteLoader
{
public:
    Sprite Load(std::string path) {
        std::vector<std::string> data;
        std::ifstream stream(path);
        int maxLength = 0;
        while (!stream.eof()) {
            std::string s;
            std::getline(stream, s);
            data.push_back(s);
            if (s.length() > maxLength)
                maxLength = s.length();
        }
        for (size_t i = 0; i < data.size(); i++)
        {
            data[i].resize(maxLength);
        }


        Sprite result;
        result.SetData(data);
        return result;
    }
};

