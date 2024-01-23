// Huzaifa Nasir
// 22I-1053
// CS_A
// Project
#ifndef BOMB_H
#define BOMB_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
class Bomb {
public:
    Sprite sprite;
    Texture texture;
    float a, b;
    float speed = 2.0f; // Speed of the bomb
    
    Bomb() {
        texture.loadFromFile("img/fire16.png");
        sprite.setTexture(texture);
    }

    void setPosition(float posX, float posY) {
       a=posX;
       b=posY;
        sprite.setPosition(posX, posY);
    }
    
    void update() {
        b += speed;
        sprite.setPosition(a, b);
    }
};
#endif