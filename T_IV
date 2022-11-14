#include <stack>
#include <iostream>
#include <map>
#include <cmath>
#include <string>

using namespace std;

//#define CATCH_CONFIG_MAIN // O Catch fornece uma main()
//#include "catch.hpp"

template<typename T>

struct Calculadora {

    // ver http://en.cppreference.com/w/cpp/container/stack
    std::stack<T> operandos;    // números, basicamente
    std::stack<char> operadores; // operadores: +, -, /, *
    int cont = 0;

    // cria a calculadora
    void cria(void){
    }

    void calc(){
        while(operadores.empty()!=true){
            if(operadores.top()=='('){
                operadores.pop();
                break;
            }else{
                if(operandos.empty()==false){
                    T x = operandos.top();
                    operandos.pop();
                    if(operandos.empty()==false){
                        T y = operandos.top();
                        operandos.pop();

                        switch(operadores.top()){
                            case '+':
                                //std::cout << "38";
                                //std::cout << y << "+" << x << "=" << y+x << std::endl;
                                operando(y+x);
                                //std::cout <<"PILHA" <<operandos.top() << std::endl;
                                break;
                            case '-':
                                operando(y-x);
                                //std::cout << y << "-" << x << std::endl;
                                break;
                            case '*':
                                operando(y*x);
                                //std::cout <<"PILHA" <<operandos.top() << std::endl;
                                //std::cout << y << "*" << x << std::endl;
                                break;
                            case '/':
                                operando(std::round(y/ static_cast<float>(x)));
                                //std::cout << y << "/" << x  << "=" << y/x << std::endl;
                                break;
                        }
                        operadores.pop();

                    }else {
                        operando(x);
                        break;
                    }
                }else break;
            }
        }
    }

    void destroi(void){
        while(operandos.empty() == false)
            operandos.pop();
        while(operadores.empty() == false)
            operadores.pop();
    }

    void operando(T op) {
        operandos.push(op);
        //std::cout <<"PILHA" << op << std::endl;
        //std::cout << "Adicionando -> " << op << std::endl;
    }

    void operador(char op){
        // verficar aqui o operador inserido
        switch(op){
            case '(':
            case '*':
            case '/':
                operadores.push(op);
                //std::cout << "Add -> " << op << std::endl;
                break;
            case '+':
            case '-':
                if(operadores.empty()!=true){
                    if((operadores.top()=='*')||(operadores.top()=='/')){
                        calc();
                        operadores.push('+');
                        //std::cout << "Add -> " << "+" << std::endl;
                    }else{
                        operadores.push('+');
                        //std::cout << "Add -> " << "+" << std::endl;
                    }
       
                }else{
                    operadores.push('+');
                    //std::cout << "Add -> " << "+" << std::endl;
                }
                break;
            case ')':
                //std::cout << "Adic: )" << std::endl;
                if(operadores.top()=='('){
                    operadores.pop();
                }else{
                    calc();
                }

                //calc();
                //std::cout << "aviso: )" << std::endl;
                //std::cout << operandos.top()<< std::endl;
                break;

        }

    }

    void formula(std::string form){
        int acm=0; //significa número sem sinal
        bool N = false;
        bool fecha = false;

        for(auto i=0;i<static_cast<int>(form.length());i++){
            //std::cout << form[i] << " ";     
            if(std::isdigit(form[i])){
                acm = (acm*10)+(form[i]-'0');
            }else if (form[i] == '(' || form[i] == ')') {

                if(acm!= 0){
                    if(N){
                        operando(acm*(-1));
                        //std::cout << "Aqui " << acm*(-1) <<std::endl;
                        N = false;
                        acm=0;
                    }else{
                        operando(acm);
                        //std::cout << "Aqui " << acm <<std::endl;
                        //number.push(acm);
                        N = false;
                        acm=0;
                    }
                }
                operador(form[i]);

                if(form[i] == '('){
                    cont += 1;
                }
                if(form[i] == ')'){
                    fecha = true;
                    cont -= 1;
                }
            }else{ 
                if(fecha){
                    fecha = !fecha;
                    //std::cout << "AAAAAAAAAAAA " << form[i];
                    //operando(acm);
                    operador(form[i]);
                    N = false;
                    acm = 0;
                    //sinal.push(form[i]);
                    continue;
                }
                //if(form[i]=='-') N = true;
                if((acm==0)&&(form[i]=='-')){
                    N = !N;
                }else{
                    
                    //std::cout << acm << std::endl;
                    
                    if(N){
                        //std::cout << "Adicionado: " << acm*(-1) << " nga" << std::endl;
                        operando(acm*(-1));
                        //number.push(acm*(-1));
                    }else{
                        //std::cout << "Adicionado: " << acm << std::endl;
                        operando(acm);
                        //number.push(acm);
                    }
                    //std::cout << " ola:             "<< form[i] << std::endl;
                    operador(form[i]);
                    //sinal.push(form[i]);
                    if(form[i]=='-'){
                        N = true;
                        
                    } else {
                    N = false;
                    }
                    acm = 0;
                }
            }
        }

        //std::cout << acm << std::endl;
        if(acm != 0){
            if(N){
                //std::cout << "Adicionado: " << acm << "negativo" << std::endl;
                operando(acm*(-1));
                //number.push(acm*(-1));
            }else{
                //std::cout << "Adicionado baixo: " << acm << std::endl;
                operando(acm);
                //number.push(acm);
            }
        }
    }

