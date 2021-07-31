#ifndef MONTADOR_H
#define MONTADOR_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list> 
#include <map>

class Montador{
    public:
       std::vector<std::vector<std::string>> comandos_entrada;
       std::map<std::string, int> mapa;
       std::vector<int> comandos_saida;
       int total_comandos_entrada;
       int total_comandos_saida;
       int inicio;
       int pilha;
    public:
        Montador(std::vector<std::vector<std::string>> comandos_entrada);
        void traducao();
        int check_instrucao(std::string s);
        bool check_int(std::string s);
        void imprime();
        void constant_map();
        void const_to_value();
        void calcula_valores_pilha();
};


#endif
