#include "Ray.h"


Ray::Ray()
{
	std::cout << "Ray constructor!" << std::endl;
}

Ray::Ray(const Ray &)
	:rotation(rotation),intersect(intersect)
{
	std::cout << "Ray copy constructor..." << std::endl;
}

Ray::~Ray()
{
	std::cout << "Ray destructed!" << std::endl;
}



void Ray::IntersectDirectionXPolygons(sf::RenderWindow & window, const double & rotation, const sf::Vector2i & mousePos, std::vector<Polygon>& polygons)
{
	this->rotation = rotation;
	this->mousePos = mousePos;
	if (rotation >= 0 && rotation < PI / 2)
	{
		pointToReach.y = mousePos.y + 1500000 * tan(rotation);
		pointToReach.x = mousePos.x + 1500000;
	}
	else if (rotation >= PI / 2 && rotation < PI) //protilehla >= 0 && prilehla <= 0)
	{
		pointToReach.y = mousePos.y + 1500000 * tan((PI - rotation));
		pointToReach.x = mousePos.x - 1500000;
	}
	else if (rotation >= PI && rotation < 3 * PI / 2) //protilehla <= 0 && prilehla <= 0)
	{
		pointToReach.y = mousePos.y - 1500000 * tan((rotation - PI));
		pointToReach.x = mousePos.x - 1500000;
	} 
	else
	{
		pointToReach.y = mousePos.y - 1500000 * tan((2 * PI - rotation));
		pointToReach.x = mousePos.x + 1500000;
	}
	IntersectPointXPolygons(window, polygons);
}

void Ray::IntersectPointXPolygons(sf::RenderWindow& window, std::vector<Polygon>& polygons)
{
	currDist = 0;
	minDistance = 1000000;
	intersect = sf::Vector2f(0, 0);
	for (Polygon& polygon : polygons)
	{
		int polygonPointsCount = polygon.GetPolygonPoints().size();
		for (size_t bod = 0; bod < polygonPointsCount; bod++) //pro kazdou usecku
		{
			std::array<sf::Vector2f, 2> PolLinePoints; //vysetrovana usecka pro prunik paprsku
			for (size_t index = 0; index < 2; index++) //nastaveni 2 bodu dane usecky
			{
				int indexOfPoint = (bod + index) % polygonPointsCount; //aby jsem opet dosel na bod s indexem [0] a neprekrocil hranici
				PolLinePoints[index].x = polygon.GetPolygon().getPoint(indexOfPoint).x;
				PolLinePoints[index].y = polygon.GetPolygon().getPoint(indexOfPoint).y;
			}
			sf::Vector2f currIntersect = IntersectPointXLine(window/*, pointToReach*/, PolLinePoints);
			currDist = sqrt((mousePos.x - currIntersect.x)*(mousePos.x - currIntersect.x) + (mousePos.y - currIntersect.y)*(mousePos.y - currIntersect.y)); //vzdalenost od mysi k pruseciku
			if (currDist < minDistance) //jestlize jsme nasli prusecik ktery je bliz nez dosavadni prusecik
			{
				minDistance = currDist;
				intersect = currIntersect;
			}
		}
	}
	//Draw ray
	//sf::Vertex ray[] =
	//{
	//	sf::Vertex(sf::Vector2f(mousePos.x, mousePos.y),sf::Color::Red),
	//	sf::Vertex(sf::Vector2f(intersect.x, intersect.y),sf::Color::Red)
	//};
	//window.draw(ray, 2, sf::Lines);
}

sf::Vector2f Ray::IntersectPointXLine(sf::RenderWindow& window/*, const sf::Vector2f& pointToReach*/, std::array<sf::Vector2f, 2> LinePoints)
{
	sf::Vector2f currIntersect;
	sf::Vector2f t(pointToReach.x - mousePos.x, pointToReach.y - mousePos.y); //tady budu zadavat vrcholy polygonu
	s = (mousePos.y + (t.y / t.x)*(LinePoints[0].x - mousePos.x) - LinePoints[0].y) / (LinePoints[1].y - LinePoints[0].y - (t.y / t.x)*(LinePoints[1].x - LinePoints[0].x));
	r = (LinePoints[0].x + s * (LinePoints[1].x - LinePoints[0].x) - mousePos.x) / t.x;
	if (s >= 0 && s <= 1 && r >= 0)
	{
		currIntersect.x = LinePoints[0].x + (LinePoints[1].x - LinePoints[0].x)*s;
		currIntersect.y = LinePoints[0].y + (LinePoints[1].y - LinePoints[0].y)*s;
	}
	else
	{
		currIntersect = pointToReach;
	}
	return currIntersect;
}

sf::Vector2f Ray::GetIntersect()
{
	return intersect;
}

double Ray::GetRotation() const
{
	return rotation;
}

//bool operator < (const std::unique_ptr<Ray>& r1, const std::unique_ptr<Ray>& r2) //operator overloading pro sort vectoru
//{
//	return r1->GetRotation() < r2->GetRotation();
//}

bool operator < (const Ray& r1, const Ray& r2) //operator overloading pro sort vectoru
{
	return r1.GetRotation() < r2.GetRotation();
}
