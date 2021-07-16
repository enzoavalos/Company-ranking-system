#ifndef PST_H_INCLUDED
#define PST_H_INCLUDED

#include "Company.h"
#include "List.h"

class PST{
    private:
        struct Node{
            Company *company = NULL;
            unsigned int priority;
            unsigned int employees;
            int distribution_key = -1;
            Node *left = NULL;
            Node *right = NULL;
        };
        Node *node = NULL;

        int locateLeastPriorityElement(Node *[],int,int) const;
        void buildPst(Node *&,Node *[],int,int);
        void mergeSort(Node *[],int,int) const;
        void merge(Node *[],int,int,int) const;
        void _delete(Node *&);
        int calculateMedian(Node *[],unsigned int,unsigned int,int&) const;
        void searchCompanies(List<Company*>&,Node *,int,int,int);

    public:
        PST();
        PST(Company *,unsigned int);
        ~PST();
        void searchCompaniesByPriority(List<Company*>&,int,int,int);
};

#endif // PST_H_INCLUDED
