#pragma once
#include <iostream> // cerr, cin, cout, endl, ios
#include "Estudiantes.h" 
#include "RegistroEstudiantes.h" 
#include "Matricula.h" 
#include "RegistroMatricula.h"
using namespace std;

Estudiantes est = Estudiantes();
RegistroEstudiantes regEstudiantes;
Matricula matr;
RegistroMatricula regMatricula;
int main() {
	int opc, salir = 0;
	int cedula = 0;

	ifstream regEst("Estudiante.txt", ios::in);
	if (!regEst) {
		ofstream("Estudiante.txt", ios::app);
		cout << "Archivo Estudiante creado correctamente" << endl;
	}
	ifstream regMat("Matricula.txt", ios::in);
	if (!regMat) {
		ofstream("Matricula.txt", ios::app);
		cout << "Archivo Matricula creado correctamente" << endl;
	}

	ifstream regMatTmp("MatriculaTemporal.txt", ios::in);
	if (!regMatTmp) {
		ofstream("MatriculaTemporal.txt", ios::app);
	}

	while (salir == 0) {
		system("cls");
		system("color 0b");  //cambios al menu - rafa 
		cout << "ฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|ฐฐ|" << endl;
		cout << "\t\t\tอออออออออออออออออออออออออออออออออออออ\t\t      "
			"\t\t\t\t\t\t\t\t\t\t SISTEMA DE MATRICULA"
			<< "\n\t\t\tอออออออออออออออออออออออออออออออออออออ\t\t      " << endl;
		cout << "\t\t\tฐ Universidad Nacional de Costa Ricaฐ\t\t      " << endl;
		cout << "\t\t\tฐ\t\t\t\t    ฐ\t\t      " << endl;
		cout << "\t\t\tฐ\t\tUNA\t\t    ฐ\t\t      " << endl;
		cout << "\t\t\tอออออออออออออออออออออออออออออออออออออ\t\t      " << endl;
		cout << "\n\t\t\t1. CREAR ARCHIVOS" << endl;
		cout << "\n\t\t\t2. CREAR REGISTRO DE ESTUDIANTES" << endl;
		cout << "\n\t\t\t3. CREAR MATRICULA" << endl;
		cout << "\n\t\t\t4. MOSTRAR" << endl;
		cout << "\n\t\t\t5. CONSULTAR" << endl;
		cout << "\n\t\t\t6. MOSTRAR MATRICULAS PENDIENTES" << endl;
		cout << "\n\t\t\t7. MODIFICAR MATRICULA" << endl;
		cout << "\n\t\t\t8. ELIMINAR ARCHIVOS" << endl;
		cout << "\n\t\t\t9. SALIR" << endl;
		cout << "\nDigite una opcion: " << endl;

		cin >> opc;
		switch (opc)
		{
		case 1:
			//CREAR ARCHIVOS
			system("cls");
			if (!regEst) {
				ofstream("Estudiante.txt", ios::app);
				cout << "Archivo Estudiante creado correctamente" << endl;
			}
			if (!regMat) {
				ofstream("Matricula.txt", ios::app);
				cout << "Archivo Matricula creado correctamente" << endl;
			}
			system("pause");
			break;
		case 2:
			//CREAR REGISTRO DE ESTUDIANTES
			est = regEstudiantes.ingresarDatos();
			regEstudiantes.ingresar(est);
			system("pause");
			break;
		case 3:
			//CREAR MATRICULA
			system("cls");
			matr = regMatricula.ingresarDatosMatricula();
			regMatricula.ingresar(matr);
			system("pause");
			break;
		case 4:
			//MOSTRAR
			regEstudiantes.mostrar();
			system("pause");
			break;
		case 5:
			//CONSULTAR
			system("cls");
			cout << "Ingrese cedula del estudiantes a consultar" << endl;
			cin >> cedula;
			regEstudiantes.consultar(cedula);
			system("pause");
			break;
		case 6:
			//MOSTRAR MATRICULAS PENDIENTES
			regMatricula.mostrarMatriculasPendientes();
			system("pause");
			break;
		case 7:
			//MODIFICAR MATRICULA
			regMatricula.modificarMatricula();
			regMat.close();


			system("pause");
			break;
		case 8:
			//ELIMINAR ARCHIVOS
			system("cls");
			//ELIMINA ARCHIVO ESTUDIANTE.TXT
			regEst.close();
			if (remove("Estudiante.txt") == 0)
				cout << "El archivo Estudiante.txt fue eliminado correctamente" << endl;
			else
				cout << "Error al eliminar el archivo Estudiante.txt" << endl;

			//ELIMINA ARCHIVO MATRICULA.TXT
			regMat.close();
			if (remove("Matricula.txt") == 0)
				cout << "El archivo Matricula.txt fue eliminado correctamente" << endl;
			else
				cout << "Error al eliminar el archivo Matricula.txt" << endl;
			system("pause");
			break;
		case 9:
			//SALIR
			system("cls");
			cout << "\n\n\n\n\n\n\n\t\t     ELABORADPO  POR:\n" << endl; //muestra el mensaje cuando salga del programa.
			Sleep(900);
			cout << "\n\t\t\t\t   -ADALBERTO DELGADO MENDEZ\n\n";
			Sleep(900);
			cout << "\n\t\t\t\t   -RAFAEL SEQUEIRA GUTIERREZ";
			Sleep(900);
			salir = 1;
			break;
		}
	}
} // fin de main