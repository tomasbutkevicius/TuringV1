// 19-09-05 Turing Machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <chrono>
#include <thread>
#include <algorithm>
#include <exception>
#include <thread>
#include "judejimas.h"

using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
struct komandos {
	int pradzia_busenos = 0;
	int galas_busenos = 0;
	int busena = 0;
	char esamas_simb;
	char naujas_simb;
	char kryptis;
	string nauja_busena;
};
void struct_print(komandos eilute) {
	cout << eilute.busena << " " << eilute.esamas_simb << " " << eilute.naujas_simb << " " << eilute.kryptis << " " << eilute.nauja_busena << endl;
}

string random_file() {
	int skaicius = rand() % 4 + 1;
	string failas = to_string(skaicius) + ".txt";
	return failas;
}
int main() {
	//https://stackoverflow.com/questions/18238747/c-holding-a-number-of-threads
	srand(time(NULL));
		vector<komandos> eilute;
		string zymejimas = "";
		srand(time(NULL));
		int a(0), busenos_vieta(0), past_busena(0);
		long long i(0), pozicija(0);
		//input:
		int get_file(1);
		string juosta; //pvz 00000000000000000000000*0000
		string failas = "4.txt";
		int thread_count(0);
		//INPUT ^^^^^^ ____________________________
			cout << "Enter >0 for random file; 0 to enter your file name" << endl;
			cin >> get_file;
			if (get_file)
			{
				failas = random_file();
			}
			else
			{
				string name;
				cout << "Enter your file (1.txt)" << endl;
				cin >> name;
				failas = name;
			}
			ifstream rf(failas);
			if (rf.fail()) {
				//File does not exist code here
				cout << "File does not exist. Wait to restart." << endl;
				sleep_for(2s);
				system("cls");
				main();
			}
	
			//_______________________^kintamieji^_____________v skaitymas v______________________________//



		rf >> pozicija;
		pozicija;
		rf >> juosta;
		while (rf >> a) //Nuskaito komandas
		{
			eilute.push_back(komandos());
			rf >> eilute[i].esamas_simb >> eilute[i].naujas_simb >> eilute[i].kryptis >> eilute[i].nauja_busena;
			eilute[i].busena = a;
			i++;
		}
		for (i = 0; i < eilute.size() - 1; i++)
		{
			for (int j = i + 1; j < eilute.size(); j++)
			{
				if (eilute[i].busena > eilute[j].busena)  //surikiuoja
				{
					komandos x;
					x = eilute[i];
					eilute[i] = eilute[j];
					eilute[j] = x;

				}
			}
		}
		//----------------------------------------------------------------//
		for (i = 0; i < eilute.size(); i++)
		{
			if (eilute[i].busena != past_busena) //nustato naujos busenos eilutes pradine pozicija
			{
				eilute[i].pradzia_busenos = busenos_vieta;
			}
			if (i > 0 && past_busena == eilute[i].busena)
			{
				eilute[i].pradzia_busenos = eilute[i - 1].pradzia_busenos;
			}
			past_busena = eilute[i].busena;
			busenos_vieta++;
		}

		for (i = 0; i < eilute.size() - 1; i++)
		{
			if (eilute[i].pradzia_busenos != eilute[i + 1].pradzia_busenos)
			{
				eilute[i].galas_busenos = eilute[i + 1].pradzia_busenos - 1;
				int j = i - 1;
				while (eilute[j].galas_busenos == 0)
				{
					eilute[j].galas_busenos = eilute[i].galas_busenos;
					if (j == 0)
						break;
					j--;
				}
			}
		}
		for (i = 0; i < eilute.size(); i++)
		{
			if (eilute[i].galas_busenos == 0)
				eilute[i].galas_busenos = eilute.size() - 1;
		}
		for (i = 0; i < juosta.length(); i++)
			zymejimas += "_";
		zymejimas[pozicija] = '^';


		print(i, zymejimas, juosta, failas, pozicija);


		//_______________Vykdymas__________________________//
		i = 0;


		while (eilute[i].nauja_busena != "X")
		{
			int nauja_busena = stoi(eilute[i].nauja_busena);
			if (eilute[i].esamas_simb == juosta[pozicija]) //Kai esamas simbolis sutampa su juosteles simboliu
			{
				if (eilute[i].esamas_simb != eilute[i].naujas_simb)  //Kai esamas simbolis nesutampa su nauju
				{
					juosta[pozicija] = eilute[i].naujas_simb;
					judejimas(eilute[i].kryptis, juosta, zymejimas, pozicija);
					print(i, zymejimas, juosta, failas, pozicija);
					//struct_print(eilute[i]);
					if (eilute[i].busena != nauja_busena)    //Kai yra nauja busena
					{
						for (int j = 0; j < eilute.size(); j++)
						{
							if (eilute[j].busena == nauja_busena)
								i = eilute[j].pradzia_busenos;
						}
					}
				}

				else  //Kai esamas simbolis sutampa su nauju
				{
					judejimas(eilute[i].kryptis, juosta, zymejimas, pozicija);
					if (eilute[i].busena != nauja_busena)
					{
						for (int j = 0; j < eilute.size(); j++)
						{
							if (eilute[j].busena == nauja_busena)
								i = eilute[j].pradzia_busenos;
						}
					}
				}
			}
			else if (eilute[i].esamas_simb != juosta[pozicija]) //Kai esamas simbolis nesutampa su juosteles simboliu
			{
				if (eilute[i].galas_busenos == i)
				{
					i = eilute[i].pradzia_busenos;
				}
				else {
					i++;
					//cout << "iesko" << endl;
				}
			}
			//__________________vvv___Print___vvv________________________________________//
			print(i, zymejimas, juosta, failas, pozicija);
			//struct_print(eilute[i]);
		}
		main();
}
/*
00000000000000000000000*0000
0 0 0 R 0
0 1 1 R 0
0 * *L 1
1 0 1 R 0
1 1 0 L 1*/


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

