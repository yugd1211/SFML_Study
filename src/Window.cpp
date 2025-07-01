#include "Window.hpp"
#include <iostream>

Window::Window() : window(nullptr)
{
	std::cout << "Window instance created" << std::endl;
}

Window::~Window()
{
	if (window != nullptr)
	{
		delete window;
		window = nullptr;
	}
	std::cout << "Window instance destroyed" << std::endl;
}

void Window::Create(const std::string &title)
{
	if (window != nullptr)
	{
		delete window;
	}

	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), title);
	std::cout << "Window created: " << title << " (" << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << ")" << std::endl;
}

void Window::Clear(const sf::Color &color)
{
	if (window != nullptr)
	{
		window->clear(color);
	}
}

void Window::Display()
{
	if (window != nullptr)
	{
		window->display();
	}
}

void Window::Close()
{
	if (window != nullptr)
	{
		window->close();
	}
}

bool Window::IsOpen() const
{
	if (window != nullptr)
	{
		return window->isOpen();
	}
	return false;
}

bool Window::PollEvent(sf::Event &event)
{
	if (window != nullptr)
	{
		return window->pollEvent(event);
	}
	return false;
}

void Window::Draw(const sf::Drawable &drawable)
{
	if (window != nullptr)
	{
		window->draw(drawable);
	}
}

sf::RenderWindow *Window::GetRenderWindow() const
{
	return window;
}

sf::Vector2u Window::GetSize() const
{
	if (window != nullptr)
	{
		return window->getSize();
	}
	return sf::Vector2u(0, 0);
}

void Window::SetSize(unsigned int width, unsigned int height)
{
	if (window != nullptr)
	{
		window->setSize(sf::Vector2u(width, height));
	}
}
