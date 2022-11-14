// Dionatan Rodrigues 
#include <iostream>

using namespace std;

int main()
{
    int n1,n2,n3;
    std::string condicao{"invalido"};

    cin >> n1 >> n2 >> n3;
    if((n1+n2)>n3){
        if((n1==n2)&&(n1==n3)){
            condicao = "equilatero";
        }else if((n1==n2)||(n2==n3)||(n1==n3)){
            condicao = "isosceles";
        }else if((n1!=n2)||(n2!=n3)||(n1!=n3)){
            condicao = "escaleno";
        }
    }
    cout << condicao << endl;

    return 0;
}
