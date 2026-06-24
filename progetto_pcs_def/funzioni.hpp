#pragma once
#include <iostream>
#include <list>
#include <limits> //per l'infinito in Dijkstra
#include <Eigen/Dense>
#include <queue>
#include "cicli.hpp"


template<typename T>
unidirected_graph<T> dijkstra(const unidirected_graph<T>& grafo, T source) {
    // Grafo con il risultato
    unidirected_graph<T> result;
	
	int TNF = std::numeric_limits<int>::max();
    
    // mappe dei predecessori e delle distanze
    std::map<T, T> pred;
    std::map<T, int> dist;
    
    // PQ = Coda di Priorità, greater per avere il minimo in cima
    std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, std::greater<std::pair<int, T>>> PQ;

    // for (i = 0; i < m; i++)
    for (const auto& i : grafo.all_nodes()) {
        dist[i] = TNF; // dist[i] = +inf
        // non serve inizializzare pred[i] = -1, basta non inserirlo nella mappa
    }

    // Se il nodo non esiste, esco dall'algoritmo
    if (dist.find(source) == dist.end()) return result;

    // pred[S] = S 
    pred[source] = source; 
    
    // dist[S] = 0
    dist[source] = 0;

    //inizializzo la PQ con le varie coppie
	for (const T& nodo : grafo.all_nodes()){
		PQ.push({dist[nodo], nodo});
	}
    
    //seguo lo pseudocodice visto in aula
    while (!PQ.empty()) {
        
        
        int p = PQ.top().first;  // distanza minore
        T u = PQ.top().second;   // Nodo u con distanza p
        PQ.pop();

        // Se p è maggiore della distanza migliore, lo ignoriamo
        if (p > dist[u]) continue; 

        // esploro nodi vicini
        for (const auto& w : grafo.neighbours(u)) {
            
            //assumo peso=1 per tutti i nodi vicini
            int W_uw = 1; 

            // if (dist[w] > dist[u] + W[u,w])
            if (dist[w] > dist[u] + W_uw) {
                
                // dist[w] = dist[u] + W[u,w]
                dist[w] = dist[u] + W_uw; 
                
                // pred[w] = u
                pred[w] = u;
                
                // aggiorno la PQ
                PQ.push({dist[w], w}); 
            }
        }
    }
    // costruisco albero risultati
    for (const auto& nodo : pred) {
        T dopo = nodo.first;
        T prima = nodo.second; //predecessore
        
        // evito self-loop nodo sorgente
        if (dopo != prima) {
            result.add_edge(prima, dopo);
        }
    }
	
	return result;
}
	
//implementiamo la funzione minimal_cycle da usare nell'algoritmo di de pina	

template<typename T> Eigen::VectorXi minimal_cycle(
	const unidirected_graph<T>& G, 
	const std::vector<unidirected_edge<T>>& archi,
	const Eigen::VectorXi& S_i) {
		
	int m = archi.size(); //numero di archi
	auto nodi = G.all_nodes(); //prendiamo i nodi di G-T_supp
	
	/*per sdoppiare il grafo G e ottenere per ogni arco u+,u-,v+,v-
	usiamo un valore di "spostamento" che permetta di creare dei nodi 
	(quelli negativi) che non sono già esistenti*/
	int nodo_max = *std::max_element(nodi.begin(), nodi.end());
	int spostamento = nodo_max + 1;
	
	//creiamo il grafo ausiliario G' sdoppiato
	unidirected_graph<T> G_primo;
	
	//lifting
	for (int i=0; i<m; i++) {
		unidirected_edge<T> arco = archi[i];
		int u = arco.from();
		int v = arco.to();
		
		//verichiamo se l'arco è arrivo nel vettore S_i
		if (S_i(i) == 1) {
			//aggiungiamo gli archi incrociati (u+,u-) e (u-,v+)
			G_primo.add_edge(u,v+spostamento);
			G_primo.add_edge(u+spostamento,v); 
		}
		else { //se non è attivo, aggiungiamo gli archi paralleli (u+,v+) e (u-,v-)
			G_primo.add_edge(u,v);
			G_primo.add_edge(u+spostamento,v+spostamento);
		}
	}
	
	//inizializziamo una variabile per tracciare il ciclo minimo
	int min_elementi = std::numeric_limits<int>::max();
	Eigen::VectorXi miglior_ciclo = Eigen::VectorXi::Zero(m);
	
	//cerchiamo, ora, per ogni vertice v il cammino minimo, usando Dijkstra, tra v- e v+ in G'
	for (int v : nodi) {
		int v_meno = v + spostamento;
		
		//chiamiamo dijkstra, con v_meno come radice
		unidirected_graph<T> albero_dijkstra = dijkstra(G_primo, v_meno);
		
		
		//estraiamo il cammino dall'albero usando una funzione ausiliaria
		//std::vector<unidirected_edge<T>> archi_cammino = estrai_cammino(albero_dijkstra, v_meno, v);
		std::vector<unidirected_edge<T>> archi_cammino;
		std::vector<int> percorso;
		std::set<int> reached;
		findpath(albero_dijkstra, v_meno, v, percorso, reached);
		for (size_t i=0; i+1<percorso.size(); i++) {
			unidirected_edge<T> arco_percorso(percorso[i],percorso[i+1]);
			archi_cammino.push_back(arco_percorso);
		}
		//forse usare find_path??
		
		
		/* per ogni cammino trovato, costruiamo un vettore di incidenza C_mu di lunghezza m,
		in cui per ogni occorrenza di arco (u_alfa,v_beta), dove alfa e beta sono + o -, 
		si incrementa modulo 2 l'elemento relativo all'arco (u,v) */
		Eigen::VectorXi C_mu = Eigen::VectorXi::Zero(m);
		
		//inizializziamo un contatore per il numero di archi nel ciclo 
		//(sarà il numero di 1 in C_mu)
		int num_archi = 0;
		
		for (const auto& arco : archi_cammino) {
			//riconvertiamo i nodi + e - nei nodi reali
			int n1 = arco.from();
			int n2 = arco.to();	
			if (n1 >= spostamento) {
				n1 -= spostamento;
			}

			if (n2 >= spostamento) {
				n2 -= spostamento;
			}
			
			//creiamo l'arco "reale" con n1 e n2
			unidirected_edge<T> arco_reale(n1,n2);
			
			//cerchiamo l'indice dell'arco nel vettore degli archi in input
			auto it = std::find(archi.begin(), archi.end(), arco_reale);
			if (it != archi.end()) { //se lo troviamo
				int indice = std::distance(archi.begin(), it);
				//incrementiamo l'elemento relativo all'arco modulo 2
				C_mu(indice) = (C_mu(indice)+1) % 2;
			}
		}
		
		//contiamo quanti archi fanno parte del ciclo (cioè gli 1 in C_mu)
		for (int e = 0; e<m; e++) {
			if (C_mu(e) == 1) {
				num_archi ++;
			}
		}
		
		//controlliamo se è il miglior ciclo
		if (num_archi < min_elementi && num_archi > 0) {
			min_elementi = num_archi;
			miglior_ciclo = C_mu;
		}
	}
	
	return miglior_ciclo;
}
	
		
//implementiamo l'algoritmo di De Pina	

