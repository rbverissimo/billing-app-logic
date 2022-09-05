#include<stdio.h>
#include<string.h>
//Esse é um script para cálculo rápido das contas de água e luz de um imóvel hipotético; 
//Esse projeto é apenas experimental, é um protótipo e uma maneira de refinar minhas habilidades em C++;


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
	double energiaCasa1;
	printf("\n\nDigite usando . o valor da energia da Casa 1: ");
	scanf("%lf", &energiaCasa1); 
	double energiaCasa2; 
	printf("\n\nDigite usando . o valor da energia da Casa 2: ");
	scanf("%lf", &energiaCasa2);
	double energiaCasa3;
	printf("\n\nDigite usando . o valor da energia da Casa 3: ");
	scanf("%lf", &energiaCasa3);
	
	double contaAgua; 
	printf("\n\nDigite usando . o valor da conta de água: ");
	scanf("%lf", &contaAgua);
	
	double fatorCasa3;
	fatorCasa3 = divisaoCasa3(energiaCasa3);
	
	
	//criando os inquilinos e aplicando a lógica do script; 
	Tenant agmar; 
	agmar.aluguel = 300.0;
	agmar.fatorCorretivo = 0.9;
	agmar.contaEnergia = calculoEnergiaCasa1(energiaCasa1, fatorCasa3, agmar.fatorCorretivo);
	agmar.contaAgua = calculoAgua(contaAgua, agmar.fatorCorretivo);
	double total = agmar.aluguel + agmar.contaEnergia + agmar.contaAgua;
	printf("O total a ser pago por Agmar sera: %.2f", total); 
	
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


