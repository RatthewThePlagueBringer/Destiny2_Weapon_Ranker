// Used SFML 2.5.1
//#include <iostream>
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

// Checks if mouse click is in circle using pythagorean distance
bool inCircle(float rad, float w, float h, sf::Vector2i mousePos) {

	float dist = sqrt(pow(static_cast<int>(mousePos.x) - w, 2.f) + pow(static_cast<int>(mousePos.y) - h, 2.f));

	if (dist <= rad) {
		return true;
	}

	return false;
}

// If search string is too long, erases the first character in the first string
void searchType(sf::String& searchString, int& searchStart, string search, sf::Sprite sprite, sf::Font font, int fontSize) {

	sf::String newString = searchString;
	sf::Text newText;
	newText.setString(newString);
	newText.setFont(font);
	newText.setCharacterSize(fontSize);
	newText.setFillColor(sf::Color::White);
	newText.setStyle(sf::Text::Bold);

	while (newText.getGlobalBounds().width > sprite.getGlobalBounds().width - 30) {
		newString.erase(0, 1);
		searchStart += 1;
		newText.setString(newString);
	}

	searchString = newString;
}

// Called after delete: if search string was shortened and now has space, adds to the front of the string
void searchDelete(sf::String& searchString, int& searchStart, string search, sf::Sprite sprite, sf::Font font, int fontSize) {

	sf::String newString = searchString;
	sf::Text newText;
	newText.setString(newString);
	newText.setFont(font);
	newText.setCharacterSize(fontSize);
	newText.setFillColor(sf::Color::White);
	newText.setStyle(sf::Text::Bold);

	if (searchStart != 0 || searchString.getSize() != search.size()) {
		while (searchStart >= 1 && (searchString.getSize() < search.size() || newText.getGlobalBounds().width < sprite.getGlobalBounds().width - 30)) {
			newString.insert(0, search.substr(searchStart - 1, 1));
			searchStart -= 1;
			newText.setString(newString);
		}
	}
}

// Returns the index of the last character that fits within the rectangle
int getLastIndex(string bestStr, sf::RectangleShape rect, sf::Font font, int fontSize) {
	
	sf::String myStr = bestStr;
	sf::Text myText;
	myText.setString(myStr);
	myText.setFont(font);
	myText.setCharacterSize(fontSize);

	sf::String subStr = "";
	sf::Text subText;
	subText.setString(subStr);
	subText.setFont(font);
	subText.setCharacterSize(fontSize);

	if (myText.getGlobalBounds().width <= rect.getGlobalBounds().width - 80) {
		return myStr.getSize();
	}

	while (subText.getGlobalBounds().width < rect.getGlobalBounds().width - 80) {
		for (int i = 0; i < myStr.getSize(); i++) {
			subStr.insert(i, myStr[i]);
			subText.setString(subStr);

			if (subText.getGlobalBounds().width > rect.getGlobalBounds().width - 80) {
				return i - 1;
			}
		}
	}

	return -1;
}

// Splits string into multiple lines to fit within a rectangle
sf::String fitText(string bestStr, sf::RectangleShape rect, sf::Font font, int fontSize) {

	sf::String retStr = bestStr;
	sf::Text retText;
	retText.setString(retStr);
	retText.setFont(font);
	retText.setCharacterSize(fontSize);

	if (retText.getGlobalBounds().width <= rect.getGlobalBounds().width - 80) {
		return retStr;
	}

	string tempStr = "";
		
	int splitIndex = getLastIndex(retStr, rect, font, fontSize);

	for (int i = splitIndex; i >= 0; i--) {

		if (!isalnum(retStr[i])) {
			splitIndex = i;
			break;
		}
		splitIndex = -1;
	}

	if (splitIndex != -1) {
		retStr.insert(splitIndex + 1, "\n");
	}

	else {
		retStr.insert(getLastIndex(retStr, rect, font, fontSize) - 1, "\n");
	}

	sf::String subStr = retStr;
	sf::Text subText;
	subText.setString(subStr);
	subText.setFont(font);
	subText.setCharacterSize(fontSize);

	subStr = subStr.substring(splitIndex + 1, subStr.getSize() - splitIndex);
	subText.setString(subStr);

	if (subText.getGlobalBounds().width > rect.getGlobalBounds().width - 80) {
		retStr.erase(splitIndex + 1, retStr.getSize() - splitIndex);
		retStr += fitText(subStr, rect, font, fontSize);
	}

	return retStr;
}

// If length of string in list is too long, fits it to the list box with an ellipse to signify it has been shortened
sf::String fitList(string listLine, sf::RectangleShape rect, sf::Font font, int fontSize) {
	
	sf::String ellipsesS = "...";
	sf::Text ellipsesT;
	ellipsesT.setString(ellipsesS);
	ellipsesT.setFont(font);
	ellipsesT.setCharacterSize(fontSize);
	ellipsesT.setFillColor(sf::Color::Black);

	sf::String newString = listLine;
	sf::Text newText;
	newText.setString(newString);
	newText.setFont(font);
	newText.setCharacterSize(fontSize);
	newText.setFillColor(sf::Color::Black);

	if (newText.getGlobalBounds().width <=  (rect.getGlobalBounds().width / 2) - 120) {
		return newString;
	}

	while (newText.getGlobalBounds().width > (rect.getGlobalBounds().width / 2) - ellipsesT.getGlobalBounds().width - 120) {
		newString.erase(newString.getSize() - 1, 1);
		newText.setString(newString);
	}

	newString += ellipsesS;
	return newString;
}

