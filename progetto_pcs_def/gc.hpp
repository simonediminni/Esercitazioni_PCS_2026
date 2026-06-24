#include <iostream>
//#include <Eigen/Dense>
#include <Eigen/SVD>


  Eigen::VectorXd gradiente_coniugato(const Eigen::MatrixXd& A, Eigen::VectorXd x_0, const Eigen::VectorXd& b, const double res_tol){
	Eigen::VectorXd r_0 = b - A*x_0;
	Eigen::VectorXd p_0 = r_0;
	const unsigned int it_max = 1000;
	unsigned int it = 0;
	
	while (r_0.norm()>= res_tol && it<=it_max) {
		Eigen::VectorXd Ap = A * p_0; //calcolo una volta per non appesantire
		const double alpha_k = (p_0.dot(r_0))/(p_0.dot(Ap));
		x_0 = x_0 + alpha_k*p_0;
		r_0 = b - A*x_0;
		const double beta_k = (p_0.dot(A*r_0))/(p_0.dot(Ap));
		p_0 = r_0 - beta_k*p_0;
		it++;
	}

	  return x_0;
  }

