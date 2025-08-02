// --- src/main.cpp ---
/*
 * [파일 설명]
 * 이 파일은 프로그램의 시작점(entry point)입니다.
 * 전체 프로그램의 흐름을 제어하는 메인 루프(main loop)가 여기에 있습니다.
 * 이전 버전에서는 플레이어의 위치, 각도, 입력 처리 등 많은 로직이 이 파일에 직접 작성되어 있었습니다.
 * 이번 리팩토링을 통해 Player 클래스를 도입하여, main.cpp는 매우 간결해졌습니다.
 * 이제 main.cpp의 주요 역할은 필요한 객체(Window, Board, Player)를 생성하고,
 * 메인 루프를 돌면서 각 객체에게 자신의 역할을 수행하도록 지시하는 것입니다.
 */

#include <SFML/Graphics.hpp> // SFML 그래픽 라이브러리
#include <iostream>          // 콘솔 입출력(cout)을 위해 포함
#include "Color.hpp"         // 색상 관련 정의를 가져옴
#include "Window.hpp"        // Window 클래스를 사용하기 위해 포함
#include "Board.hpp"         // Board 클래스를 사용하기 위해 포함
#include "Player.hpp"        // Player 클래스를 사용하기 위해 포함

// [전역 변수 및 함수 제거]
// 이전에 여기에 있던 px, py, pa와 같은 전역 변수와 PlayerMoveInput 함수가 모두 제거되었습니다.
// 이유: 전역 변수는 프로그램 어디서든 접근하고 수정할 수 있어 코드의 흐름을 파악하기 어렵게 만들고,
//      예상치 못한 오류(side effect)를 발생시킬 수 있습니다.
//      관련 데이터와 기능을 Player 클래스 안으로 옮김(캡슐화)으로써 코드가 훨씬 더 안정적이고
//      이해하기 쉬워졌습니다.

using namespace std;

// [게임 종료 함수]
// 이 함수는 게임을 안전하게 종료하는 역할을 합니다.
void GameExit()
{
    cout << "게임을 종료합니다." << endl;
    Window::GetInstance()->Close(); // 윈도우를 닫도록 요청
    Window::DestroyInstance();      // 싱글톤 인스턴스 메모리 해제
    exit(0);                        // 프로그램 즉시 종료
}

int main()
{
    // [객체 생성 및 초기화]
    // 프로그램에 필요한 핵심 객체들을 생성합니다.

    // 윈도우 인스턴스를 가져와 생성합니다. (싱글톤 패턴)
    Window::GetInstance()->Create("SFML Project");

    // 게임 보드(맵) 객체를 생성합니다.
    Board gameBoard;

    // 플레이어 객체를 생성합니다.
    // Player(75, 75)는 플레이어의 시작 위치를 (75, 75)로 설정하라는 의미입니다.
    // 이 위치는 맵의 벽이 아닌 안전한 공간이어야 합니다.
    Player player(75, 75);
    // [메인 루프 (Game Loop)]
    // 이 루프는 게임이 진행되는 동안 계속해서 반복됩니다.
    // IsOpen()이 false를 반환할 때 (예: 창의 X 버튼을 누르거나 ESC 키를 누를 때) 루프가 종료됩니다.
    while (Window::GetInstance()->IsOpen())
    {
        sf::Event event;
        // [이벤트 폴링 (Event Polling)]
        // 사용자의 입력(키보드, 마우스 등)이 있었는지 확인합니다.
        // PollEvent는 이벤트 큐(queue)에서 이벤트를 하나씩 꺼내와 event 변수에 저장합니다.
        // 처리할 이벤트가 있으면 true, 없으면 false를 반환합니다.
        while (Window::GetInstance()->PollEvent(event))
        {
            // 창 닫기 버튼을 눌렀을 경우
            if (event.type == sf::Event::Closed)
                Window::GetInstance()->Close();

            // 키보드 키가 눌렸을 경우
            if (event.type == sf::Event::KeyPressed)
            {
                // ESC 키를 누르면 게임 종료
                if (event.key.code == sf::Keyboard::Escape)
                {
                    GameExit();
                }

                // [역할 위임 (Delegation)]
                // ESC 키가 아닌 다른 키가 눌렸을 경우, main 함수가 직접 처리하지 않습니다.
                // 대신, player 객체의 handleInput 함수를 호출하여 이벤트 처리를 위임합니다.
                // 이제 main은 어떤 키가 어떤 동작을 하는지 알 필요가 없으며, 오직 Player만이 그 내용을 압니다.
                // 이것이 역할 분리를 통해 코드가 명확해지는 예시입니다.
                player.handleInput(event, gameBoard);
            }
        }

        // [렌더링 (Rendering)]
        // 화면을 그리는 과정입니다. 매 프레임마다 반복됩니다.

        // 1. 화면을 지정된 색(BACKGROUND_COLOR)으로 깨끗이 지웁니다.
        Window::GetInstance()->Clear(BACKGROUND_COLOR);

        // 2. 게임 보드를 그립니다.
        gameBoard.Draw();

        // 3. 플레이어를 그립니다.
        // player 객체에게 "너 자신을 그려라"라고 지시합니다.
        player.draw(Window::GetInstance());

        // 4. 지금까지 그린 모든 내용을 실제 화면에 표시합니다.
        Window::GetInstance()->Display();
    }

    // 메인 루프가 종료되면 프로그램이 끝나기 전에 사용했던 메모리를 정리합니다.
    Window::DestroyInstance();

    return 0; // 프로그램 정상 종료
}