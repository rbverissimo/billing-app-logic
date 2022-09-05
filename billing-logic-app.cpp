#include<stdio.h>
#include<string.h>


double calculoCasa1(double energiaCasa1, double fatorCasa3){
	
	double divisaoDaConta = (energiaCasa1 / 3) + fatorCasa3; 
	
	return divisaoDaConta;
		
}

double calculoCasa2(double energiaCasa2, double fatorCasa3) {
	
	double divisaoDaConta = (energiaCasa2 / 2) + fatorCasa3;
	
	return divisaoDaConta;
	
}

double divisaoCasa3(double energiaCasa3) {
	
	double divisaoDaConta = energiaCasa3 / 5; 
	
	return divisaoDaConta; 
}


int main(){
	
	//specific case ------> broader case
	double energiaCasa1 = 249.60;
	double energiaCasa2 = 213.37;
	double energiaCasa3 = 64.32; 
	
	double c1, c2, fatorCasa3;
	
	fatorCasa3 = divisaoCasa3(energiaCasa3); 
	c1 = calculoCasa1(energiaCasa1, fatorCasa3);
	c2 = calculoCasa2(energiaCasa2, fatorCasa3);
	
	printf("O cálculo da Casa 1: %.2f\n\n\n", c1);
	printf("O cálculo da Casa 2: %.2f\n\n\n", c2);
	
	
	
	return 0; 
}


