#include <cstdlib> 
#include <iostream> 
#include <string>
#include <sstream>
#include <vector>
#include "rechess.h"

// MISC
namespace {
	char const KING = 'K', QUEEN = 'Q', ROOK = 'R', BISHOP = 'B', KNIGHT = 'N', PAWN = 'P';
	char const LAYOUT[8] = { ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK };
	int const ORTH = 0, DIAG = 1, WHITE = 0, BLACK = 1;

	std::string const LINE = " -----------------------------------------", BAR = " | ";

	//std::string[position] to int
	//char int = int - 1
	int strtoint(char in) {
		int out;

		if (in > 96) {
			out = in - 97;

		}
		else {
			out = in - 49;
		}
		return out;
	}

	//int to char
	char inttochar(int in) {
		char out;
		out = in + 97;
		return out;
	}

	std::string sayTeam(int team) {
		if (team == 0) {
			//L + ratio + didn't ask + you're white
			return "White";
		}
		return "Black";
	}

	std::string sayType(char type) {
		switch (type) {
		case KING:
			return "King";
		case QUEEN:
			return "Queen";
		case ROOK:
			return "Rook";
		case KNIGHT:
			return "Knight";
		case BISHOP:
			return "Bishop";
		case PAWN:
			return "Pawn";
		}
	};

	void setDirection(int& initX, int& initY, int type, int dir) {
		switch (dir) {
		case 0: // N and NW
			initX = type * -1;
			initY = 1;
			break;
		case 1: //E and NE
			initX = 1;
			initY = type;
			break;
		case 2: //S and SE
			initX = type;
			initY = -1;
			break;
		case 3: //W and SW
			initX = -1;
			initY = type * -1;
			break;
		}
	}

	//returns true if input is in bounds
	bool checkBounds(int& checkX, int& checkY) {
		return (checkX < 8 && checkX >= 0 && checkY < 8 && checkY >= 0);
	}
}

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
		moves.erase(x_it, y_it+1);
	}
}

// TURN
namespace rechess {
	std::string const Chess::inputPos() {
		std::string input;
		std::cout << "\nPlease enter a rank and file (Ex: a1): ";
		std::cin >> input;
		return input;
	}

	bool const Chess::showMoves(Piece* input) {
		Piece tomove = *input;

		if (tomove.sizeofMoves() < 2) {
			std::cout << "\nThe piece " << tomove.getTeam() << tomove.getType() << " has no moves!";
			return false;
		}

		int size = tomove.sizeofMoves();
		std::cout << "\nPossible moves: " << size / 2 << "\n";
		for (int i = 0; i < size / 2; i++) {
			std::cout << i + 1 << ". " << inttochar(tomove.getMove(i * 2)) << tomove.getMove(i * 2 + 1) + 1;

			std::cout << "\t\t";

			if (i % 2 == 1) {
				std::cout << "\n";
			}
		}

		return true;
	}

	bool const Chess::movePiece(Piece* input, int pointB[2]) {
		Piece tomove = *input;
		bool out = false;
		int size = tomove.sizeofMoves();
		for (int i = 0; i < size; i += 2) {
			//std::cout << "checking " << i << ", " << i + 1;
			if (tomove.getMove(i) == pointB[0] && tomove.getMove(i + 1) == pointB[1]) {
				std::cout << "\n" << sayTeam(tomove.getTeam()) << " " << sayType(tomove.getType()) << " move is valid";
				board[pointB[0]][pointB[1]] = board[tomove.getXpos()][tomove.getYpos()];
				board[tomove.getXpos()][tomove.getYpos()] = nullptr;
				if (tomove.getTeam() == 0) {
					teams[0][tomove.getTpos()].setXpos(pointB[0]);
					teams[0][tomove.getTpos()].setYpos(pointB[1]);
				}
				else {
					teams[1][tomove.getTpos()].setXpos(pointB[0]);
					teams[1][tomove.getTpos()].setYpos(pointB[1]);
				}
				return true;
			}
		}

		return false;
	}

