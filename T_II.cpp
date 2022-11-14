
// Dionatan Rodrigues 
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main()
{  
   int n;
   std::string linha;

   std::cin >> n;
   int** mat {new int *[n]};

   for(auto i=0;i<n;i++){
        std::cin >> linha;
        mat[i] = new int [n];
        for(auto j=0;j<n;j++){
            mat[i][j] = linha[j]=='*'?-1:0;
        }
   }

   for(auto i=0;i<n;i++){
        for(auto j=0;j<n;j++){
            if(mat[i][j]==-1){

                for(auto k=i-1;k<i+2;k++){
                    if(k>=0 && k<n){
                      for(auto l=j-1;l<j+2;l++){
                        if(l>=0 && l<n && mat[k][l]!= -1){
                            mat[k][l] +=1;
                        }
                      }
                    }
                }
            }
        }
    }

    for(auto i=0;i<n;i++){
        for(auto j=0;j<n;j++){
            if(mat[i][j]==-1){
                std::cout << '*';
            }else{
                std:: cout << mat[i][j];
            }
            
        }
        std::cout << std::endl;
    }


    for(auto i=0 ; i < n; i++)
        delete[] mat[i];
    delete[] mat;

    return 0;
}
