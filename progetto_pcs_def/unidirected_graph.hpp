#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include "unidirected_edge.hpp"


template<typename I> requires std::integral<I>

class unidirected_graph {
private:
	//vettore di oggetti di tipo unidirected_edge (archi)
	std::vector<unidirected_edge<I>> archi;
	
	//mappa che ha come chiave l'arco, e come valore associato la sua posizione
	std::map<unidirected_edge<I>, int> mappa_archi; 
	
	//mappa che ha come chiave il numero di un nodo, e come valore associato il set dei nodi adiacenti
	std::map<I, std::set<I>> mappa_adiacenza;
	
public:
	
	//costruttore di default
	unidirected_graph(): archi({}), mappa_archi({}), mappa_adiacenza({}) {
	}
	
	//costruttore di copia
	unidirected_graph(const unidirected_graph& other) : 
	archi(other.archi), mappa_archi(other.mappa_archi), mappa_adiacenza(other.mappa_adiacenza) {}

	
	//implementazione del metodo neighbours()
	std::set<I> neighbours(const I& nodo) const {
		//uso la member function find 
		auto itor = mappa_adiacenza.find(nodo);
		
		if (itor != mappa_adiacenza.end()) {
			//se c'è il nodo, restituisco i suoi neighbours
			return itor->second;
		}
		else { 
			//altrimenti, restituisco il set vuoto
			return std::set<I>(); 
		}
	}
	
	//il metodo add_edge() permette di aggiungere un arco
	void add_edge(const I& from, const I& to) {
		unidirected_edge<I> arco(from,to);
		
		//controllo se l'arco già esiste
		if (mappa_archi.find(arco) == mappa_archi.end()) {
			//memorizzo la posizione in cui mettere il nuovo arco
			int posizione = archi.size();
			
			archi.push_back(arco);
			mappa_archi[arco]=posizione;
			//aggiorno i neighbours
			mappa_adiacenza[from].insert(to);
			mappa_adiacenza[to].insert(from);
		}
	}
	
	//il metodo all_edges() restituisce tutti gli archi
	std::vector<unidirected_edge<I>> all_edges() const {
		return archi;
	}
	
	//il metodo all_nodes() restituisce tutti i nodi
	std::set<I> all_nodes() const {
		std::set<I> nodi;
		for (typename std::map<I,std::set<I>>::const_iterator itor = mappa_adiacenza.begin(); 
		itor!=mappa_adiacenza.end(); itor++) {
			nodi.insert(itor->first);
		}
		return nodi; 
	}

	//il metodo edge_number(), dato un arco, restituisce la sua numerazione
	int edge_number(const unidirected_edge<I>& arco) const {
		//uso la funzione .at() che accede all'elemento e verifica se esiste
		return mappa_archi.at(arco);
	}
	
	//il metodo edge_at(), dato un numero d'arco, restituisce il corrispondente
	//oggetto arco all'interno del grafo
	unidirected_edge<I> edge_at(int numero) const {
		//uso nuovamente .at()
		return archi.at(numero);
	}
	
	//l'operatore -() permette di calcolare la differenza tra due grafi:
	//dati G e G′ la differenza G − G′ è data dagli archi presenti in G e non presenti in G'
	unidirected_graph operator-(const unidirected_graph& other) const {
		unidirected_graph differenza;
		
		for (auto itor = archi.begin(); itor!=archi.end(); itor++) {
			if (other.mappa_archi.find(*itor) == other.mappa_archi.end()) {
				differenza.add_edge(itor->from(), itor->to());
			}
		}
		return differenza;
	}
		
};