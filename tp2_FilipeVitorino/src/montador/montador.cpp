#include "montador.h"

//Construor da classe
Montador::Montador(std::vector<std::vector<std::string>> comandos_entrada){
    this->comandos_entrada = comandos_entrada;
    this->is_main = false;
}


//proocura a main 
void Montador::check_main(){
    unsigned int i;
    //int pc = 0;
    for (i = 0; i < this->comandos_entrada.size(); i++){
        if(this->comandos_entrada[i][0].back() == ':'){
            std::string cnst = this->comandos_entrada[i][0];
            cnst.pop_back();
            if (cnst == "main"){
                this->is_main = true;
            }

        }
    }
}

//remove codigo solto fora do escopo da funcao
void Montador::remove_outside_code(){
    bool inside = false;
    std::vector<int> indices;
    unsigned int i;
    //int pc = 0;
    for (i = 0; i < this->comandos_entrada.size(); i++){
        if(this->comandos_entrada[i][0].back() == ':'){
            
            if(this->comandos_entrada[i][1] != "WORD"){
                inside = true;
            }

        }else if(inside == false){
            indices.push_back(i);
        }else if(this->comandos_entrada[i][0] == "RET"){
            inside = false;
        }
    }
    int k = 0;
    for (i = 0; i < indices.size(); i++){
        this->comandos_entrada.erase(this->comandos_entrada.begin() + indices[i] - k );
        k++;
    }
}


void Montador::remove_end(){
    unsigned int i;
    //int pc = 0;
    for (i = 0; i < this->comandos_entrada.size(); i++){
        if(this->comandos_entrada[i][0] == "END"){
            this->comandos_entrada.erase(comandos_entrada.begin() + i);
            break;

        }
    }
}

