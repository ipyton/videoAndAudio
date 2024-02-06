// AdvancedAlgo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "RbTree.cpp"
int main()
{
    RBTree<int,int>* tree = new RBTree<int,int>();
    int keyArray[20] = { 24,25,13,35,23, 26,67,47,38,98, 20,19,17,49,12, 21,9,18,14,15 };
    for (int i = 0; i < 20; i++) {
        tree->insert_node(keyArray[i], keyArray[i]);
    }

    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
