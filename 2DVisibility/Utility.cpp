#include "Utility.h"

int SetNumOfPol()
{
	int numOfPol;
	printf("Welcome in 2D Visibility Application created by Dominik Jasek. \n");
	printf("Insert number of convex polygons: ");
	scanf("%d", &numOfPol);
	printf("Set vertex of polygon by left-clicking and end-vertex of polygon by right-clicking. \n");
	return numOfPol;
}


sf::Vector2i GetMousePos(const sf::Window& window)
{
	sf::Vector2i pos = sf::Mouse::getPosition(window);
	return pos;
}

void AdjustMousePos(sf::Vector2i & mousePos)
{
	if (mousePos.x > WIDTH)
		mousePos.x = WIDTH-1;
	else if (mousePos.x < 0)
		mousePos.x = 1;
	if (mousePos.y > HEIGHT)
		mousePos.y = HEIGHT-1;
	else if (mousePos.y < 0)
		mousePos.y = 1;
}

void DrawDot(sf::RenderWindow& window, const sf::Vector2i& mousePos)
{
	sf::Cursor cursor; //aby se nezobrazoval kurzor mysi
	window.setMouseCursorVisible(0);
	sf::CircleShape dot(DOTRADIUS);
	dot.setPosition(mousePos.x - DOTRADIUS, mousePos.y - DOTRADIUS);
	dot.setFillColor(sf::Color::Red);
	window.draw(dot);
}

void DisplayMousePos(sf::RenderWindow& window, const sf::Vector2i& mousePos, const sf::Font& font)
{
	sf::Text text;
	text.setFont(font);
	std::string mouse_x = std::to_string(mousePos.x);
	text.setString("x = " + mouse_x);
	text.setPosition(5, 0);
	window.draw(text);
	std::string mouse_y = std::to_string(mousePos.y);
	text.setString("y = " + mouse_y);
	text.setPosition(5, 35);
	window.draw(text);
}

void DisplayFPS(sf::RenderWindow& window, sf::Clock& clock,/* sf::Time& time,*/ const sf::Font& font)
{
	sf::Time time;
	sf::Text text;
	text.setFont(font);
	time = clock.getElapsedTime();
	clock.restart().asSeconds();
	std::string fpsText = std::to_string(int(1.0f / time.asSeconds()));
	text.setString("FPS : " + fpsText);
	text.setPosition(5, 70);
	window.draw(text);
}

bool MouseOnWindow(const sf::Window& window)
{
	sf::Vector2i mousePos = GetMousePos(window);
	return (mousePos.x > 0 && mousePos.x < WIDTH && mousePos.y > -50 && mousePos.y < HEIGHT);
}

double RotationToPoint(const sf::Vector2f& pointToReach, const sf::Vector2i& mousePos) //vypocita uhel natocni k danemu bodu
{
	double protilehla = pointToReach.y - mousePos.y;
	double prilehla = pointToReach.x - mousePos.x;
	double rotation = std::abs(std::atan(protilehla / prilehla)); //= (protilehla >=0 && prilehla >=0)
	if (protilehla >= 0 && prilehla <= 0)
	{
		rotation = PI - rotation;
	}
	else if (protilehla <= 0 && prilehla <= 0)
	{
		rotation += PI;
	}
	else if (protilehla <= 0 && prilehla >= 0)
	{
		rotation = 2 * PI - rotation;
	}
	return rotation;
}