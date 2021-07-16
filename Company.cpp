#include "Company.h"
#include<assert.h>

Company::Company(){
}

Company::Company(string brand_name,string country_of_origin,unsigned int employees,string work_area){
    assert(employees > 0);
    this->brand_name = brand_name;
    this->country_of_origin = country_of_origin;
    this->employees = employees;
    this->work_area = work_area;
}

Company::~Company(){
}

string Company::getLegalName() const{
    return brand_name;
}

string Company::getCountryOfOrigin() const{
    return country_of_origin;
}

string Company::getWorkArea() const{
    return work_area;
}

int Company::getEmployees() const{
    return employees;
}

Company& Company::operator=(const Company& other){
    this->brand_name = other.brand_name;
    this->country_of_origin = other.country_of_origin;
    this->employees = other.employees;
    this->work_area = other.work_area;
}
