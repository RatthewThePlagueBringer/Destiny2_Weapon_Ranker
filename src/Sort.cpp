/*#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

using namespace std;

// Used the COP3530 Module 8 Lecture & Discussion Slides
void swap(vector<tuple<string, string, pair<int, int>>>& v, int a, int b) {
	tuple<string, string, pair<int, int>> temp = v[a];
	v[a] = v[b];
	v[b] = temp;
}

int partition(vector<tuple<string, string, pair<int, int>>>& vec, int low, int high, string DPS) {

	if (DPS == "Sustained") {

		int pivot = get<2>(vec[low]).first;
		int up = low, down = high;

		while (up < down) {

			for (int j = up; j < high; j++) {

				if (get<2>(vec[up]).first > pivot) {
					break;
				}

				up++;
			}
			for (int j = high; j > low; j--) {

				if (get<2>(vec[down]).first < pivot) {
					break;
				}

				down--;
			}

			if (up < down) {
				swap(vec, up, down);
			}
		}

		swap(vec, low, down);
		return down;
	}
	
	else {

		int pivot = get<2>(vec[low]).second;
		int up = low, down = high;

		while (up < down) {

			for (int j = up; j < high; j++) {

				if (get<2>(vec[up]).second > pivot) {
					break;
				}

				up++;
			}
			for (int j = high; j > low; j--) {

				if (get<2>(vec[down]).second < pivot) {
					break;
				}

				down--;
			}
			if (up < down) {
				swap(vec, up, down);
			}
		}

		swap(vec, low, down);
		return down;
	}
}

void quickSort(vector<tuple<string, string, pair<int, int>>>& vec, int low, int high, string DPS) {

	if (low < high) {
		int pivot = partition(vec, low, high, DPS);
		quickSort(vec, low, pivot - 1, DPS);
		quickSort(vec, pivot + 1, high, DPS);
	}
}

void insertionSort(vector<tuple<string, string, pair<int, int>>>& vec, int gap, int n, string DPS) {

	if (DPS == "Sustained") {

		for (int i = gap; i < n; i++) {

			int key = get<2>(vec[i]).first;
			int j = i;

			while (j >= gap && key < get<2>(vec[j - gap]).first) {
				swap(vec, j, j - gap);
				j -= gap;
			}
		}
	}

	else {

		for (int i = gap; i < n; i++) {

			int key = get<2>(vec[i]).second;
			int j = i;

			while (j >= gap && key < get<2>(vec[j - gap]).second) {
				swap(vec, j, j - gap);
				j -= gap;
			}
		}
	}
}

void shellSort(vector<tuple<string, string, pair<int, int>>>& vec, string DPS) {

	int n = vec.size();
	int gap = n / 2;

	while (gap > 0) {

		insertionSort(vec, gap, n, DPS);

		if (gap == 2) {
			gap = 1;
		}

		else {
			gap /= 2;
		}
	}
}

// Used our COP3503 Minesweeper projects + https://www.sfml-dev.org/learn.php for SFML
void setText(sf::Text& text, float x, float y) {
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(x, y));
}

bool inCircle(float rad, float w, float h, sf::Vector2i mousePos) {

	float dist = sqrt(pow(static_cast<int>(mousePos.x) - w, 2.f) + pow(static_cast<int>(mousePos.y) - h, 2.f));

	if (dist <= rad) {
		return true;
	}

	return false;
}

int main() {

	vector<vector<tuple<string, string, pair<int, int>>>> Arsenal = {
		{{ "A", "Apple", { 156, 675 } },
	{ "A", "Banana", { 674, 798 } },
	{ "A", "Coconut", { 326, 492 } },
	{ "A", "Dragonfruit", { 798, 425 } },
	{ "A", "Eggplant", { 463, 586 } },
	{ "A", "Fig", { 891, 239 } },
	{ "A", "Grape", { 577, 658 } },
	{ "A", "Honeydew", { 342, 821 } },
	{ "A", "Kiwi", { 619, 134 } },
	{ "A", "Lemon", { 749, 393 } },
	{ "A", "Mango", { 184, 957 } }},
		{{ "B", "Apricot", { 743, 572 } },
	{ "B", "Blueberry", { 865, 726 } },
	{ "B", "Cherry", { 936, 438 } },
	{ "B", "Date", { 672, 509 } },
	{ "B", "Fig", { 578, 693 } },
	{ "B", "Grapefruit", { 251, 839 } },
	{ "B", "Honeydew", { 427, 315 } },
	{ "B", "Kiwi", { 869, 143 } },
	{ "B", "Lime", { 542, 781 } },
	{ "B", "Mango", { 384, 627 } },
		{"B", "Nectarine", {974, 358}}} };
	int catIndex = 0;

	// Screen dimensions
	float screenWidth = 1000.f, screenHeight = 1250.f;
	float borderDec = 40.f;
	float borderlessWidth = screenWidth - borderDec;
	float borderlessHeight = screenHeight - borderDec;
	float borderlessXY = borderDec / 2;

	// Button dimensions and coordinates
	float buttonRad = 140.f, buttonInc = 20.f, highlightInc = 30.f;
	float borderRad = buttonRad + buttonInc;
	float highlightRad = buttonRad + highlightInc;
	float sustX0 = screenWidth / 4;
	float burstX0 = 3 * (screenWidth / 4);
	float sustX = sustX0 - buttonRad;
	float burstX = burstX0 - buttonRad;
	float buttonY = screenHeight / 18;
	float buttonY0 = buttonY + buttonRad;

	// Best weapon text box
	float bestWidth = screenWidth / 2;
	float bestHeight = 128.f;
	float bestX = screenWidth / 4;
	float bestY = screenHeight / 3 + 128;

	// List of top weapons text box
	float listWidth = 4 * (screenWidth / 5);
	float listHeight = screenHeight / 3;
	float listX = screenWidth / 10;
	float listY = screenHeight - listHeight - screenHeight / 18;

	// Variables
	string search;
	bool showCursor = true, isValidSearch = true;
	bool showBest = false, showList = false, isSust = false, isBurst = false;

	// Colors
	sf::Color darkerGray(32, 40, 32);		// Window "border"
	sf::Color darkGray(64, 72, 64);			// Weapons list
	sf::Color Gray(128, 136, 128);			// Background
	sf::Color lightGray(192, 192, 192);		// Top/Best weapon & button border
	sf::Color lighterGray(224, 224, 224);	// Button interior
	sf::Color lightYellow(255, 255, 192);	// Button highlight
	sf::Color mauve(67, 52, 82);			// Icon background

	// Font reader
	sf::Font font;
	if (!font.loadFromFile("font.ttf")) {
		cout << "Invalid font!" << endl;
		return -1;
	}

	// Renders window
	sf::RenderWindow homeWindow(sf::VideoMode(static_cast<int>(screenWidth), static_cast<int>(screenHeight)), "Home Screen", sf::Style::Close);

	// Borderless background creation and formatting
	sf::RectangleShape borderlessScreen(sf::Vector2f(borderlessWidth, borderlessHeight));
	borderlessScreen.setFillColor(Gray);
	borderlessScreen.setPosition(borderlessXY, borderlessXY);

	// Button creation & Formatting
	sf::CircleShape sustHighlight(highlightRad);
	sustHighlight.setFillColor(lightYellow);
	sustHighlight.setPosition(sustX0 - highlightRad, buttonY - highlightInc);

	sf::CircleShape sustBorder(borderRad);
	sustBorder.setFillColor(lightGray);
	sustBorder.setPosition(sustX0 - borderRad, buttonY - buttonInc);

	sf::CircleShape sustButton(buttonRad);
	sustButton.setFillColor(lighterGray);
	sustButton.setPosition(sustX0 - buttonRad, buttonY);

	sf::Text sustText("Sustained\nDPS", font);
	sustText.setCharacterSize(48);
	sustText.setFillColor(sf::Color::Black);
	sustText.setStyle(sf::Text::Bold);
	setText(sustText, sustX0, screenHeight / 16 + buttonRad);

	sf::CircleShape burstHighlight(highlightRad);
	burstHighlight.setFillColor(lightYellow);
	burstHighlight.setPosition(burstX0 - highlightRad, buttonY - highlightInc);

	sf::CircleShape burstBorder(borderRad);
	burstBorder.setFillColor(lightGray);
	burstBorder.setPosition(burstX0 - borderRad, buttonY - buttonInc);

	sf::CircleShape burstButton(buttonRad);
	burstButton.setFillColor(lighterGray);
	burstButton.setPosition(burstX0 - buttonRad, buttonY);

	sf::Text burstText("Burst\nDPS", font);
	burstText.setCharacterSize(48);
	burstText.setFillColor(sf::Color::Black);
	burstText.setStyle(sf::Text::Bold);
	setText(burstText, burstX0, buttonY + buttonRad);

	// Search bar creation & formatting
	sf::Sprite searchBar;
	sf::Texture searchBarT;
	//source for search bar: https://www.vecteezy.com/png/11888174-shadow-rectangle-neumorphic-rectangle
	searchBarT.loadFromFile("searchBar.png");
	searchBar.setTexture(searchBarT);
	searchBar.setPosition(screenWidth / 2 - searchBar.getGlobalBounds().width / 2, screenHeight / 3 - searchBar.getGlobalBounds().height / 4);

	sf::String searchString;
	sf::Text searchText;
	searchText.setFont(font);
	searchText.setCharacterSize(32);
	searchText.setFillColor(sf::Color::White);
	searchText.setStyle(sf::Text::Bold);

	sf::Text cursorText("|", font);
	cursorText.setCharacterSize(32);
	cursorText.setFillColor(sf::Color::White);
	cursorText.setStyle(sf::Text::Bold);

	// Top weapon creation & formatting
	sf::RectangleShape bestRect(sf::Vector2f(bestWidth, bestHeight));
	bestRect.setFillColor(lightGray);
	bestRect.setPosition(bestX, bestY);

	sf::String bestString;
	sf::Text bestText;
	bestText.setFont(font);
	bestText.setCharacterSize(20);
	bestText.setFillColor(sf::Color::Black);
	bestText.setStyle(sf::Text::Bold);
	
	// List creation & formatting
	sf::RectangleShape listRect(sf::Vector2f(listWidth, listHeight));
	listRect.setFillColor(darkGray);
	listRect.setPosition(listX, listY);

	sf::String ltListString;
	sf::Text ltListText;
	ltListText.setFont(font);
	ltListText.setCharacterSize(24);
	ltListText.setFillColor(sf::Color::White);
	ltListText.setStyle(sf::Text::Bold);

	sf::String rtListString;
	sf::Text rtListText;
	rtListText.setFont(font);
	rtListText.setCharacterSize(24);
	rtListText.setFillColor(sf::Color::White);
	rtListText.setStyle(sf::Text::Bold);

	// Clock declaration for blinking cursor
	sf::Clock clock;
	
	while (homeWindow.isOpen()) {

		sf::Event event;

		// Hides and shows the cursor ever 0.5 seconds
		if (clock.getElapsedTime() >= sf::milliseconds(500)) {
			clock.restart();
			showCursor = !showCursor;
		}

		while (homeWindow.pollEvent(event)) {

			// Closes the window and ends the program when the window is closed
			if (event.type == sf::Event::Closed) {
				homeWindow.close();
				return 0;
			}

			else if (event.type == sf::Event::KeyPressed) {

				// Deletes the last character when backspace is pressed
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {

					if (searchString.getSize() > 0) {
						searchString.erase(searchString.getSize() - 1, 1);
						searchText.setString(searchString);
						setText(searchText, screenWidth / 2, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);
					}

					if (searchString.getSize() == 0) {
						showBest = false;
						showList = false;
						isValidSearch = true;
						searchString.clear();
						searchText.setString(searchString);
						setText(searchText, screenWidth / 2, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);
					}
				}

				// When the enter key is pressed, search validates the search input and prompts the user appropriately
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

					bestString.clear();
					bestText.setString(bestString);
					ltListString.clear();
					ltListText.setString(ltListString);
					rtListString.clear();
					rtListText.setString(rtListString);
					showList = false;

					if (searchString.getSize() > 0) {

						isValidSearch = false;

						for (int i = 0; i < Arsenal.size(); i++) {

							if (searchString == get<0>(Arsenal[i][0])) {
								catIndex = i;
								isValidSearch = true;
								showBest = true;
							}
						}

						if (!isValidSearch) {
							catIndex = 0;
							bestString = "Invalid input!\nPress \'esc' to try again.";
							bestText.setString(bestString);
							setText(bestText, screenWidth / 2, bestY + bestHeight / 2);
							showBest = true;
						}

						else if (searchString.getSize() > 0) {
							bestString = "Please select a DPS type above.";
							bestText.setString(bestString);
							setText(bestText, screenWidth / 2, bestY + bestHeight / 2);
							showBest = true;
						}

						string search = searchString.toAnsiString();	// Stores input as std::string for ease of use
					}
				}

				// Escape allows the user exit their selection and the program in its entirety
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

					if (isSust || isBurst) {
						bestString.clear();
						bestText.setString(bestString);
						ltListString.clear();
						ltListText.setString(ltListString);
						rtListString.clear();
						rtListText.setString(rtListString);
						showBest = false;
						showList = false;
						isSust = false;
						isBurst = false;
					}

					else if (searchString.getSize() > 0) {
						isValidSearch = true;
						searchString.clear();
						searchText.setString(searchString);
						setText(searchText, screenWidth / 2, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);
					}

					else {
						homeWindow.close();
						return 0;
					}
				}
			}

			else if (event.type == sf::Event::TextEntered) {
				
				// Update search string with newest character entered
				if (event.text.unicode >= 32 && event.text.unicode <= 126) {
					searchString += (char)(event.text.unicode);
					searchText.setString(searchString);
					setText(searchText, screenWidth / 2, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);
				}

				// Ignores backspace and enter keys
				if (event.text.unicode == 8 || event.text.unicode == 13) {
					continue;
				}
			}

			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

				sf::Vector2i mousePos = sf::Mouse::getPosition(homeWindow);

				// Checks if sustainable DPS button was pressed, calls sorting by sustainable DPS values and displays top 11 results
				if (inCircle(buttonRad, sustX0, buttonY0, mousePos)) {

					bestString.clear();
					bestText.setString(bestString);
					ltListString.clear();
					ltListText.setString(ltListString);
					rtListString.clear();
					rtListText.setString(rtListString);

					if (isBurst) {
						isBurst = false;
					}

					isSust = !isSust;

					if (!isSust) {
						showBest = false;
						showList = false;
					}

					int n = Arsenal[catIndex].size();
					quickSort(Arsenal[catIndex], 0, n - 1, "Sustained");
					bestString = "Best sustainable DPS: " +get<1>(Arsenal[catIndex][0]);
					bestText.setString(bestString);
					setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

					for (int j = 2; j < 12; j++) {
						if (j < 6) {
							ltListString += to_string(j) + ". " + get<1>(Arsenal[catIndex][j - 1]) + '\n';
						}
						else if (j == 6) {
							ltListString += to_string(j) + ". " + get<1>(Arsenal[catIndex][j - 1]);
						}
						else if (j > 6 && j < 11) {
							rtListString += to_string(j) + ". " + get<1>(Arsenal[catIndex][j - 1]) + '\n';
						}
						else {
							rtListString += to_string(j) + ". " + get<1>(Arsenal[catIndex][j - 1]);
						}
					}

					ltListText.setString(ltListString);
					rtListText.setString(rtListString);
					ltListText.setPosition(listX + 20, listY + 20);
					rtListText.setPosition(screenWidth / 2, listY + 20);
				}

				// Checks if burst DPS button was pressed, calls sorting by burst DPS values and displays top 11 results
				else if (inCircle(buttonRad, burstX0, buttonY0, mousePos)) {

					bestString.clear();
					bestText.setString(bestString);
					ltListString.clear();
					ltListText.setString(ltListString);
					rtListString.clear();
					rtListText.setString(rtListString);

					if (isSust) {
						isSust = false;
					}

					isBurst = !isBurst;

					if (!isBurst) {
						showBest = false;
						showList = false;
					}

					int n = Arsenal[catIndex].size();
					quickSort(Arsenal[catIndex], 0, n - 1, "Burst");
					bestString = "Best burst DPS: " +get<1>(Arsenal[catIndex][0]);
					bestText.setString(bestString);
					setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

					for (int j = 2; j < 12; j++) {
						if (j < 6) {
							ltListString += to_string(j) + ". " + get<1>(Arsenal[catIndex][j - 1]) + '\n';
						}
						else if (j == 6) {
							ltListString += to_string(j) + ". " + get<1>(Arsenal[catIndex][j - 1]);
						}
						else if (j > 6 && j < 11) {
							rtListString += to_string(j) + ". " + get<1>(Arsenal[catIndex][j - 1]) + '\n';
						}
						else {
							rtListString += to_string(j) + ". " + get<1>(Arsenal[catIndex][j - 1]);
						}
					}

					ltListText.setString(ltListString);
					rtListText.setString(rtListString);
					ltListText.setPosition(listX + 20, listY + 20);
					rtListText.setPosition(screenWidth / 2, listY + 20);
				}

				if (isSust || isBurst) {
					showBest = true;
					showList = true;
				}
			}
		}

		// Draws shapes and texts based on what bools
		homeWindow.clear(darkerGray);
		homeWindow.draw(borderlessScreen);

		if (showBest) {
			homeWindow.draw(bestRect);
			homeWindow.draw(bestText);
		}

		if (showList) {
			homeWindow.draw(listRect);
			homeWindow.draw(ltListText);
			homeWindow.draw(rtListText);
		}

		if (isSust) {
			isSust = true;
			homeWindow.draw(sustHighlight);
			
		}

		else if (isBurst) {
			isBurst = true;
			homeWindow.draw(burstHighlight);
		}

		homeWindow.draw(sustBorder);
		homeWindow.draw(burstBorder);
		homeWindow.draw(sustButton);
		homeWindow.draw(burstButton);
		homeWindow.draw(sustText);
		homeWindow.draw(burstText);

		homeWindow.draw(searchBar);
		homeWindow.draw(searchText);

		if (showCursor) {
			setText(cursorText, screenWidth / 2 + searchText.getGlobalBounds().width / 2 + 4, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);
			homeWindow.draw(cursorText);
		}
		
		homeWindow.display();
	}

	return 0;
}*/
