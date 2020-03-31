#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

float licz(float N,float D,float R)
{
    float kula=0;
    float niekula=0;
    for(int i=0;i<N;i++)
    {
        float odl=0.;
        for(int j=0;j<D;j++)
        {
            float x = pow (2*R*(rand()%1000)/1000.-R,2);
            odl+=x;
        }
        if (pow(odl,0.5)>R)
        {
            niekula+=1;
        }
        else
        {
            kula+=1;
        }
    }
    cout << (kula/N)*pow((2*R),D) << endl;
    return 0;
}

int main()
{

    cout << licz(200000,2,1) << endl;

}


    