	void const Chess::takeTurn(int turn) {
		std::string input;
		char char_in[2];
		int pointA[2], pointB[2], movelistnumber;
		bool validmove, movepick;
		Piece* tomove;

		/*if (turn == 0) {
			std::cout << "\nWHITE TURN";
		}
		else {
			std::cout << "\nBLACK TURN";
		}*/
		do {
			validmove = false;
			input = inputPos();
			pointA[0] = strtoint(input[0]);
			pointA[1] = strtoint(input[1]);

			std::cout << "\npointA input: (" << input[0] << ", " << input[1] << ") | board coords: (" << pointA[0] << ", " << pointA[1] << ")";

			if (!checkBounds(pointA[0], pointA[1])) {
				std::cout << "\nError: input out-of-bounds";
				continue;
			}

			if (board[pointA[0]][pointA[1]] == nullptr) {
				std::cout << "\nError: that space is empty";
				continue;
			}

			/*if (piecetomove.getTeam() != turn) {
				std::cout << "\nError: you must pick your own team";
				continue;
			}*/

			tomove = board[pointA[0]][pointA[1]];
			while(showMoves(tomove) == true) {
				std::cout << "\nType 0 to choose another tile.";
				input = inputPos();

				pointB[0] = strtoint(input[0]);
				pointB[1] = strtoint(input[1]);
				if (pointB[0] == -1) {
					std::cout << "\nPiece movement aborted. Choose another tile:";
					break;
				}

				validmove = movePiece(tomove, pointB);

				if (validmove == true) {
					std::cout << "\nAt previous point (" << pointA[0] << ", " << pointA[1] << "): " << board[pointA[0]][pointA[1]];
					break;
				}
				else {
					std::cout << "\n\nInvalid Move! Try again.";
				}
			}
		} while (validmove == false);
	}

	void const Chess::startGame() {
		int turncount = 0, turn;
		bool winstate = false, incheck = false;
		board[0][1] = nullptr;
		board[3][1] = nullptr;

		board[0][6] = nullptr;
		board[2][6] = nullptr;
		board[3][6] = nullptr;
		board[4][6] = nullptr;
		
		do {
			getAllMoves();
			setBoardtemp();
			turn = turncount % 2;
			//do {
			display();
			takeTurn(turn);
			clearAllmoves();
			//if (ifCheck(turn) == true){setBoard(); incheck = true;}
			//else {incheck == false;}
			//} while (incheck == true);
			turncount++;
		} while (!winstate);
	}

}

// MOVEMENT
namespace rechess {
	void const Chess::getSlider(Piece& unit, int type) {
		getSlider(unit, type, 7);
	}

	void const Chess::getSlider(Piece& unit, int type, int limit) {
		std::cout << "\tlimit: " << limit;
		int checkX = 0, checkY = 0,
			initX, initY,
			j;
		bool go;
		Piece checkP;

		/*std::cout << "\nPiece: " << unit.getTeam() << unit.getType();
		std::cout << "\nXpos: " << unit.getXpos();
		std::cout << "\nYpos: " << unit.getYpos();*/

		for (int i = 0; i < 4; i++) {
			setDirection(initX, initY, type, i);
			j = 1;
			go = true;
			do {
				//std::cout << "\n\t\t\tXpos: " << unit.getXpos() << " + " << (j * initX);
				//std::cout << "\n\t\t\tYpos: " << unit.getYpos() << " + " << (j * initY);
				checkX = unit.getXpos() + (j * initX);
				checkY = unit.getYpos() + (j * initY);
				//std::cout << "\n\t\tCheck X, Y: (" << checkX << ", " << checkY << ")";
				if (!checkBounds(checkX, checkY)) {
					//std::cout << " - Bounds";
					break; 
				}
				if (board[checkX][checkY] != nullptr) {
					checkP = *board[checkX][checkY];
					if (checkP.getTeam() == unit.getTeam()) {
						//std::cout << " - hit team";
						break;
					}
					//std::cout << " - hit enemy";
					go = false;
				}
				//std::cout << " - Adding";
				allmoves[unit.getTeam()][checkX][checkY] = 1;
				unit.addMove(checkX, checkY);
				j++;
			} while (go == true && j <= limit);
		}
	}

