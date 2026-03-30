#pragma once
#include <iostream>
#include <numeric> //mi serve per calcolare il MCD

template<typename I> requires std::integral<I>
class rational
{
	
public:
	I num_;
	I den_;
	
	rational()
		: num_(I{0}), den_(I{1})
	{}
	
	rational(const I& num, const I& den)
		: num_(num), den_(den)
	{
		if (den_==0) {
			if (num_>0) num_=I{1};
			else if (num_<0) num_=I{-1};
			else num_=I{0};
		}
		else {semplifica();}
	}
	
	
	I num() const {return num_;}
	I den() const {return den_;}
	
	//Booleani per gestire Inf e NaN 
	
	bool nan() const{return num_==0 && den_==0;}
	bool inf() const{return num_!=0 && den_==0;}
	
	//Implementazione dell'incremento	
	rational& operator+=(const rational& other) {
		if (this->nan() || other.nan()) {
			num_=0; den_=0;
			return *this;
		}
		
		if (this->inf() || other.inf()) {
			if (this->inf() && other.inf() && this->num_ != other.num_) {
			num_=0; den_=0;	//se sono infiniti di segno opposto ottengo NaN
			} else {//se sono infiniti dello stesso segno ottengo Inf
				if (this->inf()) {num_=this->num_;}
				else {num_=other.num_;}
				den_=0;
			}
		return *this;
		}
		
		num_ = (num_*other.den_ + den_*other.num_);
		den_ = (den_*other.den_);
		semplifica();
		return *this;
	}
	
	//Implementazione della somma
	rational operator+(const rational& other) const {
		rational ret = *this;
		ret += other;
		return ret;
	}
	
	//Implementazione del decremento 
	rational& operator-=(const rational& other) {
		if (this->nan() || other.nan()) {
			num_=0; den_=0;
			return *this;
		}
		
		if (this->inf() || other.inf()) {
			if (this->inf() && other.inf() && this->num_ == other.num_) {
			num_=0; den_=0;	
			} else {
				if (this->inf()) {num_=this->num_;} //conservo il segno di this
				else {num_=-other.num_;}
				den_=0;
			}
		return *this;
		}
		
		num_ = (num_*other.den_ - den_*other.num_);
		den_ = (den_*other.den_);
		semplifica();
		return *this;
	}
	
	//Implementazione della differenza
	rational operator-(const rational& other) const {
		rational ret = *this;
		ret -= other;
		return ret;
	}	
	
	//Implementazione di *=
	rational operator*=(const rational& other) {
		
		if (this->nan() || other.nan()) { 
			num_=0; den_=0; //se sono entrambi nan, ottengo nan
			return *this;
		}
		
		if ((this->num_ == 0 && other.inf()) || (this->inf() && other.num_==0)) {
			num_=0; den_=0; //se ho 0*inf oppure inf*0, ottengo nan
			return *this;
		}
		
		if (this->inf() || other.inf()) {
			if ((this->num_>0 && other.num_>0) || (this->num_<0 && other.num_<0)) { //se i segni dei numeratori sono uguali ho +1, altrimenti -1
				num_=I{1};}
			else {
				num_=I{-1};}
			den_=0;
			return *this;
		}
		
		num_ = num_*other.num_;
		den_ = den_*other.den_;
		semplifica();
		return *this;
	}
	
	//Implementazione di *
	rational operator*(const rational& other) const {
		rational ret = *this;
		ret *= other;
	return ret;
	}
	
	//Implementazione di /=
	rational operator/=(const rational& other) {
		
		if (other.nan()) {
			num_=0; den_=0; //se other è nan, ottengo nan
			return *this;
		}
		
		rational inverso(other.den_,other.num_); //inverto num e den così da sfruttare *=
		
		return (*this *= inverso);
	}
		
	//Implementazione di /
	rational operator/(const rational& other) const {
		rational ret = *this;
		ret /= other;
	return ret;
	}
	
	//Semplificazione delle frazioni
	void semplifica() {
		
		if (den_==0) return; //se ho Inf o NaN non semplifico la frazione
		
		I MCD = std::gcd(num_,den_);
		num_ /= MCD;
		den_ /= MCD;
		
	//Gestisco il segno (lo porto sempre al numeratore)
	if (den_<0) {
		num_=-num_;
		den_=-den_;
		}
	}
		
};

template<typename I>
std::ostream&
operator<<(std::ostream& os, const rational<I>& a)
{	
	if (a.nan()) os << "NaN";
	else if (a.inf()) {
		if (a.num()>0) {os << "+Inf";}
		else {os << "-Inf";}
		}
	else if (a.den()==1) { 
		os << a.num(); //se ho un numero intero, stampo solo il numeratore per motivi "estetici"
	}
	else {os << a.num() << "/" << a.den();
	}
	return os;
}

