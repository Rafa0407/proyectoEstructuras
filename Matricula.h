#pragma once
class Matricula {
public:
	int cedula; //  #0###0###
	short int ciclo; // ciclo 1 o 2
	char fecha[10]; // dd/mm/aaaa
	short int codigoCurso; // ###
	char nombreCurso[15];
	short int grupo;
	short int creditos;
	short int estado; //0 para activo y 1 para error

	Matricula(int cedula = 0, short int ciclo = 0, string fecha = "", short int codigoCurso = 0, string nombreCurso = "",
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
		const char *pFecha = fecha.data();
		strncpy_s(this->fecha, pFecha, 10);
	}

	void setCodigoCurso(short int codigoCurso) {
		this->ciclo = ciclo;
	}

	void setNombreCurso(string nombreCurso) {
		const char *pNombreCurso = nombreCurso.data();
		strncpy_s(this->nombreCurso, pNombreCurso, 15);
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
