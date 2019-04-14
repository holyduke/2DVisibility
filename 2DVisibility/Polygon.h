#pragma once
#include <SFML/Graphics.hpp>
#include "Utility.h"

class Polygon
{
private:
	static int totalPoints;
	bool rightClick;
	sf::Cursor cursor;
	sf::Event event;
	sf::ConvexShape polygon;
	std::vector<sf::Vector2i> polygonPoints; //body polygonu
public:
	Polygon(sf::RenderWindow&);
	Polygon(sf::RenderWindow&, const sf::ConvexShape&);
	Polygon(const Polygon& pol);
	~Polygon();
	sf::ConvexShape GetPolygon();
	std::vector<sf::Vector2i> GetPolygonPoints(); //get
	static int GetTotalPoints();
};

