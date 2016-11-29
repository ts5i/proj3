// Tyler Storz
// Files: lab3.cpp, lab3output.txt (program output)
// 11/29/16
// Lab3: Uses an adjacency matrix for nodes in a graph 
// 		 to perform various operations

#include <iostream>
#include <fstream>
using namespace std;

int** setArray(int);
void menu(int**, int);

void displayArray(int**, int);
void isoNode(int**, int);
void nodeDegree(int**, int, int);
void nodeEuler(int**, int);
void nodeAdj(int**, int);

bool checkEven(int*, int);
bool checkOdd(int*, int);


int main()
{
	int node;
	int** a;	// main adjacency matrix

	cout << "Enter the Number of Nodes in the Graph: ";
	cin >> node;
	
	a = setArray(node);
	
	menu(a, node);
	
	delete [] a;
	
	return 0;
}

// sets a user defined adjacency matrix taking in the number of nodes
// and a binary relation
int** setArray(int n)
{
	int x = 0;	// node start point
	int y = 0;	// node destination
	int** a = new int* [n];
	
	
	// initializes all array values to zero
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[n];
		
		for (int j = 0; j < n; j++)
		{
			a[i][j] = 0;
		}
	}
		
	cout << "\n\nEnter the Binary Relation for the Graph (Enter a number out of bounds to quit): \n";
	
	while (true)
	{
		cin >> x >> y;
		
		// if a number is entered out of bounds of the nodes then it quits
		if (x > n || x < 0 || y > n || y < 0)
			break;
		
		a[x - 1][y - 1] += 1;
	}

	return a;
}


// displays the adjacency matrix
void displayArray(int** a, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << endl;
		
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << " ";
		}
	}
}


// displays any isolated nodes
void isoNode(int** a, int n)
{
	int* iNode = new int [n]; // holds isolated nodes
	int nodeCount = 0;
	
	int count = 0;

	for (int i = 0; i < n; i++)
	{
		count = 0;
		
		for (int j = 0; j < n; j++)
		{
			count += a[i][j];
		}
		
		// nodes are checked to determine if 
		// the rows and columns equal zero
		if (count == 0)
		{
			for (int k = 0; k < n; k++)
				count += a[k][i];
			
			if (count == 0)
			{	
				iNode[i] = i+1;
				nodeCount++;
			}
		}	
	}
	
	if (nodeCount == 0)
		cout << "The Graph has no isolated nodes";
	
	for (int i = 0; i < n; i++)
	{
		if (iNode[i] != 0 && iNode[i] <= n)
			cout << iNode[i] << " ";
	}
	
	if (nodeCount == 1)
		cout << "is an isolated node\n\n";
	else if (nodeCount >= 2)
		cout <<  "are isolated nodes\n\n";
	
	delete [] iNode;
}


// displays a single node's degree
void nodeDegree(int** a, int n)
{
	int degree = 0;
	int nodeInp;
	
	cout << "\n\nEnter Node: ";
	cin >> nodeInp;
	
	for (int i = 0; i < n; i++)
		degree += a[nodeInp-1][i];
	
	cout << "\nNode " << nodeInp << " degree: " << degree << "\n\n";
}


// determines if an Euler path exists in the graph
void nodeEuler(int** a, int n)
{
	int* dNode = new int [n];
	int degree = 0;
	
	for (int i = 0; i < n; i++)
	{
		degree = 0;
		
		for (int j = 0; j < n; j++)
			degree += a[i][j];
		
		dNode[i] = degree;
	}
	
	// the actual numerical path (ex. 1 2 4 2) is not determined 
	// it is only tested to verify if an Euler path exists in the graph
	// an Euler path is found if all nodes are even (minus isolated nodes)
	// or there are only 2 odd nodes
	if (checkEven(dNode, n) || checkOdd(dNode, n))
		cout << "\n\nThe Graph has an Euler Path\n";
	else
		cout << "\n\nThe Graph does not have an Euler Path\n";
	
	delete [] dNode;
}


// determines if all nodes are even
bool checkEven(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i] % 2 != 0)
			return false;
	}
	
	return true;
}


// determines if exactly 2 nodes are odd
bool checkOdd(int* a, int n)
{
	int oddNum = 0;
	
	for (int i = 0; i < n; i++)
	{
		if (a[i] % 2 != 0)
			oddNum++;
	}
	
	if (oddNum == 2)
		return true;
	else
		return false;
}


// determines if 2 nodes are connected
void nodeAdj(int** a, int n)
{
	int node1;
	int node2;
	
	cout << "\n\nEnter two nodes: ";
	cin >> node1 >> node2;
	
	// node direction is not taken into account for determining adjacency
	if (a[node1-1][node2-1] == 1 || a[node2-1][node1-1] == 1)
	{
		cout << "\n\nNode " << node1 << " is adjacent to node "
			 << node2 << "\n\n";
	}
	else
	{
		cout << "\n\nNode " << node1 << " is not adjacent to node "
			 << node2 << "\n\n";
	}
}


void menu(int** a, int n)
{
	bool flag = true;
	int uInp;
	
	while (flag)
	{
		cout << "\nAdjacency Matrix Menu\n---------------------\n"
			 << "[1] Print the Adjacency Matrix\n"
			 << "[2] Determine if there are any Isolated Nodes\n"
			 << "[3] Determine the Degree of a Node\n"
			 << "[4] Determine if an Euler Path Exists\n"
			 << "[5] Determine if One Node is Adjacent to Another\n"
			 << "[6] Quit\n\n";
		cin >> uInp;
		
		switch (uInp)
		{
			case 1: displayArray(a,n);
				break;
			case 2: isoNode(a, n);
				break;
			case 3: nodeDegree(a, n);
				break;
			case 4: nodeEuler(a, n);
				break;
			case 5: nodeAdj(a, n);
				break;
			case 6: flag = false;
				break;
		}
	}
}