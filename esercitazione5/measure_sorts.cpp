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
			  << std::setw(15) << "Merge"
			  << std::setw(15) << "Quick"
			  << std::setw(15) << "std::sort" 
			  << std::setw(15) << "Quick modificato" << "\n";
			  
	std::vector<double> tempi_bubble;
	std::vector<double> tempi_insertion;
	std::vector<double> tempi_selection;
	std::vector<double> tempi_stdsort;
	std::vector<double> tempi_merge;
	std::vector<double> tempi_quick;
	std::vector<double> tempi_quickmodified;
	
	for (int i=2; i<=200; i+=4) {
		
		std::vector<std::vector<double>> vettore(100,std::vector<double>(i));
		for (int k=0; k<100; k++) {
			rf.fill(vettore[k],-1000.0,1000.0);
		}
		
		std::vector<double> vec; //creo un vettore "di lavoro" di appoggio
		
		tc.tic();
		for (int k=0; k<100; k++) {
			vec = vettore[k];
			bubble_sort(vec);
		}
		double sec_bubble=tc.toc()/100.0;
		
		tc.tic();
		for (int k=0; k<100; k++) {
			vec = vettore[k];
			insertion_sort(vec);
		}
		double sec_insertion=tc.toc()/100.0;		
		
		tc.tic();
		for (int k=0; k<100; k++) {
			vec = vettore[k];
			selection_sort(vec);
		}
		double sec_selection=tc.toc()/100.0;
		
		tc.tic();
		for (int k=0; k<100; k++) {
			vec = vettore[k];
			std::sort(vec.begin(),vec.end());
		}
		double sec_stdsort=tc.toc()/100.0;
		
		tc.tic();
		for (int k=0; k<100; k++) {
			vec = vettore[k];
			merge_sort(vec,0,i-1);
		}
		double sec_merge=tc.toc()/100.0;
		
		tc.tic();
		for (int k=0; k<100; k++) {
			vec = vettore[k];
			quick_sort(vec,0,i-1);
		}
		double sec_quick=tc.toc()/100.0;
		
		tc.tic();
		for (int k=0; k<100; k++) {
			vec = vettore[k];
			quick_sort_modified(vec,0,i-1);
		}
		double sec_quickmodified=tc.toc()/100.0;


		std::cout << std::setw(12) << i
				  << std::setw(15) << sec_bubble
				  << std::setw(15) << sec_insertion
				  << std::setw(15) << sec_selection
				  << std::setw(15) << sec_merge
				  << std::setw(15) << sec_quick
				  << std::setw(15) << sec_stdsort 
				  << std::setw(15) << sec_quickmodified << "\n";
				  
		tempi_bubble.push_back(sec_bubble);
		tempi_insertion.push_back(sec_insertion);
		tempi_selection.push_back(sec_selection);
		tempi_stdsort.push_back(sec_stdsort);
		tempi_merge.push_back(sec_merge);
		tempi_quick.push_back(sec_quick);
		tempi_quickmodified.push_back(sec_quickmodified);
		
	}
	
	
	//stampo i tempi da copiare su matlab per realizzare i grafici
	std::cout << "\nTempi da copiare su Matlab per realizzare il grafico\n";
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
	
	std::cout << "tempi_mergesort = ["; 
	for (int i=0; i<tempi_merge.size(); i++) {
		std::cout << tempi_merge[i] << " ";
	}
	std::cout << "];\n";
	
	std::cout << "tempi_quicksort = ["; 
	for (int i=0; i<tempi_quick.size(); i++) {
		std::cout << tempi_quick[i] << " ";
	}
	std::cout << "];\n";
	
	std::cout << "tempi_quickmodified = ["; 
	for (int i=0; i<tempi_quickmodified.size(); i++) {
		std::cout << tempi_quickmodified[i] << " ";
	}
	std::cout << "];\n";
	
	return 0;
}
	
		