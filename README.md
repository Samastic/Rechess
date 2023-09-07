TO DO:
----------rewrite chess constructor so the teams are flipped (moron)
- turn logic
	- turn clock
	- pinning (softcheck);
		i. run through every move and see if any matche the square the B king is on, if it is, find W piece
		ii. once you W find piece, find all moves inbetween W piece and B king
		iii. find all B pieces that can move to ii spaces
	- check
		+ not letting player put themself in check
	- checkmate

	
- en passant
	\\ probably needs to be a 2d array like allmoves but only 2 rows

DONE:
- piece premoves; getAllMoves()
	+ sliders; getSlider()
		* rook
		* bishop
		* queen
	+ knight; getHopper()
	+ pawn; getPawn()
	+ king; getKing()
		* validate king movement against enemy sightlines
- store premoves as vector and 2d array;
- moving pieces; takeTurn()
	+ show player all possible moves for a piece; showMoves()
	+ get player input; inputPiece()
	+ decode player input; strtoint()
	+ validate movement against premoves; movePiece()
	+ update board


NOTES:
to get opposite team do 1-n; 1-1 = 0, 1-0 = 1,
changed teams from teams[0][16], teams[1][16] to teams[2][16]