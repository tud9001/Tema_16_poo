#include<iostream>
#include "graf_neorientat.h"
using namespace std;


int main(){
graf_neorientat g,g2,suma;
cin>>g;
cout<<g;
g.parc(g);
g.comp_conex(g);
cin>>g2;
suma=g+g2;
cout<<suma;
return 0;
}
