#include<stdio.h>
#include<string.h>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<iostream>
#include<ctime>
#include<string>
#include<limits>

int main() {
	
	std::ofstream contasArquivo("contas.txt", std::ios::out);
	
	if(contasArquivo.is_open()) {
		
		std::string contaCasa1, contaCasa2, contaCasa3, contaAgua;
		
		std::cout << "Digite o valor da conta de energia da Casa 1: ";
		std::cin >> contaCasa1; 
		
		std::cout << "Digite o valor da conta de energia da Casa 2: ";
		std::cin >> contaCasa2; 
		
		std::cout << "Digite o valor da conta de energia da Casa 3: ";
		std::cin >> contaCasa3;  
		
		std::cout << "Digite o valor da conta de agua: ";
		std::cin >> contaAgua; 
		
		contasArquivo << contaCasa1 << " " << contaCasa2 << " " << contaCasa3 << " " << contaAgua;
		
		contasArquivo.close();
		
	} else {
		std::cerr << "Erro ao abrir contas.txt. Confira se o arquivo existe na pasta. " << std::endl;
				
		std::ofstream log("log.txt", std::ios::app);
		log << "Erro ao abrir contas.txt  " << std::endl;
		
		log.close();
	}
	
	
	return 0; 
}