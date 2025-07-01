#include <SFML/Graphics.hpp>
#include <iostream>
#include "Color.hpp"
#include "Window.hpp"
#define X first
#define Y second
using namespace std;

pair<int, int> PlayerMoveInput(const sf::Event &event)
{
    int x = 0, y = 0;
    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
        y = -10;
    else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
        y = 10;
    else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
        x = -10;
    else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
        x = 10;
    return make_pair(x, y);
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
    Window *gameWindow = Window::GetInstance();
    gameWindow->Create("SFML Project");

    // 플레이어
    sf::RectangleShape player(sf::Vector2f(10, 10));
    player.setPosition(500, 300);
    player.setFillColor(sf::Color::Green);

    // 메인 루프
    while (gameWindow->IsOpen())
    {
        sf::Event event;
        while (gameWindow->PollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gameWindow->Close();

            if (event.type == sf::Event::KeyPressed)
            {
                // ESC 키로 종료
                if (event.key.code == sf::Keyboard::Escape)
                    GameExit();
                else
                {
                    pair<int, int> dir = PlayerMoveInput(event);
                    player.move(dir.X, dir.Y);
                }
            }
        }

        gameWindow->Clear(BACKGROUND_COLOR);
        gameWindow->Draw(player);
        gameWindow->Display();
    }

    // 프로그램 종료 시 인스턴스 정리
    Window::DestroyInstance();

    return 0;
}