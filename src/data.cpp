#include "Data.hpp"
#include<iostream>

Data utworzDate ()
    {
        int r, m, d;
        std::cout <<"Podaj rok, miesiac, dzien (np. 2000 11 1):";
        std::cin >> r >> m >> d;
        return Data(r,m,d);
    }