    bool fim(void) {
        if(operandos.empty()||cont!=0)
            return false;
        if((operandos.size()==2)&&(operadores.size()==0) || (operandos.size()==1)&&(operadores.size()==1)){
            return false;
        }
        calc();
        return true;
    }

    T resultado(void) {
        if(operandos.empty())
            return static_cast<T>(0);

        return operandos.top();
    }
};

struct Celula {
  std::string formula;
  int valor;
};

std::map<std::string, Celula> *ptr;

struct Planilha {
    std::map<std::string, Celula> celulas;
    std::string id;
    std::string form;
    Calculadora<int> calc;

    void leitura(std::string id, std::string form){
        celulas[id].formula = form;
    }

    std::string value(std::string form){
        for(auto it= ptr->begin(); it != ptr->end(); it++){
            if(form == "("+it->first+")"){
                //std::cout << "("+it->first+")" << std::endl;
                //std::cout << it->second.formula << std::endl;
                if(it->second.formula[0] == '='){
                    std::string c = it->second.formula.substr(1,it->second.formula.length()-1);
                    return "("+c+")";
                }
                return "("+it->second.formula+")";
            }
            //std::cout << "("+it->first+")" << std::endl;
            //std::cout << form << std::endl << std::endl;
        }
        
        return form;
    } 

    std::string tratamento(std::string form){   

        form = value(form); 

        for(long unsigned int i=0;i<form.length();i++){
            if(std::isalpha(form[i])){
                //std::cout << "entre: " ;
                if(std::isdigit(form[i+2])){
                   //std::cout << "antes: ";// << std::endl;
                   std::string a = tratamento(("("+(form.substr(i,i+2)))+")");
                   form.replace(i,i+2, a);
                   i+=4;
                   //std::cout << "depois: " << form << std::endl;
                }else{
                    std::string a = tratamento(("("+(form.substr(i,i+1)))+")");
                    form.replace(i,i+1, a);
                    i+=3;
                    
                }
            }
        }
        //std::cout << form << std::endl;
        return form;
    }

    void resolve(){
        for(auto it= celulas.begin(); it != celulas.end(); it++){
            if(it->second.formula[0] == '='){
                //std::cout << "ver: " ;
                std::string b = it->second.formula.substr(1,it->second.formula.length()-1);
                //std::cout << "olhar :  " << b << std::endl;
                it->second.formula = tratamento("("+b+")");
                //calc.formula(it->second.formula);
                //it->second.formula = calc.resultado();
                
                //std::cout << it->first << "    igual   " << it->second.formula << std::endl << std::endl;
                // return 0;
                calc.formula(it->second.formula);
                //std::cout << calc.resultado() << std::endl;
                it->second.formula = (calc.resultado()+'0');
                //std::cout << it->second.formula << std::endl;
            }
        }
    }

    void imprime(){
        for(auto it= celulas.begin(); it != celulas.end(); it++){
            if(std::isdigit(it->second.formula[0])){
                std::cout << it->first << " " << it->second.formula << std::endl;
            }   
        }
        //std::cout << std::endl << std::endl;
        //for(auto it= celulas.begin(); it != celulas.end(); it++)
            //std::cout << it->first << " " << it->second.formula << std::endl;
    }

}; 

int main (){
    Planilha excel; 
    std::string id;
    std::string form; 
    ptr = &excel.celulas; 
    //std::string trato;

    while(std::cin >> id && std::cin >> form){
        excel.leitura(id,form);
               
    }
    excel.resolve();

    //std::cout << "tratado  " << trato << std::endl;
    excel.imprime();


    return 0;
}
