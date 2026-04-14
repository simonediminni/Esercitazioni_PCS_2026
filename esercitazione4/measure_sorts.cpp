#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> /*serve per usare std::setw per stampare a "tabella"*/
#include "randfiller.h"
#include "sorts.hpp"
#include "timecounter.h"

int main() {
	randfiller rf;
	timecounter tc; 
	
	std::cout << std::setw(12) << "Lunghezza"
			  << std::setw(15) << "Bubble"
			  << std::setw(15) << "Insertion"
			  << std::setw(15) << "Selection"
			  << std::setw(15) << "std::sort" << "\n";
			  
	std::vector<double> tempi_bubble;
	std::vector<double> tempi_insertion;
	std::vector<double> tempi_selection;
	std::vector<double> tempi_stdsort;
	
	for (int i=4; i<=8192; i*=2) {
		
		std::vector<double> vec(i);
		rf.fill(vec, -1000.0, 1000.0);
		
		std::vector<double> vec_bubble = vec;
		std::vector<double> vec_insertion = vec;
		std::vector<double> vec_selection = vec;
		std::vector<double> vec_stdsort = vec;
		
		tc.tic();
		bubble_sort(vec_bubble);
		double sec_bubble = tc.toc();
		
		tc.tic();
		insertion_sort(vec_insertion);
		double sec_insertion = tc.toc();
		
		tc.tic();
		selection_sort(vec_selection);
		double sec_selection = tc.toc();
		
		tc.tic();
		std::sort(vec_stdsort.begin(), vec_stdsort.end());
		double sec_stdsort = tc.toc();
		
		std::cout << std::setw(12) << i
				  << std::setw(15) << sec_bubble
				  << std::setw(15) << sec_insertion
				  << std::setw(15) << sec_selection
				  << std::setw(15) << sec_stdsort << "\n";
				  
		tempi_bubble.push_back(sec_bubble);
		tempi_insertion.push_back(sec_insertion);
		tempi_selection.push_back(sec_selection);
		tempi_stdsort.push_back(sec_stdsort);
		
	}
	
	//stampo i tempi da copiare su matlab per realizzare i grafici
	std::cout << "Tempi da copiare su Matlab per realizzare il grafico\n";
	std::cout << "tempi_bubble = ["; 
	for (int i=0; i<tempi_bubble.size(); i++) {
		std::cout << tempi_bubble[i] << " ";
	}
	std::cout << "];\n";
	
	std::cout << "tempi_insertion = ["; 
	for (int i=0; i<tempi_insertion.size(); i++) {
		std::cout << tempi_insertion[i] << " ";
	}
	std::cout << "];\n";
	
	std::cout << "tempi_selection = ["; 
	for (int i=0; i<tempi_selection.size(); i++) {
		std::cout << tempi_selection[i] << " ";
	}
	std::cout << "];\n";
	
	std::cout << "tempi_stdsort = ["; 
	for (int i=0; i<tempi_stdsort.size(); i++) {
		std::cout << tempi_stdsort[i] << " ";
	}
	std::cout << "];\n";
	
	return 0;
}
	
		