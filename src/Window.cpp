#include "Window.hpp"
#include <iostream>

Window::Window() : window(nullptr)
{
}

Window::~Window()
{
	if (window == nullptr)
		return;

	delete window;
	window = nullptr;
}

void Window::Create(const std::string &title)
{
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), title);
	std::cout << "Window created: " << title << " (" << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << ")" << std::endl;
}

void Window::Clear(const sf::Color &color)
{
	if (window == nullptr)
		return;
	window->clear(color);
}

void Window::Display()
{
	if (window == nullptr)
		return;
	window->display();
}

void Window::Close()
{
	if (window == nullptr)
		return;
	window->close();
}

bool Window::IsOpen() const
{
	if (window == nullptr)
		return false;
	return window->isOpen();
}

bool Window::PollEvent(sf::Event &event)
{
	if (window == nullptr)
		return false;
	return window->pollEvent(event);
}

void Window::Draw(const sf::Drawable &drawable)
{
	if (window == nullptr)
		return;
	window->draw(drawable);
}

sf::RenderWindow *Window::GetRenderWindow() const
{
	return window;
}

sf::Vector2u Window::GetSize() const
{
	if (window == nullptr)
		return sf::Vector2u(0, 0);
	return window->getSize();
}

void Window::SetSize(unsigned int width, unsigned int height)
{
	if (window == nullptr)
		return;
	window->setSize(sf::Vector2u(width, height));
}