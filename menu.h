// Huzaifa Nasir
// 22I-1053
// CS_A
// Project
#include "game.h"
class Menu{
public:

Menu()
{

}

void display_menu()

{


        // Create the menu window
        sf::RenderWindow window(sf::VideoMode(700, 1000), "Menu");


		  sf::Texture background_texture;
        if (!background_texture.loadFromFile("img/background_1.png")) {
            // Handle error loading texture
            cout<<"Error menu "<<endl<<endl;
        }

        // Create the background sprite and set its texture
        sf::Sprite background_sprite(background_texture);
         background_sprite.setPosition(0, 0);
        
        
        // Define the menu options
        sf::Font font;
        font.loadFromFile("Pencil Child.otf"); 
	
		// makes the button of start_select game
        sf::Text start_opt;
        start_opt.setFont(font);
        start_opt.setString("Start Game");
        start_opt.setCharacterSize(100);
        start_opt.setFillColor(sf::Color::White);
        start_opt.setPosition(80, 200);

		sf::Text inst_opt;
        inst_opt.setFont(font);
        inst_opt.setString("Instructions");
        inst_opt.setCharacterSize(100);
        inst_opt.setFillColor(sf::Color::White);
        inst_opt.setPosition(80, 400);

		sf::Text high_opt;
        high_opt.setFont(font);
        high_opt.setString("High Score");
        high_opt.setCharacterSize(100);
        high_opt.setFillColor(sf::Color::White);
        high_opt.setPosition(80, 600);
        
		//makes the button of quit
        sf::Text quit_opt;
        quit_opt.setFont(font);
        quit_opt.setString("Quit");
        quit_opt.setCharacterSize(100);
        quit_opt.setFillColor(sf::Color::White);
        quit_opt.setPosition(80, 800);

   
        bool start_select = true; // Indicates whether "Start Game" is currently selected
  		bool inst_select=false;
  		bool high_select=false;
  		bool quit_select=false;
  // Loop until the window is closed
while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                if (start_select) {
                    quit_select = true;
                    start_select = false;
                } else if (inst_select) {
                    start_select = true;
                    inst_select = false;
                } else if (high_select) {
                    inst_select = true;
                    high_select = false;
                } else{
                	high_select=true;
                	quit_select=false;
                }
             
            } else if (event.key.code == sf::Keyboard::Down) {
                if (start_select) {
                    inst_select = true;
                    start_select = false;
                } else if (inst_select) {
                    high_select = true;
                    inst_select = false;
                } else if (high_select) {
                    quit_select = true;
                    high_select = false;
                }
                else{
                	start_select=true;
                	quit_select=false;
                }
            }
           else if (event.key.code == sf::Keyboard::Enter) {
                if (start_select) {
                    Game game;
                    window.close();
                    game.start_game();
                }
        else if (inst_select) {
            // Open the instruction window
            sf::RenderWindow instructionwindow(sf::VideoMode(800, 600), "Instructions");
            bool instwindowopen = true;
            sf::Texture backgroundTexture1;
            if (!backgroundTexture1.loadFromFile("img/instback.jpg"))
            {
            cout << "Error background" << endl<<endl;
            return ; 
            }
            sf::Sprite backgroundSprite(backgroundTexture1);
            sf::Text instruction;
            instruction.setFont(font);
            instruction.setCharacterSize(24);
            instruction.setString("\n     Game Instructions:\n\n  - Use the arrow keys to move the player spaceship.\n  - Press the spacebar to shoot lasers.\n  - Avoid collision with the invaders.\n  - Your goal is to destroy all the invaders.\n\n  Press Escape to exit this window.");

            instruction.setPosition(100, 100);

            while (instwindowopen) {
                sf::Event instructionEvent;
                while (instructionwindow.pollEvent(instructionEvent)) {
                    if (instructionEvent.type == sf::Event::Closed) {
                        instructionwindow.close();
                        instwindowopen = false;
                    }
                    else if (instructionEvent.type == sf::Event::KeyPressed) {
                        if (instructionEvent.key.code == sf::Keyboard::Escape) {
                            instructionwindow.close();
                            instwindowopen = false;
                        }
                    }
                }

                instructionwindow.clear();
                instructionwindow.draw(backgroundSprite);
                instructionwindow.draw(instruction);
                instructionwindow.display();
            }
        }
                else if (high_select) {
sf::RenderWindow highwindow(sf::VideoMode(800, 600), "High Score");
bool highwindowopen = true;
sf::Texture backgroundTexture;
if (!backgroundTexture.loadFromFile("img/highback.jpg"))
{
    cout << "Error background" << endl<<endl;
    return ; 
}
sf::Sprite backgroundSprite(backgroundTexture);
sf::Text highscore;
highscore.setFont(font);
highscore.setCharacterSize(24);
highscore.setString(" \n\n");
highscore.setPosition(100, 100);

ifstream file("score.txt");
if (file.is_open())
{
    struct Score
    {
        string name;
        int score;
    };

    Score topScores[3]; // Array to store the top three scores
    for (int i = 0; i < 3; i++)
    {
        topScores[i].score = -1; // Initialize scores to -1
    }

    string name;
    int score;
    while (file >> name >> score)//it reads the file untill whole file is read
    {
        for (int i = 0; i < 3; i++)
        {
            if (score > topScores[i].score)
            {
                // Shift scores down and insert the new score at the current position
                for (int b = 2; b > i; b--)
                {
                    topScores[b] = topScores[b - 1];
                }
                topScores[i].name = name;
                topScores[i].score = score;
                break;
            }
        }
    }
    file.close();

    // Display the top scores in descending order
    for (int i = 0; i < 3; i++)
    {
        if (topScores[i].score != -1)
        {
            highscore.setString(highscore.getString() +"\t"+ topScores[i].name + "\t" + to_string(topScores[i].score) + "\n\n\n\n\n");
        }
    }
}
else
{
    cout << "Error open score file" << endl<<endl;
}

while (highwindowopen)
{
    sf::Event highEvent;
    while (highwindow.pollEvent(highEvent))
    {
        if (highEvent.type == sf::Event::Closed)
        {
            highwindow.close();
            highwindowopen = false;
        }
        else if (highEvent.type == sf::Event::KeyPressed)
        {
            if (highEvent.key.code == sf::Keyboard::Escape)
            {
                highwindow.close();
                highwindowopen = false;
            }
        }
    }

    highwindow.clear();
    highwindow.draw(backgroundSprite);
    highwindow.draw(highscore);
    highwindow.display();
}

                }
                else {
                    window.close();
                }
            }
        }
    }// window poll event ends

    // Update the appearance of the options based on the currently selected option
    if (start_select) {
        start_opt.setFillColor(sf::Color::Red);
        inst_opt.setFillColor(sf::Color::White);
        high_opt.setFillColor(sf::Color::White);
        quit_opt.setFillColor(sf::Color::White);
    }
     else if (inst_select) {
        start_opt.setFillColor(sf::Color::White);
        inst_opt.setFillColor(sf::Color::Red);
        high_opt.setFillColor(sf::Color::White);
        quit_opt.setFillColor(sf::Color::White);
    }
    else if (high_select) {
        start_opt.setFillColor(sf::Color::White);
        inst_opt.setFillColor(sf::Color::White);
        high_opt.setFillColor(sf::Color::Red);
        quit_opt.setFillColor(sf::Color::White);
    }
    else if (quit_select) {
        start_opt.setFillColor(sf::Color::White);
        inst_opt.setFillColor(sf::Color::White);
        high_opt.setFillColor(sf::Color::White);
        quit_opt.setFillColor(sf::Color::Red);
    }

    // Clear the window and draw the options
    window.clear();
    window.draw(background_sprite);
    window.draw(start_opt);
    window.draw(inst_opt);
    window.draw(quit_opt);
    window.draw(high_opt);
    window.display();
}//while window is open ends
    

}// display menu ends

};
