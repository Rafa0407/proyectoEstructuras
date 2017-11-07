#pragma once
#include <cstring>
#include <fstream> //fstream, ifstream,ofstream, ostream
#include <iomanip> //setw
#include <string>
#include <iostream>
#include<Windows.h>
#include"Matricula.h"
#include"Estudiantes.h"
#include"RegistroEstudiantes.h"

using namespace std;
using std::ofstream;

class RegistroMatricula {

public: 
	RegistroEstudiantes regEst;
	RegistroMatricula() {
		
	}
	~RegistroMatricula() {
	
	}

	// METODOS PARA EL REGISTRO DE MATRICULA 

	int obtenerHash(int numeroCedula) { // funcion que retorna el hash de cedula 
		return numeroCedula % 99;
	}

	Matricula ingresarDatosMatricula() { // metodo individual para ingresar los datos..
		Matricula mat;
		short int ciclo;
		string fecha = "";
		short int codigoCurso;
		string nombreCurso = "";
		short int grupo;
		short int creditos;
		short int estado = 0; //0 para activo y 1 para error
						  //cout << "\n Digite la cedula: ";
						  //cin >> cedula;

		int cedula = 0;
		cout << "Cedula del estudiante a matricular" << endl;
		cin >> cedula;

		Estudiantes est = regEst.buscarEstudiante(cedula);

		if (est.cedula != 0) {
			cout << "\n Digite el ciclo (1 o 2): ";
			cin >> ciclo;
			cin.ignore();
			cout << "\n Digite la fecha en formato (dd/mm/YYYY): ";
			getline(cin, fecha);
			cout << "\n Digite el codigo del curso: ";
			cin >> codigoCurso;
			cin.ignore();
			cout << "\n Digite el nombre del curso: ";
			getline(cin, nombreCurso);
			cout << "\n Digite el grupo: ";
			cin >> grupo;
			cout << "\n Digite la cantidad de creditos: ";
			cin >> creditos;
			estado = 0; //0 para activo y 1 para error
			mat = Matricula(est.cedula, ciclo, fecha, codigoCurso, nombreCurso, grupo, creditos, estado);

		}
		else {
			cout << "No se puede hacer la matricula" << endl;
		}
		return mat;
	}

	void ingresar(Matricula &matricula) {
		Estudiantes est;
		system("cls");
		fstream regMatricula("Matricula.txt", ios::in | ios::out | ios::binary); // para manipuilar matricula 
		// fstream regEstudiantes("Estudiantes.txt", ios::in | ios::out | ios::binary);
		if (!regMatricula) {
			cout << "No se pudo abrir el archivo" << endl;
			system("pause");
			exit(1);
		}
		else {
			//EN ESTA PARTE DEBE DE BUSCAR QUE EL ESTUDIANTE SE ENCUENTRE REGISTRADO, 
			//SI NO SE ENCUENTRA ENTONCES NO DEBE DE PERMITIR QUE EL REGISTRO SE HAGA
			//En este punto ya empieza a guardar
			//Estudiantes est = regEst.buscarEstudiante(matricula.cedula);
			// cout << "Si lo encontro"<< est.cedula <<endl;
			if (matricula.cedula != 0) {
				cout << "Proceda con matricula" << endl;
				int hash = obtenerHash(matricula.cedula); // XQ ESTUDIANTE???
				regMatricula.seekp(hash * sizeof(Matricula));
				regMatricula.write(reinterpret_cast < const char*>(&matricula), sizeof(Matricula));
				regMatricula.close();
				cout << "succes!" << endl;
			}
			else {
				cout << "No se puede realizar la matricula, el estudiante no existe" << endl;
			}
			
		}
	}

	void modificarMatricula() {
	}

	void mostrarMatriculasPendientes() {
	}

	


};