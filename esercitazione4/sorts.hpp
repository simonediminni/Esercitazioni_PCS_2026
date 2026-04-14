#pragma once
#include <vector>
#include <optional>

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