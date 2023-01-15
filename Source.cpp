#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <ctime>
#include <time.h>
#include<fstream>

using namespace std;
class Game {
protected:
	int tries;
public:
	static int max_tries;
	static int losses;
	static int wins;
	static int coins;
	static int hints;
	int isLost() {
		if (tries > max_tries) {
			return 1;
		}
		else {
			return 0;
		}
	}
};

int Game::max_tries = 6;
int Game::wins = 0;
int Game::losses = 0;
int Game::coins = 0;
int Game::hints = 0;

class Hangman :public Game {
private:
	string correctString;
	string guessedString;
	string originalString;
	char list[50];
public:
	Hangman() {
		tries = 0;
	}

	int getTries() {
		return tries;
	}
	void setTries(int number) {
		tries = number;
	}
	void increaseTries() {
		setTries(getTries() + 1);
	}
	string getCorrectString() {
		return correctString;
	}
	string getOriginalString() {
		return originalString;
	}
	void setCorrectString(string word) {
		correctString = word;
		originalString = word;
	}
	string getGuessedString() {
		return guessedString;
	}
	int removespace() {
		int i = 0;
		for (i;i < correctString.length();i++) {
			if (correctString[i] == ' ') {
				correctString.erase(correctString.begin() + i);
				i--;
			}
		}
		return i;
	}
	void setGuessedString() {
		guessedString = "";
		int i = removespace();
		
		for (int i = 0; i < correctString.length(); i++) {
			if (originalString[i] == ' ') {
				guessedString = guessedString + " " + "_";
			}
			else if (i == correctString.length() - 1) {
				guessedString = guessedString + "_";
			}
			else {
				guessedString = guessedString + "_";
			}
			
		}
	}
	void setGuessedString(string word) {
		guessedString = word;
	}

