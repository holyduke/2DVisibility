#include "BinaryTree.h"


void SortAndDrawWithBinaryTree(sf::RenderWindow& window, std::vector<Ray>& rays, const sf::Vector2i& mousePos)
{
	Node* root = nullptr;	//vrchni uzel

	int numOfRays = rays.size();

	// Construct the Binary Search Tree 
	root = insert(root, &rays[0]);
	for (int i = 1; i < numOfRays; i++)
		insert(root, &rays[i]);

	// Store inoder traversal of the BST 
	// in arr[] 
	int i = 0;
	sf::Vector2f* points = new sf::Vector2f[numOfRays]; //pole ukazatelu na jednotlive body
	Sort(root, points, i, mousePos, window); //setridit 
	DrawTriangles(points, mousePos, window, numOfRays); //vykreslit
	delete[] points; //dealokace
}

/* A utility function to insert a new
   Node with given key in BST */
Node* insert(Node* node, Ray* ray)
{
	/* If the tree is empty, return a new Node */
	if (node == nullptr) return newNode(ray);

	/* Otherwise, recur down the tree */
	if (*ray < *(node->Ray))
		node->left = insert(node->left, ray);
	else
		node->right = insert(node->right, ray);

	/* return the (unchanged) Node pointer */
	return node;
}

Node* newNode(Ray* ray)
{
	Node* temp = new Node;
	temp->Ray = ray;
	temp->left = temp->right = nullptr;
	return temp;
}

void Sort(Node* root, sf::Vector2f* points, int& i, const sf::Vector2i& mousePos, sf::RenderWindow& window)
{
	if (root != NULL)
	{
		Sort(root->left,points, i, mousePos, window);
		points[i++] = root->Ray->GetIntersect();
		Sort(root->right, points, i, mousePos, window);
	}
}

void DrawTriangles(const sf::Vector2f* points, const sf::Vector2i& mousePos, sf::RenderWindow& window, const int& numOfRays)
{
	sf::ConvexShape convex;
	convex.setPointCount(3);
	convex.setPoint(0, sf::Vector2f(mousePos));
	for (size_t i = 0; i < numOfRays; i++) //kresleni trojuhelniku
	{
		convex.setPoint(1, points[i % numOfRays]);
		convex.setPoint(2, points[(i + 1) % numOfRays]); //pro zajisteni toho, aby se posledni bod vratil opet na prvni
		convex.setFillColor(sf::Color(255, 238, 67, 255));
		window.draw(convex);
	}
}