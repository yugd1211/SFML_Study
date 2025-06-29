#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	// 윈도우 생성 (800x600 해상도, "SFML Study"라는 제목)
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Study");

	// 원 모양 생성
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(350.f, 250.f); // 중앙에 위치

	// 메인 루프
	while (window.isOpen())
	{
		sf::Event event;

		// 이벤트 처리
		while (window.pollEvent(event))
		{
			// 윈도우 닫기 이벤트
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// 화면 클리어 (검은색)
		window.clear(sf::Color::Black);

		// 객체 그리기
		window.draw(shape);

		// 화면에 출력
		window.display();
	}

	return 0;
}
