#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include "Company.h"

template <typename T>
class BST{
    private:
        struct Node{
            Node *left = NULL;
            Node *right = NULL;
            Company *company = NULL;
            unsigned int ranking_position = 0;
        };
        Node *node = NULL;
        void _add(Node *&,Company *,int);
        void _delete(Node *&);
        Company* _search(Node *,int) const;
        int _search(Node *,string) const;

    public:
        BST();
        BST(Company *,unsigned int);
        virtual ~BST();
        void addElement(Company *,unsigned int);
        Company* searchCompany(unsigned int);
        int searchCompany(string);
};

#endif
