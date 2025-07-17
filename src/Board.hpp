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

	// 보드 초기화
	void Initialize();

	// 특정 위치에 벽이 있는지 확인
	bool IsWall(int x, int y) const;

	// 보드 전체 그리기
	void Draw() const;

	// 보드 크기 반환
	int GetSize() const { return BOARD_SIZE; }

	// 셀 크기 반환
	int GetCellSize() const { return CELL_SIZE; }

	// 특정 위치의 값 설정/가져오기
	void SetCell(int x, int y, int value);
	int GetCell(int x, int y) const;

	// 플레이어가 이동 가능한지 확인 (보드 범위 내이고 벽이 아닌지)
	bool CanMoveTo(int x, int y) const;
};
