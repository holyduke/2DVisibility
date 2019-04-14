#pragma once
#include <SFML/Graphics.hpp>

#define WIDTH 1280
#define HEIGHT 720
#define DOTRADIUS 10
#define PI 3.14159265359

int SetNumOfPol();
sf::Vector2i GetMousePos(const sf::Window&);
void AdjustMousePos(sf::Vector2i& mousePos);
void DrawDot(sf::RenderWindow&, const sf::Vector2i&);
void DisplayMousePos(sf::RenderWindow&, const sf::Vector2i&, const sf::Font&);
void DisplayFPS(sf::RenderWindow& window, sf::Clock& clock, const sf::Font& font);
bool MouseOnWindow(const sf::Window&);
double RotationToPoint(const sf::Vector2f& pointToReach, const sf::Vector2i& mousePos);
