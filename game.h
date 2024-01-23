// Huzaifa Nasir
// 22I-1053
// CS_A
// Project
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;
#include "player.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;
struct ScoreData {
    string playername;
    int score;
};

void saveScore(const ScoreData& data)
{
    ofstream file("score.txt", ios::app);  // Open the file in append mode
    if (file.is_open())
    {
        file << data.playername << "\t";
        file << data.score << endl;
        file.close();
        cout << "Score saved successfully" << endl;
    }
    else
    {
        cout << "Failed to save score" << endl;
    }
}

ScoreData loadScore()
{
    ScoreData data;
    ifstream file("score.txt");
    if (file.is_open())
    {
        file >> data.playername;
        file >> data.score;
        file.close();
    }
    else
    {
        cout << "Failed to load score\n\n"; 
    }
    return data;
}


class Game
{
public:
Sprite background; //Game background sprite
Texture bg_texture;
Player* p; //player 
Invader invaders[10]; //invaders array
int destroyedInvaders = 0;
int score = 0;

Game()
{
p=new Player("img/player_ship.png");

bg_texture.loadFromFile("img/background.jpg");
background.setTexture(bg_texture);
background.setScale(2, 1.5);

int temp = time(0) % 4;
switch (temp)
    {
        case 0:
            invaders[0].setPosition(110, 20);
            invaders[1].setPosition(276, 20);
            invaders[2].setPosition(443, 20);
            invaders[3].setPosition(610, 20);
            invaders[4].setPosition(110, 290);
            invaders[5].setPosition(276, 290);
            invaders[6].setPosition(443, 290);
            invaders[7].setPosition(610, 290);
            invaders[8].setPosition(110, 155);
            invaders[9].setPosition(610, 155);
            break;

        case 1:
            invaders[0].setPosition(330, 130);
            invaders[1].setPosition(210, 20);
            invaders[2].setPosition(460, 20);
            invaders[3].setPosition(-110, -110);
            invaders[4].setPosition(120, 130);
            invaders[5].setPosition(310, 210);
            invaders[6].setPosition(540, 130);
            invaders[7].setPosition(240, 246);
            invaders[8].setPosition(440, 246);
            invaders[9].setPosition(340, 349);
            break;
        
        case 2:
            invaders[0].setPosition(90, 20);
            invaders[1].setPosition(256, 20);
            invaders[2].setPosition(423, 20);
            invaders[3].setPosition(590, 20);
            invaders[4].setPosition(140, 143);
            invaders[5].setPosition(540, 143);
            invaders[6].setPosition(240, 246);
            invaders[7].setPosition(440, 246);
            invaders[8].setPosition(340, 349);
            invaders[9].setPosition(-110, -110);

        break;
        case 3:
            invaders[0].setPosition(110, 30);
            invaders[1].setPosition(360, 170);
            invaders[2].setPosition(235, 100);
            invaders[3].setPosition(110, 310);
            invaders[4].setPosition(610, 310);
            invaders[5].setPosition(235, 240);
            invaders[6].setPosition(485, 100);
            invaders[7].setPosition(485, 240);
            invaders[8].setPosition(610, 30);
            invaders[9].setPosition(-110, -110);
            break;

    }

}



void start_game()
{
    srand(time(0));
    RenderWindow window(VideoMode(780, 780), title);
    Clock clock;
    float timer=0;
    ScoreData scoreData = loadScore();
    bool pausegame = false;
    Font font;
    cout << "Enter your playername "<<endl;
    string playername;
    getline(cin, playername);
    scoreData.playername = playername;

        font.loadFromFile("Pencil Child.otf");
        RectangleShape pauseScreen(Vector2f(400, 200));
        pauseScreen.setFillColor(Color(0, 0, 0, 128));
        pauseScreen.setPosition(190, 290);

        Text pausedText("Game Paused", font, 32);
        pausedText.setPosition(240, 320);
        
        Text resumeText("Resume Game", font, 24);
        resumeText.setPosition(270, 380);
		resumeText.setFillColor(sf::Color::Red);

        Text quitText("Quit Game", font, 24);
        quitText.setPosition(290, 420);
        
        
	    while (window.isOpen())
	    {
    
        float time = clock.getElapsedTime().asSeconds(); 
        clock.restart();
        timer += time;  
        // cout<<time<<endl;
        bool invaderdestroy = true;

	 	Event e;
        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
		       if (e.type == Event::KeyPressed)
	                {
                    if (e.key.code == Keyboard::Escape) // If Escape key is pressed
                    {
                        pausegame = true;
                    }
                }
	     }
		if (pausegame)
        {
                window.draw(pauseScreen);
                window.draw(pausedText);
                window.draw(resumeText);
                window.draw(quitText);
                window.display();

				bool resumeselected=true;
                while (pausegame)
                {
                    Event event;
                    while (window.pollEvent(event))
                    {
                	     if (event.type == Event::Closed)
                	      {
                            window.close();
                            pausegame = false;
                	       }
                	       else if(event.type==sf::Event::KeyPressed){
                	       		if(event.key.code==sf::Keyboard::Up || event.key.code == sf::Keyboard::Down){
                		   		resumeselected=!resumeselected;
   						   		if (resumeselected)
        						{
        						    resumeText.setFillColor(sf::Color::Red);
           							 quitText.setFillColor(sf::Color::White);
        						}
       					     	 else
        						{
            						resumeText.setFillColor(sf::Color::White);
            						quitText.setFillColor(sf::Color::Red);
        						}				
          
                   			}
                   			else if (event.key.code == sf::Keyboard::Enter){
                   				if(resumeselected) {
                   				pausegame = false;
                   				}    
                   				else {
                    			window.close();
                                pausegame = false;
                   				}
                  			}
                     
                    	}
                  
                    
                }
  		window.draw(pauseScreen);
        window.draw(pausedText);
        window.draw(resumeText);
        window.draw(quitText);
        window.display();
   
                }
                 
                
   }// if game paused
            else
            {
          
		if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
  	          p->move("l");    // Player will move to left
		if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
  	          p->move("r");  //player will move to right
		if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
  	          p->move("u");    //playet will move upwards
		if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
  	          p->move("d");  //player will move downwards
  		  if (Keyboard::isKeyPressed(Keyboard::Space)) 
  	          p->fire();
    
   


for (int i = 0; i < 10; i++) {
    sf::FloatRect playerbound = p->sprite.getGlobalBounds();
    sf::FloatRect invaderbound = invaders[i].sprite.getGlobalBounds();

    // Check for collision between player and invader
    if (playerbound.left < invaderbound.left + invaderbound.width &&
        playerbound.left + playerbound.width > invaderbound.left &&
        playerbound.top < invaderbound.top + invaderbound.height &&
        playerbound.top + playerbound.height > invaderbound.top) {
        
       window.close();
    }


    if (invaders[i].isDestroyed()) {
        destroyedInvaders++;
        score += 10;
            }
score += 10;
}

Text destroyedInvadersText("Destroyed Invaders: " + to_string(destroyedInvaders), font, 18);
destroyedInvadersText.setPosition(10, 10);

Text scoreText("Score: " + to_string(score), font, 18);
scoreText.setPosition(10, 30);

Text livesText("Lives: " + to_string(3), font, 18);
livesText.setPosition(10, 50);

	////////////////////////////////////////////////
	/////  Call your functions here            ////
	//////////////////////////////////////////////

	window.clear(Color::Black); //clears the screen
	window.draw(background);  // setting background
	window.draw(p->sprite);   // setting player on screen



 


	    window.clear();
        window.draw(background);
        window.draw(p->sprite);



for (int i = 0; i < 10; i++) {
    invaders[i].dropBomb();
    invaders[i].updateBomb();
    
    window.draw(invaders[i].bomb.sprite);
    
    window.draw(invaders[i].sprite);
}         
                
	for (int i = 0; i < p->bullet_count; i++) {
       window.draw(p->bullets[i].sprite);
    }  
    p->update_bullets(invaders);

window.draw(destroyedInvadersText);
window.draw(scoreText);
window.draw(livesText);
window.display();  //Displying all the sprites
 


    		}

		}
            scoreData.score = score;
            saveScore(scoreData);
        
}

};