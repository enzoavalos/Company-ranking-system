#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "Company.h"
#include "BST.h"
#include "List.h"
#include "PST.h"

void processInputFile(string,Company *&,BST<string> *&,BST<int> *&,unsigned int&,PST *&);
void createPositionsTree(Company*,BST<int> *&,int,int);
void destroyPointers(Company *&,BST<string> *&,BST<int> *&,PST *&);
void mainMenu(Company *&,unsigned int,BST<string> *&,BST<int> *&);
void searchWithinRange(Company *,unsigned int,unsigned int,List<int> &);
void showCompany(Company*);

void processInputFile(string origin_file,Company *&companies,BST<string> *&bst_by_name,
                              BST<int> *&bst_by_position,unsigned int &array_size,PST *&priority_tree)
{
    ifstream file(origin_file);
    if (!file.is_open())
        cout << "The following file could not be opened: " << origin_file << endl;
    else {
        string line;
        getline(file, line);
        int companies_amount = atoi(line.c_str());

        array_size = companies_amount;
        companies = new Company[companies_amount];
        bst_by_name = new BST<string>;
        bst_by_position = new BST<int>;

        //A whole line is read every time
        int ranking_position = 0;
        while (getline(file, line)) {

            //First position
            int initial_pos = 0;
            int final_pos = line.find(';');
            string legal_name = line.substr(initial_pos, final_pos);

            //Second position
            initial_pos = final_pos + 1;
            final_pos = line.find(';', initial_pos);
            string country_of_origin = line.substr(initial_pos, final_pos - initial_pos);

            //Third position
            initial_pos = final_pos + 1;
            final_pos = line.find(';', initial_pos);
            unsigned int employees = atoi(line.substr(initial_pos, final_pos - initial_pos).c_str());

            //Fourth position
            initial_pos = final_pos + 1;
            final_pos = line.find(';', initial_pos);
            string work_area = line.substr(initial_pos, final_pos - initial_pos);

            Company company_from_file(legal_name,country_of_origin,employees,work_area);
            companies[ranking_position] = company_from_file;
            ranking_position+=1;

            bst_by_name->addElement(companies,ranking_position);
        }
        priority_tree = new PST(companies,array_size);
        createPositionsTree(companies,bst_by_position,1,array_size);
    }
}

void createPositionsTree(Company *companies,BST<int> *&bst_by_position,int inferior,int superior){
    //Creates a balanced tree from an array
    if (inferior <= superior){
        int middle = (superior+inferior)/2;
        bst_by_position->addElement(companies,middle);
        createPositionsTree(companies,bst_by_position,inferior,middle-1);
        createPositionsTree(companies,bst_by_position,middle+1,superior);
    }else{ return ;}
}

void destroyPointers(Company *&companies_array,BST<string> *&bst_by_name,BST<int> *&bst_by_position,
                      PST *&priority_tree){
    delete[] companies_array;
    delete bst_by_name;
    delete bst_by_position;
    delete priority_tree;
    priority_tree = NULL;
    companies_array = NULL;
    bst_by_name = NULL;
    bst_by_position = NULL;
}

void searchWithinRange(Company *companies_array,unsigned int array_size,unsigned int inferior,unsigned int superior,
                      List<int> &list){
    for (int i=0;i<array_size;i++){
        unsigned int empleados = companies_array[i].getEmployees();
        if ((empleados >= inferior)&&(empleados <= superior)){
            list.addElement(i+1);
        }
    }
}

void showCompany(Company *company_to_show){
    cout<<"\n ~ "<<company_to_show->getLegalName();
    cout<<"\n Work area: "<<company_to_show->getWorkArea();
    cout<<"\n Country of Origin: "<<company_to_show->getCountryOfOrigin();
    cout<<"\n Amount of employees: "<<company_to_show->getEmployees()<<endl;
}

