// Used SFML 2.5.1
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "Arsenal.h"

using namespace std;

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

	Arsenal arsenal;
	vector<vector<Weapon>>& currFam = arsenal.priWeapons;
	vector<Weapon>& currSub = arsenal.autoRifles;

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

	// Best weapon/prompts text box
	float bestWidth = screenWidth / 2;
	float bestHeight = 128.f;
	float bestX = screenWidth / 4;
	float bestY = screenHeight / 3 + 128;

	// Methods buttons dimensions & coordinates
	float methodsRad = 75.f, mHighlightInc = 5.f;
	float mHighlightRad = methodsRad + mHighlightInc;
	float quickX0 = screenWidth / 5;
	float shellX0 = 2 * (screenWidth / 5);
	float fwdX0 = 3 * (screenWidth / 5);
	float bwdX0 = 4 * (screenWidth / 5);
	float quickX = quickX0 - methodsRad;
	float shellX = shellX0 - methodsRad;
	float fwdX = fwdX0 - methodsRad;
	float bwdX = bwdX0 - methodsRad;
	float methodsY = screenHeight / 2 + 75;
	float methodsY0 = methodsY + methodsRad;


	// List of top weapons text box
	float listWidth = 4 * (screenWidth / 5);
	float listHeight = screenHeight / 4;
	float listX = screenWidth / 10;
	float listY = screenHeight - listHeight - screenHeight / 18;

	// Variables
	string search;
	bool showCursor = true, isValidSearch = true, isQuickSort = true, isFwd = true;
	bool isNum = false, isSust = false, isBurst = false, isSorted = false;
	bool showBest = false, showMethods = false, showList = false, showItem = false;

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
	setText(sustText, sustX0, buttonY0);

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
	setText(burstText, burstX0, buttonY0);

	// Search bar creation & formatting
	sf::Sprite searchBar;
	sf::Texture searchBarT;
	//source for search bar: https://www.vecteezy.com/png/11888174-shadow-rectangle-neumorphic-rectangle
	if (!searchBarT.loadFromFile("searchBar.png")) {
		cout << "Invalid texture!" << endl;
		return -1;
	}
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
	bestText.setCharacterSize(32);
	bestText.setFillColor(sf::Color::Black);
	bestText.setStyle(sf::Text::Bold);

	// Methods buttons creation & formatting
	sf::CircleShape quickHighlight(mHighlightRad);
	quickHighlight.setFillColor(lightYellow);
	quickHighlight.setPosition(quickX0 - mHighlightRad, methodsY - mHighlightInc);

	sf::CircleShape quickButton(methodsRad);
	quickButton.setFillColor(lightGray);
	quickButton.setPosition(quickX0 - methodsRad, methodsY);

	sf::Text quickText("Quick Sort", font);
	quickText.setCharacterSize(18);
	quickText.setFillColor(sf::Color::Black);
	quickText.setStyle(sf::Text::Bold);
	setText(quickText, quickX0, methodsY0);

	sf::CircleShape shellHighlight(mHighlightRad);
	shellHighlight.setFillColor(lightYellow);
	shellHighlight.setPosition(shellX0 - mHighlightRad, methodsY - mHighlightInc);

	sf::CircleShape shellButton(methodsRad);
	shellButton.setFillColor(lightGray);
	shellButton.setPosition(shellX0 - methodsRad, methodsY);

	sf::Text shellText("Shell Sort", font);
	shellText.setCharacterSize(18);
	shellText.setFillColor(sf::Color::Black);
	shellText.setStyle(sf::Text::Bold);
	setText(shellText, shellX0, methodsY0);

	sf::CircleShape fwdHighlight(mHighlightRad);
	fwdHighlight.setFillColor(lightYellow);
	fwdHighlight.setPosition(fwdX0 - mHighlightRad, methodsY - mHighlightInc);

	sf::CircleShape fwdButton(methodsRad);
	fwdButton.setFillColor(lightGray);
	fwdButton.setPosition(fwdX0 - methodsRad, methodsY);

	sf::Text fwdText("Best-to-Worst", font);
	fwdText.setCharacterSize(16);
	fwdText.setFillColor(sf::Color::Black);
	fwdText.setStyle(sf::Text::Bold);
	setText(fwdText, fwdX0, methodsY0);

	sf::CircleShape bwdHighlight(mHighlightRad);
	bwdHighlight.setFillColor(lightYellow);
	bwdHighlight.setPosition(bwdX0 - mHighlightRad, methodsY - mHighlightInc);

	sf::CircleShape bwdButton(methodsRad);
	bwdButton.setFillColor(lightGray);
	bwdButton.setPosition(bwdX0 - methodsRad, methodsY);

	sf::Text bwdText("Worst-to-Best", font);
	bwdText.setCharacterSize(16);
	bwdText.setFillColor(sf::Color::Black);
	bwdText.setStyle(sf::Text::Bold);
	setText(bwdText, bwdX0, methodsY0);
	
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

	sf::String tempBest;
	sf::String tempLeft;
	sf::String tempRight;

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

						if (searchString.getSize() == 0) {

							if (showItem || !isValidSearch) {

								isValidSearch = true;
								showItem = false;
								showList = true;

								if (isSust || isBurst) {
									showMethods = true;
								}

								bestString = tempBest;
								bestText.setString(bestString);
								setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

								ltListString = tempLeft;
								rtListString = tempRight;

								ltListText.setString(ltListString);
								rtListText.setString(rtListString);
								ltListText.setPosition(listX + 40, listY + 40);
								rtListText.setPosition(screenWidth / 2, listY + 40);
							}

							else {

								isNum = false;
								isSorted = false;

								isValidSearch = true;
								searchString.clear();
								searchText.setString(searchString);
								setText(searchText, screenWidth / 2, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);
							}
						}
					}

					else {
						bestString.clear();
						bestText.setString(bestString);
						ltListString.clear();
						ltListText.setString(ltListString);
						rtListString.clear();
						rtListText.setString(rtListString);

						isSust = false;
						isBurst = false;
						isSorted = false;
						showBest = false;
						showMethods = false;
						showList = false;
					}
				}

				// When the enter key is pressed, search validates the search input and prompts the user appropriately
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

					// If enter is pressed with no search input, returns default sort
					if (searchString.getSize() == 0) {

						isSust = true;
						isSorted = true;
						showBest = true;
						showMethods = true;
						showList = true;

						int n = currSub.size();
						isQuickSort ? arsenal.quickSort(currSub, 0, n - 1, isSust, isFwd) : arsenal.shellSort(currSub, isSust, isFwd);
						bestString = currSub[0].getName();
						bestText.setString(bestString);
						setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

						int listMax = 11;
						if (currSub.size() < 11) {
							listMax = currSub.size();
						}

						for (int j = 2; j < listMax + 1; j++) {
							if (j < (listMax + 1) / 2) {
								ltListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
							}
							else if (j == (listMax + 1) / 2) {
								ltListString += to_string(j) + ". " + currSub[j - 1].getName();
							}
							else if (j > (listMax + 1) / 2 && j < listMax + 1) {
								rtListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
							}
							else {
								rtListString += to_string(j) + ". " + currSub[j - 1].getName();
							}
						}

						ltListText.setString(ltListString);
						rtListText.setString(rtListString);
						ltListText.setPosition(listX + 40, listY + 40);
						rtListText.setPosition(screenWidth / 2, listY + 40);
					}

					else if (searchString.getSize() <= 2 && (searchString[0] > 47 && searchString[0] < 58)) {

						if (searchString.getSize() == 1) {
							isNum = true;
						}
						else if (searchString.getSize() == 2 && (searchString[1] > 47 && searchString[1] < 58)) {
							isNum = true;
						}
						
						if (isNum && !showItem && isSorted) {

							tempBest = bestString;
							tempLeft = ltListString;
							tempRight = rtListString;

							if (stoi(searchString.toAnsiString()) > 0 && stoi(searchString.toAnsiString()) <= currSub.size()) {

								int itemIndex = stoi(searchString.toAnsiString()) - 1;

								Weapon result = arsenal.searchIndex(currSub, itemIndex);

								showBest = true;
								showItem = true;
								showMethods = false;
								showList = true;

								bestString = result.getName();
								bestText.setString(bestString);
								setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

								ltListString = "Rank: " + to_string(itemIndex + 1) + 
									"\nType: " + result.getType() + 
									"\nSustainable DPS: " + to_string(result.getSusDPS());
								rtListString = "Burst DPS: " + to_string(result.getBurstDPS()) + 
									"\nRank: " + to_string(arsenal.getIndex(arsenal.allWeapons, result));

								ltListText.setString(ltListString);
								rtListText.setString(rtListString);
								ltListText.setPosition(listX + 40, listY + 40);
								rtListText.setPosition(screenWidth / 2, listY + 40);
							}

							else {

								bestString = "Index out of range.\nPress \'esc' to try again.";
								bestText.setString(bestString);
								setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

								isValidSearch = false;
								showBest = true;
								showMethods = false;
							}	
						}

						else {

							if (!showItem) {
								tempBest = bestString;
								tempLeft = ltListString;
								tempRight = rtListString;
							}

							bestString = "Items not sorted.\nPlease sort first.";
							bestText.setString(bestString);
							setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

							isValidSearch = false;
							showBest = true;
							showMethods = false;
						}
					}

					else {

						if (!showItem) {
							tempBest = bestString;
							tempLeft = ltListString;
							tempRight = rtListString;
						}

						vector<vector<Weapon>> newFam = arsenal.searchFam(arsenal.allWeapons, searchString);

						vector<Weapon> newSub = arsenal.searchSub(arsenal.allWeapons, searchString);

						Weapon result = arsenal.searchItem(arsenal.allWeapons, searchString);
						
						if (!newFam.empty()) {

							currFam = newFam;
							isSorted = false;
							showBest = false;
							showMethods = false;
							showList = false;
						}

						else if (!newSub.empty()) {
							currSub = newSub;

							if (isSorted) {
								int n = currSub.size();
								isQuickSort ? arsenal.quickSort(currSub, 0, n - 1, isSust, isFwd) : arsenal.shellSort(currSub, isSust, isFwd);
								bestString = currSub[0].getName();
								bestText.setString(bestString);
								setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

								int listMax = 11;
								if (currSub.size() < 11) {
									listMax = currSub.size();
								}

								for (int j = 2; j < listMax + 1; j++) {
									if (j < (listMax + 1) / 2) {
										ltListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
									}
									else if (j == (listMax + 1) / 2) {
										ltListString += to_string(j) + ". " + currSub[j - 1].getName();
									}
									else if (j > (listMax + 1) / 2 && j < listMax + 1) {
										rtListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
									}
									else {
										rtListString += to_string(j) + ". " + currSub[j - 1].getName();
									}
								}

								ltListText.setString(ltListString);
								rtListText.setString(rtListString);
								ltListText.setPosition(listX + 40, listY + 40);
								rtListText.setPosition(screenWidth / 2, listY + 40);
							 }

							else {
								isSorted = false;
								showBest = false;
								showMethods = false;
								showList = false;
							}
						}

						else if (result.getName() != "DNE") {

							isValidSearch = true;
							showBest = true;
							showItem = true;
							showMethods = false;
							showList = true;

							bestString = result.getName();
							bestText.setString(bestString);
							setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

							if (isSorted) {
								ltListString = "Rank: " + to_string(arsenal.getIndex(arsenal.allWeapons, result)) + '\n';
							}
							else {
								ltListString = "";
							}
							ltListString += "Type: " + result.getType() + "\nTotal Damage: " + to_string(result.getTotDamage());
							rtListString = "Sustainable DPS : " + to_string(result.getSusDPS()) + "\nBurst DPS : " + to_string(result.getBurstDPS());

							ltListText.setString(ltListString);
							rtListText.setString(rtListString);
							ltListText.setPosition(listX + 40, listY + 40);
							rtListText.setPosition(screenWidth / 2, listY + 40);
						}

						else {

							isValidSearch = false;
							isSorted = false;

							bestString = "Invalid input!\nPress \'esc' to try again.";
							bestText.setString(bestString);
							setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

							showBest = true;
							showItem = false;
							showMethods = false;
						}
					}
				}

				// Escape allows the user exit their selection and the program in its entirety
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

					if (searchString.getSize() == 0 && !showBest) {
						homeWindow.close();
						return 0;
					}

					else if (showItem) {

						showItem = false;
						showList = true;

						if (isSust || isBurst) {
							showMethods = true;
						}

						bestString = tempBest;
						ltListString = tempLeft;
						rtListString = tempRight;

						bestText.setString(bestString);
						setText(bestText, screenWidth / 2, bestY + bestHeight / 2);
						ltListText.setString(ltListString);
						rtListText.setString(rtListString);
						ltListText.setPosition(listX + 40, listY + 40);
						rtListText.setPosition(screenWidth / 2, listY + 40);
					}

					else if (showBest) {

						bestString.clear();
						bestText.setString(bestString);
						ltListString.clear();
						ltListText.setString(ltListString);
						rtListString.clear();
						rtListText.setString(rtListString);

						isSust = false;
						isBurst = false;
						isSorted = false;
						showBest = false;
						showMethods = false;
						showList = false;
					}

					isValidSearch = true;
					searchString.clear();
					searchText.setString(searchString);
					setText(searchText, screenWidth / 2, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);
				}
			}

			else if (event.type == sf::Event::TextEntered) {
				
				// Update search string with newest character entered
				if (event.text.unicode >= 32 && event.text.unicode <= 126) {

					sf::String charString = static_cast<char>(event.text.unicode);
					sf::Text charText;
					charText.setString(charString);

					if (searchText.getGlobalBounds().width + charText.getGlobalBounds().width < searchBar.getGlobalBounds().width - 20) {
						searchString += charString;
						searchText.setString(searchString);
						setText(searchText, screenWidth / 2, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);
					}
				}

				// Ignores backspace and enter keys
				if (event.text.unicode == 8 || event.text.unicode == 13) {
					continue;
				}
			}

			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

				sf::Vector2i mousePos = sf::Mouse::getPosition(homeWindow);

				if (isSorted) {

					if (bestRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {

						if (!showItem) {
							tempLeft = ltListString;
							tempRight = rtListString;
						}

						showItem = !showItem;

						Weapon result = arsenal.searchItem(arsenal.allWeapons, bestString);

						if (showItem) {

							showMethods = false;
							showList = true;

							ltListString = "Rank: " + to_string(arsenal.getIndex(arsenal.allWeapons, result)) +
								"\nType: " + result.getType() +
								"\nSustainable DPS: " + to_string(result.getSusDPS());
							rtListString = "Burst DPS: " + to_string(result.getBurstDPS()) +
								"\nRank: " + to_string(arsenal.getIndex(arsenal.allWeapons, result));

							ltListText.setString(ltListString);
							rtListText.setString(rtListString);
							ltListText.setPosition(listX + 40, listY + 40);
							rtListText.setPosition(screenWidth / 2, listY + 40);
						}

						else {

							showMethods = true;

							ltListString = tempLeft;
							rtListString = tempRight;

							ltListText.setString(ltListString);
							rtListText.setString(rtListString);
							ltListText.setPosition(listX + 40, listY + 40);
							rtListText.setPosition(screenWidth / 2, listY + 40);
						}
					}
				}

				// Checks if sustainable DPS button was pressed, calls sorting by sustainable DPS values and displays top 11 results
				if (inCircle(borderRad, sustX0, buttonY0, mousePos)) {

					showMethods = true;

					bestString.clear();
					bestText.setString(bestString);
					ltListString.clear();
					ltListText.setString(ltListString);
					rtListString.clear();
					rtListText.setString(rtListString);

					isSust = !isSust;

					if (!isSust) {

						isSorted = false;
						showBest = false;
						showMethods = false;
						showList = false;
					}

					else {

						isValidSearch = true;
						isNum = false;
						isBurst = false;
						isSorted = true;
						showItem = false;
						
						searchString.clear();
						searchText.setString(searchString);
						setText(searchText, screenWidth / 2, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);

						int n = currSub.size();
						isQuickSort ? arsenal.quickSort(currSub, 0, n - 1, isSust, isFwd) : arsenal.shellSort(currSub, isSust, isFwd);
						bestString = currSub[0].getName();
						bestText.setString(bestString);
						setText(bestText, screenWidth / 2, bestY + bestHeight / 2);
					}

					int listMax = 11;
					if (currSub.size() < 11) {
						listMax = currSub.size();
					}

					for (int j = 2; j < listMax + 1; j++) {
						if (j < (listMax + 1) / 2) {
							ltListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
						}
						else if (j == (listMax + 1) / 2) {
							ltListString += to_string(j) + ". " + currSub[j - 1].getName();
						}
						else if (j > (listMax + 1) / 2 && j < listMax + 1) {
							rtListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
						}
						else {
							rtListString += to_string(j) + ". " + currSub[j - 1].getName();
						}
					}

					ltListText.setString(ltListString);
					rtListText.setString(rtListString);
					ltListText.setPosition(listX + 40, listY + 40);
					rtListText.setPosition(screenWidth / 2, listY + 40);
				}

				// Checks if burst DPS button was pressed, calls sorting by burst DPS values and displays top 11 results
				else if (inCircle(borderRad, burstX0, buttonY0, mousePos)) {

					showMethods = true;

					bestString.clear();
					bestText.setString(bestString);
					ltListString.clear();
					ltListText.setString(ltListString);
					rtListString.clear();
					rtListText.setString(rtListString);

					isBurst = !isBurst;

					if (!isBurst) {

						isSorted = true;
						showBest = false;
						showMethods = false;
						showList = false;
					}

					else {

						isValidSearch = true;
						isNum = false;
						isSust = false;
						isSorted = true;
						showItem = false;
						
						searchString.clear();
						searchText.setString(searchString);
						setText(searchText, screenWidth / 2, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);

						int n = currSub.size();
						isQuickSort ? arsenal.quickSort(currSub, 0, n - 1, isSust, isFwd) : arsenal.shellSort(currSub, isSust, isFwd);
						bestString = currSub[0].getName();
						bestText.setString(bestString);
						setText(bestText, screenWidth / 2, bestY + bestHeight / 2);
					}

					int listMax = 11;
					if (currSub.size() < 11) {
						listMax = currSub.size();
					}

					for (int j = 2; j < listMax + 1; j++) {
						if (j < (listMax + 1) / 2) {
							ltListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
						}
						else if (j == (listMax + 1) / 2) {
							ltListString += to_string(j) + ". " + currSub[j - 1].getName();
						}
						else if (j > (listMax + 1) / 2 && j < listMax + 1) {
							rtListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
						}
						else {
							rtListString += to_string(j) + ". " + currSub[j - 1].getName();
						}
					}

					ltListText.setString(ltListString);
					rtListText.setString(rtListString);
					ltListText.setPosition(listX + 40, listY + 40);
					rtListText.setPosition(screenWidth / 2, listY + 40);
				}
					
			// Checks if methods buttons are pressed, applies appropriate changes, and adjusts sorting + display
				else if (showMethods) {

					if (isQuickSort == false && inCircle(methodsRad, quickX0, methodsY0, mousePos)) {

						isQuickSort = true;
						isSorted = true;

						bestString.clear();
						bestText.setString(bestString);
						ltListString.clear();
						ltListText.setString(ltListString);
						rtListString.clear();
						rtListText.setString(rtListString);

						int n = currSub.size();
						isQuickSort ? arsenal.quickSort(currSub, 0, n - 1, isSust, isFwd) : arsenal.shellSort(currSub, isSust, isFwd);
						bestString = currSub[0].getName();
						bestText.setString(bestString);
						setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

						int listMax = 11;
						if (currSub.size() < 11) {
							listMax = currSub.size();
						}

						for (int j = 2; j < listMax + 1; j++) {
							if (j < (listMax + 1) / 2) {
								ltListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
							}
							else if (j == (listMax + 1) / 2) {
								ltListString += to_string(j) + ". " + currSub[j - 1].getName();
							}
							else if (j > (listMax + 1) / 2 && j < listMax + 1) {
								rtListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
							}
							else {
								rtListString += to_string(j) + ". " + currSub[j - 1].getName();
							}
						}

						ltListText.setString(ltListString);
						rtListText.setString(rtListString);
						ltListText.setPosition(listX + 40, listY + 40);
						rtListText.setPosition(screenWidth / 2, listY + 40);
					}

					else if (isQuickSort == true && inCircle(methodsRad, shellX0, methodsY0, mousePos)) {

						isQuickSort = false;
						isSorted = true;

						bestString.clear();
						bestText.setString(bestString);
						ltListString.clear();
						ltListText.setString(ltListString);
						rtListString.clear();
						rtListText.setString(rtListString);

						int n = currSub.size();
						isQuickSort ? arsenal.quickSort(currSub, 0, n - 1, isSust, isFwd) : arsenal.shellSort(currSub, isSust, isFwd);
						bestString = currSub[0].getName();
						bestText.setString(bestString);
						setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

						int listMax = 11;
						if (currSub.size() < 11) {
							listMax = currSub.size();
						}

						for (int j = 2; j < listMax + 1; j++) {
							if (j < (listMax + 1) / 2) {
								ltListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
							}
							else if (j == (listMax + 1) / 2) {
								ltListString += to_string(j) + ". " + currSub[j - 1].getName();
							}
							else if (j > (listMax + 1) / 2 && j < listMax + 1) {
								rtListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
							}
							else {
								rtListString += to_string(j) + ". " + currSub[j - 1].getName();
							}
						}

						ltListText.setString(ltListString);
						rtListText.setString(rtListString);
						ltListText.setPosition(listX + 40, listY + 40);
						rtListText.setPosition(screenWidth / 2, listY + 40);
					}

					else if (isFwd == false && inCircle(methodsRad, fwdX0, methodsY0, mousePos)) {

						isFwd = true;
						isSorted = true;

						bestString.clear();
						bestText.setString(bestString);
						ltListString.clear();
						ltListText.setString(ltListString);
						rtListString.clear();
						rtListText.setString(rtListString);

						int n = currSub.size();
						isQuickSort ? arsenal.quickSort(currSub, 0, n - 1, isSust, isFwd) : arsenal.shellSort(currSub, isSust, isFwd);
						bestString = currSub[0].getName();
						bestText.setString(bestString);
						setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

						int listMax = 11;
						if (currSub.size() < 11) {
							listMax = currSub.size();
						}

						for (int j = 2; j < listMax + 1; j++) {
							if (j < (listMax + 1) / 2) {
								ltListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
							}
							else if (j == (listMax + 1) / 2) {
								ltListString += to_string(j) + ". " + currSub[j - 1].getName();
							}
							else if (j > (listMax + 1) / 2 && j < listMax + 1) {
								rtListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
							}
							else {
								rtListString += to_string(j) + ". " + currSub[j - 1].getName();
							}
						}

						ltListText.setString(ltListString);
						rtListText.setString(rtListString);
						ltListText.setPosition(listX + 40, listY + 40);
						rtListText.setPosition(screenWidth / 2, listY + 40);
					}

					else if (isFwd == true && inCircle(methodsRad, bwdX0, methodsY0, mousePos)) {

						isFwd = false;
						isSorted = true;

						bestString.clear();
						bestText.setString(bestString);
						ltListString.clear();
						ltListText.setString(ltListString);
						rtListString.clear();
						rtListText.setString(rtListString);

						int n = currSub.size();
						isQuickSort ? arsenal.quickSort(currSub, 0, n - 1, isSust, isFwd) : arsenal.shellSort(currSub, isSust, isFwd);
						bestString = currSub[0].getName();
						bestText.setString(bestString);
						setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

						int listMax = 11;
						if (currSub.size() < 11) {
							listMax = currSub.size();
						}

						for (int j = 2; j < listMax + 1; j++) {
							if (j < (listMax + 1) / 2) {
								ltListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
							}
							else if (j == (listMax + 1) / 2) {
								ltListString += to_string(j) + ". " + currSub[j - 1].getName();
							}
							else if (j > (listMax + 1) / 2 && j < listMax + 1) {
								rtListString += to_string(j) + ". " + currSub[j - 1].getName() + '\n';
							}
							else {
								rtListString += to_string(j) + ". " + currSub[j - 1].getName();
							}
						}

						ltListText.setString(ltListString);
						rtListText.setString(rtListString);
						ltListText.setPosition(listX + 40, listY + 40);
						rtListText.setPosition(screenWidth / 2, listY + 40);
					}
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

		if (showBest && bestText.getGlobalBounds().width > 0) {
			homeWindow.draw(bestRect);
			homeWindow.draw(bestText);
		}
		if (showMethods) {
			if (isQuickSort) {
				homeWindow.draw(quickHighlight);
			}

			else {
				homeWindow.draw(shellHighlight);
			}

			if (isFwd) {
				homeWindow.draw(fwdHighlight);
			}

			else {
				homeWindow.draw(bwdHighlight);
			}

			homeWindow.draw(quickButton);
			homeWindow.draw(shellButton);
			homeWindow.draw(fwdButton);
			homeWindow.draw(bwdButton);
			homeWindow.draw(quickText);
			homeWindow.draw(shellText);
			homeWindow.draw(fwdText);
			homeWindow.draw(bwdText);
		}
		if (showList && isValidSearch && ltListText.getGlobalBounds().width > 0) {
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
}
