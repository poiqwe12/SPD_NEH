#include <iostream>
#include <fstream>
#include <algorithm>
#include<cstdlib>
#include <time.h>
#include <time.h>
#include <queue>
#define ROZMiAR 250 
using namespace std;

class Neh
{
public:
	int n;							// ilość zadań
	int m;							// ilość maszyn
	int tabP[ROZMiAR][ROZMiAR];		// tablica czasów trwania zadan
	int tabS[ROZMiAR][ROZMiAR];		// tablica czasów rozpoczęcia zadan
	int tabC[ROZMiAR][ROZMiAR];		// tablica czasów zakonczenia zadan
	int tabK[ROZMiAR];				// tablica permutacji zadań;
	int tabK1[ROZMiAR];				// tablica permutacji zadań;
	int omega[ROZMiAR];				// suma,mbvcX645wSDFGHJ12			asxdcfv 654,]\+_09;78k654321	234
	//vector<int> tabK;
	Neh();
	int Policztab();
	int PrzegladZupelny();
	void UstawienieDomysnejPermutacji();
	int AlgorytmNeh();
};
Neh::Neh()
{
	for (int j = 0; j < ROZMiAR; ++j)
	{
		tabK[j] = j;
		tabK1[j] = j;
	}
	for (int j = 0; j < ROZMiAR; ++j)
	{
		for (int i = 0; i < ROZMiAR; ++i)
		{
			tabP[i][j] = 0;		// tablica czasów trwania zadan
			tabS[i][j] = 0;		// tablica czasów rozpoczęcia zadan
			tabC[i][j] = 0;		// tablica czasów zakonczenia zadan
		}
	}
}
int Neh::PrzegladZupelny()
{
	int Cmax = INT16_MAX;
	int permutacjaOptymalna[ROZMiAR];

	do
	{
		Policztab();
		if (tabC[n - 1][m - 1] < Cmax)
		{
			cout << tabC[n - 1][m - 1] << endl;
			Cmax = tabC[n - 1][m - 1];
			for (int i = 0; i < n; ++i)
			{
				permutacjaOptymalna[i] = tabK[i];
			}
		}
	} while (next_permutation(tabK, tabK + n));

	for (int i = 0; i < n; ++i)
	{
		tabK[i] = permutacjaOptymalna[i];
	}
	Policztab();

	return Cmax;
}
int Neh::Policztab()
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if ((i == 0) && (j == 0))    // Pierwsza maszyna pierwsze zadanie
			{
				tabS[j][i] = 0;
				tabC[j][i] = tabP[tabK[j]][i];
			}
			else
			{
				if (i == 0)				 // Zadania na pierwszej maszynie ida bez przerw
				{
					tabS[j][i] = tabC[j - 1][i];
					tabC[j][i] = tabS[j][i] + tabP[tabK[j]][i];
				}
				else					// Nastepne maszyny 
				{
					if (j == 0)			// Pierwsze zadanie na kolejnych maszynach
					{
						tabS[j][i] = tabC[j][i - 1];
						tabC[j][i] = tabS[j][i] + tabP[tabK[j]][i];
					}
					else
					{
						if (tabC[j - 1][i] >= tabC[j][i - 1])
						{
							tabS[j][i] = tabC[j - 1][i];
							tabC[j][i] = tabS[j][i] + tabP[tabK[j]][i];
						}
						else
						{
							tabS[j][i] = tabC[j][i - 1];
							tabC[j][i] = tabS[j][i] + tabP[tabK[j]][i];
						}
					}
				}
			}
		}
	}
	return 1;
}

