#include <cstdlib> 
#include <iostream> 
#include <string>
#include <sstream>
#include <vector>
#include "rechess.h"

// MISC AND CONSTS
namespace {
	char const KING = 'K', QUEEN = 'Q', ROOK = 'R', BISHOP = 'B', KNIGHT = 'N', PAWN = 'P';
	char const LAYOUT[8] = { ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK };
	int const ORTH = 0, DIAG = 1, WHITE = 0, BLACK = 1;
	int const GAMEOVER = 2, CHECK = 1;

	std::string const LINE = " -----------------------------------------", BAR = " | ";

	//intput:
	// char position in string; string[pos]
	//output:
	//	characters a = 0, b = 1, etc
	//	integers = int - 1
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

	//returns team color
	std::string sayTeam(int team) {
		if (team == 0) {
			//L + ratio + didn't ask + you're white
			return "White";
		}
		return "Black";
	}

	//returns piece type
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
		default:
			return "Error: enter valid piece.";
		}
		return "\n\n\n\n\n\n\n\n\n... how?";
	};

	//prints all moves (x,y) = (i*2, i*2+1) in a given vector
	void sayMoves(std::vector<int> checkmoves) {
		int size = checkmoves.size() / 2;
		std::cout << "\n---Checkmoves; size = " << size;
		for (int i = 0; i < size; i++) {
			std::cout << "\n" << i << " (" << checkmoves[i * 2] << ", " << checkmoves[(i * 2 + 1)] << ")";
		}
	}

	//input:
	//	type determines is movement is Orthoganol (0) or Diagonal (1)
	//	dir chooses which direction to set initializers
	//output:
	//	modifies referenced (x,y) initializers to cast a ray
	void setSliderDirection(int& initX, int& initY, int type, int dir) {
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

	void setHopperDirection(int& initX, int& initY, int xdir, int ydir, int i, int j) {
		int temp;
		//swaps direction variables
		if (i && 1) {
			temp = ydir;
			ydir = xdir;
			xdir = temp;
		}
		//flips direction of xdir on 3,4
		if (j < 2) {
			initX = xdir;
		}
		else {
			initX = xdir * -1;
		}
		//flips direction of ydir on 1,3
		if (j % 2 == 0) {
			initY = ydir;
		}
		else {
			initY = ydir * -1;
		}
		return;
	}

	int setDirection(int a, int b) {
		if (b > a) {
			return 1;
		}
		else if (b < a) {
			return -1;
		}
		else if (a == b) {
			return 0;
		}
		else {
			std::cout << "setDirection Error";
			return 2;
		}
	}

	//returns true if input is in bounds
	bool checkBounds(int& checkX, int& checkY) {
		return (checkX < 8 && checkX >= 0 && checkY < 8 && checkY >= 0);
	}
}

// HARD/SOFT CHECK
namespace rechess {

	bool const Chess::findHit(Piece& checkP, Piece& king) {
		int size = checkP.sizeofMoves();
		//std::cout << "\nPiece: " << sayType(checkP.getType()) << " " << sayTeam(checkP.getTeam());
		//std::cout << "\nPossible moves: " << size / 2 << ", Pos:" << checkP.getXpos() << ", " << checkP.getYpos() << "\n";
		if (checkP.getTeam() == king.getTeam()) {
			return false;
		}
		for (int i = 0; i < size / 2; i++) {
			//std::cout << i + 1 << ". " << checkP.getMove(i * 2) << checkP.getMove(i * 2 + 1);

			if ((checkP.getMove(i * 2) == king.getXpos()) && (checkP.getMove(i * 2 + 1) == king.getYpos())) {
				return true;
			}

			//std::cout << "\t\t";

			if (i % 2 == 1) {
				//std::cout << "\n";
			}
		}
		return false;
	}

