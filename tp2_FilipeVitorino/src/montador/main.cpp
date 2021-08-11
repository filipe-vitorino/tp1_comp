#include "montador.h"

int main(int argc, char *argv[]) {
    
    std::ifstream f;
    //std::cout << argc << std::endl;
    switch (argc) {
        case 1:
            std::cerr << "Erro: nenhum arquivo fonte fornecido!!\n";
            return 1;
        case 2:
            f.open(argv[1]);
        break;
    }
    
    std::vector<std::vector<std::string> > dict;

    //leitura do arquivo de entrada 
    //ler linha por linha
    //separar as palavras da linha 
    //remover espacos adicionais e comentarios
    //std::vector<std::string> linha;
    for(std::string line; getline( f, line ); ){
        std::vector<std::string> linha;
        unsigned int i = 0;
        std::string palavra;

        while(i < line.size()){
            if(line[i] == ';'){
                if(!palavra.empty()){
                //     std::cout << palavra << std::endl;
                    linha.push_back(palavra);
                    //std::cout << linha.back() << std::endl;
                    //std::cout << linha.back() << " ";
                    palavra.clear();;
                    //std::cout << linha.back() << std::endl;
                }
                break;

            }else if(line[i] == ' '){
                if(!palavra.empty()){
                //       std::cout << palavra << std::endl;
                    linha.push_back(palavra);
                    //std::cout << linha.back() << " ";
                    palavra.clear();;
                    //std::cout << linha.back() << std::endl;
                }
            }else{
                palavra.push_back(line[i]);
            }
            i++;
        }

        if(!palavra.empty()){
            //std::cout << palavra << std::endl;
            linha.push_back(palavra);
        }
        //std::cout << dict.back().back() << " ";
        
        if(!linha.empty())
            dict.push_back(linha);
        //std::cout << dict.back().back() << std::endl;
        
        
    }
    f.close();

    //lista[0].imprime();
    // Montador montador(dict); 
    //Trabalho em cima das labels primeiro
    //montador.imprime();
    
    //unsigned int i;
    
    //Como eu gostaria que fosse a Saida
    //Declara o montador
    Montador montador(dict); 
    montador.check_main();
    
    if (!montador.is_main){
        
        montador.remove_end();
        montador.remove_outside_code();
    
    }
    montador.imprime();




    

    
    
    /*
    Montador montador(dict); 
    //Trabalho em cima das labels primeiro
    montador.imprime();
    montador.constant_map();
    montador.const_to_value();
    montador.imprime();
    //Funcao principal de conversao
    montador.traducao(); //nome muito ruim eu sei
    montador.calcula_valores_pilha();

    //Saida do programa
    
    std::cout << "MV-EXE" << std::endl <<std::endl;
    std::cout << montador.total_comandos_saida << ' ' 
              << montador.total_comandos_entrada << ' ' 
              << montador.pilha << ' ' 
              << montador.inicio << std::endl << std::endl;
    
    for (i = 0; i < montador.comandos_saida.size(); i++){
        std::cout << montador.comandos_saida[i] << ' ';
    }
    */
    std::cout << std::endl;

}
