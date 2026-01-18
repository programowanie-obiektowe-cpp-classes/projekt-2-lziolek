#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Data.hpp"
#include <iostream>
#include <vector>

TEST_CASE("Test formatowania daty") {
    Data d(2025, 12, 6);

    std::cout << "\n=== Formatowanie daty ===\n";
    std::cout << "ISO: " << d.formatISO() << "\n";
    std::cout << "EU : " << d.formatEU() << "\n";
    std::cout << "US : " << d.formatUS() << "\n";

    REQUIRE(d.formatISO() == "2025-12-06");
    REQUIRE(d.formatEU()  == "06.12.2025");
    REQUIRE(d.formatUS()  == "12/06/2025");
}

TEST_CASE("Test przesuwania dni") {
    Data d(2024, 2, 29);

    std::cout << "\n=== Przesuwanie dni ===\n";
    std::cout << "Start: " << d.formatEU() << "\n";

    d.przesunDni(2);
    std::cout << "+2: " << d.formatEU() << "\n";
    REQUIRE(d.formatISO() == "2024-03-02");

    d.przesunDni(-4);
    std::cout << "-4: " << d.formatEU() << "\n";
    REQUIRE(d.formatISO() == "2024-02-27");
}

TEST_CASE("Test przesuwania miesiecy") {
    Data d(2024, 2, 29);

    std::cout << "\n=== Przesuwanie miesiecy ===\n";
    std::cout << "Start: " << d.formatEU() << "\n";

    d.przesunMsc(2);
    std::cout << "+2 msc: " << d.formatEU() << "\n";
    REQUIRE(d.formatISO() == "2024-04-29");

    d.przesunMsc(-4);
    std::cout << "-4 msc: " << d.formatEU() << "\n";
    REQUIRE(d.formatISO() == "2023-12-29");
}

TEST_CASE("Test przesuwania lat") {
    Data d(2024, 2, 29);

    std::cout << "\n=== Przesuwanie lat ===\n";
    std::cout << "Start: " << d.formatEU() << "\n";

    d.przesunLata(2);
    std::cout << "+2 lata: " << d.formatEU() << "\n";
    REQUIRE(d.formatISO() == "2026-02-28");

    d.przesunLata(-4);
    std::cout << "-4 lat: " << d.formatEU() << "\n";
    REQUIRE(d.formatISO() == "2022-02-28");
}

TEST_CASE("Test dnia tygodnia") {
    Data d(2026, 1, 1);

    std::cout << "\n=== Dzien tygodnia ===\n";
    std::cout << d.formatEU() << " -> " << d.dzienTygodnia() << "\n";

    REQUIRE(d.dzienTygodnia() == "czwartek");
}

TEST_CASE("Test swiat") {
    Data sw1(2026, 1, 1);
    Data sw2(2026, 12, 25);
    Data ns(2026, 3, 15);

    std::cout << "\n=== Swieta ===\n";
    std::cout << sw1.formatEU() << " -> " << (sw1.dzienSwiateczny()? "tak":"nie") << "\n";
    std::cout << sw2.formatEU() << " -> " << (sw2.dzienSwiateczny()? "tak":"nie") << "\n";
    std::cout << ns.formatEU()  << " -> " << (ns.dzienSwiateczny()? "tak":"nie") << "\n";

    REQUIRE(sw1.dzienSwiateczny() == true);
    REQUIRE(sw2.dzienSwiateczny() == true);
    REQUIRE(ns.dzienSwiateczny()  == false);
}

TEST_CASE("Test roznicy dat") {
    Data d1(2024, 1, 1);
    Data d2(2025, 1, 15);

    std::cout << "\n=== Roznica dat ===\n";
    std::cout << d1.formatEU() << " -> " << d2.formatEU() << "\n";

    auto rdni  = d1.roznicaDni(d2);
    auto rdat  = d1.roznicaDat(d2);

    std::cout << "Dni: " << rdni << "\n";
    std::cout << "Lata: " << rdat[0]
              << " Msc: " << rdat[1]
              << " Dni: " << rdat[2] << "\n";

    REQUIRE(rdni == 380);
    REQUIRE(rdat == std::vector<int>{1,0,14});
}

TEST_CASE("Test operatora porownania") {
    Data d1(2024, 1, 1);
    Data d2(2025, 2, 15);

    std::cout << "\n=== Porownanie dat ===\n";
    std::cout << d1.formatEU() << " < " << d2.formatEU() << "\n";

    REQUIRE(d1 < d2);
    REQUIRE_FALSE(d2 < d1);
}