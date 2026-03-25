#include <iostream>
#include <cmath>

int main()
{
	static const int N=10;
	double ad[N]= {0.0, 2.4, 5.6, 3.2, 4.7, 5.2, 0.4, 1.9, 6.3, 1.1};
	double minimo=ad[0], massimo=ad[0], somma=0, mean, devst;
	for(int i=0; i<N; i++) {
		if (ad[i]<=minimo) {
			minimo=ad[i];
		}
		if (ad[i]>=massimo) {
			massimo=ad[i];
		}
		somma+=ad[i];
	}
	mean = somma/N;
	for(int i=0; i<N; i++) {
		devst += (mean-ad[i])*(mean-ad[i]);
		}
	devst = std::sqrt(devst/(N-1));
	std::cout << "Minimo: " << minimo << "\n";
	std::cout << "Massimo: " << massimo << "\n";
	std::cout << "Media: " << mean << "\n";
	std::cout << "Deviazione standard: " << devst << "\n";
	
	//implemento l'algoritmo bubblesort
	
	double max=0;
	bool scambi=true;
	while (scambi) {
		scambi = false;
		for (int i=0; i<N-1; i++) {
			if (ad[i]>ad[i+1]) {
				max=ad[i];
				ad[i]=ad[i+1];
				ad[i+1]=max;
				scambi = true;
			}	
		}
	}
	std::cout << "I numeri in ordine crescente sono: ";
	for (int i=0; i<N; i++) {
		std::cout << ad[i] << " ";
	}
	return 0;
}
		
			
			
		
	