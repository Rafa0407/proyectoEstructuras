#pragma once
#include <cstring>
#include <fstream> //fstream, ifstream,ofstream, ostream
#include <iomanip> //setw
#include <string>
#include <iostream>
#include<Windows.h>
#include"Estudiantes.h"
using namespace std;
using std::ofstream;


class RegistroEstudiantes {

private:

public:
	int cantidadEstudiantes;
	RegistroEstudiantes() {
		this->cantidadEstudiantes = 0;
	}
	~RegistroEstudiantes() {
	}

	// FUNCIONES PARA EL REGISTRO DE ESTUDIANTES
	int obtenerHash(int numeroCedula) { // funcion que retorna el hash de cedula 
		return numeroCedula % 99;
	}
	//Estudiantes buscarEstudiante(int cedulaValidar) { // busca el estudiante en el archivo por medio de la cedula
	//	Estudiantes estudiante = Estudiantes();
	//	fstream regCon("Estudiante.txt", ios::in | ios::out);
	//	if (!regCon) {
	//		cerr << "No se pudo abrir el archivo" << endl;
	//		exit(1);
	//	}
	//	else {
	//		int hash = obtenerHash(cedulaValidar); // llamada a hash
	//		regCon.seekg(hash * sizeof(Estudiantes));
	//		regCon.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiantes));
	//	}
	//	cout << "encontrado" << estudiante.cedula << endl;
	//	return estudiante;
	//}


	Estudiantes ingresarDatos() { // metodo individual para ingresar los datos.. 
		int cedula;
		string nombre = "";
		string carrera = "";
		cout << "\n Digite Cedula" << endl;
		cin >> cedula;
		cin.ignore();
		cout << "\n Digite el nombre: " << endl;
		getline(cin, nombre);
		cout << "\n Digite la carrera" << endl;
		cin >> carrera;
		Estudiantes est = Estudiantes(cedula, nombre, carrera);
		return est;
	}

	void ingresar(Estudiantes &estudiante) { //recibe un estudiante y lo ingresa al archivo
		system("cls");
		Estudiantes estudianteBuscar;
		fstream regCon("Estudiante.txt", ios::in | ios::out);
		fstream regEnt("Estudiante.txt", ios::in | ios::out);
		//ofstream regw("Estudiante.txt", ios::app);
		if (!regCon) {
			cout << "No se pudo abrir el archivo" << endl;
			system("pause");
			exit(1);
		}
		else { // valida primero si el estudiante que viene por parametro ya esta registrado
			int hash = obtenerHash(estudiante.cedula);
			regEnt.seekg(hash * sizeof(Estudiantes));
			regEnt.read(reinterpret_cast<char *>(&estudianteBuscar), sizeof(Estudiantes));
			// cout << "Cedula" << est.cedula << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			if (estudianteBuscar.cedula != 0) { // muestra el estudiante si esta registrado
				cout << "Este estudiante ya esta registrado!!" << endl;
				cout << "\n\n\t\t\t" << left << setw(12) << "Nombre " << setw(10) << "Carrera \n" << endl;
				imprimirLinea(cout, estudianteBuscar);
				cout << "-----------------------------------------------------------------------" << endl;
			}
			else { // lo registrado sino esta!! 
				
				cout << "Proceda al registro" << endl;
				int hash = obtenerHash(estudiante.cedula);
				regCon.seekp(hash * sizeof(Estudiantes));
				regCon.write(reinterpret_cast <const char *>(&estudiante), sizeof(Estudiantes));
				regCon.close();
				this->cantidadEstudiantes++;
				Sleep(800);
				cout << "Registro Completo!" << endl;
			}

		}

	}

	void imprimirLinea(ostream &salida, Estudiantes &estudiante) {
		salida << "\t\t\t" << left << setw(12) << estudiante.nombre << setw(17) << estudiante.carrera << "\n" << endl;
	}
	void mostrar() {
		system("cls");
		cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*" << endl;
		cout << "\t\t\tESTUDIANTES REGISTRADOS" << endl;
		cout << "_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*" << endl;
		Estudiantes est = Estudiantes();
		ifstream reg("Estudiante.txt", ios::in);
		if (!reg) { // comprobacion del archivo
			cout << "No se pudo abrir el archivo" << endl;
			system("pause");
			exit(1);
		}
		cout << "\n\n\t\t\t" << left << setw(12) << "Nombre " << setw(10) << "Carrera \n" << endl;
		//reg.seekg(0);
		reg.read(reinterpret_cast<char *>(&est), sizeof(Estudiantes));
		cout << "-------------------------------------------------------------------------------" << endl;
		while (reg && !reg.eof()) {
			if (est.cedula != 0) {
				imprimirLinea(cout, est);
				cout << "-----------------------------------------------------------------------" << endl;
			}
			reg.read(reinterpret_cast<char*>(&est), sizeof(Estudiantes));
		}
		reg.close();
	}

	void consultar(int cedula) {
		fstream regEnt("Estudiante.txt", ios::in | ios::out);
		Estudiantes est;
		if (!regEnt) {
			cerr << "No se pudo abrir el archivo." << endl;
			system("pause");
			exit(1);
		}

		else {
			int hash = obtenerHash(cedula);
			regEnt.seekg(hash * sizeof(Estudiantes));
			regEnt.read(reinterpret_cast<char *>(&est), sizeof(Estudiantes));
			// cout << "Cedula" << est.cedula << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			if (est.cedula != 0) {
				cout << "\n\n\t\t\t" << left << setw(12) << "Nombre " << setw(10) << "Carrera \n" << endl;
				imprimirLinea(cout, est);
				cout << "-----------------------------------------------------------------------" << endl;
			}
			else {
				cout << "El registro no se encuentra" << endl;
			}
			regEnt.close();
		}
	}


}; // end of class

