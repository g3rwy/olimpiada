#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned int uint;

#define LOGARRAY(x,l) for(uint i = 0; i < l; ++i) cout << x[i] << " ";
#define LOG(x) cout << x << "\n";

bool search_vector(vector<uint> v, uint n){
	for(uint c : v)	if(c == n) return true;
	return false;
}

bool gnomes_lying(uint g[], uint count) {
	for (uint i = 1; i < count; ++i)
	{
		if(g[i-1] == g[i]) return true;
		else if(i + 2 < count){
			for (uint j = i+2; j < count; ++j)
				if(g[i-1] == g[j]) return true;
		}
	}
	return false;
}

int main(){
	uint gnome_count = 0;
	bool impossible = false;

	cin >> gnome_count;

	uint *gnomes = new uint[gnome_count];//{3,4,2,6,3,1};//{3,4,3,4,1};

	for(uint i=0; i<gnome_count; i++)                                   
		scanf("%u", &gnomes[i]);


	// Szukamy ile czapek brakuje w opisie gnomów
	uint brakujace = 0;

	{
		vector<uint> unikalne;
		unikalne.reserve(gnome_count); // Alokuje od razu pamięć dla wektora, dzięki czemu jest szybszy ( nie musi co chwila zmieniać rozmiaru tablicy)

		for (int i = 0; i < gnome_count; ++i)
		{
			if(count(gnomes,gnomes + gnome_count,gnomes[i]) > 2){
				impossible = true;
				break;
			}

			if(!search_vector(unikalne,gnomes[i])){
				unikalne.push_back(gnomes[i]);
			}
		}
		brakujace = gnome_count - unikalne.size();
	}
	impossible |= gnomes_lying(gnomes,gnome_count);
	if(impossible || (brakujace <= 1 && gnome_count % 2 == 1)){
		LOG(0);
		return 0;
	}
	else if( brakujace <= 1 && gnome_count % 2 == 0){
		LOG(1);
		return 0;
	}

	uint possibilities = brakujace;
	for (uint i = 1; i < brakujace; i++)
	{
		possibilities *= brakujace - i;
	}

	LOG(possibilities)


	delete[] gnomes;

	return 0;
}