template<typename T> std::vector<Eigen::VectorXi> 
de_pina(unidirected_graph<T>& G) 
{
	int m = G.all_edges().size(); //numero di archi
	int V = G.all_nodes().size(); //numero di nodi
	int k = m - V + 1; //numero di cicli
	
	//costruiamo un vettore (di dim k) di vettori "booleani" (di dim m)
	std::vector<Eigen::VectorXi> vettore_S(k,Eigen::VectorXi::Zero(m));

	
	//applichiamo la dfs a G per ottenere l'albero di supporto T_supp
	lifo<int> stack;
	unidirected_graph<T> T_supp = graph_visit(G,1,stack); //assumiamo il nodo 1 come radice
	
	//costruiamo il coalbero C
	unidirected_graph<T> C = G-T_supp;
	
	//facciamo l'ordine lessicografico sugli archi di G
	std::vector<unidirected_edge<T>> archi = G.all_edges();
	std::sort(archi.begin(),archi.end());
	//usiamo il sort standard, altrimenti avremmo potuto usare il quick modificato
	//implementato nelle esercitazioni precedenti
	
	//prendiamo la lista degli archi nel coalbero C
	std::vector<unidirected_edge<T>> archi_C = C.all_edges();
	
	//inizializziamo i vettori S_i
	int indice = 0; //indice che tiene traccia della riga a cui siamo
	for (int i=0; i<m; i++) {
		unidirected_edge<T> arco = archi[i];
		
		//verifichiamo se l'arco è anche nel coalbero C
		auto itor = std::find(archi_C.begin(), archi_C.end(), arco);
		if (itor!=archi_C.end()) { //cioè se viene trovato
			vettore_S[indice](i) = 1;
			indice++;
		}
	}
	
	//inizializziamo il contenitore finale per la base di cicli minimi
	std::vector<Eigen::VectorXi> base_B;
	
	for (int i = 0; i<k; i++) {
		
		//chiamiamo la funzione minimal_cycle, che opera effettuando un lifting di G
		Eigen::VectorXi C_i = minimal_cycle(G,archi,vettore_S[i]);
		
		base_B.push_back(C_i);
		for (int j=i+1; j<k; j++) {
			int prod_scalare = (vettore_S[j].dot(C_i)) % 2; //facciamo il prodotto scalare tra C_i e S_j (mod 2)
			if (prod_scalare == 1) {
				// S_j = S_j (-) S_i, dove (-) è la differenza simmetrica,
				//cioè l'elemento k-esimo è XOR(S_k,P_k)
				for (int e=0; e<m; e++) {
					vettore_S[j](e) = vettore_S[j](e)^vettore_S[i](e); //usiamo ^ per xor
				}
			}
		}
	}
	return base_B;
}
	

	
	
	
template<typename T>
std::vector<int> converti(
    const Eigen::VectorXi& C_i, 
    const std::vector<unidirected_edge<T>>& archi) 
{
    //estraiamo solo gli archi che fanno parte di questo ciclo (dove c'è un 1)
    std::map<T, std::vector<T>> adiacenza;
    for (int i = 0; i < C_i.size(); i++) {
        if (C_i(i) == 1) {
            T u = archi[i].from();
            T v = archi[i].to();
            adiacenza[u].push_back(v);
            adiacenza[v].push_back(u);
        }
    }

    std::vector<int> ciclo_nodi;
    if (adiacenza.empty()) return ciclo_nodi;

    //ricostruiamo la sequenza dei nodi camminando lungo gli archi estratti
    T partenza = adiacenza.begin()->first;
    T corrente = partenza;
    T precedente = -1; //valore fittizio di sicurezza

    while (true) {
        ciclo_nodi.push_back(corrente);
        
        //ogni nodo nel ciclo ha esattamente 2 vicini: prendiamo quello da cui non veniamo
        T prossimo = adiacenza[corrente][0];
        if (prossimo == precedente && adiacenza[corrente].size() > 1) {
            prossimo = adiacenza[corrente][1];
        }
        
        //se il prossimo passo ci riporta alla partenza, finiamo
        if (prossimo == partenza) {
            break; 
        }
        
        precedente = corrente;
        corrente = prossimo;
    }

    return ciclo_nodi;
}	