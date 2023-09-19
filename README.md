GOALS:
1. Functioning Chess Engine in C++
(2). Custom Pieces and Piece Swapping
(3). gold pair of pants

TO DO:
----------rewrite chess constructor so the teams are flipped (moron)
- king everythinng (VERY IN PROGRESS);
	* hardCheck()
		- checks every piece on the enemy team to see if they hit the king
		- if king is hit twice, game over
		- is yes, draw a line between the king and the piece that hit it
			* trimmoves() off all moves that aren't in that line for all pieces on the king's team
	* softCheck()
		- slider
			* shoot ray out in orth and diag directions
			* if 2 pieces, enemy can't pin
			* if 1 piece is inbetween the enemy and king, softcheck
				- send piece to trimMoves()
	* trimMoves(vector<int> newmoves)
		- trims moves from a piece that don't match newmoves
- turn clock
- a pinned piece's movement, moveCheck()
	+ checks to see if a move is in the available moves during check
- checkmate
	
- en passant
	+ probably needs to be a 2d array like allmoves but only 2 rows

DONE:
- kingstuff
	+ validating king moves; checkKing()
			* move not in enemy sightlines
- piece premoves; getEveryMove()
	+ sliders; getSlider()
		* rook
		* bishop
		* queen
		* king
	+ knight; getHopper()
	+ pawn; getPawn()
	
- store premoves as vector and 2d array;
- moving pieces; takeTurn()
	+ show player all possible moves for a piece; showMoves()
	+ get player input; inputPos()
	+ decode player input; strtoint()
	+ validate movement against premoves; movePiece()
	+ update board


NOTES:
to get opposite team do 1-n; 1-1 = 0, 1-0 = 1,
changed teams from teams[0][16], teams[1][16] to teams[2][16]