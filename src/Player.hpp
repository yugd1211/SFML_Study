#pragma once
#include <SFML/Graphics.hpp>
class Board;
class Window;

class Player
{
private:
    // 플레이어를 화면에 표시하기 위한 SFML의 사각형 도형 객체입니다.
    sf::RectangleShape shape;

    // 플레이어의 현재 바라보는 방향을 나타내는 각도입니다.
    // C++의 삼각함수(cos, sin)는 라디안(radian) 단위를 사용하므로, 우리도 라디안을 기본 단위로 사용합니다.
    // (참고: 360도 = 2 * PI 라디안)
    float angle;
    float moveSpeed;
    float rotationSpeed;

public:
    Player(float startX, float startY);
    void handleInput(const sf::Event &event, const Board &board);
    void draw(Window *window) const;
};