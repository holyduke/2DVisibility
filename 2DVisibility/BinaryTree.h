#pragma once
#include <SFML/Graphics.hpp>
#include "Ray.h"
#include <vector>

struct Node
{
	Ray* Ray;
	struct Node* left;
	struct Node* right;
};

// This function sorts arr[0..n-1] using Tree Sort 
void SortAndDrawWithBinaryTree(sf::RenderWindow& window, std::vector<Ray>& rays, const sf::Vector2i& mousePos);

Node* insert(Node* node, Ray* ray); //vlozeni uzlu

Node* newNode(Ray* ray); //radoby konstruktor

void Sort(Node *root, sf::Vector2f* points, int& i, const sf::Vector2i& mousePos, sf::RenderWindow& window); //setridit podle rotace

void DrawTriangles(const sf::Vector2f* points, const sf::Vector2i& mousePos, sf::RenderWindow& window, const int& numOfRays);