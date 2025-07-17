#include "Board.hpp"
#include "Window.hpp"
#include <iostream>

void Board::CreateWallBuffer()
{
}

void Board::CreateGridBuffer()
{
}

Board::Board()
{
	Initialize();
}

Board::~Board()
{
}

void Board::Initialize()
{
	// 기본 미로 패턴으로 보드 초기화
	int initialBoard[BOARD_SIZE][BOARD_SIZE] = {
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1}};

	// 배열 복사
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			board[i][j] = initialBoard[i][j];
		}
	}

	// 버퍼 생성
	CreateWallBuffer();
	CreateGridBuffer();

	// std::cout << "Board initialized with size: " << BOARD_SIZE << "x" << BOARD_SIZE << std::endl;
	// std::cout << "Cell size: " << CELL_SIZE << "x" << CELL_SIZE << std::endl;
}

bool Board::IsWall(int x, int y) const
{
	if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
		return true;

	return board[y][x] == 1;
}

void Board::Draw() const
{
	// 버퍼를 사용하여 성능 향상 (draw 호출 최소화)
	// array에서 buffer로 바꾼 이유: 각 벽마다 draw를 호출하면 성능 저하가 발생할 수 있으므로,
	// 모든 벽을 하나의 VertexBuffer에 담아 한 번에 GPU에 그리기 위해 buffer를 사용함.
	// 벽 버퍼 생성
	// sf::VertexArray wallBuffer(sf::PrimitiveType::Quads);
	sf::VertexBuffer wallBuffer(sf::PrimitiveType::Quads);
	std::vector<sf::Vertex> wallVertices;

	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			if (board[i][j] == 1)
			{
				sf::Vector2f topLeft(j * CELL_SIZE, i * CELL_SIZE);
				sf::Vector2f topRight((j + 1) * CELL_SIZE, i * CELL_SIZE);
				sf::Vector2f bottomRight((j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE);
				sf::Vector2f bottomLeft(j * CELL_SIZE, (i + 1) * CELL_SIZE);

				wallVertices.push_back(sf::Vertex(topLeft, WALL_COLOR));
				wallVertices.push_back(sf::Vertex(topRight, WALL_COLOR));
				wallVertices.push_back(sf::Vertex(bottomRight, WALL_COLOR));
				wallVertices.push_back(sf::Vertex(bottomLeft, WALL_COLOR));
			}
		}
	}
	wallBuffer.create(wallVertices.size());
	wallBuffer.update(wallVertices.data());
	Window::GetInstance()->Draw(wallBuffer);

	// 격자 버퍼 생성
	sf::VertexBuffer gridBuffer(sf::PrimitiveType::Lines);
	std::vector<sf::Vertex> gridVertices;

	// 수평선
	for (int i = 0; i <= BOARD_SIZE; ++i)
	{
		gridVertices.push_back(sf::Vertex(sf::Vector2f(0, i * CELL_SIZE), WALL_OUTLINE_COLOR));
		gridVertices.push_back(sf::Vertex(sf::Vector2f(BOARD_SIZE * CELL_SIZE, i * CELL_SIZE), WALL_OUTLINE_COLOR));
	}

	// 수직선
	for (int i = 0; i <= BOARD_SIZE; ++i)
	{
		gridVertices.push_back(sf::Vertex(sf::Vector2f(i * CELL_SIZE, 0), WALL_OUTLINE_COLOR));
		gridVertices.push_back(sf::Vertex(sf::Vector2f(i * CELL_SIZE, BOARD_SIZE * CELL_SIZE), WALL_OUTLINE_COLOR));
	}

	gridBuffer.create(gridVertices.size());
	gridBuffer.update(gridVertices.data());
	Window::GetInstance()->Draw(gridBuffer);
}

void Board::SetCell(int x, int y, int value)
{
	if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
	{
		board[y][x] = value;
	}
}

int Board::GetCell(int x, int y) const
{
	if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
	{
		return board[y][x];
	}
	return 1; // 범위 밖은 벽으로 간주
}

bool Board::CanMoveTo(int x, int y) const
{
	// 범위 내이고 벽이 아닌 경우에만 이동 가능
	if (x < 0 || x >= BOARD_SIZE * CELL_SIZE || y < 0 || y >= BOARD_SIZE * CELL_SIZE)
		return false;

	// 픽셀 좌표를 보드 좌표로 변환
	int boardX = x / CELL_SIZE;
	int boardY = y / CELL_SIZE;

	return !IsWall(boardX, boardY);
}
