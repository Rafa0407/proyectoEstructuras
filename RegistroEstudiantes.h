#pragma once
#include <cstring>
#include <fstream> //fstream, ifstream,ofstream, ostream
#include <iomanip> //setw
#include <string>
#include <iostream>
#include<Windows.h>
#include"Estudiantes.h"
#include"Matricula.h"
using namespace std;
using std::ofstream;


class RegistroEstudiantes {

public:

	int cantidadEstudiantes;
	int cantCursosMatriculados;
	RegistroEstudiantes() {
		this->cantidadEstudiantes = 0;
		this->cantCursosMatriculados = 0;
	}
	~RegistroEstudiantes() {
	}

	int getCantidadCursosMatr() {
		return cantCursosMatriculados;
	}
	// FUNCIONES PARA EL REGISTRO DE ESTUDIANTES
	int obtenerHash(int numeroCedula) { // funcion que retorna el hash de cedula 
		return numeroCedula % 99;
	}

	void imprimiInfoEstudiante(ostream &salida, Estudiantes &estudiante) {
		salida << left << setw(12) << estudiante.cedula << setw(12) << estudiante.nombre << setw(17) << estudiante.carrera << "\n" << endl;
	}


	void imprimirInfoMatricula(ostream &salida, Matricula &matricula) {
		salida << left << setw(13) << matricula.ciclo << setw(11) << matricula.creditos << setw(10)
			<< matricula.codigoCurso << setw(25) << matricula.nombreCurso << setw(12) << matricula.grupo << setw(6)
			<< matricula.fecha << "\n" << endl;
	}

	int cantidadEstudiantesRegistrados() { // obtiene y retorna la cantidad de estudiantes registrados
		Estudiantes est = Estudiantes();
		fstream regEnt("Estudiante.txt", ios::in | ios::out);
		if (!regEnt) {
			cout << "Error al abrir el archivo" << endl;
		}
		//regEnt.seekg(0);
		regEnt.read(reinterpret_cast<char *>(&est), sizeof(Estudiantes));
		while (regEnt && !regEnt.eof()) {
			if (est.cedula != 0) {
				this->cantidadEstudiantes++;
			}
			regEnt.read(reinterpret_cast<char*>(&est), sizeof(Estudiantes));
		}
		regEnt.clear();
		return this->cantidadEstudiantes;
	}

	Estudiantes buscarEstudiante(int cedulaValidar) { // busca el estudiante en el archivo por medio de la cedula y lo retona en caso de encontrarlo
		Estudiantes estudiante = Estudiantes();
		fstream regEnt("Estudiante.txt", ios::in | ios::out);
		if (!regEnt) {
			cerr << "No se pudo abrir el archivo" << endl;
			exit(1);
		}
		else {
			int hash = obtenerHash(cedulaValidar);
			regEnt.seekg(hash * sizeof(Estudiantes));
			regEnt.read(reinterpret_cast<char *>(&estudiante), sizeof(Estudiantes));
			return estudiante;
		}
	}

	Estudiantes ingresarDatos() { // metodo  para ingresar los datos.. 
		int cedula;
		string nombre = "";
		string carrera = "";
		cout << "Digite Cedula" << endl;
		cin >> cedula;
		cin.ignore();
		cout << "Digite el nombre: " << endl;
		getline(cin, nombre);
		cout << "Digite la carrera" << endl;
		cin >> carrera;
		Estudiantes est = Estudiantes(cedula, nombre, carrera);
		return est;
	}

	void ingresar(Estudiantes &estudiante) { //recibe un estudiante y lo ingresa al archivo
		system("cls");
		cout << "Cantidad de estudiantes registrados " << cantidadEstudiantesRegistrados() << endl;
		Estudiantes estudianteBuscar;
		fstream regCon("Estudiante.txt", ios::in | ios::out);
		fstream regEnt("Estudiante.txt", ios::in | ios::out);
		if (!regCon) {
			cout << "No se pudo abrir el archivo" << endl;
			system("pause");
			exit(1);
		}
		else { // valida primero si el estudiante que viene por parametro ya esta registrado
			int hash = obtenerHash(estudiante.cedula);
			regEnt.seekg(hash * sizeof(Estudiantes));
			regEnt.read(reinterpret_cast<char *>(&estudianteBuscar), sizeof(Estudiantes));
			cout << "-----------------------------------------------------------------------" << endl;
			if (estudianteBuscar.cedula != 0) { // muestra el estudiante si esta registrado
				cout << "EL ESTUDIANTE SE ENCUENTRA EN EL SISTEMA \a" << endl;
				cout << "\n\n" << left << setw(12) << "Cedula" << setw(12) << "Nombre " << setw(10) << "Carrera \n" << endl;
				imprimiInfoEstudiante(cout, estudianteBuscar);
				cout << "-----------------------------------------------------------------------" << endl;
			}
			else { // Sino esta registrado, procede hacerlo!  
				if (cantidadEstudiantesRegistrados() <= 10) {
					cout << "Proceda al registro" << endl;
					int hash = obtenerHash(estudiante.cedula);
					regCon.seekp(hash * sizeof(Estudiantes));
					regCon.write(reinterpret_cast <const char *>(&estudiante), sizeof(Estudiantes));
					regCon.close();
					this->cantidadEstudiantes++;
					Sleep(500);
					cout << "Registro Completo!" << endl;
				}
				else {
					cout << "HA LLEGADO A LA CAPACIDAD MAXIMA DE REGISTRO \a" << endl;
				}
			}


		}

	}

