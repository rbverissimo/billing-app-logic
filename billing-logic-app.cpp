#include<stdio.h>
#include<string.h>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<iostream>
#include<ctime>
#include<string>
//Esse é um script para cálculo rápido das contas de água e luz de um imóvel hipotético; 
//Esse projeto é apenas experimental, é um protótipo e uma maneira de refinar minhas habilidades em C++;


class UserValidator {
	private:
		const std::string password = "p2@r74";
	public:
		bool validarUsuario(const std::string& input){
			if(input == password){
				return true;
			} else {
				std::cout << "Senha invalida. Acesso negado" << std::endl;
				return false;
			}
		}
};

std::string getDataAtual() {
	time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

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

void boasVindas() {
	
	std::string dataHoje = getDataAtual();
	
	std::cout << "Bem-vindo ao app de calculo das contas da Alameda P2!" << std::endl;
	std::cout << "Data de hoje: " <<  dataHoje << std::endl;
	
}

bool validarAcesso() {
	
	UserValidator validator;
	std::string inputSenha;
	
	std::cout << "Digite a senha para continuar: ";
	std::cin >> inputSenha;
	
	return validator.validarUsuario(inputSenha);
}

void declararMesReferencia(){
	
	std::ofstream mesReferenciaArquivo("mes.txt", std::ios::out);
	
	if(mesReferenciaArquivo.is_open()){
		
		std::string nomeMesAno;
		
		std::cout << "Insira o mes separado pelo ano (Exemplo: Outubro 2023): " << std::endl;
		// std::cin.ignore(); //ignore a newline character no começo do input
		
		std::getline(std::cin, nomeMesAno); //std::getLine faz com que a linha toda seja salva
		
		mesReferenciaArquivo << nomeMesAno << std::endl;
		
		mesReferenciaArquivo.close();
	} else {
		std::cerr << "Erro ao abrir mes.txt. Confira se existe o arquivo na pasta. " << std::endl;
		
		std::string dataErro = getDataAtual();
		
		std::ofstream log("log.txt", std::ios::app);
		log << "Erro ao abrir mes.txt em: " << dataErro << std::endl;
		
		log.close();
	}	
	
} 

int main(){
	
		//specific case ------> broader case
		//create a component that opens a file containing information for the energiaCasa and contaAgua variables, store in a vector
		//then retrieve each and store in the variable
	
	boasVindas();
	bool acesso = validarAcesso();
	
	if(acesso){
		std::cout << "Acesso garantido" << std::endl;
	} else {
		return 0;
	}
	
	declararMesReferencia();
	
	// abrindo os arquivos que serão lidos
	std::ifstream mesReferencia("mes.txt", std::ios::in);
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
	
	FILE* ptr;
	char mes[50];
	ptr = fopen("mes.txt", "r");
	
	if(ptr == NULL){
		std::cerr << "O arquivo nao pode ser aberto\n";
	}
	
	if(fgets(mes, 50, ptr) != NULL){
		puts(mes);
	}
	
	fclose(ptr);
	
	
	//criando os inquilinos e aplicando a lógica do script; 
	
	std::ofstream fagmar(".\\tenants\\agmar.txt", std::ios::app);
	
	if(!fagmar.is_open()){
		std::cerr << "Aconteceu um erro ao acessar o arquivo de Agmar \n";
		exit(1);
	}
		
	Tenant agmar; 
	agmar.aluguel = 330.0;
	agmar.fatorCorretivo = 0.85;
	agmar.contaEnergia = calculoEnergiaCasa1(energiaCasa1, fatorCasa3, agmar.fatorCorretivo);
	agmar.contaAgua = calculoAgua(contaAgua, agmar.fatorCorretivo);
	
	double total = agmar.aluguel + agmar.contaEnergia + agmar.contaAgua;
	
	//this section of code will be append the string into each of the files 
	fagmar << mes << std::endl;
	fagmar << "Aluguel: ";
	fagmar << agmar.aluguel << std::endl;
	fagmar << "Luz: ";
	fagmar << agmar.contaEnergia << std::endl;
	fagmar << "Agua: ";
	fagmar << agmar.contaAgua << std::endl;
	fagmar << "Total: ";
	fagmar << total << std::endl;
	fagmar << "\n\n";
	
	
	std::ofstream fbranca(".\\tenants\\branca.txt", std::ios::app);
	
	if(!fbranca.is_open()){
		std::cerr << "Aconteceu um erro ao acessar o arquivo de Branca \n";
		exit(1);
	}

	
	Tenant branca;
	branca.aluguel = 550.0;
	branca.fatorCorretivo = 0.9;
	branca.contaEnergia = calculoEnergiaCasa2(energiaCasa2, fatorCasa3, branca.fatorCorretivo);
	branca.contaAgua = calculoAgua(contaAgua, branca.fatorCorretivo);
	
	total = branca.aluguel + branca.contaEnergia + branca.contaAgua;
	
	fbranca << mes << std::endl;
	fbranca << "Aluguel: ";
	fbranca << branca.aluguel << std::endl;
	fbranca << "Luz: ";
	fbranca << branca.contaEnergia << std::endl;
	fbranca << "Agua: ";
	fbranca << branca.contaAgua << std::endl;
	fbranca << "Total: ";
	fbranca << total << std::endl;
	fbranca << "\n\n";
	
	
//	std::ofstream fdanila(".\\tenants\\danila.txt", std::ios::app);
//	
//	if(!fdanila.is_open()){
//		std::cerr << "Aconteceu um erro ao acessar o arquivo de Danila \n";
//		exit(1);
//	}
//	
//	
//	Tenant danila;
//	danila.aluguel = 500.0;
//	danila.fatorCorretivo = 1.20;
//	danila.contaEnergia = calculoEnergiaCasa2(energiaCasa2, fatorCasa3, danila.fatorCorretivo);
//	danila.contaAgua = calculoAgua(contaAgua, danila.fatorCorretivo);
//	
//	total = danila.aluguel + danila.contaEnergia + danila.contaAgua;
//	
//	fdanila << mes << std::endl;
//	fdanila << "Aluguel: ";
//	fdanila << danila.aluguel << std::endl;
//	fdanila << "Luz: ";
//	fdanila << danila.contaEnergia << std::endl;
//	fdanila << "Água: ";
//	fdanila << danila.contaAgua << std::endl;
//	fdanila << "Total: ";
//	fdanila << total << std::endl;
//	fdanila << "\n\n";
	
	
//	std::ofstream felaine(".\\tenants\\elaine.txt", std::ios::app);
//	
//	if(!felaine.is_open()){
//		std::cerr << "Aconteceu um erro ao acessar o arquivo de Elaine \n";
//		exit(1);
//	}
//	
//	
//	
//	Tenant elaine;
//	elaine.aluguel = 440.0;
//	elaine.fatorCorretivo = 1;
//	elaine.contaEnergia = calculoEnergiaCasa1(energiaCasa1, fatorCasa3, elaine.fatorCorretivo);
//	elaine.contaAgua = calculoAgua(contaAgua, elaine.fatorCorretivo);
//	
//	total = elaine.aluguel + elaine.contaEnergia + elaine.contaAgua;
//	
//	felaine << mes << std::endl;
//	felaine << "Aluguel: ";
//	felaine << elaine.aluguel << std::endl;
//	felaine << "Luz: ";
//	felaine << elaine.contaEnergia << std::endl;
//	felaine << "Água: ";
//	felaine << elaine.contaAgua << std::endl;
//	felaine << "Total: ";
//	felaine << total << std::endl;
//	felaine << "\n\n";
//	
//	
	
	std::ofstream fezequias(".\\tenants\\ezequias.txt", std::ios::app);
	
	if(!fezequias.is_open()){
		std::cerr << "Aconteceu um erro ao acessar o arquivo de Ezequias \n";
		exit(1);
	}
	
	Tenant ezequias;
	ezequias.aluguel = 440.0;
	ezequias.fatorCorretivo = 0.90;
	ezequias.contaEnergia = calculoEnergiaCasa1(energiaCasa1, fatorCasa3, ezequias.fatorCorretivo);
	ezequias.contaAgua = calculoAgua(contaAgua, ezequias.fatorCorretivo);
	
	total = ezequias.aluguel + ezequias.contaEnergia + ezequias.contaAgua;
	
	fezequias << mes << std::endl;
	fezequias << "Aluguel: ";
	fezequias << ezequias.aluguel << std::endl;
	fezequias << "Luz: ";
	fezequias << ezequias.contaEnergia << std::endl;
	fezequias << "Agua: ";
	fezequias << ezequias.contaAgua << std::endl;
	fezequias << "Total: ";
	fezequias << total << std::endl;
	fezequias << "\n\n";
	
	
	
	std::ofstream figor(".\\tenants\\igor.txt", std::ios::app);
	
	if(!figor.is_open()){
		std::cerr << "Aconteceu um erro ao acessar o arquivo de Igor \n";
		exit(1);
	}
	
	
	Tenant igor;
	igor.aluguel = 600.0;
	igor.fatorCorretivo = 1.1;
	igor.contaEnergia = calculoEnergiaCasa2(energiaCasa2, fatorCasa3, igor.fatorCorretivo);
	igor.contaAgua = calculoAgua(contaAgua, igor.fatorCorretivo);
	
	total = igor.aluguel + igor.contaEnergia + igor.contaAgua;
	
	figor << mes << std::endl;
	figor << "Aluguel: ";
	figor << igor.aluguel << std::endl;
	figor << "Luz: ";
	figor << igor.contaEnergia << std::endl;
	figor << "Agua: ";
	figor << igor.contaAgua << std::endl;
	figor << "Total: ";
	figor << total << std::endl;
	figor << "\n\n";
	
	
	
	std::ofstream fpaulo(".\\tenants\\paulo.txt", std::ios::app);
	
	if(!fpaulo.is_open()){
		std::cerr << "Aconteceu um erro ao acessar o arquivo de Paulo \n";
		exit(1);
	}
	
	
	Tenant paulo;
	paulo.aluguel = 550.0;
	paulo.fatorCorretivo = 1.25;
	paulo.contaEnergia = calculoEnergiaCasa1(energiaCasa1, fatorCasa3, paulo.fatorCorretivo);
	paulo.contaAgua = calculoAgua(contaAgua, paulo.fatorCorretivo);
	
	total = paulo.aluguel + paulo.contaEnergia + paulo.contaAgua;
	
	fpaulo << mes << std::endl;
	fpaulo << "Aluguel: ";
	fpaulo << paulo.aluguel << std::endl;
	fpaulo << "Luz: ";
	fpaulo << paulo.contaEnergia << std::endl;
	fpaulo << "Agua: ";
	fpaulo << paulo.contaAgua << std::endl;
	fpaulo << "Total: ";
	fpaulo << total << std::endl;
	fpaulo << "\n\n";
	 
	
	
	return 0; 
}


