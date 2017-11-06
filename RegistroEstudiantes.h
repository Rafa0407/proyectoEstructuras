#pragma once
#include <cstring>
#include <fstream> //fstream, ifstream,ofstream, ostream
#include <iomanip> //setw
#include <string>
#include <iostream>
#include"Estudiantes.h"
using namespace std;
using std::ofstream;


class RegistroEstudiantes {

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
	Estudiantes buscarEstudiante(int cedulaValidar) { // busca el estudiante en el archivo por medio de la cedula
		Estudiantes estudiante = Estudiantes();
		fstream regCon("Estudiante.txt", ios::in | ios::out);
		if (!regCon) {
			cerr << "No se pudo abrir el archivo" << endl;
			exit(1);
		}
		else {
			int hash = obtenerHash(cedulaValidar); // llamada a hash
			regCon.seekg(hash * sizeof(Estudiantes));
			regCon.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiantes));
		}
		cout << "encontrado" << estudiante.cedula << endl;
		return estudiante;
	}


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

	void ingresar(Estudiantes &estudiante) { //recibe una cedula para validar antes de ser ingresado al archivo
		system("cls");
		Estudiantes estudianteBuscar = Estudiantes();
		fstream regCon("Estudiante.txt", ios::in | ios::out);
		ofstream regw("Estudiante.txt", ios::app);
		if (!regCon && !regw) {
			cout << "No se pudo abrir el archivo" << endl;
			system("pause");
			exit(1);
		}
		else {

			if (cantidadEstudiantes <= 6) {
				int hash = obtenerHash(estudiante.cedula);
				cout << "cedula por busqueda" << estudianteBuscar.cedula << endl;
				cout << "cedula del estudiante ingresado" << estudiante.cedula << endl;
				if (estudianteBuscar.cedula == estudiante.cedula) {
					cout << "El estudiante ya está registrado" << estudianteBuscar.cedula << endl;
				}

				else {
					regw.seekp(hash * sizeof(Estudiantes));
					regw.write(reinterpret_cast <const char *>(&estudiante), sizeof(Estudiantes));
					regw.close();
					cantidadEstudiantes++;
					cout << "succes!" << endl;
				}
			}
			else {
				cout << "Maximo de estudiantes alcanzados" << endl;
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
		ifstream regCon("Estudiante.txt", ios::in);
		Estudiantes est = Estudiantes();
		if (!regCon) {
			cerr << "No se pudo abrir el archivo." << endl;
			system("pause");
			exit(1);
		}

		else {
			int hash = obtenerHash(cedula);
			regCon.seekg(hash * sizeof(Estudiantes));
			cout << "\n\n\t\t\t" << left << setw(12) << "Nombre " << setw(10) << "Carrera \n" << endl;
			regCon.read(reinterpret_cast<char *>(&est), sizeof(Estudiantes));
			cout << "-----------------------------------------------------------------------" << endl;
			if (est.cedula == cedula) {
				imprimirLinea(cout, est);
				cout << "-----------------------------------------------------------------------" << endl;
			}
			else {
				cout << "El registro no se encuentra" << endl;
			}
			regCon.close();
		}
	}


}; // end of class

