#include <cstdlib> 
#include <iostream> 
#include <string>
#include <sstream>
#include <vector>
#include "rechess.h"

// PIECE
namespace rechess {
	Piece::Piece() : team(0), type(0), Xpos(-1), Ypos(-1), Tpos(0), status(0)
	{}

	Piece::Piece(int team_in, char type_in, int Xpos_in, int Ypos_in, int Tpos_in)
		: team(team_in), type(type_in), Xpos(Xpos_in), Ypos(Ypos_in), Tpos(Tpos_in), status(0)
	{}

	int const Piece::getTeam() {
		return team;
	}
	void const Piece::setTeam(int in) {
		team = in;
	}

	char const Piece::getType() {
		return type;
	}
	void const Piece::setType(char in) {
		type = in;
	}

	int const Piece::getStatus() {
		return status;
	}
	void const Piece::setStatus(int in) {
		status = in;
	}

	int const Piece::getXpos() {
		//std::cout << "\ngetXpos: " << Xpos;
		return Xpos;
	}
	void const Piece::setXpos(int in) {
		Xpos = in;
	}

	int const Piece::getYpos() {
		//std::cout << "\ngetYpos: " << Ypos;
		return Ypos;
	}
	void const Piece::setYpos(int in) {
		Ypos = in;
	}

	int const Piece::getTpos() {
		return Tpos;
	}
	void const Piece::setTpos(int in) {
		Tpos = in;
	}

	void const Piece::clearMoves() {
		moves.clear();
	}

	void const Piece::addMove(int x_in, int y_in) {
		moves.push_back(x_in);
		moves.push_back(y_in);
	}

	int const Piece::sizeofMoves() {
		return moves.size();
	}

	int const Piece::getMove(int in) {
		return moves[in];
	}

	void const Piece::eraseMove(int x_in, int y_in) {
		std::vector<int>::iterator x_it = moves.begin() + x_in, y_it = moves.begin() + y_in;
		moves.erase(x_it, y_it + 1);
	}
}