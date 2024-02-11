#include "Chess.h"

void print(const Game &g) {
	std::cout << '\r' << "------------------------------------------------ MOVE " << g.turn << " -------------"<< std::endl;
	for (unsigned i=0; i < 8; ++i) {
		for (unsigned j=0; j < 8; ++j) {
			g.getPiece(i, j)->print();
			std::cout << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// random function with a uniform distribution
int random(int a, int b) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(a, b);
	return dis(gen);
}

void waitForInput() {
	std::cout << "Press enter to continue..." << "\e[A";
	std::cin.ignore();
	for (int i=0; i < 10; ++i) std::cout << "\e[A";
}

void randomMove(Game &g) {
	// get all pieces that are allowed to move
	std::vector<Piece*> moveable_pieces;
	pieceColor player = g.currentPlayer();
	for (unsigned i=0; i < 8; ++i) {
		for (unsigned j=0; j < 8; ++j) {
			Piece* p = g.getPiece(i, j);
			if (p->color == player && !p->legalMoves.empty())
				moveable_pieces.push_back(p);
		}
	}
	// pick one and make a random legal move with it
	Piece* p = moveable_pieces.at( random(0, moveable_pieces.size()-1) );
	g.move(p->legalMoves.at( random(0, p->legalMoves.size()-1) ));
}

int main() {
	Game g;
	while (g.state == gameState::PLAYING) {
		print(g);
		waitForInput();
		randomMove(g);
	}
	/* -- game ended -- */
	print(g);
	switch(g.state) {
		case gameState::DRAW: std::cout << "Game is a draw!"; break;
		case gameState::WON_WHITE: std::cout << "White won!"; break;
		case gameState::WON_BLACK: std::cout << "Black won!"; break;
		default: break;
	}
	std::cin.ignore();
	return 0;
}