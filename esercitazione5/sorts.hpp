#pragma once
#include <vector>
#include <optional>
#include <math.h>
#include <algorithm>
#include <type_traits>
#include <string>
#include <limits>

//Funzione 1: is_sorted
template<typename T>
bool is_sorted(const std::vector<T>& vec)
{
	if (vec.size() <= 1) {
		return true; //se il vettore ha 0 o 1 elemento, è ordinato
	}
		
	for (int i = 0; i<vec.size()-1; i++) {
		if (vec[i]>vec[i+1]) {
			return false;
		}
	}
	return true;
}

//Funzione 2: bubble sort
template<typename T>
void bubble_sort(std::vector<T>& vec)
{
	if (vec.size() <= 1) {
		return;
	}
	
	for (int i=0; i<vec.size()-1; i++) {
		for (int j=vec.size()-1; j>i; j--) {
			if (vec[j] < vec[j-1]) {
				T min = vec[j];
				vec[j] = vec[j-1];
				vec[j-1] = min;
			}
		}
	}
}

//Funzione 3: insertion sort
template<typename T>
void insertion_sort(std::vector<T>& vec)
{
	if (vec.size() <= 1) {
		return;
	}
	
	for (int j=1; j<vec.size(); j++) {
		T key = vec[j];
		int i = j-1;
		while (i>=0 && vec[i]>key) {
			vec[i+1] = vec[i];
			i = i-1;
		}
		vec[i+1]=key;
	}
}

//Funzione 4: selection sort
template<typename T>
void selection_sort(std::vector<T>& vec)
{
	if (vec.size() <= 1) {
		return;
	}
	
	for (int i=0; i<vec.size()-1; i++) {
		int min = i;
		for (int j=i+1; j<vec.size(); j++) {
			if (vec[j]<vec[min]) {
				min = j;
			}
		}
		T vec_min=vec[i];
		vec[i]=vec[min];
		vec[min]=vec_min;
	}
}

//Funzione merge
template<typename T>
void merge(std::vector<T>& vec, int p, int q, int r)
{
	int n1 = q-p+1;
	int n2 = r-q;
	std::vector<T> L(n1+1);
	std::vector<T> R(n2+1);
	for (int i=0; i<=n1-1; i++) {
		L[i]=vec[p+i];
	}
	for (int j=0; j<=n2-1; j++) {
		R[j]=vec[q+j+1];
	}
	
	//verifico se sto ordinando un vettore di stringhe usando std::is_same 
	if constexpr (std::is_same<T,std::string>::value) {
		int i=0;
		int j=0;
		for (int k=p; k<=r; k++) {
			//controllo se L non è finito && (R è finito || L è più piccolo)
			if (i<n1 && (j>=n2 || L[i]<=R[j])) {
				vec[k]=L[i];
				i++;
			}
			else {
				vec[k]=R[j];
				j++;
			}
		}
	}
	else {
		L[n1]=std::numeric_limits<T>::max();
		R[n2]=std::numeric_limits<T>::max(); 
		int i=0;
		int j=0;
		for (int k=p; k<=r; k++) {
			if (L[i]<=R[j]) {
				vec[k]=L[i];
				i++;
			}
			else {
				vec[k]=R[j];
				j++;
			}
		}
	}
}
	

//Funzione 5: merge sort
template<typename T>
void merge_sort(std::vector<T>& vec, int p, int r)
{
	
	if (p<r) {
		int q = (p+r)/2;
		merge_sort(vec,p,q);
		merge_sort(vec,q+1,r);
		merge(vec,p,q,r);
		return;
	}
}

//Funzione partition
template<typename T>
int partition(std::vector<T>& vec, int p, int r)
{
	T x = vec[r];
	int i = p-1;
	for (int j=p; j<=r-1; j++) {
		if (vec[j]<=x) {
			i = i+1;
			std::swap(vec[i],vec[j]);
		}
	}
	std::swap(vec[i+1],vec[r]);
	return i+1;
}                 


//Funzione 6: quick sort 
template<typename T>
void quick_sort(std::vector<T>& vec, int p, int r)
{
	if (p<r) {
		int q = partition(vec,p,r);
		quick_sort(vec,p,q-1);
		quick_sort(vec,q+1,r);
	}
}
	
//Costruisco un insertion sort "modificato" che agisce solo su una parte del vettore
template<typename T>
void insertion_sort_blocco(std::vector<T>& vec, int p, int r) {
	for (int j=p+1;j<=r;j++) {
		T key = vec[j];
		int i = j-1;
		while (i>=p && vec[i]>key) {
			vec[i+1]=vec[i];
			i=i-1;
		}
		vec[i+1]=key;
	}
}

//Funzione 7: quick sort modificato
template<typename T>
void quick_sort_modified(std::vector<T>& vec, int p, int r)
{
	int valore_soglia = 38; //è la lunghezza del vettore fino alla quale insertion sort è più veloce di quick sort
	if (p<r) {
		int n=r-p+1;
		
		if (n<=38) {
			insertion_sort_blocco(vec,p,r);
		}
		else {
			int q = partition(vec,p,r);
			quick_sort_modified(vec,p,q-1);
			quick_sort_modified(vec,q+1,r);
		}
	}
}
