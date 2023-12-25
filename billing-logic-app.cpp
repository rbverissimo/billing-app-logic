#include<stdio.h>
#include<string.h>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<iostream>
#include<ctime>
#include<string>
#include<limits>
#include "libs/sqlite3.h"
//Esse é um script para cálculo rápido das contas de água e luz de um imóvel hipotético; 
//Esse projeto é apenas experimental, é um protótipo e uma maneira de refinar minhas habilidades em C++;


// O intuito dessa classe é a chamada do método validarUsuario() conferindo a string passada pelo usuário como certa para acesso ao app
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

/********* MÉTODOS ÚTEIS *********************/

// esse método constroi e retorna uma string formatada com o timestamp atual YYYY-mm-dd HH:mm:ss
std::string getDataAtual() {
	time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

// esse método converte qualquer array de strings em uma std::string
std::string converterCharArrayEmString(char a[]){
	
	int a_size = sizeof(&a) / sizeof(char);
	
	std::string convert; 
	int i;
	
	for(i = 0; i < a_size; i++){
		convert = convert + a[i];
	}
	
	return convert; 
}

void escreverAcaoNoLog(std::string nomeInquilino, std::string acao) {
	
	std::ofstream log;
	log.open("log.txt", std::ios::app);
	
	std::string dataAcao = getDataAtual();
	log << acao << " " << nomeInquilino << " Data: " << dataAcao << std::endl;
	
	log.close();
} 

typedef struct Tenant {
	
	std::string nome;
	double aluguel;
	double fatorCorretivo;
	double contaEnergia;
	double contaAgua;

} Tenant;

void processarContas(struct Tenant t, std::ofstream& file, char mes[], std::string mes_string){
	
	double total = t.aluguel + t.contaEnergia + t.contaAgua;
	
	// Essa é a parte do código que vai anotar as informações nos arquivos
	
	file << mes << std::endl;
	file << "Aluguel: ";
	file << t.aluguel << std::endl;
	file << "Luz: ";
	file << t.contaEnergia << std::endl;
	file << "Agua: ";
	file << t.contaAgua << std::endl;
	file << "Total: ";
	file << total << std::endl;
	file << "\n\n";
	
	std::string mensagensDoLog = "Mes: " + mes_string + " Aluguel: " + std::to_string(t.aluguel) + " Luz: " + std::to_string(t.contaEnergia) + " Agua: " 
					+ std::to_string(t.contaAgua) + " Total: " + std::to_string(total);
	
	escreverAcaoNoLog(t.nome, "Contas geradas: " + mensagensDoLog);
	
	
	
}

double calculoEnergiaCasa1(double energiaCasa1, double fatorCasa3, double fatorCorretivo){
	
	double divisaoDaConta = ((energiaCasa1 / 3) * fatorCorretivo) + fatorCasa3; 
	
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
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	return validator.validarUsuario(inputSenha);
}

void declararMesReferencia(){
	
	std::ofstream mesReferenciaArquivo("mes.txt", std::ios::out);
	
	if(mesReferenciaArquivo.is_open()){
		
		std::string nomeMesAno;
		
		std::cout << "Insira o mes separado pelo ano (Exemplo: Outubro 2023): " << std::endl;
		// std::cin.ignore(); //ignore a newline character no começo do input
		
		std::getline(std::cin, nomeMesAno); //std::getLine faz com que a linha toda seja salva
		
		if(!nomeMesAno.empty() && nomeMesAno[nomeMesAno.length() - 1] == '\n'){
			nomeMesAno.pop_back();
		}
		
		mesReferenciaArquivo << nomeMesAno;
		
		mesReferenciaArquivo.close();
	} else {
		std::cerr << "Erro ao abrir mes.txt. Confira se existe o arquivo na pasta. " << std::endl;
		
		std::string dataErro = getDataAtual();
		
		std::ofstream log("log.txt", std::ios::app);
		log << "Erro ao abrir mes.txt em: " << dataErro << std::endl;
		
		log.close();
	}	
	
}

void declararContas() {
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
		
		std::string dataErro = getDataAtual();
				
		std::ofstream log("log.txt", std::ios::app);
		log << "Erro ao abrir contas.txt em:  " << dataErro << std::endl;
		
		log.close();
	}
}


void escreverErroNoLog(std::string mensagem) {
	
	std::ofstream log;
	log.open("log.txt", std::ios::app);
	
	std::string dataErro = getDataAtual();
	log << mensagem << dataErro << std::endl;
	
	log.close();
}

void fecharArquivoLog() {
	
	std::ofstream log;
	log.open("log.txt", std::ios::app);
	
	std::string dataAcao = getDataAtual();
	log << "Aplicação executada em: " << dataAcao << std::endl;
	log << "\n";
	log.close();
}