	bool isWon() {
		if (guessedString == correctString) {
			return true;
		}
		else {
			return false;
		}
	}
	int rewards(int tries) {
		int r = tries;
		if (tries == 0) {
			return 20;
		}
		else if (tries == 1) {
			return 18;
		}
		else if (tries == 2) {
			return 15;
		}
		else if (tries == 3) {
			return 10;
		}
		else if (tries == 4) {
			return 8;
		}
		else if (tries == 5) {
			return 5;
		}
		else if (tries == 6) {
			return 1;
		}
	}
	bool guessWord(char letter) {
		bool correctness = false;
		int sizeOfString = correctString.length();
		for (int i = 0; i < correctString.length(); i++) {
			if (letter == correctString[i]) {
				
				guessedString = guessedString.substr(0, i) + correctString.substr(i, 1) + guessedString.substr(i + 1, sizeOfString - (i + 1));
				
				correctness = true;
			}
		}
		return correctness;
	}
};
int main()
{
	srand(time(0));
	Hangman hg;

	bool playing = false;

	int positions[20][2];
	bool choice[40];
	for (int i = 0; i < 40; i++) {
		choice[i] = false;
	}
	sf::RenderWindow window(sf::VideoMode(900, 900), "Hindow!");

	sf::Texture texture;
	if (!texture.loadFromFile("images\\image.jpg"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);

	sf::Font font;
	font.loadFromFile("Fonts\\Nexa.ttf");

	sf::Font font1;
	font1.loadFromFile("Fonts\\Montserrat-Light.otf");

	sf::SoundBuffer buffer;
	buffer.loadFromFile("Audio\\Wrong-answer.wav");
	sf::Sound sound;
	sound.setBuffer(buffer);

	sf::SoundBuffer buffer2;
	if (!buffer2.loadFromFile("Audio\\wrong.wav"))
		return -1;
	sf::Sound soundwrong;
	soundwrong.setBuffer(buffer2);

	sf::SoundBuffer buffer3;
	if (!buffer3.loadFromFile("Audio\\correct.wav"))
		return -1;
	sf::Sound soundcorrect;
	soundcorrect.setBuffer(buffer3);

	// Create a text
	sf::Text text("Hangman", font);
	text.setCharacterSize(120);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(220, 0);

	sf::Text text1("Play", font);
	text1.setCharacterSize(90);
	text1.setStyle(sf::Text::Bold);
	text1.setFillColor(sf::Color::Cyan);
	sf::IntRect r1(320, 500, 250, 90);
	text1.setPosition(320, 500);

	sf::Text text2("Rules", font);
	text2.setCharacterSize(90);
	text2.setStyle(sf::Text::Bold);
	text2.setFillColor(sf::Color::Cyan);
	sf::IntRect r2(320, 600, 250, 90);
	text2.setPosition(320, 600);

	sf::Text text3("Close", font);
	text3.setCharacterSize(90);
	text3.setStyle(sf::Text::Bold);
	text3.setFillColor(sf::Color::Red);
	sf::IntRect r3(320, 700, 250, 90);
	text3.setPosition(320, 700);

	sf::Text text4(hg.getGuessedString(), font1);
	text4.setCharacterSize(60);
	text4.setStyle(sf::Text::Bold);
	text4.setFillColor(sf::Color::White);
	text4.setPosition(1000, 0);

	sf::Text text5("Guess the word", font);
	text5.setCharacterSize(80);
	text5.setStyle(sf::Text::Bold);
	text5.setFillColor(sf::Color::White);
	text5.setPosition(1000, 0);

	sf::Text text6("Rules", font);
	text6.setCharacterSize(120);
	text6.setStyle(sf::Text::Bold);
	text6.setFillColor(sf::Color::White);
	text6.setPosition(1000, 0);

	string s = "Press a key to complete the word to be guessed.\nIf the key you pressed is correct than it will be shown\n on the screen else the hangman will begin to draw.\n If the user guesses the word correctly than he/she\n will win and if hangman is fully drawn he/she\n will loose and the game continues till the word\n is guessed fully . Quit the game by clicking close\n button.";

	sf::Text text7(s, font1);
	text7.setCharacterSize(30);
	text7.setStyle(sf::Text::Bold);
	text7.setFillColor(sf::Color::White);
	text7.setPosition(1000, 0);

	sf::Text text8("Wins: " + to_string(hg.wins) + "\nLosses: " + to_string(hg.losses), font1);
	text8.setCharacterSize(70);
	text8.setStyle(sf::Text::Bold);
	text8.setFillColor(sf::Color::Green);
	text8.setPosition(1000, 00);

	sf::Text text9("Flowers", font);
	text9.setCharacterSize(60);
	text9.setStyle(sf::Text::Bold);
	text9.setFillColor(sf::Color::Red);
	sf::IntRect r4(1000, 1000, 1000, 1000);
	text9.setPosition(1000, 0);

	sf::Text text10("Countries", font);
	text10.setCharacterSize(60);
	text10.setStyle(sf::Text::Bold);
	text10.setFillColor(sf::Color::Red);
	sf::IntRect r6(1000, 1000, 1000, 1000);
	text10.setPosition(1000, 0);

	sf::Text text11("Celebrities", font);
	text11.setCharacterSize(60);
	text11.setStyle(sf::Text::Bold);
	text11.setFillColor(sf::Color::Red);
	sf::IntRect r5(1000, 1000, 1000, 1000);
	text11.setPosition(1000, 0);

	sf::Text text12("Movies", font);
	text12.setCharacterSize(60);
	text12.setStyle(sf::Text::Bold);
	text12.setFillColor(sf::Color::Red);
	sf::IntRect r8(1000, 1000, 1000, 1000);
	text12.setPosition(1000, 0);

	sf::Text text13("Household", font);
	text13.setCharacterSize(60);
	text13.setStyle(sf::Text::Bold);
	text13.setFillColor(sf::Color::Red);
	sf::IntRect r7(1000, 1000, 1000, 1000);
	text13.setPosition(1000, 0);

	sf::Text text14("Coins:", font);
	text14.setCharacterSize(60);
	text14.setStyle(sf::Text::Bold);
	text14.setFillColor(sf::Color::Yellow);
	text14.setPosition(1000, 0);

	sf::Text text15("Hints:", font);
	text15.setCharacterSize(60);
	text15.setStyle(sf::Text::Bold);
	text15.setFillColor(sf::Color::Yellow);
	sf::IntRect r9(600, 0, 150, 60);
	text15.setPosition(1000, 0);

	//Hangman shape
	sf::CircleShape Head(30);
	Head.setTexture(&texture);
	Head.setOutlineColor(sf::Color::Black);
	Head.setOutlineThickness(5);
	Head.setPosition(410, 200);
	
	sf::RectangleShape Body;
	Body.setSize(sf::Vector2f(5, 100));
	Body.setTexture(&texture);
	Body.setOutlineColor(sf::Color::Black);
	Body.setOutlineThickness(5);
	Body.setPosition(437, 270);//437,270

	sf::RectangleShape Lhand;
	Lhand.setSize(sf::Vector2f(5, 50));
	Lhand.setTexture(&texture);
	Lhand.setRotation(45);
	Lhand.setOutlineColor(sf::Color::Black);
	Lhand.setOutlineThickness(5);
	Lhand.setPosition(427, 295);//427,295

	sf::RectangleShape Rhand;
	Rhand.setSize(sf::Vector2f(5, 50));
	Rhand.setTexture(&texture);
	Rhand.setPosition(427, 295);
	Rhand.setRotation(315);
	Rhand.setOutlineColor(sf::Color::Black);
	Rhand.setOutlineThickness(5);
	Rhand.setPosition(450, 297);//450,297

	sf::RectangleShape Lleg;
	Lleg.setSize(sf::Vector2f(5, 75));
	Lleg.setTexture(&texture);
	Lleg.setRotation(15);
	Lleg.setOutlineColor(sf::Color::Black);
	Lleg.setOutlineThickness(5);
	Lleg.setPosition(427, 365);//427,365

	sf::RectangleShape Rleg;
	Rleg.setSize(sf::Vector2f(5, 75));
	Rleg.setTexture(&texture);
	Rleg.setRotation(345);
	Rleg.setOutlineColor(sf::Color::Black);
	Rleg.setOutlineThickness(5);
	Rleg.setPosition(450, 367);//450,367

	sf::RectangleShape Bsupport;
	Bsupport.setSize(sf::Vector2f(5, 125));
	Bsupport.setTexture(&texture);
	Bsupport.setOutlineColor(sf::Color::Black);
	Bsupport.setOutlineThickness(5);
	Bsupport.setPosition(300, 340);//300,340

	sf::RectangleShape Usupport;
	Usupport.setSize(sf::Vector2f(5, 120));
	Usupport.setTexture(&texture);
	Usupport.setOutlineColor(sf::Color::Black);
	Usupport.setOutlineThickness(5);
	Usupport.setPosition(300, 210);//300,210

	sf::RectangleShape Hsupport;
	Hsupport.setSize(sf::Vector2f(5, 125));
	Hsupport.setTexture(&texture);
	Hsupport.setRotation(270);
	Hsupport.setOutlineColor(sf::Color::Black);
	Hsupport.setOutlineThickness(5);
	Hsupport.setPosition(305, 278);//300,277

	positions[0][0] = 437; positions[0][1] = 270;
	positions[1][0] = 427; positions[1][1] = 295;
	positions[2][0] = 450; positions[2][1] = 297;
	positions[3][0] = 427; positions[3][1] = 365;
	positions[4][0] = 450; positions[4][1] = 367;
	positions[5][0] = 300; positions[5][1] = 340;
	positions[6][0] = 300; positions[6][1] = 210;
	positions[7][0] = 305; positions[7][1] = 278;
	positions[8][0] = 410; positions[8][1] = 200;

	soundcorrect.setVolume(5.0f);
	soundwrong.setVolume(1.0f);

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			//to perform a function when the mouse button is clicked
			if (event.type == sf::Event::MouseButtonPressed) {
				if (r1.contains(event.mouseButton.x, event.mouseButton.y)) {
					
					std::cout << "Play button pressed";
					Body.setPosition(1000, 0);
					Lhand.setPosition(1000, 0);
					Rhand.setPosition(1000, 0);
					Lleg.setPosition(1000, 0);
					Rleg.setPosition(1000, 0);
					Bsupport.setPosition(1000, 0);
					Usupport.setPosition(1000, 0);
					Hsupport.setPosition(1000, 0);
					Head.setPosition(1000,0);
					text.setPosition(1000, 0);
					text1.setPosition(1000,0);
					r1.left = 1000;
					r2.left = 1000;
					text3.setPosition(1000,0);
					r3.left = 1000;
					r4.left = 250, r4.top = 150, r4.width = 400, r4.height = 90;
					r5.left = 250, r5.top = 450, r5.width = 600, r5.height = 90;
					r6.left = 250, r6.top = 300, r6.width = 400, r6.height = 90;
					r7.left = 250, r7.top = 750, r7.width = 400, r7.height = 90;
					r8.left = 250, r8.top = 600, r8.width = 300, r8.height = 90;
					text8.setPosition(1000, 0);
					text6.setPosition(1000, 0);
					text7.setPosition(1000,0);

					text9.setPosition(250, 150);
					text9.setCharacterSize(90);
					text9.setStyle(sf::Text::Bold);
					text9.setFillColor(sf::Color::Red);

					text10.setPosition(250, 300);
					text10.setCharacterSize(90);
					text10.setStyle(sf::Text::Bold);
					text10.setFillColor(sf::Color::Red);

					text11.setPosition(250, 450);
					text11.setCharacterSize(90);
					text11.setStyle(sf::Text::Bold);
					text11.setFillColor(sf::Color::Red);

					text12.setPosition(250, 600);
					text12.setCharacterSize(90);
					text12.setStyle(sf::Text::Bold);
					text12.setFillColor(sf::Color::Red);

					text13.setPosition(250, 750);
					text13.setCharacterSize(90);
					text13.setStyle(sf::Text::Bold);
					text13.setFillColor(sf::Color::Red);

					text14.setPosition(1000, 0);
					text15.setPosition(1000, 0);

					text2.setString("Choose a topic:");
					text2.setStyle(sf::Text::Underlined);
					text2.setFillColor(sf::Color::Cyan);
					text2.setPosition(150, 0);
					text4.setPosition(1000, 0);
					text5.setPosition(1000, 0);

					soundcorrect.play();

				}
				if (r2.contains(event.mouseButton.x, event.mouseButton.y)) {
					std::cout << "Rules Button pressed\n";
					Body.setPosition(1000, 0);
					Lhand.setPosition(1000, 0);
					Rhand.setPosition(1000, 0);
					Lleg.setPosition(1000, 0);
					Rleg.setPosition(1000, 0);
					Bsupport.setPosition(1000, 0);
					Usupport.setPosition(1000, 0);
					Hsupport.setPosition(1000, 0);
					Head.setPosition(1000, 0);
					text2.setPosition(1000, 0);
					r2.left = 1000;
					text3.setPosition(1000, 0);
					r3.left = 1000;
					text6.setPosition(310, 150);
					text7.setPosition(50, 300);
					text1.setPosition(370, 650);
					r1.top = 650;
					soundcorrect.play();

				}
				if (r3.contains(event.mouseButton.x, event.mouseButton.y)) {
					std::cout << "Exit Button pressed\n";
					sound.play();
					window.close();
				}
				
				if (r4.contains(event.mouseButton.x, event.mouseButton.y)) {
					int randnum = (rand() % 75) + 1;
					int counter = 1;
					string line, word;
					ifstream file("Words\\Flower.txt");
					while (getline(file, line)) {
						if (randnum == counter) {
							word = line;
							break;
						}
						counter++;
					}
					hg.setCorrectString(word);
					hg.setGuessedString();
					hg.setTries(0);
					text4.setString(hg.getGuessedString());
					for (int i = 0;i < 40;i++) {
						choice[i] = false;
					}
					std::cout << "Picked Flowers";
					Body.setPosition(1000, 0);
					Lhand.setPosition(1000, 0);
					Rhand.setPosition(1000, 0);
					Lleg.setPosition(1000, 0);
					Rleg.setPosition(1000, 0);
					Bsupport.setPosition(1000, 0);
					Usupport.setPosition(1000, 0);
					Hsupport.setPosition(1000, 0);
					Head.setPosition(1000, 0);
					text.setPosition(1000, 0);
					text1.setPosition(1000, 0);
					text2.setPosition(1000, 0);
					r1.left = 1000;
					r2.left = 1000;
					text3.setPosition(1000, 0);
					r3.left = 1000;
					r4.left = 1000, r4.top = 1000, r4.width = 1000, r4.height = 1000;
					r5.left = 1000, r5.top = 1000, r5.width = 1000, r5.height = 1000;
					r6.left = 1000, r6.top = 1000, r6.width = 1000, r6.height = 1000;
					r7.left = 1000, r7.top = 1000, r7.width = 1000, r7.height = 1000;
					r8.left = 1000, r8.top = 1000, r8.width = 1000, r8.height = 1000;
					text6.setPosition(1000,0);
					text7.setPosition(1000, 0);
					text8.setPosition(1000, 0);
					text9.setPosition(0, 50);
					text9.setCharacterSize(100);
					text9.setFillColor(sf::Color::Cyan);
					text10.setPosition(1000, 0);
					text11.setPosition(1000, 0);
					text12.setPosition(1000, 0);
					text13.setPosition(1000, 0);
					text14.setPosition(200, 0);
					text15.setPosition(600, 0);
					text4.setPosition(100, 700);
					text4.setCharacterSize(90);
					text5.setPosition(150, 500);
					soundcorrect.play();
					playing = true;
				}
				if (r5.contains(event.mouseButton.x, event.mouseButton.y)) {
					int randnum = (rand() % 91) + 1;
						int counter = 1;
						string line, word;
						ifstream file("Words\\Celebrities.txt");
						while (getline(file, line)) {
							if (randnum == counter) {
								word = line;
									break;
							}
							counter++;
						}
					hg.setCorrectString(word);
					hg.setGuessedString();
					hg.setTries(0);
					text4.setString(hg.getGuessedString());
					for (int i = 0;i < 40;i++) {
						choice[i] = false;
					}
					std::cout << "Picked Celebrities";
					Body.setPosition(1000, 0);
					Lhand.setPosition(1000, 0);
					Rhand.setPosition(1000, 0);
					Lleg.setPosition(1000, 0);
					Rleg.setPosition(1000, 0);
					Bsupport.setPosition(1000, 0);
					Usupport.setPosition(1000, 0);
					Hsupport.setPosition(1000, 0);
					Head.setPosition(1000, 0);
					text.setPosition(1000, 0);
					text1.setPosition(1000, 0);
					text2.setPosition(1000, 0);
					r1.left = 1000;
					r2.left = 1000;
					text3.setPosition(1000, 0);
					r3.left = 1000;
					r4.left = 1000, r4.top = 1000, r4.width = 1000, r4.height = 1000;
					r5.left = 1000, r5.top = 1000, r5.width = 1000, r5.height = 1000;
					r6.left = 1000, r6.top = 1000, r6.width = 1000, r6.height = 1000;
					r7.left = 1000, r7.top = 1000, r7.width = 1000, r7.height = 1000;
					r8.left = 1000, r8.top = 1000, r8.width = 1000, r8.height = 1000;
					text6.setPosition(1000, 0);
					text7.setPosition(1000, 0);
					text8.setPosition(1000, 0);
					text9.setPosition(1000, 0);
					text10.setPosition(1000, 0);
					text11.setCharacterSize(100);
					text11.setFillColor(sf::Color::Cyan);
					text11.setPosition(0, 50);
					text12.setPosition(1000, 0);
					text13.setPosition(1000, 0);
					text14.setPosition(200, 0);
					text15.setPosition(600, 0);
					text4.setPosition(100, 700);
					text4.setCharacterSize(90);
					text5.setPosition(100, 500);
					soundcorrect.play();
					playing = true;
				}
				
				if (r6.contains(event.mouseButton.x, event.mouseButton.y)) {
					int randnum = (rand() % 91) + 1;
					int counter = 1;
					string line, word;
					ifstream file("Words\\Countries.txt");
					while (getline(file, line)) {
						if (randnum == counter) {
							word = line;
							break;
						}
						counter++;
					}
					hg.setCorrectString(word);
					hg.setGuessedString();
					hg.setTries(0);
					text4.setString(hg.getGuessedString());
					for (int i = 0;i < 40;i++) {
						choice[i] = false;
					}
					std::cout << "Picked Countries";
					Body.setPosition(1000, 0);
					Lhand.setPosition(1000, 0);
					Rhand.setPosition(1000, 0);
					Lleg.setPosition(1000, 0);
					Rleg.setPosition(1000, 0);
					Bsupport.setPosition(1000, 0);
					Usupport.setPosition(1000, 0);
					Hsupport.setPosition(1000, 0);
					Head.setPosition(1000, 0);
					text.setPosition(1000, 0);
					text1.setPosition(1000, 0);
					text2.setPosition(1000, 0);
					r1.left = 1000;
					r2.left = 1000;
					text3.setPosition(1000, 0);
					r3.left = 1000;
					r4.left = 1000, r4.top = 1000, r4.width = 1000, r4.height = 1000;
					r5.left = 1000, r5.top = 1000, r5.width = 1000, r5.height = 1000;
					r6.left = 1000, r6.top = 1000, r6.width = 1000, r6.height = 1000;
					r7.left = 1000, r7.top = 1000, r7.width = 1000, r7.height = 1000;
					r8.left = 1000, r8.top = 1000, r8.width = 1000, r8.height = 1000;
					text6.setPosition(1000, 0);
					text7.setPosition(1000, 0);
					text8.setPosition(1000, 0);
					text9.setPosition(1000, 0);
					text10.setPosition(0, 50);
					text10.setCharacterSize(100);
					text10.setFillColor(sf::Color::Cyan);
					text11.setPosition(1000, 0);
					text12.setPosition(1000, 0);
					text13.setPosition(1000, 0);
					text14.setPosition(200, 0);
					text15.setPosition(600, 0);
					text4.setPosition(100, 700);
					text4.setCharacterSize(90);
					text5.setPosition(100, 500);
					soundcorrect.play();
					playing = true;
				}
				
				if (r7.contains(event.mouseButton.x, event.mouseButton.y)) {
					int randnum = (rand() % 91) + 1;
					int counter = 1;
					string line, word;
					ifstream file("Words\\Household.txt");
					while (getline(file, line)) {
						if (randnum == counter) {
							word = line;
							break;
						}
						counter++;
					}
					hg.setCorrectString(word);
					hg.setGuessedString();
					hg.setTries(0);
					text4.setString(hg.getGuessedString());
					for (int i = 0;i < 40;i++) {
						choice[i] = false;
					}
					std::cout << "Picked Household";
					Body.setPosition(1000, 0);
					Lhand.setPosition(1000, 0);
					Rhand.setPosition(1000, 0);
					Lleg.setPosition(1000, 0);
					Rleg.setPosition(1000, 0);
					Bsupport.setPosition(1000, 0);
					Usupport.setPosition(1000, 0);
					Hsupport.setPosition(1000, 0);
					Head.setPosition(1000, 0);
					text.setPosition(1000, 0);
					text1.setPosition(1000, 0);
					text2.setPosition(1000, 0);
					r1.left = 1000;
					r2.left = 1000;
					text3.setPosition(1000, 0);
					r3.left = 1000;
					r4.left = 1000, r4.top = 1000, r4.width = 1000, r4.height = 1000;
					r5.left = 1000, r5.top = 1000, r5.width = 1000, r5.height = 1000;
					r6.left = 1000, r6.top = 1000, r6.width = 1000, r6.height = 1000;
					r7.left = 1000, r7.top = 1000, r7.width = 1000, r7.height = 1000;
					r8.left = 1000, r8.top = 1000, r8.width = 1000, r8.height = 1000;
					text6.setPosition(1000, 0);
					text7.setPosition(1000, 0);
					text8.setPosition(1000, 0);
					text9.setPosition(1000, 0);
					text10.setPosition(1000, 0);
					text13.setCharacterSize(100);
					text13.setFillColor(sf::Color::Cyan);
					text11.setPosition(1000, 0);
					text12.setPosition(1000, 0);
					text13.setPosition(0, 50);
					text14.setPosition(200, 0);
					text15.setPosition(600, 0);
					text4.setPosition(100, 700);
					text4.setCharacterSize(90);
					text5.setPosition(100, 500);
					soundcorrect.play();
					playing = true;
				}
				if (r8.contains(event.mouseButton.x, event.mouseButton.y)) {
					int randnum = (rand() % 40) + 1;
					int counter = 1;
					string line, word;
					ifstream file("Words\\Movies.txt");
					while (getline(file, line)) {
						if (randnum == counter) {
							word = line;
							break;
						}
						counter++;
					}
					hg.setCorrectString(word);
					hg.setGuessedString();
					hg.setTries(0);
					text4.setString(hg.getGuessedString());
					for (int i = 0;i < 40;i++) {
						choice[i] = false;
					}
					std::cout << "Picked Movies";
					Body.setPosition(1000, 0);
					Lhand.setPosition(1000, 0);
					Rhand.setPosition(1000, 0);
					Lleg.setPosition(1000, 0);
					Rleg.setPosition(1000, 0);
					Bsupport.setPosition(1000, 0);
					Usupport.setPosition(1000, 0);
					Hsupport.setPosition(1000, 0);
					Head.setPosition(1000, 0);
					text.setPosition(1000, 0);
					text1.setPosition(1000, 0);
					text2.setPosition(1000, 0);
					r1.left = 1000;
					r2.left = 1000;
					text3.setPosition(1000, 0);
					r3.left = 1000;
					r4.left = 1000, r4.top = 1000, r4.width = 1000, r4.height = 1000;
					r5.left = 1000, r5.top = 1000, r5.width = 1000, r5.height = 1000;
					r6.left = 1000, r6.top = 1000, r6.width = 1000, r6.height = 1000;
					r7.left = 1000, r7.top = 1000, r7.width = 1000, r7.height = 1000;
					r8.left = 1000, r8.top = 1000, r8.width = 1000, r8.height = 1000;
					text6.setPosition(1000, 0);
					text7.setPosition(1000, 0);
					text8.setPosition(1000, 0);
					text9.setPosition(1000, 0);
					text10.setPosition(1000, 0);
					text12.setCharacterSize(100);
					text12.setFillColor(sf::Color::Cyan);
					text11.setPosition(1000, 0);
					text13.setPosition(1000, 0);
					text14.setPosition(200, 0);
					text15.setPosition(600, 0);
					text12.setPosition(0, 50);
					text4.setPosition(100, 700);
					text4.setCharacterSize(90);
					text5.setPosition(100, 500);
					soundcorrect.play();
					playing = true;
				}
				if (r9.contains(event.mouseButton.x, event.mouseButton.y)) {
					if (hg.coins >= 10) {
						char letter = 0, char_array[50];
						string word = hg.getCorrectString();
						int count = 0, len, pos, counter = 0, list[50];

						for (int i = 0;i < 50;i++) {
							list[i] = 0;
						}

						// remove spaces
						for (int i = 0;word[i];i++) {
							if (word[i] != ' ') {
								word[count++] = word[i];
							}
						}
						word[count] = '\0';
						// 

						strcpy_s(char_array, word.c_str());

						// find the random letter
						len = word.length();
						pos = (rand() % len) + 1;
						//

						// to always get new hints
						for (int i = 0;i < counter;i++) {
							if (list[i] == pos) {
								pos = (rand() % len) + 1;
								i = 0;
							}
						}
						counter++;
						//

						for (int i = 0;i < len;i++) {
							if (i == pos) {
								letter = char_array[i];
							}
						}

						hg.guessWord(letter);
						text4.setString(hg.getGuessedString());
						soundcorrect.play();
						playing = true;
						hg.hints++;
						hg.coins = hg.coins - 10;
						text14.setString("Coins: " + to_string(hg.coins));
						text15.setString("Hints: " + to_string(hg.hints));
						text15.setCharacterSize(60);
						text15.setPosition(600, 0);

					}
					else {
						soundwrong.play();
					}
					
				}
			}
			
			
			if (event.type == sf::Event::TextEntered)
			{
				if (playing) {
					if (event.text.unicode < 128)
						if (isalnum(static_cast<char>(event.text.unicode))) {

							std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
							std::cout << "ASCII character typed: " << event.text.unicode << std::endl;
							if (choice[toupper(event.text.unicode) - 65] == true) {
								std::cout << "Already guessed\n";
							}
							else {
								choice[toupper(event.text.unicode) - 65] = true;
								if (hg.guessWord((static_cast<char>(event.text.unicode)))) {
									std::cout << "Correct Choice\n";
									soundcorrect.play();
									text4.setString(hg.getGuessedString());
									if (hg.isWon()) {
										text10.setPosition(1000, 0);
										text12.setPosition(1000, 0);
										text13.setPosition(1000, 0);
										text11.setPosition(1000, 0);
										text9.setPosition(1000, 0);
										text5.setPosition(1000, 0);
										text2.setString("You Won!!!!");
										text2.setPosition(250, 50);
										text2.setFillColor(sf::Color::Green);
										text4.setCharacterSize(40);
										text4.setPosition(0,750);
										text4.setString("You guessed \"" + hg.getOriginalString() + "\"");
										playing = false;
										text1.setString("Play Again!");
										text1.setPosition(200, 500);
										r1.top = 500;
										r1.left = 200;
										r1.width = 500;
										r1.height = 90;
										r4.left = 1000, r4.top = 1000, r4.width = 1000, r4.height = 1000;
										r5.left = 1000, r5.top = 1000, r5.width = 1000, r5.height = 1000;
										r6.left = 1000, r6.top = 1000, r6.width = 1000, r6.height = 1000;
										r7.left = 1000, r7.top = 1000, r7.width = 1000, r7.height = 1000;
										r8.left = 1000, r8.top = 1000, r8.width = 1000, r8.height = 1000;
										hg.coins += hg.rewards(hg.getTries());
										hg.wins++;
										cout << "Losses=" << hg.losses << endl;
										cout << "Wins=" << hg.wins << endl;
										text6.setString("Wins: " + to_string(hg.wins) + "\nLosses: " + to_string(hg.losses));
										text6.setPosition(500, 200);
										text6.setCharacterSize(60);
										text14.setString("Coins: " + to_string(hg.coins));
									}
								}
								else {
									soundwrong.play();
									std::cout << "Wrong choice\n";
									hg.increaseTries();
									if (hg.getTries() == 1) {
										Bsupport.setPosition(positions[5][0], positions[5][1]);
									}
									if (hg.getTries() == 2) {
										Usupport.setPosition(positions[6][0], positions[6][1]);
									}
									if (hg.getTries() == 3) {
										Hsupport.setPosition(positions[7][0], positions[7][1]);
									}
									if (hg.getTries() == 4) {
										Head.setPosition(positions[8][0], positions[8][1]);
									}
									if (hg.getTries() == 5) {
										Body.setPosition(positions[0][0], positions[0][1]);
									}
									if (hg.getTries() == 6) {
										Lhand.setPosition(positions[1][0], positions[1][1]);
										Rhand.setPosition(positions[2][0], positions[2][1]);
									}
									if (hg.getTries() == 7) {
										Lleg.setPosition(positions[3][0], positions[3][1]);
										Rleg.setPosition(positions[4][0], positions[4][1]);
									}
									if (hg.isLost()) {
										text10.setPosition(1000, 0);
										text12.setPosition(1000, 0);
										text13.setPosition(1000, 0);
										text11.setPosition(1000, 0);
										text9.setPosition(1000, 0);
										text5.setPosition(1000, 0);
										text2.setString("You Lost!!!!");
										text2.setPosition(250, 50);
										text2.setFillColor(sf::Color::Red);
										text4.setCharacterSize(40);
										text4.setPosition(0, 750);
										text4.setString("You didnt guess \"" + hg.getOriginalString() + "\"");
										playing = false;
										text1.setString("Play Again!");
										text1.setPosition(200, 500);
										r1.top = 500;
										r1.left = 200;
										r1.width = 500;
										r1.height = 90;
										r4.left = 1000, r4.top = 1000, r4.width = 1000, r4.height = 1000;
										r5.left = 1000, r5.top = 1000, r5.width = 1000, r5.height = 1000;
										r6.left = 1000, r6.top = 1000, r6.width = 1000, r6.height = 1000;
										r7.left = 1000, r7.top = 1000, r7.width = 1000, r7.height = 1000;
										r8.left = 1000, r8.top = 1000, r8.width = 1000, r8.height = 1000;
										hg.losses++;
										cout << "Losses=" << hg.losses << endl;
										cout << "Wins=" << hg.wins << endl;
										text6.setString("Wins: " + to_string(hg.wins) + "\nLosses: " + to_string(hg.losses));
										text6.setPosition(500, 200);
										text6.setCharacterSize(60);
									}


								}
							}
						}
				}
			}

		}

		window.clear();
		window.draw(sprite);
		window.draw(Head);
		window.draw(text);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.draw(text4);
		window.draw(text5);
		window.draw(text6);
		window.draw(text7);
		window.draw(text8);
		window.draw(text9);
		window.draw(text10);
		window.draw(text11);
		window.draw(text12);
		window.draw(text13);
		window.draw(text14);
		window.draw(text15);
		window.draw(Body);
		window.draw(Lhand);
		window.draw(Rhand);
		window.draw(Lleg);
		window.draw(Rleg);
		window.draw(Bsupport);
		window.draw(Usupport);
		window.draw(Hsupport);

		window.display();
	}

	return 0;
}