	void const Chess::getHopper(Piece& unit) {
		int checkX = 0, checkY = 0,
			initX = 0, initY = 0;
		bool go = false;
		Piece checkP;

		//std::cout << "\nPiece: " << unit.getTeam() << unit.getType();
		//std::cout << "\nXpos: " << unit.getXpos();
		///std::cout << "\nYpos: " << unit.getYpos();

		for (int i = 0; i < 4; i++) {
			initX = ((i % 2) + 1);
			initY = (2 - (i % 2));
			switch (i) {
			case 2:
				initY *= -1;
				break;
			case 3:
				initX *= -1;
				break;
			}
			for (int j = 0; j < 2; j++) {
				if (i % 2 == 0) {
					//std::cout << "\n\tvertical " << initY;
					initX *= -1; //first does negative check and then times' itself to get postive check
				}
				else {
					//std::cout << "\n\thorizontal " << initX;
					initY *= -1;
				}

				checkX = unit.getXpos() + initX;
				checkY = unit.getYpos() + initY;
				//std::cout << "\n\t\tCheck X, Y (" << checkX << "," << checkY << ")";

				if (checkX < 8 && checkX >= 0 && checkY < 8 && checkY >= 0) {
					if (board[checkX][checkY] != nullptr) {
						checkP = *board[checkX][checkY];
						if (checkP.getTeam() != unit.getTeam()) {
							//std::cout << " - hit enemy";
						}
						else if (checkP.getTeam() == unit.getTeam()) {
							//std::cout << " - hit team";
							continue;
						}
					}

					allmoves[unit.getTeam()][checkX][checkY] = 1;
					unit.addMove(checkX, checkY);
					//std::cout << "\n\t\t  Adding to " << unit.getTeam() << unit.getType() << " move (" << checkX << "," << checkY << ")";
				}
				else {
					//std::cout << " - out of bounds";
				}
			}
		}

	}

	void const Chess::getPawn(Piece& unit) {
		int checkX, checkY,
			initX = unit.getXpos(), initY = unit.getYpos(),
			dir = 1;
		bool go = false;
		Piece checkP;

		//std::cout << "\nPiece: " << unit.getTeam() << unit.getType();
		//std::cout << "\nXpos: " << unit.getXpos();
		//std::cout << "\nYpos: " << unit.getYpos();

		if (unit.getTeam() == 1) {
			dir = -1;
		}

		if (board[initX][initY + dir] == nullptr) {
			//std::cout << "\t\n Forward (" << initX << ", " << initY + dir << ")";
			allmoves[unit.getTeam()][initX][initY + dir] = 1;
			unit.addMove(initX, initY + dir);

			if (board[initX][initY + (dir * 2)] == nullptr && initY == (7 * unit.getTeam()) + dir) {
				//std::cout << "\t\n Two Forward (" << initX << ", " << initY + dir << ")";
				unit.addMove(initX, initY + (dir * 2));
			}
		}

		for (int i = -1; i < 2; i += 2) {
			checkX = initX + i;
			checkY = initY + dir;
			if (checkX < 8 && checkX >= 0 && checkY < 8 && checkY >= 0) {
				if (board[checkX][checkY] != nullptr) {
					checkP = *board[checkX][checkY];
					if (checkP.getTeam() != unit.getTeam()) {
						//std::cout << " - hit enemy";
						allmoves[unit.getTeam()][checkX][checkY] = 1;
						unit.addMove(checkX, checkY);
					}
				}
			}
		}
	}

