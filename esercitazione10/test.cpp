#include <iostream>
#include <iomanip>
#include <Eigen/Dense> 
#include <Eigen/SVD>
#include "gradiente_coniugato.hpp"

double condA(const Eigen::MatrixXd& A) //funzione per calcolare il condizionamento della matrice, come visto a lezione
{
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
  Eigen::VectorXd singularValuesA = svd.singularValues();
  return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}

int main(void) {
	const double tol = 1.0e-12; 
	
	std::cout << std::scientific;
	std::cout << std::setw(6) << "Dim (n)"
		      << std::setw(15) << "Cond(A)"
			  << std::setw(15) << "Res rel" 
              << std::setw(15) << "Err rel" << std::endl;			  


	for (int n = 2; n <= 50; n += 2) { //ciclo sulle dimensioni della matrice da 2 a 50 con passo 2
		Eigen::MatrixXd B = Eigen::MatrixXd::Random(n,n); //genero una matrice casuale di dimensione name
		
		if (std::abs(B.determinant()) < tol) { //se il determinante è troppo vicino a 0, salto questa dimensione
			continue;
		}
		
		//costruisco la matrice A simmetrica e definita positiva
		Eigen::MatrixXd A = B.transpose() * B;
		
		//soluzione esatta di riferimento (vettore unitario di dimensione n)
		Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);
		
		//calcolo il termine noto: b=A*x_ex	
		Eigen::VectorXd b = A * x_ex;
		
		//uso il metodo del gradiente coniugato implementato
		Eigen::VectorXd x = gradiente_coniugato(A, b, tol);
		
		//calcolo il residuo
		Eigen::VectorXd res_finale = b - A*x;
		Eigen::VectorXd x_zero = Eigen::VectorXd::Zero(n);
		Eigen::VectorXd res_iniziale = b - A * x_zero;
		double res_relativo = res_finale.norm() / res_iniziale.norm();
		
		//calcolo l'errore relativo
		double err_rel;
		if (x_ex.norm() == 0.0) {
			err_rel=(x-x_ex).norm(); //calcoliamo praticamente l'errore assoluto
		}
		else {
			err_rel=(x - x_ex).norm() / x_ex.norm();
		}
		
		std::cout << std::setw(6) << n 
              << std::setw(15) << std::setprecision(2) << condA(A) 
              << std::setw(15) << std::setprecision(4) << res_relativo 
              << std::setw(15) << std::setprecision(4) << err_rel << std::endl;
  }

  return 0;
}
		
		