	void const Chess::getCheckmoves(Piece* checkP, Piece& king, std::vector<int>& checkmoves) {
		int Kxpos = king.getXpos(), Kypos = king.getYpos(),
			Pxpos = checkP->getXpos(), Pypos = checkP->getYpos(),
			checkX, checkY,
			xdir = 0, ydir = 0,
			xdist = abs(Kxpos - Pxpos), ydist = abs(Kypos - Pypos),
			checkdist = (xdist >= ydist) ? xdist : ydist;
		std::cout << "\n" << checkP->getType();
		std::cout << "\n\n" << "Kpos (" << Kxpos << ", " << Kypos << "); Ppos (" << Pxpos << ", " << Pypos << ")\n";

		if (xdist == 0 && ydist == 0) {
			std::cout << "\n no distance";
			return;
		}

		xdir = setDirection(Kxpos, Pxpos);
		ydir = setDirection(Kypos, Pypos);

		std::cout << "\n  xdir = " << xdir << "\n  ydir = " << ydir;

		int step = 1;
		while (step < checkdist) {
			checkX = Kxpos + (step * xdir);
			checkY = Kypos + (step * ydir);
			
			if (board[checkX][checkY] != nullptr) {
				break;
			}

			std::cout << "\n\t\tcheckmove: (" << checkX << ", " << checkY << ")";
			checkmoves.push_back(checkX);
			checkmoves.push_back(checkY);
			step++;
		}
	}

	//returns different integers for different situations
	// 2 = game over
	// 1 = in check
	// 0 = not in check
	int const Chess::hardCheck(Piece& king) {

		int hits = 0, enemyteam = 1 - king.getTeam();
		bool incheck = false;
		std::vector<Piece*> enemy;
		std::vector<int> checkmoves;
		for (int i = 0; i < 16; i++) {
			if (teams[0][i].getType() == 'K') { continue; }
			if (findHit(teams[enemyteam][i], king)) {
				hits++;
				enemy.push_back(&teams[enemyteam][i]);
				std::cout << "\nHit! " << teams[enemyteam][i].getType();
			}
		}
		
		if (hits < 1) {
			return incheck;
		}

		std::cout << "\n-------------------In check!";
		incheck = true;
		std::cout << "\n\nHits = " << hits;
		for (int i = 0; i < hits; i++) {
			if (enemy[i]->getType() != KNIGHT) {
				getCheckmoves(enemy[i], king, checkmoves);
			}
			else {
				std::cout << "\n Knight hit the king. No checkmoves!";
			}
		}

		//sayMoves(checkmoves);

		if (checkmoves.size() > 0) {
			//trimTeamMoves();
		}

		return incheck;
	}

	bool const Chess::softCheck(Piece& king) {
		if (sliderCheck(king) || hopperCheck(king)) {
			return true;
		}
		return false;
	}

	//returns true if in check, also coordinates softchecking
	bool const Chess::sliderCheck(Piece& king) {
		int enemyteam = 1 - king.getTeam();
		int checkX = 0, checkY = 0,
			initX, initY,
			j;
		bool go, check = false;
		Piece checkP, * tempP;
		std::vector<Piece*> teammates;
		std::vector<int> tempmoves;
		/*if (king.getType() == 'K') {
			std::cout << "\n\ninCheck revieved king, " << king.getTeam() << king.getType();
		}
		else {
			std::cout << "\n\ninCheck not king, " << king.getTeam() << king.getType();

			return false;
		}*/
		for (int type = 0; type < 2; type++) {
			for (int i = 0; i < 4; i++) {
				setSliderDirection(initX, initY, type, i);
				//std::cout << "\n---raycaster inits: " << initX << ", " << initY;
				j = 1;
				go = true;
				teammates.clear();
				do {
					/*std::cout << "\n\tLoop#: " << j << ", go = " << go
						<< "\n\t\tXpos: " << king.getXpos() << " + " << (j * initX)
						<< "\n\t\tXpos: " << king.getXpos() << " + " << (j * initX)
						<< "\n\t\tYpos: " << king.getYpos() << " + " << (j * initY);
					*/
					checkX = king.getXpos() + (j * initX);
					checkY = king.getYpos() + (j * initY);
					//std::cout << "\n\t\t\tCheck X, Y: (" << checkX << ", " << checkY << ")";
					if (!checkBounds(checkX, checkY)) {
						//std::cout << " - Bounds";
						break;
					}
					if (board[checkX][checkY] == nullptr) {
						j++;
						tempmoves.push_back(checkX);
						tempmoves.push_back(checkY);
						continue;
					}
					//std::cout << " - not null";
					tempP = board[checkX][checkY];
					checkP = *tempP;
					if (checkP.getTeam() == king.getTeam()) {
						//std::cout << " - hit friend";
						teammates.push_back(tempP);
						continue;
					}
					//std::cout << " - hit enemy";
					tempmoves.push_back(checkX);
					tempmoves.push_back(checkY);
					if (teammates.size() > 1) {
						//std::cout << " - enemy can't pin";
					}
					else {
						if (type == ORTH && (checkP.getType() == ROOK || checkP.getType() == QUEEN)) {
							//teammate is in soft check
						}
						else if (type == DIAG && (checkP.getType() == BISHOP || checkP.getType() == QUEEN)) {
							//teammate is in soft check

						}
					}

					j++;
				} while (go);
			}
		}
		return check;
	}