// Sorts the weapons by parameters and displays the time it took to sort
void sortNTime(sf::Text& timerText, Arsenal& arsenal, vector<Weapon>& currSub, bool isQuickSort, bool isSust, bool isFwd, sf::RenderWindow& homeScreen, sf::Font font) {

		sf::Clock sortClock;
		sortClock.restart();
		cout << "Starting Clock and " << (isQuickSort ? "Quick" : "Shell") << " Sorting by " << (isSust ? "Sustained" : "Burst") << " DPS from " << (isFwd ? "Best-to-Worst..." : "Worst-to-Best...") << endl;

		int n = currSub.size();
		isQuickSort ? arsenal.quickSort(currSub, 0, n - 1, isSust, isFwd) : arsenal.shellSort(currSub, isSust, isFwd);

		sf::Time elapsedTime = sortClock.getElapsedTime();

		double milliSecs = elapsedTime.asMicroseconds() / 1000.0;
		string milliString = to_string(milliSecs);
		milliString = milliString.substr(0, milliString.find('.') + 4);
		cout << "Time elapsed: " << milliString << " milliseconds" << endl;
		timerText.setString(milliString+ " ms");

		setText(timerText, homeScreen.getSize().x / 2, homeScreen.getSize().y / 25);
}

bool isPri(Weapon w) {
	return w.getFam() == "Primary Weapons";
}

