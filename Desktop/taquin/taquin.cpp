#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
const int nmax=5;

class point
{int x;
int y;
public :
   point(int a=0,int b=0){x=a;y=b;};
    friend class taquin;
    friend class joueur;
    void paffiche()
    {cout<<"("<<x<<","<<y<<")";
    };


};
class taquin
{
private:
	int size;
	int t[nmax][nmax];
public:
    friend class joueur;

	taquin(int n)
	{
		size = n;
		int k = 1;
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
			{
				t[i][j] = k; k++;
			}
			t[size-1][size-1]=0;
	}
	bool gagne(taquin);
    point casevide(taquin);
	void inverse(taquin*, point, point);
	void affiche();
	taquin melanger(int ,point *);
	taquin& operator=(const taquin&);
};
//les methodes
taquin& taquin::operator=(const taquin& s)
{
 size=s.size;
 for(int i=0;i<size;i++)
    for(int j=0;j<size;j++)
    t[i][j]=s.t[i][j];
 return *this;
}
// 1ere methode
bool taquin::gagne(taquin taq)
{
	bool v = true;
	int t1[size][size];
	int k=1;
	for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
    {t1[i][j]=k;k++;}
    t1[size-1][size-1]=0;
	for (int i = 0; i < size; i++)
	{
		int j = 0;
		while (j < size)
		{
			if ((taq.t)[i][j] != t1[i][j])
				return(false);
			else
				j++;
		}
	}
	return(v);
}
// 2eme methode
point taquin::casevide(taquin taq)
{
	point pos;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			if ((taq.t)[i][j] == 0)
			{
				pos.x = i;
				pos.y = j;
				return(pos);
			}
		}
}
// 3 eme methode
taquin taquin::melanger(int n,point* w)
{
	int v;
	point p;
	srand((int)time(0));
	for(int i=0;i<n;i++)
	{
	p=casevide(*this);
	point p1(p.x,p.y-1), p2(p.x,p.y+1), p3(p.x-1,p.y), p4(p.x+1,p.y);
	point t[4]={p1,p2,p3,p4};
	v=rand()%4 ;

	if((t[v].x>=0&&t[v].x<size&&t[v].y>=0&&t[v].y<size))
	{this->inverse(this,p,t[v]);
	w[i]=p;
}
else i--;
}return *this;
}




//5 eme methode
void taquin::inverse(taquin* taq, point p1, point p2)
{
	int aux;
	aux = taq->t[p1.x][p1.y];
	taq->t[p1.x][p1.y] = taq->t[p2.x][p2.y];
	taq->t[p2.x][p2.y] = aux;
}
//6 eme methode
void taquin::affiche()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			cout <<this->t[i][j]<<"  |"<<"\t";

		if(size==3)
      {cout << endl<<"--------------------"<<endl;

      }
      if(size==4)
      {cout << endl<<"----------------------------"<<endl;

      }
       if(size==5)
      {cout << endl<<"------------------------------------"<<endl;

      }

	}
}
class joueur
{char x;
public:
    friend class taquin;
    friend class point;
    taquin dep(taquin&  , char);

};
taquin joueur::dep(taquin& h,char y)
{
    point p1;
    p1=h.casevide(h);

    switch(y)
{case 's':
    if (p1.x+1<h.size)
      {point p(p1.x+1,p1.y);
         h.inverse(&h,p1,p);
      }
        break;
 case 'z':
        if (p1.x-1>=0)
        {point p(p1.x-1,p1.y);
        h.inverse(&h,p1,p);}
        break;
 case 'd':
    if (p1.y+1<h.size)
    {point p(p1.x,p1.y+1);
        h.inverse(&h,p1,p);}
        break;
 case 'q':
    if (p1.y-1>=0)
    {point p(p1.x,p1.y-1);
        h.inverse(&h,p1,p);}
        break;
 default :
    break;

}

}
int main()
{
    int t,k;
    do{ cout<<"Donner la taille du taquin "<<endl;
    cin>>t;}while(t<3||t>5);
    cout<<"Alors vous voulez jouer avec taquin "<<t<<"x"<<t<<endl<<endl;
    cout<<"choisir le degre de difficulte"<<endl<<endl;
    cin>>k;
    if(k>0&&k<=50)
        cout<<endl<<"niveau facile , entrainer vous afin de choisir d'autres niveau ??"<<endl;
    if(k>50&&k<=200)
        cout<<endl<<"niveau moyen , nous sommes heureux de votre progres "<<endl;
    if(k>200)
        cout<<endl<<"niveau difficle , Montrez-nous votre talent ! "<<endl;
    int n=0;
    point* e=new point [k];
    taquin h(t),p(t);
    cout<<endl<<"On commence !! Votre but est :"<<endl<<endl;
    h.affiche();
    p=h.melanger(k,e);
    cout<<endl<<"Votre taquin de depart est :"<<endl;
    h.affiche();
    joueur j;
    do {char c;
    cout<<"d:droite,q:gauche,z:haut,s:bas";
    cout<<endl<<"             "<<endl;
    cin>>c;
    j.dep(h,c);
    h.affiche();
    cout<<endl<<"              "<<endl;
    n++;
    int reponse;
    if(n%15==0)
    {cout<<"Voulez vous repeter de depart: entrer 1 si oui ,entrer 0 si non:"<<endl;
    cin>>reponse;
    if (reponse==0)
      continue;
    else
      {h=p;cout<<endl<<"Recommencer avec le meme taquin de depart!"<<endl<<endl;h.affiche();
    }
    }}while(!h.gagne(h));
    cout<<"BRAVO!!!! VOUS AVEZ GANGNE!!";

}