void lerInquilinos() {
	
	sqlite3 *db;
	sqlite3_stmt *response;
	
	int rc = sqlite3_open("database/db.sqlite", &db);
	
	if(rc != SQLITE_OK) {	
		fprintf(stderr, "Não foi possível abrir o banco de dados", sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	
}

int main(){
		
		
	boasVindas();
	bool acesso = validarAcesso();
	
	if(acesso){
		std::cout << "Acesso garantido" << std::endl;
	} else {
		escreverErroNoLog("Usuário teve acesso negado em: ");
		exit(1);
	}
	
	declararMesReferencia();
	declararContas();
	
	// abrindo os arquivos que serão lidos
	std::ifstream mesReferencia("mes.txt", std::ios::in);
	std::ifstream arquivo("contas.txt", std::ios::in);
	
	std::vector<double> contas;
	
	if(!arquivo.is_open()){
		std::cerr << "Aconteceu um erro ao acessar o arquivo de contas!\n";
		escreverErroNoLog("Aconteceu um erro ao acessar o arquivo de contas ");
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
	
	std::string mes_string = converterCharArrayEmString(mes);
	
	//criando os inquilinos e aplicando a lógica do script; 
	
	std::ofstream fagmar(".\\tenants\\agmar.txt", std::ios::app);
	
	if(!fagmar.is_open()){
		std::cerr << "Aconteceu um erro ao acessar o arquivo de Agmar \n";
		exit(1);
	}
		
	Tenant agmar; 
	agmar.nome = "Agmar";
	agmar.aluguel = 330.0;
	agmar.fatorCorretivo = 0.9;
	agmar.contaEnergia = calculoEnergiaCasa1(energiaCasa1, fatorCasa3, agmar.fatorCorretivo);
	agmar.contaAgua = calculoAgua(contaAgua, agmar.fatorCorretivo);
	
	processarContas(agmar, fagmar, mes, mes_string);
	
	
	std::ofstream fbranca(".\\tenants\\branca.txt", std::ios::app);
	
	if(!fbranca.is_open()){
		std::cerr << "Aconteceu um erro ao acessar o arquivo de Branca \n";
		exit(1);
	}

	
	Tenant branca;
	branca.nome = "Branca";
	branca.aluguel = 550.0;
	branca.fatorCorretivo = 0.95;
	branca.contaEnergia = calculoEnergiaCasa2(energiaCasa2, fatorCasa3, branca.fatorCorretivo);
	branca.contaAgua = calculoAgua(contaAgua, branca.fatorCorretivo);
	
	processarContas(branca, fbranca, mes, mes_string);
	
	
	std::ofstream fezequias(".\\tenants\\ezequias.txt", std::ios::app);
	
	if(!fezequias.is_open()){
		std::cerr << "Aconteceu um erro ao acessar o arquivo de Ezequias \n";
		exit(1);
	}
	
	Tenant ezequias;
	ezequias.nome = "Ezequias";
	ezequias.aluguel = 440.0;
	ezequias.fatorCorretivo = 0.9;
	ezequias.contaEnergia = calculoEnergiaCasa1(energiaCasa1, fatorCasa3, ezequias.fatorCorretivo);
	ezequias.contaAgua = calculoAgua(contaAgua, ezequias.fatorCorretivo);
	
	processarContas(ezequias, fezequias, mes, mes_string);
	
	fezequias.close();
	
	std::ofstream figor(".\\tenants\\igor.txt", std::ios::app);
	
	if(!figor.is_open()){
		std::cerr << "Aconteceu um erro ao acessar o arquivo de Igor \n";
		exit(1);
	}
	
	Tenant igor;
	igor.nome = "Igor";
	igor.aluguel = 600.0;
	igor.fatorCorretivo = 1.05;
	igor.contaEnergia = calculoEnergiaCasa2(energiaCasa2, fatorCasa3, igor.fatorCorretivo);
	igor.contaAgua = calculoAgua(contaAgua, igor.fatorCorretivo);
	
	processarContas(igor, figor, mes, mes_string);
	
	
	std::ofstream fpaulo(".\\tenants\\paulo.txt", std::ios::app);
	
	if(!fpaulo.is_open()){
		std::cerr << "Aconteceu um erro ao acessar o arquivo de Paulo \n";
		exit(1);
	}
	
	Tenant paulo;
	paulo.nome = "Paulo";
	paulo.aluguel = 550.0;
	paulo.fatorCorretivo = 1.2;
	paulo.contaEnergia = calculoEnergiaCasa1(energiaCasa1, fatorCasa3, paulo.fatorCorretivo);
	paulo.contaAgua = calculoAgua(contaAgua, paulo.fatorCorretivo);
	
	processarContas(paulo, fpaulo, mes, mes_string);
	
	fecharArquivoLog();
	
	return 0; 
}


