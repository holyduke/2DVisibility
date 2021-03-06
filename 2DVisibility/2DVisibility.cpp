#include <SFML/Graphics.hpp>
#include "Utility.h"
#include "Polygon.h"
#include "Ray.h"
#include "BinaryTree.h"

int main()
{
	//Uvod + zvoleni poctu mnohouhelniku
	unsigned int numOfPol = SetNumOfPol();
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT, 32), "2D Visibility!");
	window.setPosition(sf::Vector2i(400, 200));
	window.setFramerateLimit(60);
	window.clear(sf::Color(32, 66, 70, 170));

	//settings mouse position
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) printf("Error loading file!\n");

	//fps Clock
	sf::Clock clock;

	//Naklikani konvexnich mnohouhelniku
	window.display();
	std::vector<Polygon> polygons;
	polygons.reserve(numOfPol+1); //pocet polzgonu + obvodovy obdelnik
	for (size_t i = 0; i < numOfPol; i++)
	{
		polygons.emplace_back(window); //Emplace_back zajisti to, ze se dany objekt vytvori primo ve vectoru a ne ve funkci main, tudiz se uz nemusi kopirovat a tudiz nevznika copy constructor https://www.youtube.com/watch?v=HcESuwmlHEY&index=48&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb
	}
	//Pridani obvodoveho obdelniku
	sf::ConvexShape obdelnik = sf::ConvexShape(4);
	polygons.emplace_back(Polygon(window, obdelnik)); //zavolani constructoru pro obvodovy obdelnik polygons.emplace_back(Polygon(window, obdelnik)) takhle by doslo k zavolani copy constructoru

	std::vector </* std::unique_ptr<Ray>*/Ray> rays;
	int numOfRays = 2 * Polygon::GetTotalPoints();
	rays.reserve(numOfRays);
	for (size_t i = 0; i < numOfRays; i++)
	{
		//pro jeden bod delam celkem 2 body, normalni + nepatrne nalevo a napravo
		rays.emplace_back();

	}

	///////////////////////////////////////////////while-loop//////////////////////////////////////////////////////////////
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Vector2i mousePos = GetMousePos(window);
		AdjustMousePos(mousePos);
		window.clear(sf::Color(32, 66, 70, 170));

		//DrawPolygons
		for (size_t i = 0; i < numOfPol; i++)
		{
			window.draw(polygons[i].GetPolygon());
		}

		//Make Rays
		int rayi = 0; //resetovani indexu paprsku
		for (Polygon& polygon : polygons) //pro kazdy polygon
		{
			for (sf::Vector2i& pointToReach : polygon.GetPolygonPoints()) //checknout vsechny bodu daneho polygonu
			{
				double delta = 0.00001; //+ a - odchylka, v jake budu vystrelovat paprsky
				double rotation = RotationToPoint((sf::Vector2f)pointToReach, mousePos); //vypocitat uhel natoceni k danemu bodu
				rays[rayi]/*->*/.IntersectDirectionXPolygons(window, rotation + delta, mousePos, polygons); // bod nalevo
				rays[rayi + 1]/*->*/.IntersectDirectionXPolygons(window, rotation - delta, mousePos, polygons); // bod nalevo
				rayi += 2;
			}
		}
		

		//Sorting Algorithm by STL
		//std::sort(rays.begin(), rays.end()); //pouzitim smart pointeru zamezim opakovanemu volani copy constructoru, ktery zpomaluje FPS

		//Sorting Algorithm by me
		SortAndDrawWithBinaryTree(window, rays, mousePos);

		//Display info
		DrawDot(window, mousePos);
		DisplayMousePos(window, mousePos, font);
		DisplayFPS(window, clock, font);
		window.display();
	}
}