#include <concepts>
#include "rational.hpp"


int main(void)
{
    rational<int> a(2,0); //esempio di a
    rational<int> b(-9,12); //esempio di b
    
    rational<int> c = a*b; //esempio di operazione
    
    std::cout << c.num() << " " << c.den() << "\n";
    std::cout << c << "\n";
    
	
    return 0;
}