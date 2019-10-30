#ifndef GRAF_NEORIENTAT_H_INCLUDED
#define GRAF_NEORIENTAT_H_INCLUDED
#include<iostream>
using namespace std;
class graf_neorientat{
    int nrn,nrm;
    int *a,*b,*lat,*ver,*ad;
    bool **m;
public:
    graf_neorientat(){}
    ~graf_neorientat(){
    nrn=nrm=0;
    delete a;
    delete b;
    delete m;
    delete ver;
    delete ad;
    }
    void detmatr(graf_neorientat&);
    void parc(graf_neorientat&);
    void parc_ad(graf_neorientat&,int,int);
    void parc_lat(graf_neorientat&,int,int*,int);
    void conex(graf_neorientat&);
    void comp_conex(graf_neorientat&);
    graf_neorientat& operator =(const graf_neorientat&);
    graf_neorientat& operator +(const graf_neorientat&);
    friend istream& operator >>(istream&, graf_neorientat&);
    friend ostream& operator <<(ostream&, graf_neorientat&);
};
istream& operator >>(istream& in, graf_neorientat& graf)
{
    int i,inc,fin,max=0,vcta[101],vctb[101],j;
    cout<<"Numar muchii:"<<endl;
    in>>graf.nrm;
    cout<<"Muchii:"<<endl;
    for(i=1;i<=graf.nrm;i++)
        {
            in>>inc>>fin;
            vcta[i]=inc;
            vctb[i]=fin;
            if(max<inc)max=inc;
            if(max<fin)max=fin;
        }
    graf.nrn=max;
    graf.a=new int[graf.nrm+5];
    graf.b=new int[graf.nrm+5];
    graf.m=new bool*[graf.nrn+5];
    for(i=1;i<=graf.nrn;i++)
        graf.m[i]=new bool[graf.nrn+5];
    graf.a=new int[105];
    graf.b=new int[105];
    graf.m=new bool*[105];
    for(i=1;i<=graf.nrn;i++)
        graf.m[i]=new bool[105];

    for(i=1;i<=graf.nrn;i++)
        for(j=1;j<=graf.nrn;j++)
            graf.m[i][j]=0;
    for(i=1;i<=graf.nrm;i++)
        {
            inc=vcta[i];
            fin=vctb[i];
            graf.a[i]=inc;
            graf.b[i]=fin;
        }
    graf.graf_neorientat::detmatr(graf);
    return in;
}
ostream& operator <<(ostream& out,graf_neorientat& graf)
{
    int i,j;
    out<<"Matricea de adiacenta:"<<endl<<endl;
    for(i=1;i<=graf.nrn;i++){
        for(j=1;j<=graf.nrn;j++)
            out<<graf.m[i][j]<<" ";
    out<<endl;
    }
    out<<"Muchiile grafului:"<<endl;
    for(i=1;i<=graf.nrm;i++){
        out<<graf.a[i]<<" "<<graf.b[i]<<endl;
    }
    out<<"Liste de vecini:"<<endl;
    for(i=1;i<=graf.nrn;i++){
        out<<i<<": ";
        for(j=1;j<=graf.nrn;j++)
            if(graf.m[i][j]){
                out<<j<<" ";
            }
        out<<endl;
    }
    return out;
}
graf_neorientat& graf_neorientat::operator+(const graf_neorientat&gout){
    int i,j;
    graf_neorientat *sum,gin;
    gin=*this;
    sum=new graf_neorientat();
    sum->nrn=gout.nrn;
    sum->nrm=0;
    sum->a=new int[105];
    sum->b=new int[105];
    sum->m=new bool*[105];
    for(i=1;i<=sum->nrn;i++)
        sum->m[i]=new bool[105];
    gin=*this;
    for(i=1;i<=gin.nrn;i++)
        for(j=1;j<=gin.nrn;j++){
            if(i==j)sum->m[i][j]=sum->m[j][i]=0;
            if(gin.m[i][j] || gout.m[i][j]){
                    sum->m[i][j]=sum->m[j][i]=1;
                    sum->nrm++;
                    sum->a[sum->nrm]=i;
                    sum->b[sum->nrm]=j;
            }
    }
    return *sum;
}
graf_neorientat& graf_neorientat::operator=(const graf_neorientat&gout){
    this->nrn=gout.nrn;
    this->nrm=gout.nrm;
    this->m=gout.m;
    this->a=gout.a;
    this->b=gout.b;
    return *this;
}
void graf_neorientat::conex(graf_neorientat&graf){
    int nad,i;
    parc_ad(graf,1,1);
    for(i=1;i<=graf.nrn;i++)
        if(graf.ver[i]==0){cout<<"Graful nu este conex"<<endl;return;}
    cout<<"Graful este conex"<<endl;
}
void graf_neorientat::comp_conex(graf_neorientat&graf){
    int nad,j,i;
    delete graf.ver;
    graf.ver=new int[nrn+5];
     for(j=1;j<=graf.nrn;j++)
                graf.ver[j]=0;
    for(i=1;i<=graf.nrn;i++)
        {
            cout<<i<<" ";
            parc_ad(graf,i,1);
            cout<<endl;
        }
}
void graf_neorientat::detmatr(graf_neorientat& graf)
{
    int i,inc,fin;
    for(i=1;i<=graf.nrm;i++)
    {
        inc=graf.a[i];
        fin=graf.b[i];
        graf.m[inc][fin]=graf.m[fin][inc]=1;
    }
}
void graf_neorientat::parc_ad(graf_neorientat &graf,int urm,int nad)
{
    int i;
    graf.ver[urm]=1;
    for(i=1;i<=graf.nrn;i++)
    {
        if(graf.m[urm][i]==1 && graf.ver[i]==0){
            cout<<i<<" ";
            graf.ad[++nad]=i;
            graf_neorientat::parc_ad(graf,i,nad);
        }
    }
}
void graf_neorientat::parc_lat(graf_neorientat &graf,int urm,int c[101],int u)
{
    int i;
    for(i=1;i<=graf.nrn;i++)
    {
        if(graf.m[c[urm]][i]==1 && graf.ver[i]==0){
            cout<<i<<" ";
            c[++u]=i;
            graf.ver[i]=1;
            graf_neorientat::parc_lat(graf,urm+1,c,u);
        }
    }
}
void graf_neorientat::parc(graf_neorientat& graf){
    int c[101],nad=1;
    graf.ver=new int[nrn+5];
    graf.ad=new int[nrn+5];
    for(int i=1;i<=graf.nrn;i++)
        graf.ver[i]=0;
    cout<<1<<" ";
    ad[1]=1;
    graf_neorientat::parc_ad(graf,1,nad);
    cout<<endl;
}
#endif // GRAF_NEORIENTAT_H_INCLUDED
