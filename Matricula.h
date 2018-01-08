#pragma once
#include <cstring>
#include <iomanip>
#include <string>
#include <iostream>
using namespace std;

class Matricula {

public:

	int cedula; //  #0###0###
	short int ciclo; // ciclo 1 o 2
	char fecha[11]; // dd/mm/aaaa
	short int codigoCurso; // ###
	string nombreCurso;
	short int grupo;
	short int creditos;
	short int estado; //0 para activo y 1 para error

	Matricula(int cedula = 0, short int ciclo = 0, string fecha = " ", short int codigoCurso = 0, string nombreCurso = " ",
		short int grupo = 0, short int creditos = 0, short int estado = 0) {
		setCedula(cedula);
		setCiclo(ciclo);
		setFecha(fecha);
		setCodigoCurso(codigoCurso);
		setNombreCurso(nombreCurso);
		setGrupo(grupo);
		setCreditos(creditos);
		setEstado(estado);
	}

	~Matricula() {
	}

	//METODOS SET
	void setCedula(int cedula) {
		this->cedula = cedula;
	}

	void setCiclo(short int ciclo) {
		this->ciclo = ciclo;
	}

	void setFecha(string fecha) {
		const char *pNombreCurso = fecha.data();
		int tam = fecha.size();
		strncpy_s(this->fecha, pNombreCurso, 11); // 8 por el formato de dd/mm/yy
		//this->nombreCurso[8] = '\0';
	}

	void setCodigoCurso(short int codigoCurso) {
		this->codigoCurso = codigoCurso;
	}

	void setNombreCurso(string nombreCurso) {
		this->nombreCurso = nombreCurso;
	}

	void setGrupo(short int grupo) {
		this->grupo = grupo;
	}

	void setCreditos(short int creditos) {
		this->creditos = creditos;
	}

	void setEstado(short int estado) {
		this->estado = estado;
	}
};
