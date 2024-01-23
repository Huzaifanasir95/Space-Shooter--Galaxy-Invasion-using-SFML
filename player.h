// Huzaifa Nasir
// 22I-1053
// CS_A
// Project
#include <SFML/Graphics.hpp>
#include <string.h>
#include"Invaders.h"
using namespace std;
using namespace sf;

class Bullet {
public:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed = 5.0f;

    Bullet() {
        texture.loadFromFile("img/speed.png");
        sprite.setTexture(texture);
        sprite.setScale(0.5f, 0.5f);
    }

    void update() {
        sprite.move(0.0f, -speed);
    }
};

class Player {

public:
    sf::Texture tex;
    sf::Sprite sprite;
    
    float speed = 0.1f;
    int x, y;
    Bullet* bullets;
    int bullet_count = 0;
    int max = 10000;

    Player(std::string png_path) {
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        x = 340;
        y = 700;
        sprite.setPosition(x, y);
        sprite.setScale(0.75, 0.75);
        bullets = new Bullet[max];
      
    }

    ~Player() {
        delete[] bullets;
    }

    void fire() {
        if (bullet_count < max) {
            Bullet bullet;//it firt gets the x coordinates and then calculates half the width of the player's sprite. and then calculates half the width of the bullet's sprite.
            bullet.sprite.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width / 2.0f - bullet.sprite.getGlobalBounds().width / 2.0f,
                                      sprite.getPosition().y - bullet.sprite.getGlobalBounds().height);
            bullets[bullet_count++] = std::move(bullet);
        }
    }

    void move(string s) {
        float delta_x = 0, delta_y = 0;
        if (s == "l") {
            delta_x = -3;
        if (sprite.getPosition().x <= 0)
            sprite.setPosition(800 - sprite.getGlobalBounds().width, sprite.getPosition().y);
//If the check is true, the sprite's position is set to the right side of the screen (800 - sprite.getGlobalBounds().width) while maintaining its y-coordinate (sprite.getPosition().y). This creates the effect of wrapping the player's sprite from the left edge to the right edge of the screen.
        } else if (s == "r") {
            delta_x = 3;
             if (sprite.getPosition().x >= 800 - sprite.getGlobalBounds().width)
            sprite.setPosition(0, sprite.getPosition().y);

        } else if (s == "u") {
            delta_y = -3;

        } else if (s == "d") {
            delta_y = 3;

        }
        delta_x *= speed;
        delta_y *= speed;

        sprite.move(delta_x, delta_y);
    }

void update_bullets(Invader* invaders)
{
    for (int a = 0; a < bullet_count; a++)
    {
        bullets[a].update();

        for (int b = 0; b < 10; b++)
        {
            sf::FloatRect bulletbound = bullets[a].sprite.getGlobalBounds();
            sf::FloatRect invaderbound = invaders[b].sprite.getGlobalBounds();

            if (bulletbound.left < invaderbound.left + invaderbound.width &&
                bulletbound.left + bulletbound.width > invaderbound.left &&
                bulletbound.top < invaderbound.top + invaderbound.height &&
                bulletbound.top + bulletbound.height > invaderbound.top)
            {
               invaders[b].setDestroyed(true);
              
                bullets[a].sprite.setPosition(-10000, -10000); // Set bullet position outside the visible area
                delete_bullet(a, bullets[a].sprite);
                
                for (int c = b; c < 10; c++)
                {
                    invaders[c] = invaders[c + 1];
                }
                return;
            }
        }

        if (bullets[a].sprite.getPosition().y < -100)
        {
            bullets[a].sprite.setPosition(-1000, -1000); // Set bullet position outside the visible area
        }
    }
}
void delete_bullet(int& ind, sf::Sprite& bulletSprite) {
    if (ind >= 0 && ind < bullet_count) {
        bulletSprite.setPosition(-1000, -1000);

        int a=ind;
        while(a < bullet_count - 1) {
            bullets[a] = bullets[a + 1];
            a++;
        }
        bullet_count--;
    }
}


};

