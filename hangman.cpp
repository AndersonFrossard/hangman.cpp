/* mingw32-make hangman */

#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

string SECRET_WORD = "";
map<char, bool> dict_tries;
vector<char> wrong_guesses;

string stringToUpper(string s){
    string p = "";
    char ch;
    for (char l : s){
        ch = toupper(l);
        p = p + ch;
    }
    return p;
}


bool letra_existe(char chute){
	for (char letra : SECRET_WORD) {
		if (chute == letra){
			return true;
		}
	}
	return false;
}

bool nao_acertou(){
	for (char letter : SECRET_WORD){
		if (!dict_tries[letter]){
			return true;
		}
	}
	return false;

}

bool nao_enforcou(){
	return wrong_guesses.size() < 5;
}

void chuta(){
	cout << "Seu chute : ";
	char guess;
	cin >> guess;
	guess = toupper(guess);
	dict_tries[guess] = true; 
	if (letra_existe(guess)) {
		cout << "Right! Your guess is in the secret word !!" << endl;
	}
	else {
		cout << "Wrong! Secret word does not contain your guess !!" << endl;
		wrong_guesses.push_back(guess); 
	}
	cout << endl;
}

void imprime_palavra(){
	for (char letra : SECRET_WORD){
		if (dict_tries[letra]){
			cout << letra << " ";
		}
		else {
			cout << "_ ";
		}
	}
	cout << endl;
}

void imprime_erros(){
	cout << "Chutes errados : ";
	for (char letter : wrong_guesses){
		cout << letter << " ";
	}
	cout << endl;
}

void imprime_cabecalho(){
	cout << "*******************" << endl;
	cout << "** JOGO DA FORCA **" << endl;
	cout << "*******************" << endl;
}

vector<string> le_arquivo(){
	ifstream arquivo;
	int quant_palavras;
	string palavra_lida;
	vector<string> lista_de_palavras;
	arquivo.open("palavras.txt");

	if (arquivo.is_open()) {
		arquivo >> quant_palavras;
		for (int i = 0; i< quant_palavras; i++){
			arquivo >> palavra_lida;
			lista_de_palavras.push_back(palavra_lida);
		}
		arquivo.close();
		return lista_de_palavras;
	}
	else {
		cout << "Não foi possível abrir o arquivo de palavras. O programa será encerrado. " << endl;
		exit(0);
	}
}

void sorteia_palavras(){
	vector<string> lista_de_palavras = le_arquivo();
	srand(time(NULL));
	int indice_sorteado = rand() % lista_de_palavras.size();
	SECRET_WORD = lista_de_palavras[indice_sorteado];
	
}

void salva_arquivo(vector<string> nova_lista){
	ofstream arquivo;
	arquivo.open("palavras.txt");
	if (arquivo.is_open()){
		arquivo << nova_lista.size() << endl;
		for (string palavra : nova_lista){
			arquivo << palavra << endl;
		}
		arquivo.close();

	}
	else{
		cout << "Não foi possível abrir o arquivo de palavras. Encerrando o programa. " << endl;
		exit(0);
	}
}

void adiciona_palavra(){
	cout << "Digite a nova palavra a ser adicionada : ";
	string nova_palavra;
	cin >> nova_palavra;
	nova_palavra = stringToUpper(nova_palavra);

	vector<string> lista_palavras = le_arquivo();
	lista_palavras.push_back(nova_palavra);
	salva_arquivo(lista_palavras);
}

int main () {

	imprime_cabecalho();
	
	sorteia_palavras();

	while (nao_acertou() && nao_enforcou()) {
		imprime_erros();

		imprime_palavra();

		chuta();

	}

	cout << "Endgame !!" << endl;
	cout << "A palavra secreta era : " << SECRET_WORD << endl;
	if (nao_acertou()){
		cout << "Tente novamente seu bucha! " << endl;
	}
	else {
		cout << "Parabéns você acertou a palavra secreta. " << endl;
		cout << "Você deseja adicionar uma nova Palavra? (S/N)" << endl; 
		char resposta;
		cin >> resposta;
		resposta = toupper(resposta);
		if (resposta == 'S') {
			adiciona_palavra();
		}
	}


}