#include <fstream>
#include <iostream>
#include <string>

int main(int argc, const char *argv[]) {
	
	if (argc < 2) {
		std::cerr << "Errore: inserire il nome del file\n";
		return 1;
	}
	std::ifstream ifs(argv[1]);
	if (ifs.is_open() ) {
			std::string location;
			double temp1=0;
			double temp2=0;
			double temp3=0;
			double temp4=0;
			while(!ifs.eof() ) {
				ifs >> location >> temp1 >> temp2 >> temp3 >> temp4;
				double sum = temp1 + temp2+ temp3 + temp4;
				double mean = sum/4;
				std::cout << location << " " << mean << "\n";
			}
		}
	else {
		std::cerr << "Errore: impossibile aprire il file\n";
		return 1;
	}
	return 0;
}