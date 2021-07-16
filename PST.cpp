#include "PST.h"
#include<assert.h>

PST::PST(){
}

PST::PST(Company *companies,unsigned int array_size){
    assert(companies != NULL);
    Node *auxiliary_array[array_size];

    for (int i=0;i<array_size;i++){
        auxiliary_array[i] = new Node;
        auxiliary_array[i]->company = &companies[i];
        auxiliary_array[i]->priority = i+1;
        auxiliary_array[i]->employees = companies[i].getEmployees();
    }
    buildPst(node,auxiliary_array,0,array_size-1);
}

void PST::buildPst(Node *&parent,Node *subarray[],int start,int end){
    if (start > end){
        return;
    }else if(start == end){
        parent = subarray[start];
    }else{
        int position_least_priority = locateLeastPriorityElement(subarray,start,end); //O(n)
        if (position_least_priority != start){
            Node *aux = subarray[start];
            subarray[start] = subarray[position_least_priority];
            subarray[position_least_priority] = aux;
        }

        mergeSort(subarray,start+1,end);  //O(n * log n)
        int median_index = -1;
        int median = calculateMedian(subarray,start+1,end,median_index);  //O(1)

        parent = subarray[start];
        parent->distribution_key = median;

        buildPst(parent->left,subarray,start+1,median_index);  //O(n * log n)
        buildPst(parent->right,subarray,median_index+1,end);     //O(n * log n)
    }
}

void PST::_delete(Node *&node){
    if (node != NULL){
        _delete(node->left);
        _delete(node->right);
    }
    delete node;
    node = NULL;
}

PST::~PST(){
    _delete(node);
}

void PST::mergeSort(Node *subarray[],int l,int r) const{
	int m;
	if(l<r){
		int m = (l+r) / 2;
		mergeSort(subarray,l,m);
		mergeSort(subarray,m+1,r);
		merge(subarray,l,r,m);
	}else{
		return;
	}
}

void PST::merge(Node *subarray[],int left,int right,int middle) const{
	int n1 = middle - left +1;
	int n2 = right - middle;
	Node *l_array[n1],*r_array[n2];

	for (int x=0; x < n1; x++)
        l_array[x] = subarray[left + x];
    for (int z = 0; z < n2; z++)
        r_array[z] = subarray[middle + 1 + z];

	int i=0,j=0,k=left;
	while ((i < n1)&&(j < n2)){
		if (l_array[i]->employees <= r_array[j]->employees){
			subarray[k] = l_array[i];
			i++;
		}else{
			subarray[k] = r_array[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
        subarray[k] = l_array[i];
        i++;
        k++;
    }

    while (j < n2) {
        subarray[k] = r_array[j];
        j++;
        k++;
    }
}

int PST::calculateMedian(Node *ordered_array[],unsigned int left, unsigned int right,int &index) const{
    index = (right+left)/2;
    return ordered_array[index]->employees;
}

int PST::locateLeastPriorityElement(Node *subarray[],int start,int end) const{
    if (start >= end){ return start;}
    int least_priority = subarray[start]->priority;
    int position_least_priority = start;
    for (int i=start+1;i<end;i++){
        if (subarray[i]->priority < least_priority){
            least_priority = subarray[i]->priority;
            position_least_priority = i;
        }
    }
    return position_least_priority;
}

void PST::searchCompanies(List<Company*> &list,Node *node,int priority,int minimum,int maximum){
    if (node != NULL){
        if (node->priority > priority){ return;}
        if ((node->employees >=minimum)&&(node->employees <= maximum)){
            list.addElement(node->company);
        }
        if (minimum < node->distribution_key){
            searchCompanies(list,node->left,priority,minimum,maximum);
        }
        if (maximum > node->distribution_key){
            searchCompanies(list,node->right,priority,minimum,maximum);
        }
    }
}

void PST::searchCompaniesByPriority(List<Company*> &list_by_priority,int priority,int inf_limit,int sup_limit){
    searchCompanies(list_by_priority,node,priority,inf_limit,sup_limit);
}
