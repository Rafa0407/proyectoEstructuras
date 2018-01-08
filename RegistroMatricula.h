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
	RegistroMatricula() {

	}
	~RegistroMatricula() {

	}

	// METODOS PARA EL REGISTRO DE MATRICULA 
	Matricula ingresarDatosMatricula() { // metodo individual para ingresar los datos..
		RegistroEstudiantes regEst;
		Matricula mat;
		short int ciclo;
		string fecha;
		short int codigoCurso = 0;
		string nombreCurso;
		short int grupo;
		short int creditos;
		short int estado = 0; //0 para activo y 1 para error
						  //cout << "\n Digite la cedula: ";
						  //cin >> cedula;

		int cedula = 0;
		cout << "Cedula del estudiante a matricular" << endl;
		cin >> cedula;

		Estudiantes est = regEst.buscarEstudiante(cedula);
		cout << "Estudiante " << est.nombre << endl;
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
			cout << "No se puede hacer la matricula \a" << endl;
		}
		return mat;
	}

	void ingresar(Matricula &matricula) { // ingresa de manera secuencial en el archivo
		Estudiantes est;
		system("cls");
		ofstream regMatricula("Matricula.txt", ios::app); // para manipuilar matricula 
		if (!regMatricula) {
			cout << "No se pudo abrir el archivo" << endl;
			system("pause");
			exit(1);
		}
		else {
			//EN ESTA PARTE DEBE DE BUSCAR QUE EL ESTUDIANTE SE ENCUENTRE REGISTRADO, 
			//SI NO SE ENCUENTRA ENTONCES NO DEBE DE PERMITIR QUE EL REGISTRO SE HAGA
			if (matricula.cedula != 0) {
				cout << "Proceda con matricula" << endl;
				regMatricula << matricula.cedula << ' ' << matricula.ciclo << ' ' << matricula.fecha << ' ' << matricula.codigoCurso <<
					' ' << matricula.nombreCurso << ' ' << matricula.grupo << ' ' << matricula.creditos << ' ' << matricula.estado << ' ' << endl;
				regMatricula.close();
				cout << "succes!" << endl;
			}
			else {
				cout << "Ocurrio un problema \a" << endl;
			}

		}
		regMatricula.close();
	}

	void imprimirInfoMatricula(ostream &salida, Matricula &matricula) {
		salida << left << setw(13) << matricula.ciclo << setw(12) << matricula.creditos << setw(12)
			<< matricula.codigoCurso << setw(13) << matricula.nombreCurso << setw(15) << matricula.grupo << setw(13)
			<< matricula.fecha << setw(10) << "\n" << endl;
	}


	void MostrarCursosPorEstudiante(int cedula) {
		Matricula matr;
		ifstream regEntMat("Matricula.txt", ios::in);
		if (!regEntMat) {
			cerr << "No se pudo abrir el archivo." << endl;
			system("pause");
			exit(1);
		}
		cout << "Informacion de cursos" << endl;
		cout << "\n\n" << left << setw(12) << "Ciclo " << setw(10) << "Creditos " << setw(10) << "Codigo " << setw(10) <<
			setw(12) << "Nombre Curso " << setw(12) << "Grupo " << setw(10) << "Fecha " << endl;
		while (regEntMat >> matr.cedula >> matr.ciclo >> matr.fecha >> matr.codigoCurso >> matr.nombreCurso >> matr.grupo
			>> matr.creditos >> matr.estado) {
			if (matr.cedula == cedula) {
				imprimirInfoMatricula(cout, matr);
			}

		}
		regEntMat.clear();
		regEntMat.close();
	}

	void modificarMatricula() {
		system("cls");
		RegistroEstudiantes regEst;
		Estudiantes est;
		Matricula mat;
		int cedula;
		short int codigoCurso;

		ifstream regMatricula("Matricula.txt", ios::in | ios::out | ios::binary); // para manipuilar matricula
		ofstream regMatriculaTemp("MatriculaTemporal.txt", ios::out); // para manipuilar temporal

		if (!regMatricula && !regMatriculaTemp) {
			cout << "No se pudo abrir el archivo" << endl;
			system("pause");
			exit(1);
		}
		else {
			cout << "Digite la cedula del estudiante: " << endl;
			cin >> cedula;
			est = regEst.buscarEstudiante(cedula);
			regEst.consultar(est.cedula);
			// if (est.cedula != 0) { //validacion de si la consulta devolvio un resultado o no para que haga o no la modificacion
				cout << "Digite el codigo del curso a modificar: ";//
				cin >> codigoCurso;
				while (regMatricula >> mat.cedula >> mat.ciclo >> mat.fecha >> mat.codigoCurso >> mat.nombreCurso >> mat.grupo >>
					mat.creditos >> mat.estado) {
					if (mat.cedula == est.cedula && mat.codigoCurso == codigoCurso) {
						cout << "Ingrese la nueva fecha: ";
						cin >> mat.fecha;
						if (mat.estado == 0) {
							mat.estado = 1;
						}//comprueba que el estado esté en estado error o 1

						else {
							mat.estado;
						}//si no lo deja a como estaba

						//cin >> mat.estado;
						regMatriculaTemp << mat.cedula << ' ' << mat.ciclo << ' ' << mat.fecha << ' ' << mat.codigoCurso << ' '
							<< mat.nombreCurso << ' ' << mat.grupo << ' ' << mat.creditos << ' ' << mat.estado << ' ' << endl; // adding enld
					}
					else {
						regMatriculaTemp << mat.cedula << ' ' << mat.ciclo << ' ' << mat.fecha << ' ' << mat.codigoCurso << ' '
							<< mat.nombreCurso << ' ' << mat.grupo << ' ' << mat.creditos << ' ' << mat.estado << ' ' << endl;;
					}
				} // fin while
			//}
		} // fin primer else

		regMatricula.close();
		regMatricula.clear();
		if (remove("Matricula.txt") == 0) {
			cout << "Archivo Matricula.txt eliminado" << endl;
		}
		else {
			cout << "error al eliminar" << endl;
		}
		regMatriculaTemp.close();
		rename("MatriculaTemporal.txt", "Matricula.txt");
	}

	void mostrarMatriculasPendientes() {
		system("cls");
		Matricula matr;
		ifstream regEntMat("Matricula.txt", ios::in);
		if (!regEntMat) {
			cerr << "No se pudo abrir el archivo." << endl;
			system("pause");
			exit(1);
		}
		cout << "Informacion de cursos" << endl;
		cout << "\n\n" << left << setw(12) << "Ciclo " << setw(10) << "Creditos " << setw(10) << "Codigo " << setw(10) <<
			setw(12) << "Nombre Curso " << setw(12) << "Grupo " << setw(10) << "Fecha " << endl;
		while (regEntMat >> matr.cedula >> matr.ciclo >> matr.fecha >> matr.codigoCurso >> matr.nombreCurso >> matr.grupo
			>> matr.creditos >> matr.estado) {
			if (matr.cedula != 0 && matr.estado == 1) {
				imprimirInfoMatricula(cout, matr);
			}
		}
		regEntMat.clear();
		regEntMat.close();
	}





};