	bool const Chess::hopperCheck(Piece& unit) {

		return false;
	}
}

// MOVEMENT
namespace rechess {
	void const Chess::getSlider(Piece& unit, int type) {
		getSlider(unit, type, 8);
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
		for (int dir = 0; dir < 4; dir++) {
			setSliderDirection(initX, initY, type, dir);
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
				sightlines[unit.getTeam()][checkX][checkY] = 1;
				unit.addMove(checkX, checkY);
				j++;
			} while (go == true && j <= limit);
		}
	}

	void const Chess::getHopper(Piece& unit) {
		int xdir = 1, ydir = 2,
			checkX = 0, checkY = 0,
			initX = 0, initY = 0;
		bool go = false;
		Piece checkP;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				setHopperDirection(initX, initY, xdir, ydir, i, j);
				checkX = unit.getXpos() + initX;
				checkY = unit.getYpos() + initY;
				//std::cout << "\n\t\tCheck X, Y (" << checkX << "," << checkY << ") ; (" << initX << "," << initY << ")";

				if (!checkBounds(checkX, checkY)) {
					//std::cout << " - bounds";
					continue;
				}
				if (board[checkX][checkY] != nullptr) {
					checkP = *board[checkX][checkY];
					if (checkP.getTeam() == unit.getTeam()) {
						//std::cout << " - hit team";
						continue;
					}
					//std::cout << " - hit enemy";
				}
				sightlines[unit.getTeam()][checkX][checkY] = 1;
				unit.addMove(checkX, checkY);
				//std::cout << "\n\t\t  Adding to " << unit.getTeam() << unit.getType() << " move (" << checkX << "," << checkY << ")";

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
			sightlines[unit.getTeam()][initX][initY + dir] = 1;
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
						sightlines[unit.getTeam()][checkX][checkY] = 1;
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
			if (sightlines[enemyteam][unit.getMove(i - 1)][unit.getMove(i)] == 1) {
				//std::cout << " ---------erased << "," << i - 1 << ", " << i;"					
				unit.eraseMove(i - 1, i);
			}
		}
	}

	void const Chess::getPieceMoves(Piece& unit) {
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

	void const Chess::getEveryMove() {
		
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				sightlines[0][i][j] = 0;
				sightlines[1][i][j] = 0;
			}
		}

		for (int i = 0; i < 16; i++) {
			
			if (teams[0][i].getType() != 'K') {
				getPieceMoves(teams[0][i]);
				getPieceMoves(teams[1][i]);
			}
			
		}
	
		getPieceMoves(teams[0][4]);
		getPieceMoves(teams[1][4]);
		getPieceMoves(teams[0][4]);
	}

}

