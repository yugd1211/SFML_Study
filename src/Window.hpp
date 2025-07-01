#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.hpp"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512

class Window : public Singleton<Window>
{
	friend class Singleton<Window>; // Singleton에서 생성자 접근 허용

private:
	sf::RenderWindow *window;

	// private 생성자 (Singleton 패턴)
	Window();

public:
	// 소멸자
	~Window();

	// 윈도우 관련 메서드들
	void Create(const std::string &title = "SFML Study");
	void Clear(const sf::Color &color = sf::Color::Black);
	void Display();
	void Close();
	bool IsOpen() const;
	bool PollEvent(sf::Event &event);
	void DrawPlayer(const sf::RectangleShape &player);

	// 그리기 메서드
	void Draw(const sf::Drawable &drawable);

	// 윈도우 직접 접근 (필요한 경우)
	sf::RenderWindow *GetRenderWindow() const;

	// 윈도우 크기 관련
	sf::Vector2u GetSize() const;
	void SetSize(unsigned int width, unsigned int height);
};
