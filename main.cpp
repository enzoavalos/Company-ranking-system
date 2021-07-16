#include <iostream>
using namespace std;

#include <fstream>
#include<assert.h>
#include<stdlib.h>
#include<conio.h>

#include "Company.h"
#include "BST.h"
#include "Functions.h"
#include "PST.h"

int main()
{
    Company *companies = NULL;
    unsigned int array_size = 0;
    BST<string> *bst_by_name = NULL;
    BST<int> *bst_by_position = NULL;
    PST *priority_tree = NULL;

    processInputFile("company_ranking.csv",companies,bst_by_name,bst_by_position,array_size,priority_tree);
    mainMenu(companies,array_size,bst_by_name,bst_by_position,priority_tree);

    return 0;
}
