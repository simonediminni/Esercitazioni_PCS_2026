#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include "unidirected_graph.hpp"

using namespace std;

template<typename T>
class lifo {
	std::list<T> s;
	
	public: 
	//costruttore di default
	lifo() : s() {}
	
	//metodo put()
	void put(T elem) {
		s.push_front(elem);
	}
	
	//metodo get()
	T get(void){
		T first = s.front();
		s.pop_front();
		return first;
	}
	
	//metodo empty()
	bool empty(void) {
		return s.empty();
	}

};

//GRAPH VISIT
//crea l'albero della DFS

template<typename T, typename Contenitore>
unidirected_graph<T> graph_visit(const unidirected_graph<T>& grafo, T nodo, Contenitore& c) {
	unidirected_graph<T> result;
	std::map<T, bool> reached;
	for (const auto& n : grafo.all_nodes()) { 
		reached[n] = false;
	}
	
	// Controllo se il nodo di partenza esiste, se no restituisco un grafo vuoto
    if (reached.find(nodo) == reached.end()) return result;
	
	reached[nodo] = true;
    c.put(nodo);
	
	
	while (!c.empty()){
		T u = c.get();
		
		for (const auto& v : grafo.neighbours(u)) { 
			if(!reached[v]){
			reached[v] = true;
			c.put(v);
			result.add_edge(u, v);
			}
		}
	}
	return result;

}

//CICLI TRAMITE DFS
	
//algoritmo ricorsivo che trova percorso da u nodo u a nodo v
bool findpath(unidirected_graph<int>& dfs, int u, int v, std::vector<int>& path,
	std::set<int>& visited) {
	
	visited.insert(u);
	path.push_back(u);
	if (u==v) {
		return true;
		}
	for (const auto& n : dfs.neighbours(u)) {
		if (!visited.count(n)) {
			if (findpath(dfs, n, v, path, visited)) {
				return true;
			}
		}
	}
	path.pop_back();
	return false;
}

//per ogni arco (n1,n2) del coalbero, trovo percorso sull'albero dfs che porta da n1 a n2, ovvero un ciclo
std::vector<std::vector<int>> find_cicli(unidirected_graph<int>& g, int nodo) {
	std::vector<std::vector<int>> result;
	lifo<int> stack;
	unidirected_graph<int> dfsT = graph_visit(g, nodo, stack);
	unidirected_graph<int> coalbero = g-dfsT; 
	
	//itero sugli archi del coalbero e chiamo algoritmo ricorsivo
	for (const auto& edge : coalbero.all_edges()){
		int n1 = edge.from(); int n2=edge.to();
		std::vector<int> path;
		
		std::set<int> visited;
		
		findpath(dfsT, n1, n2, path, visited);
		result.push_back(path);
		}
		return result;
	}