#ifndef COMPANY_H_INCLUDED
#define COMPANY_H_INCLUDED

#include<iostream>
using namespace std;

class Company{
    private:
        string brand_name;
        string country_of_origin;
        unsigned int employees;
        string work_area;
    public:
        Company();
        Company(string,string,unsigned int,string);
        virtual ~Company();
        Company& operator=(const Company&);

        string getLegalName() const;
        string getCountryOfOrigin() const;
        string getWorkArea() const;
        int getEmployees() const;
};

#endif // COMPANY_H_INCLUDED
