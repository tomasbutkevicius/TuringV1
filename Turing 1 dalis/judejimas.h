using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
void print(int i, string zymejimas, string juosta, string failas, int pozicija) {
	system("cls");
	cout << "Failas:" << failas << endl;
	//cout << "pozicija: " << pozicija << " " << juosta[pozicija] << endl;
	//cout << "komanda: " << i << endl;
	cout << juosta << endl;
	cout << zymejimas << endl;
	//sleep_for(0.05s);
}
void judejimas(char kryptis, string& juosta, string& zymejimas, long long& pozicija) {
	int back = pozicija;
	if (kryptis == 'R')
	{
		pozicija++;
		if (pozicija < 0 || pozicija >= juosta.length())
		{
			cout << "Juosta baigesi//End of tape" << endl;
			exit(0);
		}
		zymejimas[pozicija] = '^';
		zymejimas[back] = '_';
		//cout << zymejimas << endl;
	}
	else
	{
		pozicija--;
		if (pozicija < 0 || pozicija >= juosta.length())
		{
			cout << "Juosta baigesi//End of tape" << endl;
			exit(0);
		}
		zymejimas[pozicija] = '^';
		zymejimas[back] = '_';
		//cout << zymejimas << endl;
	}

}