int Neh::AlgorytmNeh()
{
	int zm = 0;
	for (int i = 0; i < n; i++)
	{
		zm = 0;
		for (int j = 0; j < m; j++)
		{
			zm = zm + tabP[i][j];
		}
		omega[i] = zm;
	}
	//Sortowanie zbioru omega
	for (int i = 0; i < n; i++)
		for (int j = 1; j < n - i; j++)
			if (omega[j - 1] < omega[j])
			{
				swap(omega[j - 1], omega[j]);
				swap(tabK1[j - 1], tabK1[j]);
			}

	for (int i = 0; i < n; i++)
	{
		//cout << "O" << omega[i] << "  ";
	}
	
	int Cmax = INT16_MAX;
	int permutacjaOptymalna[ROZMiAR];
	for (int i = 0; i < n; ++i)
	{
		permutacjaOptymalna[i]=100;	
	}
	int kk = 0;
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; ++k)
		{
			tabK[k] = permutacjaOptymalna[k];		
		}
		//cout << tabK[tabK1[i]] << "   " << tabK[0]<<endl;
		
		tabK[i] = tabK1[i];
		//cout << endl;
		Policztab();
		Cmax = INT16_MAX;
		if (tabC[i][m - 1] < Cmax)
		{/*
			cout << "Permutacja optymalna: " << i << " | ";
			for (int k = 0; k <= kk; ++k)
			{
				cout << tabK[k] << "   ";
			}
			cout << "|" << tabC[i][m - 1] << endl;
			//cout << tabC[i][m - 1] << endl;
			*/
			Cmax = tabC[i][m - 1];
			for (int i = 0; i < n; ++i)
			{
				permutacjaOptymalna[i] = tabK[i];
			}
		}
		
		for (int j = i; j > 0 ; j--)
		{			
			swap(tabK[j], tabK[j - 1]);
			Policztab();
			if (tabC[i][m - 1] < Cmax)
			{
				/*cout << tabC[i][m - 1] << endl;
				cout << "Permutacja optymalna: " << i << " | ";
				for (int k = 0; k <= kk; ++k)
				{
					cout << tabK[k] << "   ";
				}
				cout << "|" << tabC[i][m - 1] << endl;
				*/
				Cmax = tabC[i][m - 1];
				for (int s = 0; s < n; ++s)
				{
					permutacjaOptymalna[s] = tabK[s];
				}
			}
			
			
		}
		++kk;
	}
	for (int k = 0; k <n; ++k)
	{
		tabK[k] = permutacjaOptymalna[k];

	}
	return 0;
}
istream & operator>> (istream &wej, Neh &zm)
{
	char a;
	wej >> a >> a >> a >> a >> a;
	wej >> zm.n >> zm.m;
	char b;
	for (int i = 0; i < zm.n; ++i)
	{
		for (int j = 0; j < zm.m; ++j)
		{
			wej >> b >> zm.tabP[i][j];
		}
	}
	return wej;
}
ostream & operator<< (ostream &wyj, Neh &zm)
{
	wyj << "--Dane Wejsciowe--" << endl;
	wyj << " n: " << zm.n << "\tm: " << zm.m << endl;
	for (int i = 0; i < zm.n; ++i)
	{
		wyj << "  ";
		for (int j = 0; j < zm.m; ++j)
		{
			wyj << zm.tabP[i][j] << "\t";
		}
		wyj << endl;
	}
	wyj << " --Macierz Momentow Rozpoczecia--" << endl;
	for (int i = 0; i < zm.n; ++i)
	{
		wyj << "  ";
		for (int j = 0; j < zm.m; ++j)
		{
			wyj << zm.tabS[i][j] << "\t";
		}
		wyj << endl;
	}
	wyj << " --Macierz Momentow Zakonczenia--" << endl;
	for (int i = 0; i < zm.n; ++i)
	{
		wyj << "  ";
		for (int j = 0; j < zm.m; ++j)
		{
			wyj << zm.tabC[i][j] << "\t";
		}
		wyj << endl;
	}
	wyj << " --Permutacja optymalna--" << endl;
	for (int i = 0; i < zm.n; ++i)
	{
		wyj << "  " << zm.tabK[i];
	}
	wyj << endl;
	return wyj;
}
bool WczytajZPliku(string nazwaPliku, Neh &F)
{
	fstream plik;
	plik.open(nazwaPliku, std::ios::in | std::ios::out);
	if (plik.good() == true)
	{
		plik >> F;
		plik.close();
		return true;
	}
	return false;
}


int main()
{
	std::cout << "Hello World!\n";
	Neh H;
	string tabNazwaPliku[] = { "ta001.txt","ta002.txt","ta003.txt","ta004.txt","ta005.txt","ta006.txt","ta007.txt","ta008.txt","ta009.txt","ta010.txt",
								"ta011.txt","ta012.txt","ta013.txt","ta014.txt","ta015.txt","ta016.txt","ta017.txt","ta018.txt","ta019.txt","ta020.txt" 
								"ta021.txt","ta022.txt","ta023.txt","ta024.txt","ta025.txt","ta026.txt","ta027.txt","ta028.txt","ta029.txt","ta030.txt", 
								"ta031.txt","ta032.txt","ta033.txt","ta034.txt","ta035.txt","ta036.txt","ta037.txt","ta038.txt","ta039.txt","ta040.txt",
								"ta041.txt","ta042.txt","ta043.txt","ta044.txt","ta045.txt","ta046.txt","ta047.txt","ta048.txt","ta049.txt","ta050.txt",
								"ta051.txt","ta052.txt","ta053.txt","ta054.txt","ta055.txt","ta056.txt","ta057.txt","ta058.txt","ta059.txt","ta060.txt",
								"ta061.txt","ta062.txt","ta063.txt","ta064.txt","ta065.txt","ta066.txt","ta067.txt","ta068.txt","ta069.txt","ta070.txt",
								"ta071.txt","ta072.txt","ta073.txt","ta074.txt","ta075.txt","ta076.txt","ta077.txt","ta078.txt","ta079.txt","ta080.txt",
								"ta081.txt","ta082.txt","ta083.txt","ta084.txt","ta085.txt","ta086.txt","ta087.txt","ta088.txt","ta089.txt","ta090.txt",
								"ta091.txt","ta092.txt","ta093.txt","ta094.txt","ta095.txt","ta096.txt","ta097.txt","ta098.txt","ta099.txt","ta100.txt",
								"ta101.txt","ta102.txt","ta103.txt","ta104.txt","ta105.txt","ta106.txt","ta107.txt","ta108.txt","ta109.txt","ta110.txt" };
	
	
	
	
	
	
	string tabNazwaPliku2[] = { "ta001.txt","ta010.txt","ta020.txt","ta030.txt","ta040.txt","ta050.txt","ta060.txt","ta070.txt","ta080.txt","ta090.txt",
								"ta100.txt","ta110.txt","ta120.txt","ta014.txt","ta015.txt","ta016.txt","ta017.txt","ta018.txt","ta019.txt","ta020.txt" };
	string tabNazwaPliku3[] = { "ta001.txt","ta011.txt","ta021.txt","ta031.txt","ta041.txt","ta051.txt","ta061.txt","ta071.txt","ta081.txt","ta091.txt",
								"ta101.txt","ta111.txt","ta120.txt","ta014.txt","ta015.txt","ta016.txt","ta017.txt","ta018.txt","ta019.txt","ta020.txt" };
	for (int i = 99; i < 110; ++i)
	{
		WczytajZPliku(tabNazwaPliku[i], H);
		clock_t start = clock();
		H.AlgorytmNeh();
		double czas = (double)(clock() - start);
		cout<< i+1 <<"  M: "<<H.m<<" N: "<<H.n<<"  Czas trwania algorytmu: " << czas << endl;
	}
}

