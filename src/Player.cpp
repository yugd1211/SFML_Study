
#include "Player.hpp"
#include "Board.hpp"
#include "Window.hpp"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Player::Player(float startX, float startY)
{
    // 플레이어의 외형 설정 크기를 10x10 픽셀로 설정
    shape.setSize(sf::Vector2f(10, 10));

    // [회전 중심 설정]
    // 기본적으로 SFML 도형은 좌측 상단(0,0)을 기준으로 회전합니다.
    // 이 경우, 플레이어가 제자리에서 팽이처럼 돌지 않고 좌측 상단 꼭짓점을 중심으로 공전하게 됩니다.
    // setOrigin(5, 5)는 도형의 중심점(10x10 크기의 절반)을 회전의 기준점으로 변경하여
    // 플레이어가 제자리에서 자연스럽게 회전하도록 만듭니다.
    shape.setOrigin(5, 5);

    shape.setPosition(startX, startY);      // 시작 위치 설정
    shape.setFillColor(sf::Color::Green); // 색상 설정

    // 플레이어의 초기 상태 값 설정
    angle = 0.0f;         // 초기 각도는 0 (오른쪽을 바라봄)
    moveSpeed = 3.0f;     // 한 번에 3픽셀씩 이동
    rotationSpeed = 0.1f; // 한 번에 0.1 라디안(약 5.7도)씩 회전
}

// [입력 처리 함수 구현]
void Player::handleInput(const sf::Event &event, const Board &board)
{
    // 이 함수는 키가 눌렸을 때만 동작해야 합니다.
    // event.type이 KeyPressed가 아니면 함수를 즉시 종료하여 불필요한 연산을 막습니다.
    if (event.type != sf::Event::KeyPressed)
    {
        return;
    }

    // [회전 처리]
    if (event.key.code == sf::Keyboard::Q)
    {
        angle -= rotationSpeed; // Q를 누르면 반시계 방향으로 회전 (각도 감소)
    }
    else if (event.key.code == sf::Keyboard::E)
    {
        angle += rotationSpeed; // E를 누르면 시계 방향으로 회전 (각도 증가)
    }

    // [각도 정규화 (Normalization)]
    // 각도가 계속 증가하거나 감소하면 값이 무한정 커지거나 작아질 수 있습니다.
    // 예를 들어 720도와 360도는 같은 방향을 의미하지만 값은 다릅니다.
    // 이런 문제를 방지하고 각도를 항상 0 ~ 2*PI (0 ~ 360도) 사이의 값으로 유지하기 위해 정규화를 수행합니다.
    if (angle < 0)
        angle += 2 * M_PI; // 각도가 음수가 되면 2*PI를 더해 양수로 만듦
    if (angle > 2 * M_PI)
        angle -= 2 * M_PI; // 각도가 2*PI를 넘으면 2*PI를 빼서 범위 안으로 가져옴

    // [SFML 도형에 회전 적용]
    // shape.setRotation() 함수는 라디안이 아닌 도(degree) 단위를 사용합니다.
    // 따라서 우리가 내부적으로 관리하는 라디안 단위의 angle 값을 도 단위로 변환하여 전달해야 합니다.
    // 변환 공식: degrees = radians * (180 / PI)
    shape.setRotation(angle * 180 / M_PI);

    // [이동 처리]
    float moveX = 0.0f;
    float moveY = 0.0f;

    // W 또는 위쪽 화살표 키를 누르면 플레이어가 현재 바라보는 방향으로 전진합니다.
    // 삼각함수를 사용하여 x, y 이동량을 계산합니다.
    // x 이동량 = cos(각도) * 속도
    // y 이동량 = sin(각도) * 속도
    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
    {
        moveX = cos(angle) * moveSpeed;
        moveY = sin(angle) * moveSpeed;
    }
    else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
    {
        // 후진은 전진과 방향만 반대입니다.
        moveX = -cos(angle) * moveSpeed;
        moveY = -sin(angle) * moveSpeed;
    }
    else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
    {
        // 왼쪽으로 평행 이동(strafe)은 현재 각도에서 -90도(-PI/2 라디안) 방향으로 이동하는 것과 같습니다.
        moveX = cos(angle - M_PI / 2) * moveSpeed;
        moveY = sin(angle - M_PI / 2) * moveSpeed;
    }
    else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
    {
        // 오른쪽으로 평행 이동(strafe)은 현재 각도에서 +90도(+PI/2 라디안) 방향으로 이동하는 것과 같습니다.
        moveX = cos(angle + M_PI / 2) * moveSpeed;
        moveY = sin(angle + M_PI / 2) * moveSpeed;
    }

    // [충돌 감지]
    // 이동하기 전에, 플레이어가 이동할 새로운 위치가 벽이 아닌지 확인해야 합니다.
    sf::Vector2f currentPos = shape.getPosition(); // 현재 위치
    float newX = currentPos.x + moveX;             // 이동 후의 예상 x 위치
    float newY = currentPos.y + moveY;             // 이동 후의 예상 y 위치

    // Board 객체의 CanMoveTo 함수를 호출하여 이동 가능 여부를 확인합니다.
    if (board.CanMoveTo(newX, newY))
    {
        // 이동이 가능한 경우에만 실제로 플레이어의 위치를 변경합니다.
        shape.move(moveX, moveY);
    }
}

// [그리기 함수 구현]
// const 키워드는 이 함수가 멤버 변수(shape, angle 등)의 값을 변경하지 않는다는 것을 의미합니다.
void Player::draw(Window *window) const
{
    // Window 클래스의 Draw 함수를 호출하여 자신의 shape를 그립니다.
    // Player는 자신이 어떻게 생겼는지만 알고, 그리는 책임은 Window에게 넘깁니다.
    // 이를 통해 역할 분리가 이루어집니다.
    window->Draw(shape);
}