	void MostrarCursosPorEstudiante(int cedula) {
		int cantCreditos = 0;
		int cantCursos = 0;
		Matricula matr;
		ifstream regEntMat("Matricula.txt", ios::in);
		if (!regEntMat) {
			cerr << "No se pudo abrir el archivo." << endl;
			system("pause");
			exit(1);
		}
		cout << "\t\t\t---Cursos del estudiante---" << endl;
		cout << "\n\n" << left << setw(12) << "Ciclo " << setw(10) << "Creditos " << setw(10) << "Codigo " << setw(10) <<
			setw(25) << "Nombre Curso " << setw(13) << "Grupo " << setw(15
			) << "Fecha " << endl;
		while (regEntMat >> matr.cedula >> matr.ciclo >> matr.fecha >> matr.codigoCurso >> matr.nombreCurso >> matr.grupo
			>> matr.creditos >> matr.estado) {
			if (matr.cedula == cedula) {
				imprimirInfoMatricula(cout, matr);
				cantCursos++;
				cantCreditos = cantCreditos + matr.creditos;
			}
		}
		cout << "\t\t\t° CANTIDAD DE CURSOS     " << cantCursos << "         °\t\t" << endl;
		cout << "\t\t\t° TOTAL DE CREDITOS      " << cantCreditos << "        °\t\t" << endl;
		regEntMat.clear();
		regEntMat.close();
	}

	void mostrar() {
		system("cls");
		cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*" << endl;
		cout << "\t\t\t\tESTUDIANTES REGISTRADOS" << endl;
		cout << "_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n\n\n" << endl;
		Estudiantes est = Estudiantes();
		Matricula matr;
		ifstream regEntMat("Matricula.txt", ios::in);
		ifstream reg("Estudiante.txt", ios::in);
		if (!reg && !regEntMat) {
			cout << "No se pudo abrir el archivo" << endl;
			system("pause");
			exit(1);
		}

		reg.read(reinterpret_cast<char *>(&est), sizeof(Estudiantes));
		while (reg && !reg.eof()) {
			if (est.cedula != 0) {
				cout << "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n" << endl;
				cout << "\t\t\t---Informacion de estudiante---" << endl;
				cout <<left << setw(12) << "Cedula" << setw(12) << "Nombre " << setw(10) << "Carrera" << endl;
				cout << "------------------------------------------------------------------------------\n" << endl;
				imprimiInfoEstudiante(cout, est);
				cout << "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n" << endl;
				MostrarCursosPorEstudiante(est.cedula);
				cout << "*********************************************************************************\n" << endl;
			}
			reg.read(reinterpret_cast<char*>(&est), sizeof(Estudiantes));
		}
		reg.clear();
		reg.close();
		regEntMat.clear();
		regEntMat.close();
	}

	void consultar(int cedula) { // consulta el estudiante por cedula, devuelve la informacion personal y sus cursos matriculados
		int cantCreditos = 0;
		int cantCursos = 0;
		fstream regEnt("Estudiante.txt", ios::in | ios::out);
		Estudiantes est;
		Matricula matr;
		ifstream regEntMat("Matricula.txt", ios::in);
		if (!regEnt && !regEntMat) {
			cerr << "No se pudo abrir el archivo." << endl;
			system("pause");
			exit(1);
		}
		else {
			int hash = obtenerHash(cedula);
			regEnt.seekg(hash * sizeof(Estudiantes));
			regEnt.read(reinterpret_cast<char *>(&est), sizeof(Estudiantes));
			cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*" << endl;
			cout << "\t\t\tINFORMACION DEL ESTUDIANTE" << endl;
			cout << "_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*" << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			if (est.cedula != 0) {
				cout << "\n\n" << left << setw(12) << "Cedula" << setw(12) << "Nombre " << setw(10) << "Carrera \n" << endl;
				imprimiInfoEstudiante(cout, est);
				cout << "-----------------------------------------------------------------------" << endl;
				cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*" << endl;
				cout << "\t\t\tINFORMACION DE CURSOS MATRICULADOS" << endl;
				cout << "_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*" << endl;
				cout << "\n\n" << left << setw(12) << "Ciclo " << setw(10) << "Creditos " << setw(10) << "Codigo " << setw(10) <<
					setw(25) << "Nombre Curso " << setw(12) << "Grupo " << setw(12) << "Fecha " << endl;
				while (regEntMat >> matr.cedula >> matr.ciclo >> matr.fecha >> matr.codigoCurso >> matr.nombreCurso >> matr.grupo
					>> matr.creditos >> matr.estado) {
					if (est.cedula == matr.cedula) {
						imprimirInfoMatricula(cout, matr);
						cantCursos++;
						cantCreditos = cantCreditos + matr.creditos;
					}
				}
				cout << "°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|°°|" << endl;
				cout << "\t\t\tÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ\t\t      "
					"\t\t\t\t\t\t\t\t\t\t\t RESUMEN"
					<< "\n\t\t\tÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ\t\t      " << endl;
				cout << "\t\t\t° CANTIDAD DE CURSOS=     " << cantCursos << "         °\t\t" << endl;
				cout << "\t\t\t° TOTAL DE CREDITOS=      " << cantCreditos << "        °\t\t" << endl;
				cout << "\t\t\t°\t\t\t\t    °\t\t      " << endl;
				cout << "\t\t\t°\t\tUNA\t\t    °\t\t      " << endl;
				cout << "\t\t\tÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ\t\t      " << endl;
			}
			else {
				cout << "ESTUDIANTE NO ENCONTRADO \a" << endl;
			}
			regEnt.close();
			regEntMat.close();
		}
	}
}; // end of class

