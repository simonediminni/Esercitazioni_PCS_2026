# include <iostream>

int main()
{
double ad[4] = {0.0, 1.1, 2.2, 3.3};
float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
int ai[3] = {0, 1, 2};

int x = 1;
float y = 1.1;

std::cout << "Indirizzo di x: " << &x << "\n";
std::cout << "Indirizzo di y: " << &y << "\n";

(&y)[1] = 0;

std::cout << "Il valore di x dopo l'operazione è: " << x << "\n";


std::cout << "Stampo gli indirizzi di alcuni elementi degli array\n";
std::cout << "ad[2]: " << &ad[2] << "\n";
std::cout << "af[5]: " << &af[5] << "\n";
std::cout << "ai[1]: " << &ai[1] << "\n";

return 0;
}
