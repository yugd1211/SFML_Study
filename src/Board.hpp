#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#define BOARD_SIZE 8
#define CELL_SIZE 50
#define OUTLINE_SIZE 5

#define WALL_COLOR sf::Color::White
#define WALL_OUTLINE_COLOR sf::Color::Black

class Board
{
private:
	int board[BOARD_SIZE][BOARD_SIZE];

	// 렌더링 버퍼들
	sf::VertexBuffer wallBuffer;
	sf::VertexBuffer gridBuffer;

	// 버퍼 생성 함수들
	void CreateWallBuffer();
	void CreateGridBuffer();

public:
	Board();
	~Board();

	void Initialize();
	bool IsWall(int x, int y) const;
	void Draw() const;

	int GetSize() const { return BOARD_SIZE; }
	int GetCellSize() const { return CELL_SIZE; }

	void SetCell(int x, int y, int value);
	int GetCell(int x, int y) const;

	bool CanMoveTo(int x, int y) const;
};