// TURN & I/O
namespace rechess {
	std::string const Chess::inputPos() {
		std::string input;
		std::cout << "\nEnter a rank and file (Ex: a1): ";
		std::cin >> input;
		return input;
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

	bool const Chess::showMoves(Piece* input) {

		if (input->sizeofMoves() < 2) {
			std::cout << "\nThe piece " << input->getTeam() << input->getType() << " has no moves!";
			return false;
		}

		int size = input->sizeofMoves();
		std::cout << "\nPossible moves: " << size / 2 << "\n";
		for (int i = 0; i < size / 2; i++) {
			std::cout << i + 1 << ". " << inttochar(input->getMove(i * 2)) << input->getMove(i * 2 + 1) + 1;

			std::cout << "\t\t";

			if (i % 2 == 1) {
				std::cout << "\n";
			}
		}

		return true;
	}

	bool const Chess::movePiece(Piece* input, int pointB[2]) {
		bool out = false;
		int size = input->sizeofMoves(),
			team = input->getTeam();
		for (int i = 0; i < size; i += 2) {
			std::cout << "movePiece " << i << ", " << i + 1;
			if (input->getMove(i) == pointB[0] && input->getMove(i + 1) == pointB[1]) {
				std::cout << "\n" << sayTeam(input->getTeam()) << " " << sayType(input->getType()) << " move is valid";

				board[pointB[0]][pointB[1]] = board[input->getXpos()][input->getYpos()];
				board[input->getXpos()][input->getYpos()] = nullptr;

				teams[team][input->getTpos()].setXpos(pointB[0]);
				teams[team][input->getTpos()].setYpos(pointB[1]);
				return true;
			}
		}

		return false;
	}

	void const Chess::takeTurn(int turn) {
		std::string input;
		int pointA[2], pointB[2];
		bool validmove;
		Piece temp, * tomove;

		/*if (turn == 0) {
			std::cout << "\nWHITE TURN";
		}
		else {
			std::cout << "\nBLACK TURN";
		}*/
		do {
			validmove = false;
			std::cout << "\nPick a piece to move. ";
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

			tomove = board[pointA[0]][pointA[1]];
			temp = *tomove;

			if (temp.getTeam() != turn) {
				std::cout << "\nError: you must pick your own team";
				continue;
			}

			while (showMoves(board[pointA[0]][pointA[1]]) == true) {
				std::cout << "\nType 0 to choose another piece.";
				input = inputPos();

				pointB[0] = strtoint(input[0]);
				pointB[1] = strtoint(input[1]);
				if (pointB[0] == -1) {
					//std::cout << "\nPiece movement aborted.";
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
		int turncount = 0, turn = 0, checkstate;
		bool winstate = false;
		
		std::cout << "\nSTARTING GAME.";

		//moving left w bishop
		

		//white pawns
		board[0][1] = nullptr;
		board[3][1] = nullptr;

		//black pawns
		board[0][6] = nullptr;
		board[2][6] = nullptr;
		board[3][6] = nullptr;
		board[4][6] = nullptr;

		getEveryMove();
		std::cout << "\nturn #" << turncount << ", " << sayTeam(turn);
		
		//int pointB[2] = { 6, 4 };
		//movePiece(board[0][2], pointB);

		do {
			setBoardtemp();
			
			//do {

			display();
			takeTurn(turn);			
			
			getEveryMove();

			turncount++;
			turn = turncount % 2;

			switch (hardCheck(teams[turn][4])) {
			case GAMEOVER:
				winstate = true;
				std::cout << "\n\n\n\nGame Over! " << sayTeam(turn) << " is checkmate, " << sayTeam(1 - turn) << " wins! Conchessulations!";
				break;
			case CHECK:
				break;
			case 0:
				//king is not in check;
				break;
			}
			
			
			

			clearSightlines();
			

			std::cout << "turn #" << turncount << ", " << sayTeam(turn);
		} while (!winstate);

		display();
	}

}

// VARIABLES MANIPULATORS & CONSTRUCTER
namespace rechess {
	/*Chess::Chess() {
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
	}*/

	Chess::Chess() {
		int unitstart, pawnstart;
		Piece* pawnlocation, * unitlocation;

		for (int i = 0; i < 2; i++) {
			unitstart = i * 7;  // unitstart is 0 for white (i=0) and 7 for black (i=1)
			pawnstart = 1 + (i * 5);  // pawnstart is 1 for white (i=0) and 6 for black (i=1)

			for (int j = 0; j < 8; j++) {
				Piece man(i, LAYOUT[j], abs(unitstart - j), unitstart, j);
				Piece pawn(i, PAWN, abs(unitstart - j), pawnstart, j + 8);

				teams[i][j] = man;                                   
				teams[i][j + 8] = pawn;                              
				unitlocation = &teams[i][j];                         
				pawnlocation = &teams[i][j + 8];

				board[abs(unitstart - j)][unitstart] = unitlocation;
				board[abs(unitstart - j)][pawnstart] = pawnlocation;
			}
		}
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

	void const Chess::clearSightlines() {
		for (int t = 0; t < 2; t++) {
			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {
					//std::cout << "sightlines(" << t << x << y << "): " << sightlines[t][x][y] << "\n";
					sightlines[t][x][y] = 0;
				}
			}
		}
	}
}
