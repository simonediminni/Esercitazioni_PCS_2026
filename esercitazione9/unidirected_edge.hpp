#pragma once
#include <iostream>
#include <concepts>

template<typename I> requires std::integral<I>
class unidirected_edge
{
	
private:
	I from_;
	I to_;
	
public:
	
	unidirected_edge() : from_(I{0}), to_(I{0})
	{}
	unidirected_edge(const I& from, const I& to)
		: from_(from), to_(to)
	{ 
		if (from_>to_) {
			I temp = from_;
			from_=to_;
			to_=temp;
		}
	}
		
	I from() const {return from_;}
	I to() const {return to_;}

	bool operator<(const unidirected_edge& other) const {
		if (this->from_<other.from_) {
			return true; 
		}
		if (this->from_>other.from_) {
			return false; 
		}
		//rimane solo il caso from_==other.from_
		return this->to_ < other.to_;
	}
	
		
	bool operator==(const unidirected_edge& other) const {
		if (this->from_==other.from_ && this->to_==other.to_) {
			return true; 
		}
		return false;
	}
};
	
template<typename I>
std::ostream& operator<<(std::ostream& os, const unidirected_edge<I>& a)
{
	os << "(" << a.from() << "," << a.to() << ")";
	return os;
}