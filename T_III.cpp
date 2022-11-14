// Dionatan Rodrigues 
#include <iostream>
#include <list>
#include <memory>
#include <iomanip>

double bruto = 0.0;
double impost = 0.0;

struct comando{
  double val_cotas;
  double n_cotas;
  int year;
};

typedef std::list<std::unique_ptr<comando>> list;

void aporte(list *lista, double valor, double cota, int ano){
  std::unique_ptr<comando>cmd(new comando{valor/cota,cota,ano});
  lista->push_back(std::move(cmd));

}

double imposto(double renda, int year, int ano){
  int i = (ano-year);
   if(i<2){
      return renda*0.35;
   }else if(i<4){
      return renda*0.30;
   }else if(i<6){
      return renda*0.25;
   }else if(i<8){
      return renda*0.20;
   }else if(i<10){
      return renda*0.15;
   }else{
      return renda*0.10;
   }
}

void resgate_unitario(list * lista, double valor, double cota, int ano){
  if(valor > -1 && valor < (lista->begin()->get()->val_cotas)*cota){
    double renda =(valor / lista->begin()->get()->n_cotas) - (valor / cota);

    bruto = (bruto + valor);
    impost = (impost + imposto(renda, lista->begin()->get()->year, ano));

    lista->begin()->get()->val_cotas = (lista->begin()->get()->val_cotas -(valor - renda));
  }else{
    bruto+= lista->begin()->get()->val_cotas*cota;
    double renda = (lista->begin()->get()->val_cotas)*cota - (lista->begin()->get()->val_cotas/lista->begin()->get()->n_cotas);
    impost = (impost + imposto(renda, lista->begin()->get()->year, ano));
    lista->begin()->get()->val_cotas = 0;

  } 
}

void resgate(list *lista, double valor, double cota, int ano){

  while(!lista->empty()){
    if(bruto < valor || valor < 0){
      resgate_unitario(lista,(valor-bruto),cota,ano);
      if(lista->begin()->get()->val_cotas == 0) {
        lista->pop_front();
      }

    }else {break;}
  }

}

int main(void)
{
  char situacao;
  double valor, cota;
  int ano;
  list lista;
  //list p = &lista; // ptr

  while((std::cin >> situacao)&&(std::cin >> valor)&&(std::cin >> cota)&&(std::cin >> ano)){   

    if(situacao == 'A'){
      aporte(&lista,valor,cota,ano);    
    }
    if (situacao == 'R'){
      bruto = 0.0;
      impost = 0.0;
      resgate(&lista,valor,cota,ano);
      std::cout << std::endl << bruto << " " << impost << std::endl;
    }

  }  
 
  return 0;
}
