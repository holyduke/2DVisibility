#include "Polygon.h"
#include <iostream>

int Polygon::totalPoints = 0;

Polygon::Polygon(const Polygon& pol)	//copy constructor kvuli zvetsovani velikosti ve vectoru
	:polygon(pol.polygon), polygonPoints(pol.polygonPoints)
{
	printf("Polygon Copy constructor called!\n");
}


Polygon::Polygon(sf::RenderWindow& window)
{
	rightClick = false;
	cursor.loadFromSystem(sf::Cursor::Arrow);
	window.setMouseCursor(cursor);

	while (!rightClick) //dokud nekliknuto pravym tlacitkem
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					polygonPoints.push_back(GetMousePos(window)); //pridat posledni bod stiskem praveho tlacitka
					rightClick = true;
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					polygonPoints.push_back(GetMousePos(window));
					cursor.loadFromSystem(sf::Cursor::Hand);  //nastaveni kurzoru mysi + just wait aby se nepridal vicekrat*/	
					window.setMouseCursor(cursor);
				}
			}
		}
	}
	polygon = sf::ConvexShape(polygonPoints.size()); //deklarace pointeru
	for (size_t i = 0; i < polygonPoints.size(); i++) //nastavit rohy polygonu
	{
		polygon.setPoint(i, sf::Vector2f(polygonPoints[i]));
		totalPoints++;
	}
	polygon.setFillColor(sf::Color::Black);
	polygon.setOutlineColor(sf::Color::White);
	polygon.setOutlineThickness(2.f);
	window.draw(polygon);
	window.display();
	printf("Polygon constructor!\n");
}

Polygon::Polygon(sf::RenderWindow& window,const sf::ConvexShape& rectangle) //constructor pro obvodovz obdelnik
{
	polygon = sf::ConvexShape(rectangle.getPointCount()); //deklarace pointeru
	polygonPoints.push_back(sf::Vector2i(WIDTH, 0));
	polygonPoints.push_back(sf::Vector2i(WIDTH, HEIGHT));
	polygonPoints.push_back(sf::Vector2i(0, HEIGHT));
	polygonPoints.push_back(sf::Vector2i(0, 0));
	for (size_t i = 0; i < polygonPoints.size(); i++) //nastavit rohy polygonu
	{
		polygon.setPoint(i, sf::Vector2f(polygonPoints[i]));
		totalPoints++;
	}
	polygon.setFillColor(sf::Color(32, 66, 70, 170));
	window.draw(polygon);
	window.display();
}

Polygon::~Polygon()
{
	std::cout << "Polygon Destructor" << std::endl;
}

sf::ConvexShape Polygon::GetPolygon()
{
	return polygon;
}
std::vector<sf::Vector2i> Polygon::GetPolygonPoints()
{
	return polygonPoints;
}

int Polygon::GetTotalPoints() //nemuze byt slovo static!
{
	return totalPoints;
}
