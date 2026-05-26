#pragma once
#include <iostream>
#include <Eigen/Dense> 

Eigen::VectorXd gradiente_coniugato(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, double tol) {
	Eigen::VectorXd x0 = Eigen::VectorXd::Zero(b.size());
	
	Eigen::VectorXd r0 = b - A*x0;
	Eigen::VectorXd p0 = r0;
	
	while (r0.norm() >= tol) {
		Eigen::VectorXd A_p0 = A * p0;
		double alfa = p0.dot(r0)/p0.dot(A_p0);
		
		x0 += alfa*p0; //aggiorno la soluzione
		r0 = b - A*x0; //aggiorno il residuo 
		
		if (r0.norm() < tol) {
			break; //se il nuovo residuo è gia minore di tol, esco dal ciclo 
		}          //così da evitare di dividere per 0
		
		double beta = (p0.dot(A*r0))/(p0.dot(A_p0));
		p0 = r0-beta*p0;
	}
	return x0;
}
		
