#include "ligador.h"


std::vector<std::vector<std::string>> merge(std::vector<Ligador> v){
    unsigned int i;
    unsigned int j;
    unsigned int indx;
    unsigned int k;
    //get main
    for (i=0; i < v.size(); i++ ){
        if( v[i].is_main ){
            indx = i;
            break;
        }
    }

    std::vector<std::vector<std::string>> matrix;

    for (i = 0; i < v[indx].comandos_entrada.size(); i++){
        matrix.push_back(v[indx].comandos_entrada[i]);
        if (v[indx].comandos_entrada[i][0] == "HALT"){
            
            for (k=0; k < v.size(); k++ ){
                if( k != indx ){
                    for (j = 0; j < v[k].comandos_entrada.size(); j++){
                        matrix.push_back(v[k].comandos_entrada[j]); 
                    }
                }
            }
        }
    }

/*
    for(i = 0; i < matrix.size(); i++){
        for(j =0; j < matrix[i].size(); j++){
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << "\n";
    }
    std::cout << "aaa";
  */
    return matrix;
}



int main(int argc, char *argv[]) {
   std::ifstream f;
    //std::cout << argc << std::endl;
    switch (argc) {
        case 1:
            std::cerr << "Erro: nenhum arquivo fonte fornecido!!\n";
            return 1;
    }

    int k;
    unsigned int i;
    
    
    std::vector<Ligador> entrada;
    for (k = 1; k < argc; k++){
        int tipo;
        std::vector<std::vector<std::string> > dict;
        
        f.open(argv[k]);
        f >> tipo;
        
       // std::cout << "aaaaa = " << tipo << "\n";
        for(std::string line; getline( f, line); ){
            if(line.size() > 0){
               // std::cout << "aaaaa = " << line << "\n";        
                
                std::string palavra;
                std::vector<std::string> linha;    
            

                for (i = 0; i < line.size(); i++){
                    if(line[i] == ' '){
                            if(palavra.size() > 0){
                            linha.push_back(palavra);
                            //std::cout << "bbb = " << palavra.back() << "\n";    
                            palavra = "";
                        }
                    }else{
                        palavra.push_back(line[i]);
                    }
                }
                if(linha.size() > 0){
                    dict.push_back(linha);        
                }
            }
        
        }

        f.close();
       
        
        entrada.push_back(Ligador(dict, tipo));
    
    }
   
    //entrada[1].imprime();
    Ligador ligador (merge(entrada), true);
    //ligador.imprime();
    
    //Trabalho em cima das labels primeir
 

    ligador.constant_map();
    //ligador.imprime();
    
    ligador.const_to_value();
    
    //ligador.imprime();
   
    //Funcao principal de conversao
    
    ligador.traducao(); //nome muito ruim eu sei
   
    
    ligador.calcula_valores_pilha();
   
    //Saida do programa
    std::cout << "MV-EXE" << std::endl <<std::endl;
    std::cout << ligador.total_comandos_saida << ' ' 
              << ligador.total_comandos_entrada << ' ' 
              << ligador.pilha << ' ' 
              << ligador.inicio << std::endl << std::endl;
    
    for (i = 0; i < ligador.comandos_saida.size(); i++){
        std::cout << ligador.comandos_saida[i] << ' ';
    }
    
    std::cout << std::endl;
    
    return 0;
}
