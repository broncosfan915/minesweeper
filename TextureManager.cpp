#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <iostream>

unordered_map<string, sf::Texture> TextureManager::textures;

sf::Texture& TextureManager::getTexture(string textureName) {
    auto result = textures.find(textureName);
    if (result == textures.end()) {
        sf::Texture newTexture;
        newTexture.loadFromFile("files/images/" + textureName + ".png");
        textures[textureName] = newTexture;
        return textures[textureName];
    }
    else {
        return result->second;
    }
}

void TextureManager::displayTextures() {
    int count;
    for (auto it = textures.begin(); it != textures.end(); it++) {
        std::cout << count << std::endl;
        count++;
    }
}