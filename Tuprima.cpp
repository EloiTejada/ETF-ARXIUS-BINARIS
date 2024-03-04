#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>


using namespace std;
/// <summary>
/// Definim una clase Persona, que tindrà 3 variables, un char de com a mol 50 caràcters, un numero sense límit per la edat, i un altre char de 50.
/// </summary>
struct Persona {
	char nom[50];
	int age;
	char surname[50];
};

//Declarem les funcions.
void FAke_incerir(Persona& Eloi, Persona& Jaume, Persona& Quim);
void Incerir_info(string& usuari);
static void Llegir_info();
void Modify_info(string& usuari);
int Mitjana(int& suma_numeros, int& i);
int Moda(unordered_map<int, int>& conteo_numeros);
void Mediana(vector<int>& numerets);

int main() {

	int resposta;
	string usuari;
	
	//Creem usuaris amb la clase Persona, ens serveixen per fer una incerció inicial del arxiu de text.
	Persona Eloi = { "Eloi", 19, "Tejada" };
	Persona Jaume = { "Jaume", 24, "Frigola" };
	Persona Quim = { "Quim", 33, "Martinez" };

	
	//Petit menú per decidir que fer.
	cout << "Escull que fer: " << endl; //Estàn pensades per ser executades una darrera l'altra.
	cout << "Incerir dades al fitxer.(1)" << endl;
	cout << "Llegir la informació del fitxer.(2)" << endl; //Les funcions de trobar la mida, moda i mediana estàn a la funció de llegir info.
	cout << "Canviar la informació de un usuari. (3)" << endl;
	cin >> resposta;
	
	switch (resposta) {

		case 1:
			
				Incerir_info(usuari);
			break;
		case 2:
			Llegir_info();
			break;
		case 3:
			cout << "Escriu el nom de l'usuari: "; cin >> usuari;
			Modify_info(usuari);
			break;
	}
	
	

	return 0;
}
/// <summary>
/// Aquesta funció serveix per inicialitzar l'arxiu, no serveix per rés de la pràctica, simplement quan havía emplenat l'arxiu de info innecessaria i no savia com eliminar-la, simplement feia un arxiu nou i li inceria la informació bàsica amb aquesta funció.
/// </summary>
/// <param name="Eloi"></param>
/// <param name="Jaume"></param>
/// <param name="Quim"></param>
void FAke_incerir(Persona& Eloi, Persona& Jaume, Persona& Quim) {
	try { //Un try catch que atrapa les excepcions.
		fstream file("mashallah.txt", ios::in | ios::out | ios::binary); // Obrim l'arxiu, que està en binari.

		if (!file) { //Condició per si no es pot obrir l'arxiu.
			throw runtime_error("Error al obrir l'arxiu.");
		}

		file.write(reinterpret_cast<char*>(&Eloi), sizeof(Persona)); //EScribim a l'arxiu binari les clases que seleccionem, ocupant la mida exacta d'una clase Persona.
		file.write(reinterpret_cast<char*>(&Jaume), sizeof(Persona));
		file.write(reinterpret_cast<char*>(&Quim), sizeof(Persona));
		cout << "Edicio completada." << endl;

		file.close(); //Tenquem l'arxiu.
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
}
/// <summary>
/// Aquesta si que es la funció per incerir informació, busca on la informació incerida en l'arxiu acaba i n'escribeix més.
/// </summary>
/// <param name="usuari">Aquesta clase Persona de nom "usuari" ens serveix per incerir cualsevol Persona sense haver de declarar-la, si no incerint-la durant la execució del codi</param>
static void Incerir_info(string& usuari) {
	try {
		fstream file("mashallah.txt", ios::binary | ios::app | ios::in | ios::out);

		if (!file.is_open()) {
			throw runtime_error("Error al obrir l'arxiu.");
		}

		int resposta;
		Persona personaNova;

			cout << "Escriu el nom: ";
			cin >> personaNova.nom;

			cout << "Escriu la edat: ";
			cin >> personaNova.age;

			cout << "Escriu el cognom: ";
			cin >> personaNova.surname;

			file.seekg(0, ios::end); // Busca el final de l'arxiu.
			file.write(reinterpret_cast<const char*>(&personaNova), sizeof(Persona));

			if (!file.good()) {
				throw runtime_error("Error d'escriptura en el fitxer.");
			}
			file.close();
		
		
	} catch (const exception& e) {
		cout << e.what() << endl;
	}
}

/// <summary>
/// Obre l'arxiu, llegeix la infromació d'ell i la mostra enumeradament a l'usuari, també fa operacions de trobar la mitjana, moda i mediana de la edat dels objectes de clase persona.
/// </summary>
static void Llegir_info() {
	try {

		vector<int> numerets; // Declarem un vector per amagatzemar les edats de les persones i poder realitzar operacions.
		unordered_map<int, int> conteo_numeros; //Fem un mapa per anar contant les vegades que es repeteix un numero.
		int Numeros;
		int suma_numeros = 0;
		int nombre_num = 0;
		Persona persona;
		ifstream file("mashallah.txt", ios::binary);
		int i = 0;

		if (!file.is_open()) {
			throw runtime_error("Error al obrir l'arxiu.");
		}

		while (file.read(reinterpret_cast<char*>(&persona), sizeof(Persona))) {
			i++;
			cout << "Usuari " << i << ": " << endl;
			cout << "Nom: " << persona.nom << ", Cognom: " << persona.surname << ", Edat: " << persona.age << endl;
			numerets.push_back(persona.age);
			conteo_numeros[persona.age]++;
			suma_numeros += persona.age;
		}

		if (file.eof()) {
			cout << "Final del fitxer." << endl;
		}
		else if (file.fail()) {
			cout << "Error de lectura del fitxer." << endl;
		}

		Mitjana(suma_numeros, i);
		Moda(conteo_numeros);
		Mediana(numerets);
		file.close();
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
}
/// <summary>
/// Modifiquem la informació de cualsevol Persona que volguem, només hem de especificar el nom, i el programa busca la persona que coincideixi amb aquest.
/// </summary>
/// <param name="usuari"></param>
void Modify_info(string& usuari) {
	try {
	fstream file("mashallah.txt", ios::in | ios::out | ios::binary);

	if (!file) {
		cout << "Error al obrir l'arxiu." << endl;
		return;
	}

	Persona persona;
	bool found = false;

	while (file.read(reinterpret_cast<char*>(&persona), sizeof(Persona))) {
		if (persona.nom == usuari) { //Si l'usuari incerit existeix:
			found = true;

			cout << "Escriu el nou nom: "; cin >> persona.nom;
			cout << "Escriu la nova edat: "; cin >> persona.age;
			cout << "Escriu el nou cognom: "; cin >> persona.surname;

			file.seekp(-static_cast<int>(sizeof(Persona)), ios::cur);
			file.write(reinterpret_cast<char*>(&persona), sizeof(Persona));
			cout << "Edicio completada" << endl;
			break;
		}
	}
	if (!found) { //Si no eisteix:
		cout << "Persona no trobada." << endl;
	}
	file.close();
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}

}
/// <summary>
/// Calcula la mitjana, amb la suma de tots els numeros, dividit pel nombre d'aquests.
/// </summary>
/// <param name="suma_numeros"></param>
/// <param name="i"></param>
/// <returns></returns>
int Mitjana(int& suma_numeros, int& i) {
	try {
		if (i == 0) {
			throw runtime_error("No es pot dividir per zero.");
		}
		int mitjana = suma_numeros / i;
		cout << "La mitjana es: " << mitjana << endl;
		return mitjana;
	}
	catch (const exception& e) {
		cout << e.what() << endl;
		return 0;
	}
}

/// <summary>
/// Busca en el mapa el numero que més vegades es repeteixi.
/// </summary>
/// <param name="conteo_numeros"></param>
/// <returns></returns>
int Moda(unordered_map<int, int>& conteo_numeros) {

	int moda = 1;
	int frecuencia_maxima = 0;

	for (const auto& par : conteo_numeros) {

		if (par.second > frecuencia_maxima) {
			moda = par.first;
			frecuencia_maxima = par.second;
		}
	}
	cout << "La moda es: " << moda << endl;
	return moda;
}
/// <summary>
/// Troba el numero situat a la meitat entre el més petit i el més gros.
/// </summary>
/// <param name="numerets"></param>
void Mediana(vector<int>& numerets) {
	
	sort(numerets.begin(), numerets.end());

	double mediana;

	size_t n = numerets.size();

	if (n % 2 == 0) { // Si el residuu es 0:
		
		mediana = (numerets[n / 2 - 1] + numerets[n / 2]) / 2.0;
	}
	else { // Si no ho es:
		
		mediana = numerets[n / 2];
	}
	cout << "La mediana es: " << mediana << endl;
}