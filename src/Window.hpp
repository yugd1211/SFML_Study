// --- src/Window.hpp ---
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

	// Draw(const sf::Drawable &drawable) 함수는 SFML이 그릴 수 있는 모든 것(sf::Drawable을 상속하는 모든 객체)을
	// 윈도우에 그리는 역할을 합니다.
	void Draw(const sf::Drawable &drawable);

	sf::RenderWindow *GetRenderWindow() const;

	sf::Vector2u GetSize() const;
	void SetSize(unsigned int width, unsigned int height);
};
