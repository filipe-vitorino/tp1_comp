#ifndef LIGADOR_H
#define LIGADOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list> 
#include <map>

class Ligador{
    public:
       std::vector<std::vector<std::string>> comandos_entrada;
       std::map<std::string, int> mapa;
       std::vector<int> comandos_saida;
       int total_comandos_entrada;
       int total_comandos_saida;
       int inicio;
       int pilha;
       bool is_main;
    public:
        Ligador(std::vector<std::vector<std::string>>, bool);
        void traducao();
        int check_instrucao(std::string);
        bool check_int(std::string);
        void imprime();
        void constant_map();
        void const_to_value();
        void calcula_valores_pilha();
};


#endif
