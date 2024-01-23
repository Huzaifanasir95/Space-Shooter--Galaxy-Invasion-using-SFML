// Huzaifa Nasir
// 22I-1053
// CS_A
// Project
#ifndef INVADERS_H_
#define INVADERS_H_
#include <SFML/Graphics.hpp>
#include <iostream>
#include"Bomb.h"
using namespace sf;
using namespace std;
class Invader {

public:
    Sprite sprite;
    Texture texture;
    float a, b;
    bool destroyed = false;
    Bomb bomb; 

    Invader() {
        texture.loadFromFile("img/enemy_1.png");
        if (!texture.loadFromFile("img/enemy_1.png")) {
    cout << "Failed to load texture!" << endl;
}
        sprite.setTexture(texture);

    }

    Invader(const char* image_file) {
        setTexture(image_file);
        a = 0;
        b = 0;
        sprite.setPosition(a, b);
    }

    Invader(const string& image_file) {
        setTexture(image_file);
        a = 0;
        b = 0;

    sprite.setPosition(a, b);
    }
   bool isDestroyed() const {
        return destroyed;
    }

    void setDestroyed(bool value) {
        destroyed = value;
    }

void setPosition(float posX, float posY) {
    a = posX;
    b = posY;

    sprite.setPosition(a, b);
}
    
    void dropBomb() {
        bomb.setPosition(a, b);
    }
    
    void updateBomb() {
        bomb.update();
    }

    void setTexture(const string& image_file) {
        texture.loadFromFile(image_file);
        sprite.setTexture(texture);
        if (!texture.loadFromFile("img/enemy_1.png")) {
    cout << "Error texture" << endl;
}     
    }
};

#endif
