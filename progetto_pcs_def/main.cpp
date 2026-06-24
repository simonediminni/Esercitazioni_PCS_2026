#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <vector>
#include "unidirected_graph.hpp"
#include "cicli.hpp"
#include "funzioni.hpp"
#include "gc.hpp"


int main(int argc, const char *argv[])
{
	
	//LETTURA DEL FILE
	if (argc >1)
		{ifstream ifs(argv[1]);
	if (ifs.is_open()) {
		std::string tipo;
		double valore;
		int n1;
		int n2;
		unidirected_graph<int> g;
		
		std::vector<double> valori_resistenze; //vettore per salvare i valori delle resistenze
		std::vector<unidirected_edge<int>> archi_resistenze; //vettore di archi
		std::vector<double> valori_generatori; //salviamo i valori dei generatori di tensione 
		std::vector<std::pair<int, int>> nodi_generatori; //non si può usare unidirected_edge perché scambia l'ordine dei nodi: qui salviamo un vettore di coppie ("archi orientati")

		while (ifs >> tipo >> valore >> n1 >> n2){
			g.add_edge(n1,n2);
			
			if (tipo[0] == 'R'){ //è una resistenza
				valori_resistenze.push_back(valore); 
				archi_resistenze.push_back(unidirected_edge<int>(n1, n2)); //aggiungiamo l'arco associato alla resistenza
			}
			if (tipo[0] == 'V'){ //è un generatore
				valori_generatori.push_back(valore);
				nodi_generatori.push_back({n1,n2}); //aggiungiamo la pair associata al generatore
			}
			
			//std::cout <<"Tipo: " << tipo << " valore: "<< valore << " "<< n1<< " " << n2<<"\n"; 
		}
		
		for (int decidi_ciclo=0; decidi_ciclo<2; decidi_ciclo++) {
			std::vector<std::vector<int>> cicli;
			
			//ALGORITMO DFS
			if (decidi_ciclo==0) {
			
				std::cout << "Risoluzione con algoritmo DFS per la ricerca dei cicli: \n";
				cicli = find_cicli(g,n2); //usiamo come radice per la DFS il generico nodo n1 (l'ultimo salvato)
			}
			
			//ALGORITMO DE PINA
			if (decidi_ciclo==1) {
				
				std::cout << "\n\nRisoluzione con algoritmo De Pina per la ricerca dei cicli minimi: \n";
				std::vector<Eigen::VectorXi> base_de_pina = de_pina(g); //otteniamo con De Pina la base dei cicli minimi
				
				std::vector<unidirected_edge<int>> tutti_archi = g.all_edges();
				std::sort(tutti_archi.begin(),tutti_archi.end()); //ordiniamo gli archi usando il sort standard
				
				for (const auto& C_i : base_de_pina) {
					std::vector<int> ciclo_nodi = converti(C_i, tutti_archi);
					cicli.push_back(ciclo_nodi);
				}
			}
			
			std::cout << "Numero di maglie nel circuito: "  << cicli.size() << "\n";
			std::cout << "Cicli: ";
			for (const auto& ciclo : cicli) {
				std::cout << "\n( ";
				
				for (const int nodo : ciclo){
					std::cout << nodo << " ";
					}
				std::cout << ")\n";
				}
			
			//COSTRUZIONE SISTEMA LINEARE
			int m = valori_resistenze.size();
			int n_cicli = cicli.size();
			
			Eigen::MatrixXd R = Eigen::MatrixXd::Zero(m, m);
			Eigen::MatrixXd B = Eigen::MatrixXd::Zero(m, n_cicli);
				
			//creiamo R
			for (int i = 0; i < m; i++) {
				R(i, i) = valori_resistenze[i];
				}

			//creiamo B
			for (int j = 0; j < n_cicli; j++) {
				const auto& ciclo = cicli[j];
				int num_nodi = ciclo.size();

				//scorriamo gli archi formati dai nodi del ciclo
				for (int k = 0; k < num_nodi; k++) {
					int u = ciclo[k];
					int v = ciclo[(k + 1) % num_nodi]; //se siamo all'ultimo nodo, v torna a essere il primo (per chiudere il ciclo)

					unidirected_edge<int> arco_percorso(u, v);

					//cerchiamo se questo arco corrisponde a uno dei nostri resistori
					for (int i = 0; i < m; i++) {
						if (archi_resistenze[i] == arco_percorso) { //sono entrambi ordinati per come è costruita la classe
							if (u < v) {
								B(i,j) = 1.0;
							} else {
								B(i,j) = -1.0;
							}
						break; //una volta che troviamo la corrispondenza, usciamo dal ciclo for
							}
						}
					}
				}
				
			//creiamo v, il vettore dei termini noti
			Eigen::VectorXd v = Eigen::VectorXd::Zero(n_cicli); 

			//scorriamo su ciascuna maglia (colonna)
			for (int j = 0; j < n_cicli; j++) {
				const auto& ciclo = cicli[j];
				int num_nodi = ciclo.size();

				for (int k = 0; k < num_nodi; k++) {
					int u = ciclo[k];
					int verso_v = ciclo[(k + 1) % num_nodi];

					// controllo se l'arco (u, verso_v) contiene un generatore 
					for (unsigned int i = 0; i < valori_generatori.size(); i++) {
						int polo_positivo = nodi_generatori[i].first;
						int polo_negativo = nodi_generatori[i].second;
							
						if (u == polo_negativo && verso_v == polo_positivo) {
							// stiamo andando da - a + : sommo
							v(j) += valori_generatori[i];
							break;
							} 
						else if (u == polo_positivo && verso_v == polo_negativo) {
							// da + a - : sottraggo
							v(j) -= valori_generatori[i];
							break;
							}
					}
				}
			}


			std::cout << "\nMatrice delle Resistenze R:\n" << R << "\n";
			std::cout << "\nMatrice di incidenza B:\n" << B << "\n";
			std::cout << "\nVettore dei termini noti v:\n" << v << "\n";
			
			//RISOLUZIONE SISTEMA LINEARE
			
			Eigen::MatrixXd A = B.transpose()*R*B; 
			Eigen::VectorXd i_0 = Eigen::VectorXd::Zero(n_cicli); //inizializziamo il vettore arbitrario da cui parte il gradiente coniugato
			const double tol = 1.0e-12; //tolleranza per il metodo del gradiente
				
			Eigen::VectorXd i_calcolata = gradiente_coniugato(A, i_0, v, tol);
			//std::cout<< "i calcolata da gradiente_coniugato: "<<i_calcolata <<"\n";
			std::cout<<"\n\n";
			Eigen::VectorXd V_r = R*B*i_calcolata;
			Eigen::VectorXd I = B*i_calcolata;
			
			//STAMPA DEI RISULTATI
			
			for (int i=0; i<m; i++) {
				std::cout << "R" << i+1 << ": V = " << V_r(i) << " volts, I = "<<  I(i) <<" amps.\n";
			}
		}		

	}
	}
	else {
		std::cout << "Nome del file mancante.\n";
	}
	
return 0;
}
