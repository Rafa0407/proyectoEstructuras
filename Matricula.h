#pragma once
#include <cstring>
#include <iomanip>
#include <string>
#include <iostream>
using namespace std;

class Matricula {
public:
	Matricula() {
	}
	~Matricula() {
	}

private:
	short int cedula; //  #0###0###
	short int ciclo; // ciclo 1 o 2
	char fecha[10]; // dd/mm/aaaa
	short int codigoCurso; // ###
	char nombreCurso[15];
	short int grupo;
	short int creditos;
	short int estado; // 0 o 1
};