	void const Chess::checkKing(Piece& unit) {
		int enemyteam = 1 - unit.getTeam(),
			totalmoves = unit.sizeofMoves() - 1;
		//validate king moves
		for (int i = totalmoves; i > 0; i -= 2) {
			/*std::cout << "\n enemy team = " << enemyteam 
				<< ",\t moves size = " << (totalmoves+1)/2
				<< ",\t moves pos: " << i - 1 << ", " << i 
				<< ",\t board pos: " << unit.getMove(i-1) << ", " << unit.getMove(i);*/
			if (allmoves[enemyteam][unit.getMove(i-1)][unit.getMove(i)] == 1) {
				//std::cout << " ---------erased << "," << i - 1 << ", " << i;"					
				unit.eraseMove(i-1, i);
			}
		}
	}

	/*void const Chess::checkKing(Piece& unit) {
		int checkX = 0, checkY = 0,
			initX, initY,
			checkteam = 1 - unit.getTeam();
		Piece checkP;

		std::cout << "\nPiece: " << unit.getTeam() << unit.getType();
		std::cout << "\nXpos: " << unit.getXpos();
		std::cout << "\nYpos: " << unit.getYpos();

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				setDirection(initX, initY, i, j);

				checkX = unit.getXpos() + initX;
				checkY = unit.getYpos() + initY;
				std::cout << "\n\t\tCheck Allmoves " << sayTeam(checkteam) << " team: " << allmoves[checkteam][checkX][checkY];
				std::cout << "\n\t\tCheck X, Y (" << checkX << "," << checkY << ")";



				if (checkBounds(checkX, checkY)) {
					if (allmoves[checkteam][checkX][checkY] == 1) {
						std::cout << " - enemy sight line";
						continue;
					}
					else if (allmoves[checkteam][checkX][checkY] == 2) {
						std::cout << " - king sight line";
						allmoves[unit.getTeam()][checkX][checkY] = 2;

						for (int k = 0; k < unit.sizeofMoves(); k += 2) {
							std::cout << "\n\t\t\t\t" << i << ", " << i + 1;
							if (unit.getMove(k) == checkX && unit.getMove(k + 1) == checkY) {
								unit.eraseMove(k, k + 1);
								break;
							}
						}
						continue;
					}

					if (board[checkX][checkY] != nullptr) {

						checkP = *board[checkX][checkY];
						if (checkP.getTeam() != unit.getTeam()) {
							std::cout << " - hit enemy";
						}
						else if (checkP.getTeam() == unit.getTeam()) {
							std::cout << " - hit team";
							continue;
						}
					}


					if (allmoves[checkteam][checkX][checkY] != 1) {
						allmoves[unit.getTeam()][checkX][checkY] = 2;
						std::cout << "\n\t\t\t allmoves";
					}

					unit.addMove(checkX, checkY);
					std::cout << "\n\t\t  Adding to " << unit.getTeam() << unit.getType() << " move (" << checkX << "," << checkY << ")";
				}
				else {
					std::cout << " - out of bounds";
				}
			}
		}
	}*/

	void const Chess::addtoAllMoves(Piece& unit) {
		unit.clearMoves();
		std::cout << "\nChecking: " << unit.getTeam() << unit.getType();
		switch (unit.getType()) {
		case KING:
			getSlider(unit, ORTH, 1);
			getSlider(unit, DIAG, 1);
			checkKing(unit);
			break;
		case QUEEN:
			getSlider(unit, ORTH);
			getSlider(unit, DIAG);
			break;
		case ROOK:
			getSlider(unit, ORTH);
			break;
		case KNIGHT:
			getHopper(unit);
			break;
		case BISHOP:
			getSlider(unit, DIAG);
			break;
		case PAWN:
			getPawn(unit);
			break;
		default:
			break;
		}
	}

