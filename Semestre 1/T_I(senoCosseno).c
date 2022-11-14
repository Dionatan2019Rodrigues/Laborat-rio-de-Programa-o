/** Dionatan Eduardo Correa Rodrigues **/
#include <stdio.h>
#include <math.h>

double cosseno(double Lado, double L2, double L3);
double cossLAL(double l1, double a2, double l33);
double sennLLA(double la, double l2, double aa);
double sennAAL(double Aa, double Ab, double La);
double triangulo(double La,double Lb,double Lc,double Aa,double Ab,double Ac);

int main()
{
    float number, La=0, Lb=0, Lc=0, Aa=0, Ab=0, Ac=0, Ax1, Ax2, Ax3;
    
    printf("1 -> LLL - três lados\n");
    printf("2 -> LAL - dois lados e o ângulo entre eles\n");
    printf("3 -> LLA - dois lados e o ângulo adjacente ao segundo lado e oposto ao primeiro\n");
    printf("4 -> ALA - dois ângulos e o lado entre eles\n");
    printf("5 -> AAL - dois ângulos e o lado adjacente ao segundo ângulo e oposto ao primeiro\n");
    printf("Escolha quais informações deseja informar sobre seu triângulo(entre 1 e 5):\n");
    scanf("%f",&number);
    if(number>5 || number<1){
        printf("Valor não corresponde a nenhuma das opções");
    }else{
    printf("Valor 1º valor: ");
    scanf("%f",&Ax1);
    printf("Valor 2º valor: ");
    scanf("%f",&Ax2);
    printf("Valor 3º valor: ");
    scanf("%f",&Ax3);
    if(number==1){
        La = Ax1;
        Lb = Ax2;
        Lc = Ax3;
        Aa =cosseno(La, Lb, Lc);
        Ab = cosseno(Lb, La, Lc);
        Ac= cosseno(Lc, Lb, La);
        
    }else if(number==2){
        La = Ax1;
        Ab = Ax2;
        Lc = Ax3;
        Lb = cossLAL(La, Ab, Lc);
        Aa =cosseno(La, Lb, Lc);
        Ac =cosseno(Lc, Lb, La);
        
    }else if(number==3){
        La = Ax1;
        Lb = Ax2;
        Aa = Ax3;
        Ab = sennLLA(La,Lb,Aa);
        Ac = 180-(Aa+Ab);
        Lc = cossLAL(La,Ac,Lb);
        
    }else if(number==4){
        Aa = Ax1;
        Lc = Ax2;
        Ab = Ax3;
        Ac = 180-(Aa+Ab);
        La = sennAAL(Ac,Aa,Lc);
        Lb = sennAAL(Aa,Ab,La);
        
    }else if(number==5){
        Aa = Ax1;
        Ab = Ax2;
        La = Ax3;
        Ac = 180-(Aa+Ab);
        Lc = sennAAL(Aa,Ac,La);
        Lb = sennAAL(Aa,Ab,La);
        
    }
    triangulo(La,Lb,Lc,Aa,Ab,Ac);
   }
    return 0;
    
}

double cosseno(double Lado, double L2, double L3){
    double coss;
    coss = acos((pow(Lado,2)-pow(L2,2)-pow(L3,2))/(-2*L2*L3));
    return coss*180/M_PI;
     
}

double cossLAL(double l1, double a2, double l33){
    double coos;
    coos = sqrt((pow(l1,2)+pow(l33,2))-(2*l1*l33*(cos(a2*(M_PI/180)))));
    return coos;
}

double sennLLA(double la, double l2, double aa){
    double ang;
    ang = asin((la*sin(aa*(M_PI/180)))/l2);
    return ang*180/M_PI;
    
}

double sennAAL(double Aa, double Ab, double La){
    double seno;
    seno = (sin(Ab*(M_PI/180)))/(sin(Aa*(M_PI/180)));
    return La*seno;
    
}
double triangulo(double La,double Lb,double Lc,double Aa,double Ab,double Ac){
    printf("\n\nLado A: %.2f\n",La);
    printf("Lado B: %.2f",Lb);
    printf("\nLado C: %.2f",Lc);
    printf("\nAngulo A: %.2f",Aa);
    printf("\nAngulo B: %.2f",Ab);
    printf("\nAngulo C: %.2f",Ac);
}





