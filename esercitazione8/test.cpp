#include "unidirected_edge.hpp"
#include "unidirected_graph.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>

int main(void)
{
	bool test = true;
	
	unidirected_graph<int> grafo;
	
	grafo.add_edge(1,2); //0
	grafo.add_edge(1,3); //1
	grafo.add_edge(1,4); //2
	grafo.add_edge(1,5); //3
	grafo.add_edge(3,4); //4
	grafo.add_edge(5,6); //5
	grafo.add_edge(6,7); //6
	
	//verifico che neighbours() restituisca i vicini
	std::set<int> set_prova{2,3,4,5}; //sono i vicini del nodo 1
	if (grafo.neighbours(1) != set_prova) {
		std::cout << "Errore nei neighbours di 1\n";
		test = false;
	}
	
	//verifico il metodo all_edges()
	std::vector<unidirected_edge<int>> 
	archi_prova = {
		unidirected_edge<int>(1,2),
		unidirected_edge<int>(1,3), 
		unidirected_edge<int>(1,4),
		unidirected_edge<int>(1,5), 
		unidirected_edge<int>(3,4), 
		unidirected_edge<int>(5,6),
		unidirected_edge<int>(6,7)};
	if (grafo.all_edges() != archi_prova) {
		std::cout << "Errore in all_edges()\n";
		test = false;
	}
	
	//verifico il metodo all_nodes() 
	std::set<int> nodi_prova{1,2,3,4,5,6,7};
	if (grafo.all_nodes() != nodi_prova) {
		std::cout << "Errore in all_nodes\n"; 
		test=false;
	}
	
	//verifico il metodo edge_number() 
	int numero_arco = 3; //il terzo arco (l'indice parte da 0) è (1,5)
	if (grafo.edge_number(unidirected_edge<int>(1,5)) != numero_arco) {
		std::cout << "Errore in edge_number\n";
		test=false;
	}
	
	//verifico il metodo edge_at()
	unidirected_edge<int> arco_prova(5,6); //(5,6) è il settimo arco
	if (grafo.edge_at(5) != arco_prova) {
		std::cout << "Errore in edge_at\n";
		test=false;
	}
	
	//verifico l'operatore -()
	unidirected_graph<int> grafo2;
	//grafo2 è il ciclo 1-3-4 presente nel grafo 1
	grafo2.add_edge(1,3);
	grafo2.add_edge(3,4);
	grafo2.add_edge(1,4);
	unidirected_graph<int> differenza = grafo - grafo2;
	if (differenza.all_edges().size() != 4) {
		std::cout << "Errore nella dimensione della differenza\n"; 
	}
	
	if (test) {
		std::cout << "Test eseguito con successo.\n";
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
	
}