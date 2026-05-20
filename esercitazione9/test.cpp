#include "unidirected_edge.hpp"
#include "unidirected_graph.hpp"
#include "contenitori.hpp"
#include <iostream>

int main(void)
{	
	//costruisco un grafo su cui testare graph_visit
	unidirected_graph<int> G;
	G.add_edge(1,2); G.add_edge(1,3); G.add_edge(1,4); G.add_edge(1,6);
	G.add_edge(2,4); G.add_edge(2,5); G.add_edge(2,7);
	G.add_edge(3,6);
	G.add_edge(4,6); G.add_edge(4,7);
	G.add_edge(5,7);
	G.add_edge(6,7); G.add_edge(6,8);
	G.add_edge(7,9);
	G.add_edge(8,9);
	
	/*unidirected_graph<int> G;
	G.add_edge(1,2); G.add_edge(1,3); G.add_edge(2,3); 
	G.add_edge(3,4); G.add_edge(3,5); G.add_edge(4,5);
	G.add_edge(4,6); G.add_edge(5,6); */
	
	fifo<int> queue;
	lifo<int> stack;
	auto bfs = graph_visit(G,1,queue);
	auto dfs = graph_visit(G,1,stack);
	auto dfs_ricorsiva=recursive_dfs(G,1);
	auto dij=dijkstra(G,1);
	
	//stampo gli archi da copiare su graphviz
	//bfs
	std::cout << "bfs:\n";
	auto archi_bfs = bfs.all_edges();
	for (auto itor=archi_bfs.begin(); itor!=archi_bfs.end(); itor++) {
		const unidirected_edge<int>& arco = *itor;
		std::cout << arco.from() << " -- " << arco.to() << "\n";
	}

	//dfs
	std::cout << "\ndfs:\n";
	auto archi_dfs = dfs.all_edges();
	for (auto itor=archi_dfs.begin(); itor!=archi_dfs.end(); itor++) {
		const unidirected_edge<int>& arco = *itor;
		std::cout << arco.from() << " -- " << arco.to() << "\n";
	}
	
	//dfs ricorsiva
	std::cout << "\ndfs ricorsiva:\n";
	auto archi_dfsrecursive = dfs_ricorsiva.all_edges();
	for (auto itor=archi_dfsrecursive.begin(); itor!=archi_dfsrecursive.end(); itor++) {
		const unidirected_edge<int>& arco = *itor;
		std::cout << arco.from() << " -- " << arco.to() << "\n";
	}
    
	//dijkstra 
	std::cout << "\ndijkstra:\n";
	auto archi_dijkstra = dij.all_edges();
	for (auto itor=archi_dijkstra.begin(); itor!=archi_dijkstra.end(); itor++) {
		const unidirected_edge<int>& arco = *itor;
		std::cout << arco.from() << " -- " << arco.to() << "\n";
	}
	
}
	
	