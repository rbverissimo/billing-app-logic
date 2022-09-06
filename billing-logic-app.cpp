#include<stdio.h>
#include<string.h>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<iostream>
//Esse � um script para c�lculo r�pido das contas de �gua e luz de um im�vel hipot�tico; 
//Esse projeto � apenas experimental, � um prot�tipo e uma maneira de refinar minhas habilidades em C++;


typedef struct Tenant {
	
	double aluguel;
	double fatorCorretivo;
	double contaEnergia;
	double contaAgua;

} Tenant;

double calculoEnergiaCasa1(double energiaCasa1, double fatorCasa3, double fatorCorretivo){
	
	double divisaoDaConta = (energiaCasa1 / 3) + fatorCasa3; 
	
	return divisaoDaConta;
		
}

double calculoEnergiaCasa2(double energiaCasa2, double fatorCasa3, double fatorCorretivo) {
	
	double divisaoDaConta = ((energiaCasa2 / 2) * fatorCorretivo) + fatorCasa3;
	
	return divisaoDaConta;
	
}

double divisaoCasa3(double energiaCasa3) {
	
	double divisaoDaConta = energiaCasa3 / 5; 
	
	return divisaoDaConta; 
}

double calculoAgua(double contaAgua, double fatorCorretivo){
	
	double divisaoDaConta = (contaAgua / 5) * fatorCorretivo; 
	
	return divisaoDaConta;
}


int main(){
	
		//specific case ------> broader case
		//create a component that opens a file containing information for the energiaCasa and contaAgua variables, store in a vector
		//then retrieve each and store in the variable
		
	std::ifstream arquivo("contas.txt", std::ios::in);
	std::vector<double> contas;
	
	if(!arquivo.is_open()){
		std::cerr << "Aconteceu um erro ao acessar o arquivo de contas!\n";
		exit(1);
	}
	
	
	double valor = 0.0;
	while(arquivo >> valor){
		contas.push_back(valor);
	}
	
	/*for(int i = 0; i < contas.size(); ++i){
		std::cout << contas[i] << std::endl;
	} */
	
	double energiaCasa1 = contas[0];
	double energiaCasa2 = contas[1]; 
	double energiaCasa3 = contas[2];
	double contaAgua = contas[3]; 
	
	double fatorCasa3;
	fatorCasa3 = divisaoCasa3(energiaCasa3);
	
	
	//criando os inquilinos e aplicando a l�gica do script; 
	
	std::ofstream fagmar(".\\tenants\\agmar.txt", std::ios::app);
	
	if(!fagmar.is_open()){
		std::cerr << "Aconteceu um erro ao acessar o arquivo de Agmar \n";
		exit(1);
	}
		
	Tenant agmar; 
	agmar.aluguel = 300.0;
	agmar.fatorCorretivo = 0.9;
	agmar.contaEnergia = calculoEnergiaCasa1(energiaCasa1, fatorCasa3, agmar.fatorCorretivo);
	agmar.contaAgua = calculoAgua(contaAgua, agmar.fatorCorretivo);
	double total = agmar.aluguel + agmar.contaEnergia + agmar.contaAgua;
	
	
	fagmar << "Aluguel: ";
	fagmar << agmar.aluguel << std::endl;
	fagmar << "Luz: ";
	fagmar << agmar.contaEnergia << std::endl;
	fagmar << "�gua: ";
	fagmar << agmar.contaAgua << std::endl;
	fagmar << "Total: ";
	fagmar << total << std::endl;
	fagmar << "\n\n";

	
	
	Tenant branca;
	branca.aluguel = 500.0;
	branca.fatorCorretivo = 0.9;
	branca.contaEnergia = calculoEnergiaCasa2(energiaCasa2, fatorCasa3, branca.fatorCorretivo);
	branca.contaAgua = calculoAgua(contaAgua, branca.fatorCorretivo);
	
	Tenant danila;
	danila.aluguel = 500.0;
	danila.fatorCorretivo = 1.1;
	danila.contaEnergia = calculoEnergiaCasa2(energiaCasa2, fatorCasa3, danila.fatorCorretivo);
	danila.contaAgua = calculoAgua(contaAgua, danila.fatorCorretivo);
	
	Tenant elaine;
	elaine.aluguel = 400.0;
	elaine.fatorCorretivo = 1.05;
	elaine.contaEnergia = calculoEnergiaCasa1(energiaCasa1, fatorCasa3, elaine.fatorCorretivo);
	elaine.contaAgua = calculoAgua(contaAgua, elaine.fatorCorretivo);
	
	Tenant paulo;
	paulo.aluguel = 500.0;
	paulo.fatorCorretivo = 1.05;
	paulo.contaEnergia = calculoEnergiaCasa1(energiaCasa1, fatorCasa3, paulo.fatorCorretivo);
	paulo.contaAgua = calculoAgua(contaAgua, paulo.fatorCorretivo);
	 
	
	
	return 0; 
}


