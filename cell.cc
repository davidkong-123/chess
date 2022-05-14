#include "cell.h"


bool Cell::get_occupy() {
	return is_occupy;
}

X Cell::get_x() {
	return x_cor;
}

int Cell::get_y() {
	return y_cor; 
}

char Cell::get_colour() {
	return colour;
}

void Cell::erase() {
	is_occupy = false;
}

// Sets the colour of a given piece. 
void Cell::setPiece(Chess chess) { 
	is_occupy = true;
	this->colour = chess.get_colour();
}

/*
// Flips the colour of a given piece. 
void Cell::toggle() {
	if (colour == Colour::Black) { 
		this->colour = Colour::White;
	} else if (colour == Colour::White) {
		this->colour = Colour::Black;
	} else {
		return;
	}
}

// Changes the state or info of a cell based on the subject, and then
// recursively notify each one of its own observers. 
void Cell::notify(Subject<Info, State> &whoFrom) {
	if (colour == Colour::NoColour) return;
	State other = whoFrom.getState();
	Info other_info = whoFrom.getInfo(); 

	struct State tmp;

	// getting the direction from whoFrom to me. 
	if (other_info.row == r && other_info.col > c) {
		tmp.direction = Direction::E;
	} else if (other_info.row == r) {
		tmp.direction = Direction::W;
	} else if (other_info.col == c && other_info.row > r) {
		tmp.direction = Direction::S;
	} else if (other_info.col == c) {
		tmp.direction = Direction::N;
	} else if (other_info.col < c && other_info.row < r) {	
		tmp.direction = Direction::NW;
	} else if (other_info.col > c && other_info.row > r) {
		tmp.direction = Direction::SE;
	} else if (other_info.col < c && other_info.row > r) {
		tmp.direction = Direction::SW;
	} else if (other_info.row < r && other_info.col > c) {
		tmp.direction = Direction::NE;
	}
	
	// Reacts dependending on subject's state. 
	if (other.type == StateType::NewPiece) {
		if (other_info.colour == colour) return;
		tmp.type = StateType::Relay;
		tmp.colour = other_info.colour;
		setState(tmp);
		notifyObservers();
	} else if (other.type == StateType::Relay) {
		if (other.direction != tmp.direction) return;
		if (other.colour != colour) {
			tmp.type = StateType::Relay;
			tmp.colour = other.colour;
		} else {
			tmp.type = StateType::Reply;
			tmp.colour = other.colour;
		}
		setState(tmp);
		notifyObservers();
	} else {
		if ((other.direction == Direction::W && tmp.direction == Direction::E) 
			||(other.direction == Direction::E && tmp.direction == Direction::W)
			||(other.direction == Direction::N && tmp.direction == Direction::S)
			||(other.direction == Direction::S && tmp.direction == Direction::N)
			||(other.direction == Direction::NW && tmp.direction == Direction::SE)
			||(other.direction == Direction::SE && tmp.direction == Direction::NW)
			||(other.direction == Direction::SW && tmp.direction == Direction::NE)
			||(other.direction == Direction::NE && 
				tmp.direction == Direction::SW)) {
			if (colour == other.colour) return;
			tmp.type = StateType::Reply;
			tmp.colour = other.colour;
			tmp.direction = other.direction;
			this->toggle();
			setState(tmp);
			notifyObservers();
		}
	}
}

// Gets the info (its row, column, colour) of a cell. 
Info Cell::getInfo() const {
  Info tmp = {r, c, colour};
	return tmp;
}*/
