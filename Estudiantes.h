#pragma once
#include <cstring>
#include <iomanip>
#include <string>
#include <iostream>
using namespace std;


class Estudiantes {
public:
	int cedula;  // formato -> #0###0###
	char nombre[15];
	char carrera[35];

	Estudiantes(int cedula = 0, string nombre = " ", string carrera = " ") {
		setCedula(cedula);
		setNombre(nombre);
		setCarrera(carrera);
	}
	~Estudiantes() {
	}
	void setCedula(int cedula) {
		this->cedula = cedula;
	}
	// setters y getters de miembros de datos 
	void setNombre(string nombre) {
		const char *pNombre = nombre.data();
		int tam = nombre.size();
		tam = (tam < 15 ? tam : 14); // operador ternario, ahorro de lineas de codigo, similar a el if else
		strncpy_s(this->nombre, pNombre, tam);
		this->nombre[tam] = '\0';
	}
	void setCarrera(string carrera) {
		const char *pCarrera = carrera.data();
		int tam = carrera.size();
		tam = (tam < 35 ? tam : 34);// operador ternario, ahorro de lineas de codigo, similar a el if else
		strncpy_s(this->carrera, pCarrera, tam);
		this->carrera[tam] = '\0';
	}
};
