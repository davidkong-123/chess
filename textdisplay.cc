#include "textdisplay.h"
#include "observer.h"
#include <iostream>
#include <string>

// Initializes textdisplay. 
TextDisplay::TextDisplay() {
	for (int i = 0; i < 8; ++i) {
		std::vector <char> text;
		for (int j = 0; j < 8; ++j) {

			if (i == 0) {
				if ((j == 0) || (j == 7)) {
					text.emplace_back('r');
				} else if ((j == 1) || (j == 6)) {
					text.emplace_back('n');
				} else if ((j == 2) || (j == 5)) {
					text.emplace_back('b');
				} else if (j == 3) {
					text.emplace_back('q');
				} else {
					text.emplace_back('k');
				}
			} else if (i == 1) {
				text.emplace_back('p');
			} else if (i == 6) {
				text.emplace_back('P');
			} else if (i == 7) {
				if ((j == 0) || (j == 7)) {
					text.emplace_back('R');
				} else if ((j == 1) || (j == 6)) {
					text.emplace_back('N');
				} else if ((j == 2) || (j == 5)) {
					text.emplace_back('B');
				} else if (j == 3) {
					text.emplace_back('Q');
				} else {
					text.emplace_back('K');
				}
			} else if ((i == 2) || (i == 4)) {
				if ((j % 2) == 0) {
					text.emplace_back(' ');
				} else {
					text.emplace_back('_');
				}
			} else {
				if ((j % 2) == 0) {
					text.emplace_back('_');
				} else {
					text.emplace_back(' ');
				}
			}
		}
		theDisplay.emplace_back(text);
	}
}

// Updates textdisplay according to the Info of the board.
void TextDisplay::notify(int r, X c, char type) {
	theDisplay.at(8 - r).at(static_cast<int>(c)) = type;
}

// reset td
void TextDisplay::reset_td(){
    theDisplay.clear();
    for (int i = 0; i < 8; ++i) {
		std::vector <char> text;
		for (int j = 0; j < 8; ++j) {

			if (i == 0) {
				if ((j == 0) || (j == 7)) {
					text.emplace_back('r');
				} else if ((j == 1) || (j == 6)) {
					text.emplace_back('n');
				} else if ((j == 2) || (j == 5)) {
					text.emplace_back('b');
				} else if (j == 3) {
					text.emplace_back('q');
				} else {
					text.emplace_back('k');
				}
			} else if (i == 1) {
				text.emplace_back('p');
			} else if (i == 6) {
				text.emplace_back('P');
			} else if (i == 7) {
				if ((j == 0) || (j == 7)) {
					text.emplace_back('R');
				} else if ((j == 1) || (j == 6)) {
					text.emplace_back('N');
				} else if ((j == 2) || (j == 5)) {
					text.emplace_back('B');
				} else if (j == 3) {
					text.emplace_back('Q');
				} else {
					text.emplace_back('K');
				}
			} else if ((i == 2) || (i == 4)) {
				if ((j % 2) == 0) {
					text.emplace_back(' ');
				} else {
					text.emplace_back('_');
				}
			} else {
				if ((j % 2) == 0) {
					text.emplace_back('_');
				} else {
					text.emplace_back(' ');
				}
			}
		}
		theDisplay.emplace_back(text);
	}
}

char TextDisplay::output_char(int i, int j) {
    char a = theDisplay.at(i).at(j);
    return a;
}

void TextDisplay::make_td(std::shared_ptr<TextDisplay> const_td) {
    theDisplay.clear();
    for (int i = 0; i < 8; ++i) {
        std::vector <char> text;
        for (int j = 0; j < 8; ++j) {
            text.emplace_back(const_td->output_char(i,j));
        }
        theDisplay.emplace_back(text);
    }
}



// Outputs textdisplay. 
std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
	for (int i = 0; i < 8; ++i) {
		std::vector <char> tmp = td.theDisplay[i];
		std::cout << 8 - i << " ";
		for (int j = 0; j < 8; ++j) {
			std::cout << tmp[j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "  abcdefgh" << std::endl;
	return out;
}	