	void const Chess::getAllMoves() {
		
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				allmoves[0][i][j] = 0;
				allmoves[1][i][j] = 0;
			}
		}

		for (int i = 0; i < 16; i++) {
			
			if (teams[0][i].getType() != 'K') {
				addtoAllMoves(teams[0][i]);
				addtoAllMoves(teams[1][i]);
			}
			
		}
	
		addtoAllMoves(teams[0][4]);
		addtoAllMoves(teams[1][4]);
		addtoAllMoves(teams[0][4]);
	}

}

// GAME & BOARD
namespace rechess {
	Chess::Chess() {
		int file1, file2,
			k;
		Piece* pawnlocation, * unitlocation;

		for (int i = 0; i < 2; i++) {
			if (i == 0) {
				//std::cout << "\n--WHITE";
				k = 0;
				file1 = 0;
				file2 = 1;
			}
			else {
				//std::cout << "\n--BLACK";
				k = 7;
				file1 = 7;
				file2 = 6;
			}
			for (int j = 0; j < 8; j++) {
				Piece man(i, LAYOUT[j], abs(k - j), file1, j);
				Piece pawn(i, PAWN, abs(k - j), file2, j + 8);

				//std::cout << "\ni: " << i << " | Type: " << LAYOUT[j] << " | abs(k-j): " << k << " - " << j << " = " << abs(k-j);
				if (i == 0) {
					teams[0][j] = man;
					teams[0][j + 8] = pawn;
					unitlocation = &teams[0][j];
					pawnlocation = &teams[0][j + 8];

					//std::cout << "\n" << "W MAN:  " << teams[0][j].getTeam() << teams[0][j].getType() << " | STORED: " << unitlocation;
					//std::cout << "\tW PAWN: " << teams[0][j + 8].getTeam() << teams[0][j + 8].getType() << " | STORED: " << pawnlocation;
				}
				else {
					teams[1][j] = man;
					teams[1][j + 8] = pawn;
					unitlocation = &teams[1][j];
					pawnlocation = &teams[1][j + 8];

					//std::cout << "\n" << "B MAN:  " << teams[1][j].getTeam() << teams[1][j].getType() << " | STORED: " << unitlocation;
					//std::cout << "\tB PAWN: " << teams[1][j + 8].getTeam() << teams[1][j + 8].getType() << " | STORED: " << pawnlocation;
				}
				board[abs(k - j)][file1] = unitlocation;
				//std::cout << "\n\t " << teams[0][j].getType() << " pos: " << teams[0][j].getXpos() << ", " << teams[0][j].getYpos();
				board[abs(k - j)][file2] = pawnlocation;

			}
			//std::cout << "\n";
		}
	}

	void const Chess::display() {
		int team;
		char type, color = 0;
		Piece temp;

		std::cout << "\n";
		for (int y = 7; y > -1; y--) {
			std::cout << LINE << "\n";

			for (int x = 0; x < 8; x++) {
				std::cout << BAR;
				if (board[x][y] != nullptr) {
					temp = *board[x][y];
					team = temp.getTeam();
					type = temp.getType();
					if (team == 0) {
						color = 'W';
					}
					else {
						color = 'B';
					}
					std::cout << color << type;
				}
				else {
					std::cout << "  ";
				}
			}
			std::cout << BAR << " " << y + 1 << "\n";
		}
		std::cout << LINE << "\n" << "   a    b    c    d    e    f    g    h\n";
	}

	void const Chess::setBoardtemp() {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				boardtemp[x][y] = board[x][y];
			}
		}
	}

	void const Chess::setBoard() {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				board[x][y] = boardtemp[x][y];
			}
		}
	}

	void const Chess::clearAllmoves() {
		for (int t = 0; t < 2; t++) {
			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {
					//std::cout << "allmoves(" << t << x << y << "): " << allmoves[t][x][y] << "\n";
					allmoves[t][x][y] = 0;
				}
			}
		}
	}
}