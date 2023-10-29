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
		
		std::string conta;
		
		std::cout << "Digite o valor da conta de energia da Casa 1: " << std::endl;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		std::cin >> conta; 
		
		std::cout << "Digite o valor da conta de energia da Casa 2: " << std::endl;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		std::cin >> conta; 
		
		std::cout << "Digite o valor da conta de energia da Casa 3: " << std::endl;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		std::cin >> conta;  
		
		std::cout << "Digite o valor da conta de agua: " << std::endl;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		std::cin >> conta; 
		
		contasArquivo.close();
		
	} else {
		std::cerr << "Erro ao abrir contas.txt. Confira se o arquivo existe na pasta. " << std::endl;
				
		std::ofstream log("log.txt", std::ios::app);
		log << "Erro ao abrir contas.txt  " << std::endl;
		
		log.close();
	}
	
	
	return 0; 
}