//funcao de debug
//imprime toda a matriz de comando
void Montador::imprime(){
    
    unsigned int i;
    unsigned int j;
    std::cout << this->is_main << "\n";
    for (i = 0; i < this->comandos_entrada.size(); i++){
        for  (j = 0 ; j < this->comandos_entrada[i].size(); j++ ){
            std::cout << this->comandos_entrada[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

/*

//Funcao principal do programa 
//Traduz a string de operacao/comando em seu valor em int
//labels WORD e END nao possuem valor em inteiro
void Montador::traducao(){

    int op;
    unsigned int i;
    unsigned int j;
    for (i = 0; i < this->comandos_entrada.size(); i++){
        for  (j = 0 ; j < this->comandos_entrada[i].size(); j++ ){
       
            if(this->comandos_entrada[i][j] != "WORD" && this->comandos_entrada[i][j] != "END" && this->comandos_entrada[i][j].back() != ':' ){
                op = check_instrucao(this->comandos_entrada[i][j]);
                this->comandos_saida.push_back(op);
               
            }
        }
    }

    this->total_comandos_saida = this->comandos_saida.size();
}

//Funcao auziliar para funcao traducao
//nessa funcao verfica se a string representa um inteiro
//usado para as constantes e saltos de memoria
bool Montador::check_int(std::string s){
    bool check = 1;
    unsigned int i = 0;
    //verifica se tem um sinal negativo
    if(s[0] == '-'){
        i++;
        check = -1;
    }
    //verifica se todos os caracteres da string representam um numero
    //necessario para a funcao stoi que converte string para int
    for( ; i < s.size(); i++){
        char c = int( s[i] );
        if(c < '0' || c > '9'){
            check = 0;
            break;
        }
    }
    //std::cout << check << "\n";

    return check;

}



//Mapeando as constantes
//varre toda a matriz de entrada e verefica onde se declaram labels :
//onde se encontra uma label ela e salva junto com sua posicao de momoria do programa

void Montador::constant_map(){
    
    unsigned int i;
    unsigned int j;
    std::map<std::string, int> mapa;
    int pc = 0;
    for (i = 0; i < this->comandos_entrada.size(); i++){
        for  (j = 0 ; j < this->comandos_entrada[i].size(); j++ ){
            if(this->comandos_entrada[i][j].back() == ':'){

                std::string cnst = this->comandos_entrada[i][j];
                cnst.pop_back();
                mapa[cnst] = pc;

            }else if (this->comandos_entrada[i][j] != "WORD"){
                pc = pc + 1;
            }
        }
    }
    this->mapa = mapa;
}


// Funcao com um nome muito ruim
// mas ela tem o objetivo de encontrar onde uma label e usada como parametro
//entao substituir o parametro que e uma label por um int que corresponde
// a diferanca da posicao de memoria do comando e da label
void Montador::const_to_value(){
    unsigned int i;
    unsigned int j;
    int pc = 0;
    std::map<std::string, int>::iterator it;
    for (i = 0; i < this->comandos_entrada.size(); i++){
        for  (j = 0 ; j < this->comandos_entrada[i].size(); j++ ){
            
            if( mapa.find(this->comandos_entrada[i][j]) != mapa.end() ){    
                this->comandos_entrada[i][j] = std::to_string(this->mapa[this->comandos_entrada[i][j]] - pc - 1);
            }

            if(this->comandos_entrada[i][j] != "WORD" && this->comandos_entrada[i][j] != "END" && this->comandos_entrada[i][j].back() !=':' )
                pc = pc + 1;
        }
    }
}

//Calcula os 4 inteiros principais para o montador
void Montador::calcula_valores_pilha(){
    unsigned int i;
    
    for(i = 0; i< comandos_entrada.size() ;i++){
        this->total_comandos_entrada = this->total_comandos_entrada + this->comandos_entrada[i].size();
    }
    
    //find inicio
    int init = 0;
    for(i = 0; i< this->comandos_entrada.size() ;i++){
        //sei que nao tem declaracao de fucao no inicio ainda
        if(this->comandos_entrada[i][0].back() == ':' || this->comandos_entrada[i][0] == "WORD"){
            init++;
        }else{
            break;
        }
    }
    this->inicio = init + this-> total_comandos_entrada;
    this->pilha = 1000 + this->total_comandos_saida + this->total_comandos_entrada;
}


//funcao auxiliar de traducao
//aqui checa qual comando em string foi dado e retorna seu valor em int
//foi pensado como switch porem c+  so itera int para switch case 
//triste :(
int Montador::check_instrucao(std::string s){
    int operacao = -1;
    
    bool check = check_int(s);
    if(check){
        return std::stoi(s);
    }
 
    if (s == "HALT")
        operacao = 0;
    if (s == "LOAD")
        operacao = 1;
    if (s ==  "STORE")
        operacao = 2;
    if (s ==  "READ")
        operacao = 3;
    if (s ==  "WRITE")
        operacao = 4;
    if (s ==  "COPY")
        operacao = 5;
    if (s ==  "PUSH")
        operacao = 6;
    if (s ==  "POP")
        operacao = 7;
    if (s ==  "ADD")
        operacao = 8;
    if (s ==  "SUB")
        operacao = 9;
    if (s ==  "MUL")
        operacao = 10;
    if (s ==  "DIV")
        operacao = 11;
    if (s ==  "MOD")
        operacao = 12;
    if (s ==  "AND")
        operacao = 13;
    if (s ==  "OR")
        operacao = 14;
    if (s ==  "NOT")
        operacao = 15;
    if (s ==  "JUMP")
        operacao = 16;
    if (s ==  "JZ")
        operacao = 17;
    if (s ==  "JN")
        operacao = 18;
    if (s ==  "CALL")
        operacao = 19;
    if (s ==  "RET")
        operacao = 20;
    
    if (s ==  "R0")
        operacao = 0;
    if (s ==  "R1")
        operacao = 1;
    if (s ==  "R2")
        operacao = 2;
    if (s ==  "R3")
        operacao = 3;        
    
    return operacao;
}

*/