int main() {

	// Initializes an arsenal object and 2 vectors to store weapons
	Arsenal arsenal;
	vector<Weapon>& currSub = arsenal.tempVec;
	vector<Weapon> unsortedSub;

	// Screen dimensions
	float screenWidth = 1000.f, screenHeight = 1250.f;
	float borderDec = 40.f;
	float borderlessWidth = screenWidth - borderDec;
	float borderlessHeight = screenHeight - borderDec;
	float borderlessXY = borderDec / 2;

	// Text font sizes
	int timerPts = 32, buttonPts = 56, searchPts = 32, bestPts = 32, sortPts = 26, fwdPts = 22, listPts = 24;

	// Timer dimensions and coordinates
	float timerWidth = 250.f, timerHeight = 64.f;
	float timerX = screenWidth / 2 - timerWidth / 2;
	float timerY = screenHeight / 25 - timerHeight / 2;

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
	float bestWidth = (4 * screenWidth) / 5;
	float bestHeight = 128.f;
	float bestX = screenWidth / 10;
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
	string search = "", bestStr = "", tempStr = "";
	int searchStart = 0, microS = 0;
	bool showCursor = true, isValidSearch = true, isQuickSort = true, isFwd = true;
	bool isNum = false, isSust = false, isBurst = false, isSorted = false;
	bool inSub = false, inFam = false;
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
	// Source for font: https://www.1001fonts.com/roboto-condensed-font.html (Roboto Condensed Light)
	sf::Font font;
	if (!font.loadFromFile("files/font.ttf")) {
		cout << "Invalid font!" << endl;
		return -1;
	}

	// Renders window
	sf::RenderWindow homeWindow(sf::VideoMode(static_cast<int>(screenWidth), static_cast<int>(screenHeight)), "Destiny 2 Weapons Ranker by DPS", sf::Style::Close);

	// Borderless background creation and formatting
	sf::RectangleShape borderlessScreen(sf::Vector2f(borderlessWidth, borderlessHeight));
	borderlessScreen.setFillColor(Gray);
	borderlessScreen.setPosition(borderlessXY, borderlessXY);

	// Timer creation & formatting
	sf::Text timerText;
	timerText.setFont(font);
	timerText.setCharacterSize(32);
	timerText.setFillColor(sf::Color::White);

	sf::RectangleShape timerRect(sf::Vector2f(timerWidth, timerHeight));
	timerRect.setFillColor(darkerGray);
	timerRect.setPosition(timerX, timerY);

	// Button creation & formatting
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
	sustText.setCharacterSize(buttonPts);
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
	burstText.setCharacterSize(buttonPts);
	burstText.setFillColor(sf::Color::Black);
	burstText.setStyle(sf::Text::Bold);
	setText(burstText, burstX0, buttonY0);

	// Search bar creation & formatting
	sf::Sprite searchBar;
	sf::Texture searchBarT;
	//source for search bar: https://www.vecteezy.com/png/11888174-shadow-rectangle-neumorphic-rectangle
	if (!searchBarT.loadFromFile("files/searchBar.png")) {
		cout << "Invalid texture!" << endl;
		return -1;
	}
	searchBar.setTexture(searchBarT);
	searchBar.setPosition(screenWidth / 2 - searchBar.getGlobalBounds().width / 2, screenHeight / 3 - searchBar.getGlobalBounds().height / 4);

	sf::String searchString;
	sf::Text searchText;
	searchText.setFont(font);
	searchText.setCharacterSize(searchPts);
	searchText.setFillColor(sf::Color::White);
	searchText.setStyle(sf::Text::Bold);

	sf::Text cursorText("|", font);
	cursorText.setCharacterSize(searchPts);
	cursorText.setFillColor(sf::Color::White);
	cursorText.setStyle(sf::Text::Bold);

	// Top weapon creation & formatting
	sf::RectangleShape bestRect(sf::Vector2f(bestWidth, bestHeight));
	bestRect.setFillColor(lightGray);
	bestRect.setPosition(bestX, bestY);

	sf::String bestString;
	sf::Text bestText;
	bestText.setFont(font);
	bestText.setCharacterSize(bestPts);
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
	quickText.setCharacterSize(sortPts);
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
	shellText.setCharacterSize(sortPts);
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
	fwdText.setCharacterSize(fwdPts);
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
	bwdText.setCharacterSize(fwdPts);
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
	ltListText.setCharacterSize(listPts);
	ltListText.setFillColor(sf::Color::White);
	ltListText.setStyle(sf::Text::Bold);

	sf::String rtListString;
	sf::Text rtListText;
	rtListText.setFont(font);
	rtListText.setCharacterSize(listPts);
	rtListText.setFillColor(sf::Color::White);
	rtListText.setStyle(sf::Text::Bold);

	sf::String tempTime;
	sf::String tempBest;
	sf::String tempLeft;
	sf::String tempRight;

	// Clock declaration for blinking cursor
	sf::Clock clock;
	
	while (homeWindow.isOpen()) {

		// Hides and shows the cursor every 0.5 seconds
		if (clock.getElapsedTime() >= sf::milliseconds(500)) {
			clock.restart();
			showCursor = !showCursor;
		}

		sf::Event event;

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
						search.erase(search.size() - 1, 1);
						searchString.erase(searchString.getSize() - 1, 1);
						searchDelete(searchString, searchStart, search, searchBar, font, searchPts);
						searchText.setString(searchString);
						setText(searchText, screenWidth / 2, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);

						// If deleting the last character, reverts display to previous screen
						if (searchString.getSize() == 0) {

							if (showItem || !isValidSearch) {
								isValidSearch = true;
								inSub = false;
								inFam = false;
								showItem = false;
								showList = true;

								if (isSust || isBurst) {
									showMethods = true;
								}

								timerText.setString(tempTime);

								bestString = tempBest;
								bestString = fitText(bestString, bestRect, font, bestPts);
								bestText.setString(bestString);
								setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

								ltListString = tempLeft;
								rtListString = tempRight;

								ltListText.setString(ltListString);
								rtListText.setString(rtListString);
								ltListText.setPosition(listX + 20, listY + 20);
								rtListText.setPosition(screenWidth / 2 + 20, listY + 20);
							}

							else {

								isNum = false;
								isValidSearch = true;

								search.clear();
								searchString.clear();
								searchText.setString(searchString);
								setText(searchText, screenWidth / 2, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);
							}
						}
					}

					// If the search string is empty, resets the display
					else {

						timerText.setString("");
						bestString.clear();
						bestText.setString(bestString);
						ltListString.clear();
						ltListText.setString(ltListString);
						rtListString.clear();
						rtListText.setString(rtListString);

						currSub = arsenal.tempVec;
						arsenal.tempVec.clear();

						isSust = false;
						isBurst = false;
						isSorted = false;
						inSub = false;
						inFam = false;
						showBest = false;
						showMethods = false;
						showList = false;
					}
				}

				// When the enter key is pressed, search validates the search input and prompts the user appropriately
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

					// If enter is pressed with no search input, returns default sort
					if (search.size() == 0) {

						if (!showBest) {

							isSust = true;
							isSorted = true;
							showBest = true;
							showMethods = true;
							showList = true;

							currSub = arsenal.tempVec;
							currSub = arsenal.createAll(arsenal.allWeapons);
							cout << "Size of arsenal: " << currSub.size() << endl;
							unsortedSub = currSub;

							sortNTime(timerText, arsenal, currSub, isQuickSort, isSust, isFwd, homeWindow, font);
							bestStr = currSub[0].getName();
							bestString = fitText(bestStr, bestRect, font, bestPts);
							bestText.setString(bestString);
							setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

							int listMax = 19;
							if (currSub.size() < 19) {
								listMax = currSub.size();
							}

							for (int j = 2; j < listMax + 1; j++) {
								if (j < (listMax + 1) / 2) {
									tempStr = to_string(j) + ". " + currSub[j - 1].getName();
									ltListString += fitList(tempStr, listRect, font, listPts) + '\n';
								}
								else if (j == (listMax + 1) / 2) {
									tempStr = to_string(j) + ". " + currSub[j - 1].getName();
									ltListString += fitList(tempStr, listRect, font, listPts);
								}
								else if (j > (listMax + 1) / 2 && j < listMax + 1) {
									tempStr = to_string(j) + ". " + currSub[j - 1].getName();
									rtListString += fitList(tempStr, listRect, font, listPts) + '\n';
								}
								else {
									tempStr = to_string(j) + ". " + currSub[j - 1].getName();
									rtListString += fitList(tempStr, listRect, font, listPts);
								}
							}

							ltListText.setString(ltListString);
							rtListText.setString(rtListString);
							ltListText.setPosition(listX + 20, listY + 20);
							rtListText.setPosition(screenWidth / 2 + 20, listY + 20);

							tempTime = timerText.getString();
							tempBest = bestString;
							tempLeft = ltListString;
							tempRight = rtListString;
						}
					}

					// If input is a number, returns item found at that index
					else if (search.size() <= 6 && (search[0] > 47 && search[0] < 58)) {

						if (!showItem && isValidSearch) {
							tempTime = timerText.getString();
							timerText.setString("");
							tempBest = bestString;
							tempLeft = ltListString;
							tempRight = rtListString;
						}

						if (search.size() == 1) {
							isNum = true;
						}
						else {
							int numChar = 1;

							for (int i = 1; i < search.size(); i++) {
								if (search[i] > 47 && search[i] < 58) {
									numChar++;
								}
								if (numChar == search.size()) {
									isNum = true;
								}
							}
						}

						if (isNum && isSorted) {

							if (stoi(search) > 0 && stoi(search) <= currSub.size()) {

								int itemIndex = stoi(search) - 1;

								Weapon result = arsenal.searchIndex(currSub, itemIndex);

								showBest = true;
								showItem = true;
								showMethods = false;
								showList = true;

								bestStr= result.getName();
								bestString = fitText(bestStr, bestRect, font, bestPts);
								bestText.setString(bestString);
								setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

								ltListString = "Rank: " + to_string(itemIndex + 1) +
									"\nFamily: " + result.getFam() +
									"\nSubfamily: " + result.getSubFam();
								rtListString = "Sustained DPS : " + to_string(result.getSusDPS()) +
									"\nBurst DPS: " + to_string(result.getBurstDPS());
								if (!isPri(result)) {
									rtListString += "\nTotal Damage: " + to_string(result.getTotDamage());
								}

								ltListText.setString(ltListString);
								rtListText.setString(rtListString);
								ltListText.setPosition(listX + 20, listY + 20);
								rtListText.setPosition(screenWidth / 2 + 20, listY + 20);
							}

							else {

								bestStr = "";
								bestString = "Index out of range.\nPress \'esc' to try again.";
								bestText.setString(bestString);
								setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

								isValidSearch = false;
								showBest = true;
								showMethods = false;
								showItem = false;
							}	
						}

						else {

							bestStr = "";
							bestString = "Items not sorted.\nPlease sort first.";
							bestText.setString(bestString);
							setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

							isValidSearch = false;
							showBest = true;
							showMethods = false;
							showItem = false;
						}
					}

					else {

						// Saves previous screen info if not showing item
						if (!showItem && isValidSearch) {
							tempTime = timerText.getString();
							timerText.setString("");
							tempBest = bestString;
							tempLeft = ltListString;
							tempRight = rtListString;
						}

						// Searches for family, subfamily, and weapon from user input
						vector<vector<Weapon>> newFam = arsenal.searchFam(arsenal.allWeapons, search);

						vector<Weapon> newSub = arsenal.searchSub(arsenal.allWeapons, search);

						Weapon result = arsenal.searchItem(currSub, search);
						
						// If family is found, sorts all the weapons in that family and displays the top 11
						if (!newFam.empty()) {

							/*tempTime.clear();
							timerText.setString(tempTime);
							tempBest.clear();
							tempLeft.clear();
							tempRight.clear();*/

							isValidSearch = true;
							isSorted = true;
							inSub = false;
							inFam = true;
							showBest = true;
							showMethods = true;
							showList = true;
							showItem = false;

							bestString.clear();
							bestText.setString(bestString);
							ltListString.clear();
							ltListText.setString(ltListString);
							rtListString.clear();
							rtListText.setString(rtListString);

							currSub = arsenal.tempVec;
							currSub = arsenal.createFam(arsenal.allWeapons, search);
							cout << "Size of Family \"" << search << "\": " << currSub.size() << endl;
							unsortedSub = currSub;

							sortNTime(timerText, arsenal, currSub, isQuickSort, isSust, isFwd, homeWindow, font);
							bestStr = currSub[0].getName();
							bestString = fitText(bestStr, bestRect, font, bestPts);
							bestText.setString(bestString);
							setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

							int listMax = 19;
							if (currSub.size() < 19) {
								listMax = currSub.size();
							}

							for (int j = 2; j < listMax + 1; j++) {
								if (j < (listMax + 1) / 2) {
									tempStr = to_string(j) + ". " + currSub[j - 1].getName();
									ltListString += fitList(tempStr, listRect, font, listPts) + '\n';
								}
								else if (j == (listMax + 1) / 2) {
									tempStr = to_string(j) + ". " + currSub[j - 1].getName();
									ltListString += fitList(tempStr, listRect, font, listPts);
								}
								else if (j > (listMax + 1) / 2 && j < listMax + 1) {
									tempStr = to_string(j) + ". " + currSub[j - 1].getName();
									rtListString += fitList(tempStr, listRect, font, listPts) + '\n';
								}
								else {
									tempStr = to_string(j) + ". " + currSub[j - 1].getName();
									rtListString += fitList(tempStr, listRect, font, listPts);
								}
							}

							ltListText.setString(ltListString);
							rtListText.setString(rtListString);
							ltListText.setPosition(listX + 20, listY + 20);
							rtListText.setPosition(screenWidth / 2 + 20, listY + 20);

							tempTime = timerText.getString();
							tempBest = bestString;
							tempLeft = ltListString;
							tempRight = rtListString;
						}

						// If subfamily is found, sorts all the weapons in that subfamily and displays the top 11
						else if (!newSub.empty()) {

							isValidSearch = true;
							inSub = true;
							inFam = false;
							isSorted = true;
							showBest = true;
							showMethods = true;
							showList = true;
							showItem = false;

							/*tempTime.clear();
							timerText.setString(tempTime);
							tempBest.clear();
							tempLeft.clear();
							tempRight.clear();*/

							bestString.clear();
							bestText.setString(bestString);
							ltListString.clear();
							ltListText.setString(ltListString);
							rtListString.clear();
							rtListText.setString(rtListString);

							arsenal.tempVec.clear();

							currSub = newSub;
							cout << "Size of Subfamily \"" << search << "\": " << currSub.size() << endl;
							unsortedSub = currSub;

							sortNTime(timerText, arsenal, currSub, isQuickSort, isSust, isFwd, homeWindow, font);
							bestStr = currSub[0].getName();
							bestString = fitText(bestStr, bestRect, font, bestPts);
							bestText.setString(bestString);
							setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

							int listMax = 19;
							if (currSub.size() < 19) {
								listMax = currSub.size();
							}

							for (int j = 2; j < listMax + 1; j++) {
								if (j < (listMax + 1) / 2) {
									tempStr = to_string(j) + ". " + currSub[j - 1].getName();
									ltListString += fitList(tempStr, listRect, font, listPts) + '\n';
								}
								else if (j == (listMax + 1) / 2) {
									tempStr = to_string(j) + ". " + currSub[j - 1].getName();
									ltListString += fitList(tempStr, listRect, font, listPts);
								}
								else if (j > (listMax + 1) / 2 && j < listMax + 1) {
									tempStr = to_string(j) + ". " + currSub[j - 1].getName();
									rtListString += fitList(tempStr, listRect, font, listPts) + '\n';
								}
								else {
									tempStr = to_string(j) + ". " + currSub[j - 1].getName();
									rtListString += fitList(tempStr, listRect, font, listPts);
								}
							}

							ltListText.setString(ltListString);
							rtListText.setString(rtListString);
							ltListText.setPosition(listX + 20, listY + 20);
							rtListText.setPosition(screenWidth / 2 + 20, listY + 20);

							tempTime = timerText.getString();
							tempBest = bestString;
							tempLeft = ltListString;
							tempRight = rtListString;
						}

						// If weapon is found, displays the weapon's stats of its first instance found
						else if (result.getName() != "DNE") {

							isValidSearch = true;
							showBest = true;
							showItem = true;
							showMethods = false;
							showList = true;

							bestStr = result.getName();
							bestString = fitText(bestStr, bestRect, font, bestPts);
							bestText.setString(bestString);
							setText(bestText, screenWidth / 2, bestY + bestHeight / 2);
						
							if (isSorted) {
								ltListString = "Rank: " + to_string(arsenal.getIndex(currSub, result) + 1) + '\n';
							}
							else {
								ltListString = "";
							}
							ltListString += "\nFamily: " + result.getFam() +
								"\nSubfamily: " + result.getSubFam();
							rtListString = "Sustained DPS : " + to_string(result.getSusDPS()) +
								"\nBurst DPS: " + to_string(result.getBurstDPS());
							if (!isPri(result)) {
								rtListString += "\nTotal Damage: " + to_string(result.getTotDamage());
							}

							ltListText.setString(ltListString);
							rtListText.setString(rtListString);
							ltListText.setPosition(listX + 20, listY + 20);
							rtListText.setPosition(screenWidth / 2 + 20, listY + 20);
						}

						// If no results are found, prompts the user to try again
						else {

							isValidSearch = false;

							bestStr = "";
							bestString = "Invalid input!\nPress \'esc' to try again.";
							bestText.setString(bestString);
							setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

							showBest = true;
							showItem = false;
							showMethods = false;
							showList = false;
						}
					}
					cout << "Will item be shown on next screen? " << showItem << endl;
				}

				// Escape allows the user exit their selection and the program in its entirety
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

					// If search is empty, exits the program
					if (searchString.getSize() == 0 && !showBest) {
						homeWindow.close();
						return 0;
					}

					else if (searchString.getSize() > 0) {
							
						    // If in a sorted family or subfamily list screen, resets screen and family/subfamily
							if ((inSub || inFam) && !showItem && isValidSearch) {

								timerText.setString("");
								bestString.clear();
								bestText.setString(bestString);
								ltListString.clear();
								ltListText.setString(ltListString);
								rtListString.clear();
								rtListText.setString(rtListString);

								currSub = arsenal.tempVec;
								arsenal.tempVec.clear();

								isSust = false;
								isBurst = false;
								isSorted = false;
								inSub = false;
								inFam = false;
								showBest = false;
								showMethods = false;
								showList = false;
							}

							// If an invalid search or item screen, resets to previous screen
							else if (!isValidSearch || showItem || showBest) {

							showItem = false;
							showList = true;

							if (isSust || isBurst) {
								showMethods = true;
							}

							timerText.setString(tempTime);

							bestString = tempBest;
							bestString = fitText(bestString, bestRect, font, bestPts);
							bestText.setString(bestString);
							setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

							ltListString = tempLeft;
							rtListString = tempRight;

							ltListText.setString(ltListString);
							rtListText.setString(rtListString);
							ltListText.setPosition(listX + 20, listY + 20);
							rtListText.setPosition(screenWidth / 2 + 20, listY + 20);
						}
					}

					// If on item screen, exits to previous screen
					else if (showItem) {

						showItem = false;
						showList = true;

						if (isSust || isBurst) {
							showMethods = true;
						}

						timerText.setString(tempTime);

						bestString = tempBest;
						bestString = fitText(bestString, bestRect, font, bestPts);
						bestText.setString(bestString);
						setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

						ltListString = tempLeft;
						rtListString = tempRight;

						ltListText.setString(ltListString);
						rtListText.setString(rtListString);
						ltListText.setPosition(listX + 20, listY + 20);
						rtListText.setPosition(screenWidth / 2 + 20, listY + 20);
					}

					// If showing information but not showing item, clears screen
					else if (showBest) {

						timerText.setString("");
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

					// Resets search
					isValidSearch = true;
					search.clear();
					searchString.clear();
					searchText.setString(searchString);
					setText(searchText, screenWidth / 2, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);
				}
			}

			else if (event.type == sf::Event::TextEntered) {
				
				// Update search string with newest character entered
				if (event.text.unicode >= 32 && event.text.unicode <= 126) {

					search += static_cast<char>(event.text.unicode);
					searchString += static_cast<char>(event.text.unicode);
					searchType(searchString, searchStart, search, searchBar, font, searchPts);
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

				// If current subfamily is empty, sets it to all weapons
				if (currSub.empty()) {
					currSub = arsenal.tempVec;
					currSub = arsenal.createAll(arsenal.allWeapons);
					cout << "Size of arsenal: " << currSub.size() << endl;
					unsortedSub = currSub;
				}

				if (isSorted && isValidSearch) {
					cout << "Is item currently being show? " << showItem << endl;
					// Pressing the top weapon box reveals that weapons stats
					if (bestRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {

						if (!showItem) {
							tempTime = timerText.getString();
							timerText.setString("");
							tempBest = bestString;
							tempLeft = ltListString;
							tempRight = rtListString;
						}

						showItem = !showItem;

						Weapon result = arsenal.searchItem(currSub, bestStr);

						if (showItem) {

							showMethods = false;
							showList = true;

							ltListString = "Rank: " + to_string(arsenal.getIndex(currSub, result) + 1) +
								"\nFamily: " + result.getFam() +
								"\nSubfamily: " + result.getSubFam();
							rtListString = "Sustained DPS : " + to_string(result.getSusDPS()) +
								"\nBurst DPS: " + to_string(result.getBurstDPS());
							if (!isPri(result)) {
								rtListString += "\nTotal Damage: " + to_string(result.getTotDamage());
							}

							ltListText.setString(ltListString);
							rtListText.setString(rtListString);
							ltListText.setPosition(listX + 20, listY + 20);
							rtListText.setPosition(screenWidth / 2 + 20, listY + 20);
						}

						else {

							timerText.setString(tempTime);

							bestString = tempBest;
							bestString = fitText(bestString, bestRect, font, bestPts);
							bestText.setString(bestString);
							setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

							showMethods = true;

							ltListString = tempLeft;
							rtListString = tempRight;

							ltListText.setString(ltListString);
							rtListText.setString(rtListString);
							ltListText.setPosition(listX + 20, listY + 20);
							rtListText.setPosition(screenWidth / 2 + 20, listY + 20);
						}
					}
				}

				// Checks if sustained DPS button was pressed, calls sorting by sustained DPS values and displays top results
				if (inCircle(borderRad, sustX0, buttonY0, mousePos)) {

					cout << "Current vector size: " << currSub.size() << endl;

					showMethods = true;

					bestString.clear();
					bestText.setString(bestString);
					ltListString.clear();
					ltListText.setString(ltListString);
					rtListString.clear();
					rtListText.setString(rtListString);

					isSust = !isSust;

					if (!isSust) {
						timerText.setString("");
						isSorted = false;
						showBest = false;
						showMethods = false;
						showList = false;
						currSub = unsortedSub;
					}

					else {

						isValidSearch = true;
						isNum = false;
						isBurst = false;
						isSorted = true;
						showItem = false;
						
						search.clear();
						searchString.clear();
						searchText.setString(searchString);
						setText(searchText, screenWidth / 2, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);

						currSub = unsortedSub;

						sortNTime(timerText, arsenal, currSub, isQuickSort, isSust, isFwd, homeWindow, font);
						bestStr = currSub[0].getName();
						bestString = fitText(bestStr, bestRect, font, bestPts);
						bestText.setString(bestString);
						setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

						tempTime = timerText.getString();
						tempBest = bestString;
					}

					int listMax = 19;
					if (currSub.size() < 19) {
						listMax = currSub.size();
					}

					for (int j = 2; j < listMax + 1; j++) {
						if (j < (listMax + 1) / 2) {
							tempStr = to_string(j) + ". " + currSub[j - 1].getName();
							ltListString += fitList(tempStr, listRect, font, listPts) + '\n';
						}
						else if (j == (listMax + 1) / 2) {
							tempStr = to_string(j) + ". " + currSub[j - 1].getName();
							ltListString += fitList(tempStr, listRect, font, listPts);
						}
						else if (j > (listMax + 1) / 2 && j < listMax + 1) {
							tempStr = to_string(j) + ". " + currSub[j - 1].getName();
							rtListString += fitList(tempStr, listRect, font, listPts) + '\n';
						}
						else {
							tempStr = to_string(j) + ". " + currSub[j - 1].getName();
							rtListString += fitList(tempStr, listRect, font, listPts);
						}
					}

					ltListText.setString(ltListString);
					rtListText.setString(rtListString);
					ltListText.setPosition(listX + 20, listY + 20);
					rtListText.setPosition(screenWidth / 2 + 20, listY + 20);
					
					if (isSust) {
						tempLeft = ltListString;
						tempRight = rtListString;
					}
				}

				// Checks if burst DPS button was pressed, calls sorting by burst DPS values and displays top results
				else if (inCircle(borderRad, burstX0, buttonY0, mousePos)) {

					cout << "Current vector size: " << currSub.size() << endl;

					showMethods = true;

					bestString.clear();
					bestText.setString(bestString);
					ltListString.clear();
					ltListText.setString(ltListString);
					rtListString.clear();
					rtListText.setString(rtListString);

					isBurst = !isBurst;

					if (!isBurst) {
						timerText.setString("");
						isSorted = true;
						showBest = false;
						showMethods = false;
						showList = false;
						currSub = unsortedSub;
					}

					else {

						isValidSearch = true;
						isNum = false;
						isSust = false;
						isSorted = true;
						showItem = false;
						
						search.clear();
						searchString.clear();
						searchText.setString(searchString);
						setText(searchText, screenWidth / 2, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);

						currSub = unsortedSub;

						sortNTime(timerText, arsenal, currSub, isQuickSort, isSust, isFwd, homeWindow, font);
						bestStr = currSub[0].getName();
						bestString = fitText(bestStr, bestRect, font, bestPts);
						bestText.setString(bestString);
						setText(bestText, screenWidth / 2, bestY + bestHeight / 2);
					}

					int listMax = 19;
					if (currSub.size() < 19) {
						listMax = currSub.size();
					}

					for (int j = 2; j < listMax + 1; j++) {
						if (j < (listMax + 1) / 2) {
							tempStr = to_string(j) + ". " + currSub[j - 1].getName();
							ltListString += fitList(tempStr, listRect, font, listPts) + '\n';
						}
						else if (j == (listMax + 1) / 2) {
							tempStr = to_string(j) + ". " + currSub[j - 1].getName();
							ltListString += fitList(tempStr, listRect, font, listPts);
						}
						else if (j > (listMax + 1) / 2 && j < listMax + 1) {
							tempStr = to_string(j) + ". " + currSub[j - 1].getName();
							rtListString += fitList(tempStr, listRect, font, listPts) + '\n';
						}
						else {
							tempStr = to_string(j) + ". " + currSub[j - 1].getName();
							rtListString += fitList(tempStr, listRect, font, listPts);
						}
					}

					ltListText.setString(ltListString);
					rtListText.setString(rtListString);
					ltListText.setPosition(listX + 20, listY + 20);
					rtListText.setPosition(screenWidth / 2 + 20, listY + 20);

					if (isBurst) {
						tempLeft = ltListString;
						tempRight = rtListString;
					}
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

						currSub = unsortedSub;

						sortNTime(timerText, arsenal, currSub, isQuickSort, isSust, isFwd, homeWindow, font);
						bestStr = currSub[0].getName();
						bestString = fitText(bestStr, bestRect, font, bestPts);
						bestText.setString(bestString);
						setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

						int listMax = 19;
						if (currSub.size() < 19) {
							listMax = currSub.size();
						}

						for (int j = 2; j < listMax + 1; j++) {
							if (j < (listMax + 1) / 2) {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								ltListString += fitList(tempStr, listRect, font, listPts) + '\n';
							}
							else if (j == (listMax + 1) / 2) {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								ltListString += fitList(tempStr, listRect, font, listPts);
							}
							else if (j > (listMax + 1) / 2 && j < listMax + 1) {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								rtListString += fitList(tempStr, listRect, font, listPts) + '\n';
							}
							else {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								rtListString += fitList(tempStr, listRect, font, listPts);
							}
						}

						ltListText.setString(ltListString);
						rtListText.setString(rtListString);
						ltListText.setPosition(listX + 20, listY + 20);
						rtListText.setPosition(screenWidth / 2 + 20, listY + 20);

						tempTime = timerText.getString();
						tempBest = bestString;
						tempLeft = ltListString;
						tempRight = rtListString;
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

						currSub = unsortedSub;

						sortNTime(timerText, arsenal, currSub, isQuickSort, isSust, isFwd, homeWindow, font);
						bestStr = currSub[0].getName();
						bestString = fitText(bestStr, bestRect, font, bestPts);
						bestText.setString(bestString);
						setText(bestText, screenWidth / 2, bestY + bestHeight / 2);


						int listMax = 19;
						if (currSub.size() < 19) {
							listMax = currSub.size();
						}

						for (int j = 2; j < listMax + 1; j++) {
							if (j < (listMax + 1) / 2) {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								ltListString += fitList(tempStr, listRect, font, listPts) + '\n';
							}
							else if (j == (listMax + 1) / 2) {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								ltListString += fitList(tempStr, listRect, font, listPts);
							}
							else if (j > (listMax + 1) / 2 && j < listMax + 1) {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								rtListString += fitList(tempStr, listRect, font, listPts) + '\n';
							}
							else {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								rtListString += fitList(tempStr, listRect, font, listPts);
							}
						}

						ltListText.setString(ltListString);
						rtListText.setString(rtListString);
						ltListText.setPosition(listX + 20, listY + 20);
						rtListText.setPosition(screenWidth / 2 + 20, listY + 20);

						tempTime = timerText.getString();
						tempBest = bestString;
						tempLeft = ltListString;
						tempRight = rtListString;
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

						currSub = unsortedSub;

						sortNTime(timerText, arsenal, currSub, isQuickSort, isSust, isFwd, homeWindow, font);
						bestStr = currSub[0].getName();
						bestString = fitText(bestStr, bestRect, font, bestPts);
						bestText.setString(bestString);
						setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

						int listMax = 19;
						if (currSub.size() < 19) {
							listMax = currSub.size();
						}

						for (int j = 2; j < listMax + 1; j++) {
							if (j < (listMax + 1) / 2) {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								ltListString += fitList(tempStr, listRect, font, listPts) + '\n';
							}
							else if (j == (listMax + 1) / 2) {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								ltListString += fitList(tempStr, listRect, font, listPts);
							}
							else if (j > (listMax + 1) / 2 && j < listMax + 1) {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								rtListString += fitList(tempStr, listRect, font, listPts) + '\n';
							}
							else {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								rtListString += fitList(tempStr, listRect, font, listPts);
							}
						}

						ltListText.setString(ltListString);
						rtListText.setString(rtListString);
						ltListText.setPosition(listX + 20, listY + 20);
						rtListText.setPosition(screenWidth / 2 + 20, listY + 20);

						tempTime = timerText.getString();
						tempBest = bestString;
						tempLeft = ltListString;
						tempRight = rtListString;
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

						currSub = unsortedSub;

						sortNTime(timerText, arsenal, currSub, isQuickSort, isSust, isFwd, homeWindow, font);
						bestStr = currSub[0].getName();
						bestString = fitText(bestStr, bestRect, font, bestPts);
						bestText.setString(bestString);
						setText(bestText, screenWidth / 2, bestY + bestHeight / 2);

						int listMax = 19;
						if (currSub.size() < 19) {
							listMax = currSub.size();
						}

						for (int j = 2; j < listMax + 1; j++) {
							if (j < (listMax + 1) / 2) {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								ltListString += fitList(tempStr, listRect, font, listPts) + '\n';
							}
							else if (j == (listMax + 1) / 2) {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								ltListString += fitList(tempStr, listRect, font, listPts);
							}
							else if (j > (listMax + 1) / 2 && j < listMax + 1) {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								rtListString += fitList(tempStr, listRect, font, listPts) + '\n';
							}
							else {
								tempStr = to_string(j) + ". " + currSub[j - 1].getName();
								rtListString += fitList(tempStr, listRect, font, listPts);
							}
						}

						ltListText.setString(ltListString);
						rtListText.setString(rtListString);
						ltListText.setPosition(listX + 20, listY + 20);
						rtListText.setPosition(screenWidth / 2 + 20, listY + 20);

						tempTime = timerText.getString();
						tempBest = bestString;
						tempLeft = ltListString;
						tempRight = rtListString;
					}
				}
				
				if (isSust || isBurst) {
					showBest = true;
					showList = true;
				}
			}
		}

		// Clears window and sets color and borderless screen
		homeWindow.clear(darkerGray);
		homeWindow.draw(borderlessScreen);

		// Displays timer text box if text exists
		if (timerText.getGlobalBounds().width > 0) {
			homeWindow.draw(timerRect);
			homeWindow.draw(timerText);
		}

		// Displays best text box if showBest is true and text exists
		if (showBest && bestText.getGlobalBounds().width > 0) {
			homeWindow.draw(bestRect);
			homeWindow.draw(bestText);
		}

		// Displays methods buttons if showMethods is true, with appropriate highlights to show current selection
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

		// Displays list text box if showList is true and text exists
		if (showList && isValidSearch && ltListText.getGlobalBounds().width > 0) {
			homeWindow.draw(listRect);
			homeWindow.draw(ltListText);
			homeWindow.draw(rtListText);
		}

		// Displays DPS button highlights to show current selection
		if (isSust) {
			isSust = true;
			homeWindow.draw(sustHighlight);
			
		}
		else if (isBurst) {
			isBurst = true;
			homeWindow.draw(burstHighlight);
		}

		// Displays DPS buttons
		homeWindow.draw(sustBorder);
		homeWindow.draw(burstBorder);
		homeWindow.draw(sustButton);
		homeWindow.draw(burstButton);
		homeWindow.draw(sustText);
		homeWindow.draw(burstText);

		// Displays search bar and text
		homeWindow.draw(searchBar);
		homeWindow.draw(searchText);

		// Displays cursor if showCursor is true
		if (showCursor) {
			setText(cursorText, screenWidth / 2 + searchText.getGlobalBounds().width / 2 + 4, screenHeight / 3 + searchBar.getGlobalBounds().height / 4);
			homeWindow.draw(cursorText);
		}
		
		// Actually displays the window
		homeWindow.display();
	}

	return 0;
}
