// rho0,R0,P0,Polytropic index n, Vexpを入力したらABCが出力され、Rの時間依存性をルンゲクッタ法で解いてくれるプログラム
#include<iostream>
#include<cmath>
#include<math.h>
#include<fstream>
using namespace std;

// 定数
const double G = 6.674*1.0E-23;
const double PI = 3.141592;

// 初期条件によって決まるABCを定義
double A=0.0 ,B=0.0, C=0.0;

// 初期半径
double R0=0.0;

double rho0=0.0, P0=0.0, K=0.0, n=0.0, Vexp=0.0;
double gamma=0.0, rhogamma=0.0, Rgamma=0.0, rc=0.0;    


// 初期条件ABCの決定
void ABC(){
    
    // rho0[g cm^-3] = rho0*1.0E15 [g km^-3]
    rho0=rho0*1.0E15;

    // P0[MeV fm^-3]= P0 *1.602*1.0E44
    // MeV/J = 1.602 * 1.0E-13
    P0=P0*1.602*1.0E38;
    
    gamma = (n+1.0)/n;
    rhogamma=pow(rho0,gamma);
    Rgamma=pow(R0,3*(gamma-1));
    K = P0/rhogamma;

    A = - 4.0* PI * G * rho0 * R0 *R0 * R0/3;
    B = 3 * gamma * P0 * Rgamma /rho0;
    C = R0 /Vexp;

    cout << "A=" << A <<endl;
    cout << "B=" << B << endl;
    cout << "C=" << C << endl;

}

// 関数 dx/dt=y =f1の定義
double f1(double t,double x,double y)
{
        return y;
}

//関数 dy/dt=d^2x/dt^2=f2の定義 
double f2(double t,double x,double y)
{
    A=1;B=1;C=1;
        return A*pow(x,-2) +B*pow(x, -3*gamma +2) +(C+3*t/2)*x;
}

int main(){

    cout << "初期密度：rho0[g/cm^3]=";
    cin >> rho0;
    cout << "初期半径：R0[km]=";
    cin >> R0;
    cout << "初期圧力:P0[MeV/fm^3]=";
    cin >> P0;
    cout << "Polytropic index：n=";
    cin >> n;
    // cout << "NSとchunkの距離：rc[km]=";
    // cin >> rc;
    cout << "膨張速度：Vexp[km/s]=";
    cin >> Vexp;

    ABC();
    cout << endl;

    double t,x,y,dt,tmax;
    double k1[2],k2[2],k3[2],k4[2];

    x=R0;                   //位置の初期値
    y=0.0;                  //速度の初期値
    dt=0.1;                //刻み幅
    tmax=500.0;             //繰り返し最大回数

    FILE *output;
    output=fopen("sample.txt","w");

    fprintf(output,"%f %f %f\n", A,B,C );

    for(t=0;t<tmax;t+=dt) {
        k1[0]=dt*f1(t,x,y);
        k1[1]=dt*f2(t,x,y);

        k2[0]=dt*f1(t+dt/2.0,x+k1[0]/2.0,y+k1[1]/2.0);
        k2[1]=dt*f2(t+dt/2.0,x+k1[0]/2.0,y+k1[1]/2.0);

        k3[0]=dt*f1(t+dt/2.0,x+k2[0]/2.0,y+k2[1]/2.0);
        k3[1]=dt*f2(t+dt/2.0,x+k2[0]/2.0,y+k2[1]/2.0);

        k4[0]=dt*f1(t+dt,x+k3[0],y+k3[1]);
        k4[1]=dt*f2(t+dt,x+k3[0],y+k3[1]);

        x=x+(k1[0]+2.0*k2[0]+2.0*k3[0]+k4[0])/6.0;
        y=y+(k1[1]+2.0*k2[1]+2.0*k3[1]+k4[1])/6.0;

        fprintf(output,"%f %f\n",t,x);
        // fprintf(output,"%f %f %f\n",t,x,y);
        }

    fclose(output);

    return 0;
}

