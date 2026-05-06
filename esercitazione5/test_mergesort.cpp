#include <iostream>
#include <vector>
#include <cstdlib> //mi serve per generare casualmente la lunghezza dei vettori 
#include "randfiller.h"
#include "sorts.hpp"

int main(void) {
	
	randfiller rf;
	
	for (int i=0; i<100; i++) {
		
		int lunghezza = (std::rand() % 500); /*seguo la funzione suggerita 
		da cppreference così diminuisco il range da [0,rand_max(32767)] a [0,499]*/
		std::vector<double> vec(lunghezza);
		rf.fill(vec,-1000.0,1000.0); 
		
		merge_sort(vec,0,lunghezza-1);
		if (!is_sorted(vec)) {
			std::cout << "Errore: il vettore " << i+1 << " non è ordinato.\n";
			return EXIT_FAILURE;
		}
	}
	
	std::vector<std::string> vec_stringhe = {"vivamus", "mea", "lesbia", "atque", "amemus",
		"rumoresque", "senum", "severiorum", "omnes", "unius", "aestimemus", "assis"};
	merge_sort(vec_stringhe,0,vec_stringhe.size()-1);
	
	if (!is_sorted(vec_stringhe)) {
		std::cout << "Errore: il vettore di stringhe non è ordinato.\n";
		return EXIT_FAILURE;
	} 
	
	std::cout << "Il test merge sort è andato a buon fine.\n";
	return EXIT_SUCCESS;
}