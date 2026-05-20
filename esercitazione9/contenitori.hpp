#pragma once
#include <iostream>
#include <list>
#include <limits> //per l'infinito in Dijkstra

template<typename I>
class fifo
{
private:
	std::list<I> queue;
public:
	fifo(): queue({}) {}
	
	void put(const I& elemento) {
		queue.push_back(elemento);
		return;
	}
	
	I get() {
		I primo = queue.front();
		queue.pop_front();
		return primo;
		
	}
	
	bool empty() {
		return queue.empty();
	}
	
};

template<typename I>
class lifo
{
private:
	std::list<I>  stack;

public:
	lifo(): stack({}) {}
	
	void put(const I& elemento) {
		stack.push_front(elemento);
		return;
	}
	
	I get() {
		I primo = stack.front();
		stack.pop_front();
		return primo;
		
	}
	
	bool empty() {
		return stack.empty();
	}
	
};

template<typename I, typename T> 
unidirected_graph<I> 
graph_visit(const unidirected_graph<I>& grafo, const I& sorgente, T contenitore) {
	
	unidirected_graph<I> albero;
	//inizializzo un set di nodi che funge da "reached" (qui reached=false)
	std::set<I> nodi_visitati; 
	
	contenitore.put(sorgente);
	nodi_visitati.insert(sorgente); //reached[sorgente]=true
	
	while (!contenitore.empty()) {
		I u = contenitore.get();
		//scorro ora sui vicini
		auto vicini = grafo.neighbours(u); //prendo il set dei vicini di u
		for (auto itor=vicini.begin();itor!=vicini.end();itor++) {
			const I& w = *itor; //prendo il nodo corrente dall'iteratore
			if (nodi_visitati.find(w) == nodi_visitati.end()) { //cioè se reached[w]=false
				nodi_visitati.insert(w); //reached[w]=true
				albero.add_edge(u,w); //aggiungo l'arco tra u e w
				contenitore.put(w); 
			}
		}
	}
	return albero;
}

//funzione ricorsiva da chiamare in recursive_dfs
template<typename I>
void ricorsione(const unidirected_graph<I>& grafo,
						  const I& nodo,
						  std::set<I>& visitati,
						  unidirected_graph<I>& albero) {
							  
	auto vicini = grafo.neighbours(nodo);
	
	for (auto itor = vicini.begin(); itor !=vicini.end(); itor++) {
		const I&w = *itor; //considero ogni vicino del nodo
		
		//se w non è stato ancora raggiunto (reached=false)
		if (visitati.find(w) == visitati.end()) {
			visitati.insert(w); //reached = true
			albero.add_edge(nodo,w); //aggiungo l'arco all'albero
			
			ricorsione(grafo, w, visitati, albero);

		}
	}
}	
		

template<typename I> unidirected_graph<I> 
recursive_dfs(const unidirected_graph<I>& grafo, const I& sorgente) {
	unidirected_graph<I> albero;
	std::set<I> visitati; //uso come per graph_visit un set come "reached"
	
	//inserisco la sorgente nei visitati
	visitati.insert(sorgente);
	
	//ricorsione
	ricorsione(grafo,sorgente,visitati,albero);
	
	return albero;
}
	
//implemento l'algoritmo di Dijkstra mettendo i pesi a 1
template<typename I> unidirected_graph<I> 
dijkstra(const unidirected_graph<I>& grafo, const I& sorgente) {
	std::map<I,I> pred; //predecessori
	std::map<I,int> dist; //distanze
	
	//inizializzazione di pred e dist
	const int infinito = std::numeric_limits<int>::max();
	auto nodi = grafo.all_nodes();
	for (auto itor = nodi.begin(); itor!=nodi.end(); itor++) {
		const I& i = *itor;
		pred[i]=-1;
		dist[i]=infinito;
	}
	
	pred[sorgente]=sorgente;
	dist[sorgente]=0;
	
	//inizializzazione della priority queue
	/*rappresento la PQ come un set di coppie (std::pair)
	nella pair il primo elemento è la priorità associata alla distanza,
	il secondo elemento è il nodo:
	in questo modo il set ordina gli elementi in base alla distanza*/
	
	std::set<std::pair<int,I>> PQ;
	
	for (auto itor=nodi.begin(); itor!=nodi.end(); itor++) {
		const I& nodo_corrente=*itor;
		PQ.insert({dist[nodo_corrente],nodo_corrente});
	}
	
	while (!PQ.empty()) {
		auto itor = PQ.begin(); //prendo l'iteratore all'inizio di PQ 
		int p = itor->first; //p è la distanza tra p e u
		I u = itor->second; //u è il nodo associato
		PQ.erase(itor); //rimuovo la coppia (u,dist) da PQ
		
		auto vicini = grafo.neighbours(u);
		//scorro tra i vicini di u
		for (auto it = vicini.begin(); it!=vicini.end(); it++) {
			const I& w = *it;
			int peso_arco = 1; //imposto come peso sempre 1
			
			if (dist[u] != infinito && dist[w]>dist[u] + peso_arco) {
				PQ.erase({dist[w],w}); //cancello la vecchia coppia
				dist[w] = dist[u] + peso_arco;
				pred[w]=u;
				PQ.insert({dist[w],w}); //aggiorno la priorità di w con nuova distanza
			}
		}
	}
		
	//costruisco ora l'albero dei cammini minimi in output_iterator
	unidirected_graph<I> albero;
	for (auto itor = nodi.begin(); itor != nodi.end(); itor++) {
		const I& w = *itor;
		//controllo se ci sono dei nodi isolati (in questo caso il valore è -1 quindi non lo inserisco
		//controllo, inoltre, che il nodo da aggiungere non sia il nodo sorgente, altrimenti si creerebbe un cappio
		if (pred[w] != -1 && pred[w]!=w) {
			albero.add_edge(pred[w],w);
		}
	}
	return albero;
	
}

		
		
		
	