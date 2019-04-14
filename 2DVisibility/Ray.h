#pragma once
#include <SFML/Graphics.hpp>
#include "Polygon.h"
#include "Utility.h"
#include <vector>
#include <array>
#include <iostream>
#include <math.h>


class Ray
{
private:
	double rotation;
	float currDist;
	int minDistance;
	float r, s; //parametry parametrickych rovnic cary polygonu a paprsku
	sf::Vector2i mousePos;
	sf::Vector2f intersect;
	sf::Vector2f pointToReach;
	sf::Vector2f IntersectPointXLine(sf::RenderWindow& window, std::array<sf::Vector2f, 2> LinePoints);
	void IntersectPointXPolygons(sf::RenderWindow& window, std::vector<Polygon>& polygons);
public:
	Ray();
	Ray(const Ray&);
	~Ray();
	double GetRotation() const;
	sf::Vector2f GetIntersect();
	void IntersectDirectionXPolygons(sf::RenderWindow& window, const double& rotation, const sf::Vector2i& mousePos, std::vector<Polygon>& polygons);
};

//bool operator<(const std::unique_ptr<Ray>& r1, const std::unique_ptr<Ray>& r2);
bool operator<(const Ray& r1, const Ray& r2);