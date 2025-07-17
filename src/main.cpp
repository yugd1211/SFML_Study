#include <SFML/Graphics.hpp>
#include <iostream>
#include "Color.hpp"
#include "Window.hpp"
#include "Board.hpp"
#define X first
#define Y second
using namespace std;

pair<int, int> PlayerMoveInput(const sf::Event &event, const Board &board, const sf::RectangleShape &player)
{
    int moveDistance = 10;
    int x = 0, y = 0;

    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
        y = -moveDistance;
    else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
        y = moveDistance;
    else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
        x = -moveDistance;
    else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
        x = moveDistance;

    // 새로운 위치가 이동 가능한지 확인
    sf::Vector2f currentPos = player.getPosition();
    int newX = currentPos.x + x;
    int newY = currentPos.y + y;

    if (board.CanMoveTo(newX, newY))
    {
        return make_pair(x, y);
    }

    return make_pair(0, 0); // 이동 불가능한 경우 이동하지 않음
}

void GameExit()
{
    cout << "게임을 종료합니다." << endl;
    Window::GetInstance()->Close();
    Window::DestroyInstance();
    exit(0);
}

int main()
{
    // 윈도우 인스턴스 생성 및 초기화
    Window::GetInstance()->Create("SFML Project");

    // 보드 생성
    Board gameBoard;

    // 플레이어
    sf::RectangleShape player(sf::Vector2f(10, 10));
    player.setPosition(50, 50); // 빈 공간에 배치
    player.setFillColor(sf::Color::Green);

    // 메인 루프
    while (Window::GetInstance()->IsOpen())
    {
        sf::Event event;
        while (Window::GetInstance()->PollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Window::GetInstance()->Close();

            if (event.type == sf::Event::KeyPressed)
            {
                // ESC 키로 종료
                if (event.key.code == sf::Keyboard::Escape)
                    GameExit();
                else
                {
                    pair<int, int> dir = PlayerMoveInput(event, gameBoard, player);
                    player.move(dir.X, dir.Y);
                }
            }
        }
        Window::GetInstance()->Clear(BACKGROUND_COLOR);

        // 벽 그리기 (Board 클래스 사용)
        gameBoard.Draw();

        // 플레이어 그리기
        Window::GetInstance()->Draw(player);
        Window::GetInstance()->Display();
    }

    // 프로그램 종료 시 인스턴스 정리
    Window::DestroyInstance();

    return 0;
}