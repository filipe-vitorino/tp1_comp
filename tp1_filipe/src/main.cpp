#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list> 


int main(int argc, char *argv[]) {

    std::ifstream f;

    switch (argc) {
        case 1:
            std::cerr << "Erro: nenhum arquivo fonte fornecido!!\n";
            return 1;
        case 2:
            f.open(argv[1]);
        break;
    
    }

    std::vector<std::vector<std::string> > dict;
    //std::vector<std::string> linha;
    for(std::string line; getline( f, line ); ){
        std::vector<std::string> linha;
        long unsigned int i = 0;
        std::string palavra;

        while(i < line.size()){
            if(line[i] == ';'){
                if(!palavra.empty()){
               //     std::cout << palavra << std::endl;
                    linha.push_back(palavra);
                    std::cout << linha.back() << std::endl;
                    //std::cout << linha.back() << " ";
                    palavra.clear();;
                    //std::cout << linha.back() << std::endl;
                }
                break;

            }else if(line[i] == ' '){
                if(!palavra.empty()){
             //       std::cout << palavra << std::endl;
                    linha.push_back(palavra);
                    std::cout << linha.back() << " ";
                    palavra.clear();;
                    std::cout << linha.back() << std::endl;
                }
            }else{
                palavra.push_back(line[i]);
            }
            i++;
        }

        if(!palavra.empty()){
            std::cout << palavra << std::endl;
            linha.push_back(palavra);
        }
        //std::cout << dict.back().back() << " ";
        
        if(!linha.empty())
            dict.push_back(linha);
        //std::cout << dict.back().back() << std::endl;

    }
    f.close();
    
    long unsigned int i;
    long unsigned int j;

    std::cout << "--------------" << std::endl;
    for (i = 0; i < dict.size(); i++){
        for  (j = 0 ; j < dict[i].size(); j++ ){
            std::cout << dict[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    for (i = 0; i < dict.size(); i++){
        if(dict[i][0].back() == ':'){
            std::cout << dict[i][0] << ' ' << i+1 << std::endl;
        }
    }


    /*
    std::string line;    
    std::list<std::string> entrada;
    f >> line; // prsime read here
    while (!f.eof()) {
        if(line[0] == ';'){
            std::getline(f,line);
        }else{
            entrada.push_back(line);
            ///std::cout << line << std::endl;
        }
        f >> line;
    }   
    f.close();
    //int it = 0;
    std::string aux;
    std::list<std::string>::iterator it;
    
    for (it=entrada.begin(); it != entrada.end(); ++it){
      aux = *it;
      if(aux.back() == ':' ){
          
      }else{
          std::cout << ' ' << *it;
      }
    }
    */
}