void mainMenu(Company *&companies_array,unsigned int array_size,BST<string> *&bst_by_name,BST<int> *&bst_by_position,
                   PST *&priority_tree){
    char user_input='a';
    do{
        fflush(stdin);
        system("cls");
        cout<<"\n\t\t ~~ Welcome ~~";
        cout<<"\n Select one of the following: ";
        cout<<"\n 1- Get the position of a company";
        cout<<"\n 2- Get company at a certain position";
        cout<<"\n 3- Get companies with employees within a given range";
        cout<<"\n 4- Get the first n companies with employees within a given range";
        cout<<"\n 5- Exit"<<endl;
        cin>>user_input;

        switch(user_input){
            case '1':{
                fflush(stdin);
                system("cls");
                string company_to_search = "";
                cout<<"\n Enter the name of the desired company: ";
                getline(cin,company_to_search);

                int company_position = bst_by_name->searchCompany(company_to_search);
                if (company_position > 0){
                    cout<<"\n ~ "<<company_to_search<<" was found at position: "<<company_position<<endl;
                }else{
                    cout<<"\n The company could not be found. Please, try again\n";
                }
                break;
                }
            case '2':{
                fflush(stdin);
                system("cls");
                string user_position;
                cout<<"\n Enter the position you are looking for: ";
                getline(cin,user_position);

                unsigned int searched_position;
                try{
                    searched_position = stoi(user_position);
                }catch(...){
                    cout<<"\n Invalid input, please try again";
                    break;
                }

                Company *company_at_position = bst_by_position->searchCompany(searched_position);
                if (company_at_position != NULL){
                    showCompany(company_at_position);
                }else{
                    cout<<"\n The company could not be found. Please, try again\n";
                }
                break;
                }
            case '3':{
                fflush(stdin);
                system("cls");
                string minimum,maximum;
                cout<<"\n Enter the search limits \n";
                cout<<" Minimum amount of employees: ";
                getline(cin,minimum);
                cout<<" Maximum amount of employees: ";
                getline(cin,maximum);

                unsigned int inf_limit,sup_limit;
                try{
                    inf_limit = stoi(minimum);
                    sup_limit = stoi(maximum);
                    if (inf_limit > sup_limit){ throw(NULL); }
                }catch(...){
                    cout<<"\n Invalid input, please try again";
                    break;
                }

                List<int> range_list;
                searchWithinRange(companies_array,array_size,inf_limit,sup_limit,range_list);
                if (!range_list.listIsEmpty()){
                    range_list.initializeCursor();
                    unsigned int position_to_search;
                    while (!range_list.cursorIsFinal()){
                        position_to_search = range_list.getElementByCursor();
                        cout<<"\n Position: "<<position_to_search;
                        showCompany(&companies_array[position_to_search-1]);
                        range_list.advanceCursor();
                    }
                }else{
                    cout<<"\n We could not find companies with the desired characteristics";
                }
                break;}
            case '4':{
                system("cls");
                unsigned int priority = 0,inf_limit,sup_limit;
                string minimum="",maximum="";

                cout<<" Enter up to what position to look for: ";
                cin>>priority;
                cout<<"\n Enter the search limits \n";
                cout<<" Minimum amount of employees: ";
                fflush(stdin);
                getline(cin,minimum);
                cout<<" Maximum amount of employees: ";
                getline(cin,maximum);

                try{
                    inf_limit = stoi(minimum);
                    sup_limit = stoi(maximum);
                    if (inf_limit > sup_limit){ throw(NULL); }
                }catch(...){
                    cout<<"\n Invalid input, please try again";
                    break;
                }

                List<Company*> list_by_priority;
                priority_tree->searchCompaniesByPriority(list_by_priority,priority,inf_limit,sup_limit);
                if (!list_by_priority.listIsEmpty()){
                    list_by_priority.initializeCursor();
                    while (!list_by_priority.cursorIsFinal()){
                        showCompany(list_by_priority.getElementByCursor());
                        list_by_priority.advanceCursor();
                    }
                }else{
                    cout<<"\n We could not find companies with the desired characteristics";
                }
                break;
            }
            case '5':{
                cout<<"\n\t Goodbye!!\n";
                break;
            }
            default:{
                cout<<"\n Invalid input, please try again.";
                break;
            }
        }
        getch();
    }while(user_input != '5');

    destroyPointers(companies_array,bst_by_name,bst_by_position,priority_tree);
}

#endif // FUNCTIONS_H_INCLUDED
