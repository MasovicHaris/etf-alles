#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <iomanip>


using namespace std;


template <typename TipKljuca, typename TipVrijednosti>
class Mapa
{
    public:
    Mapa(){};
    virtual ~Mapa(){};
    virtual int brojElemenata() const = 0;
    virtual void obrisi() = 0;
    virtual void obrisi(TipKljuca kljuc) = 0;
    virtual TipVrijednosti operator[](const TipKljuca k) const = 0;
    virtual TipVrijednosti &operator[](TipKljuca k) = 0;
};



// znaci stablo je organizovano po kljucu

template<typename TipKljuca, typename TipVrijednosti>
class AVLStabloMapa: public Mapa<TipKljuca,TipVrijednosti>
{
  private:
  struct node
  {
    TipKljuca kljuc;
    TipVrijednosti value = TipVrijednosti();
    int balance : 2;
    node* left;
    node* right;
    node(const TipKljuca& d, const TipVrijednosti& t, int b=0):
      kljuc(d), balance(b), left(0), right(0), value(t){}
  };
  
  node* root;
  node*** pstack;
  bool* dstack;
  
  unsigned int size_var;
  inline void AVL_LL_rotate(node** p)
  {
    node* t=*p;
    *p=t->left;
    t->left=(*p)->right;
    (*p)->right=t;
    t->balance=-(++(*p)->balance);
  }
  inline void AVL_RR_rotate(node** p)
  {
    node* t=*p;
    *p=t->right;
    t->right=(*p)->left;
    (*p)->left=t;
    t->balance=-(--(*p)->balance);
  }
  inline void AVL_LR_rotate(node** p)
  {
    node* t=*p, *l=t->left;
    *p=l->right;
    l->right=(*p)->left;
    t->left = (*p)->right;
    (*p)->right = t;
    (*p)->left = l;
    if((*p)->balance != 1){
      l->balance=0;
      t->balance=-(*p)->balance;
    }
    else
    {
      l->balance=-1;
      t->balance=0;
    }
    (*p)->balance=0;
  }
  inline void AVL_RL_rotate(node** p)
  {
    node* t=*p, *l=t->right;
    *p=l->left;
    l->left=(*p)->right;
    t->right = (*p)->left;
    (*p)->left = t;
    (*p)->right = l;
    if((*p)->balance != -1){
      l->balance=0;
      t->balance=-(*p)->balance;
    }
    else
    {
      l->balance=1;
      t->balance=0;
    }
    (*p)->balance=0;
    
  }
  node* find(const TipKljuca &d) const
  {
      node* p = root;
      while(p)
      {
        if(d<p->kljuc) p=p->left;
        else if(!(d==p->kljuc)) p=p->right;
        else return p;
      }
      return nullptr;
  }
  
  void AVL_copy(node*& p, node* rp)
  {
      p=new node(rp->kljuc, rp->value, rp->balance);
      if(rp->left) AVL_copy(p->left, rp->left);
      if(rp->right) AVL_copy(p->right, rp->right);
  }
  
  
  AVLStabloMapa<TipKljuca,TipVrijednosti>& insert(const TipKljuca& d)
  {
    node*** s = pstack, **p=&root;
    bool* b = dstack;
    while(*p){
      *(++s) = p;
      if((*(++b)=(d<(*p)->kljuc)))
          p=&((*p)->left);
      else if(!(d==(*p)->kljuc))
        p=&((*p)->right);
      else return *this;
    }
    
    TipVrijednosti bezze = TipVrijednosti();
    
    *p=new node(d, bezze);
    size_var++;
    while(s!=pstack)
    {
      p=*s;
      if(*b)
      {
        if((*p)->balance==-1){
          if((*p)->left->balance!=1)
              AVL_LL_rotate(p);
          else
              AVL_LR_rotate(p);
          return *this;
        }
        if(!--(*p)->balance) return *this;
      }
      else{
        if((*p)->balance==1){
          if((*p)->right->balance!=-1)
              AVL_RR_rotate(p);
          else
              AVL_RL_rotate(p);
          return *this;
        }
        if(!++(*p)->balance) return *this;
      }
      b--;
      s--;
    }
    return *this;
  }
  
  public:
  
  AVLStabloMapa() : root(0), size_var(0)
  {
    pstack=new node**[sizeof(unsigned int) * 12];
    try{
      dstack=new bool[sizeof(unsigned int) * 12];
    }catch(...)
    {
      delete[] pstack;
      throw;
    }
  }
  
  AVLStabloMapa(const AVLStabloMapa& param) : root(0), size_var(param.size_var)
  {
    pstack = new node**[sizeof(unsigned int)*12];
    try{
      dstack=new bool[sizeof(unsigned int) * 12];
    }catch(...)
    {
      delete[] pstack;
      throw;
    }
    if(param.root)
    {
      try{
        AVL_copy(root, param.root);
      }catch(...)
      {
        delete[] pstack;
        delete[] dstack;
        obrisi();
        throw;
      }
    }
  }
  
  AVLStabloMapa& operator=(const  AVLStabloMapa<TipKljuca, TipVrijednosti>& temp)
  {
    if(this==&temp) return *this;
    delete[] dstack;
    this->obrisi();
    delete[] pstack;
    
    pstack= new node**[sizeof(unsigned int)*12];
    try{
      dstack=new bool[sizeof(unsigned int)*12];
    }catch(...)
    {
      delete[] pstack;
      throw;
    }
    
    try{
      AVL_copy(root, temp.root);
      size_var=temp.size_var;
      return *this;
    }catch(...)
    {
      delete[] pstack;
      delete[] dstack;
      obrisi();
      throw;
    }
  }
  
  ~AVLStabloMapa()
  {
    delete[] dstack;
    obrisi();
    delete[] pstack;
  }
  
  int brojElemenata() const
  {
    return size_var;
  }
  
  void obrisi()
  {
    node*** s=pstack, **p;
    if(!root) return;
    *(++s)=&root;
    while(s!=pstack){
      p=*s;
      if((*p)->left)* (++s) = &((*p)->left);
      else if((*p)->right)* (++s) = &((*p)->right);
      else
      {
        delete* p;
        *p=0;
        s--;
      }
    }
    root=0;
    size_var=0;
  }
  
  void obrisi(const TipKljuca);
  
  TipVrijednosti operator[](const TipKljuca k) const
  {
    node* temp=find(k);
    if(temp==nullptr) return TipVrijednosti();
    return temp->value;
  }
  
  TipVrijednosti& operator [](TipKljuca k)
  {
    node* temp = find(k);
    if(temp==nullptr) insert(k);
    temp=find(k);
    return temp->value;
  }

 
};


template<typename TipKljuca, typename TipVrijednosti>
void AVLStabloMapa<TipKljuca,TipVrijednosti>::obrisi(const TipKljuca d)
{
  node*** s=pstack, **p=&root, *t;
  bool* b=dstack;
  
  while(*p){
    *(++s)=p;
    if((*(++b)=(d<(*p)->kljuc)))
        p=&((*p)->left);
    else if(!(d==(*p)->kljuc))
        p=&((*p)->right);
    else break;
  }
  
  if(!(*p)) return;
  size_var--;
  
  if(!(*p)->left)
  {
    t=*p;
    *p=(*p)->right;
    delete t;
    b--;
    s--;
  }
  
  else if(!(*p)->right)
  {
    t=*p;
    *p=(*p)->left;
    delete t;
    b--;
    s--;
  }
  else
  {
    node** r = p, ***w=s+1;
    p=&((*p)->right);
    while((*p)->left){
      *(++s) = p;
      *(++b) = true;
      p=&((*p)->left);
    }
    
    t=*p;
    *p=(*p)->right;
    t->balance=(*r)->balance;
    t->left=(*r)->left;
    t->right=(*r)->right;
    delete* r;
    *r=t;
    *w=&(t->right);
  }
  
  while(s!=pstack){
    p=*s;
    if(*b)
    {
      if((*p)->balance==1)
      {
        if((*p)->right->balance!=-1){
          AVL_RR_rotate(p);
          if((*p)->balance) return;
        }
        else AVL_RL_rotate(p);
      }
      else if(++(*p)->balance) return;
    }
    else
    {
      if((*p)->balance == -1){
        if((*p)->left->balance!=1){
          AVL_LL_rotate(p);
          if((*p)->balance) return;
        }
        else AVL_LR_rotate(p);
      }
      else if(--(*p)->balance) return;
    }
    b--;
    s--;
  }
  return;
  
}

template<typename TipKljuca, typename TipVrijednosti>
class BinStabloMapa: public Mapa<TipKljuca,TipVrijednosti>
{
  
  struct Cvor
  {
      TipKljuca key;
      TipVrijednosti value;
      Cvor* desni=nullptr;
      Cvor* lijevi=nullptr;
      Cvor* parent=nullptr;
      Cvor(TipKljuca k1, TipVrijednosti p1, Cvor* desni1, Cvor* lijevi1, Cvor* parent1): key(k1), value(p1), desni(desni1), lijevi(lijevi1), parent(parent1){}
     
  };
  
  Cvor* root;
  int brElemenata;
  
  void tempObrisi(Cvor* r)
  {
      if(r!=nullptr)
      {
          tempObrisi(r->desni);
          tempObrisi(r->lijevi);
          delete r;
      }
  }
  
  Cvor* nadjiCvor(const TipKljuca &k, Cvor* r) const
  {
      if(r==nullptr || k==r->key) return r;
      else if(k>r->key) r=nadjiCvor(k, r->desni);
      else
      {
          r=nadjiCvor(k, r->lijevi);
      }
  }
  
  Cvor* NadjiMax(Cvor* r)
  {
      if(r->desni == nullptr) return r;
      NadjiMax(r->desni);
  }
  
  Cvor* obrisiCvor(Cvor* &r, TipKljuca k)  //rekurzija at her peak, ugl stvara se bruku ovih r->lijevi r->desni pokazivaca al sve OK radi! GLAVNA FUNKCIJA
  {
      if(r==nullptr) return r;
      else if(k>r->key) r->desni=obrisiCvor(r->desni, k);     //lociramo trazeni cvor
      else if(k<r->key) r->lijevi=obrisiCvor(r->lijevi, k);
      else
      {
          if(r->desni==nullptr && r->lijevi==nullptr) //kad je cvor koji se briše list, odnosno nema djece
          {
              delete r;
              r=nullptr;
          }
          else if(r->desni==nullptr)        //po jedno dijete
          {
              Cvor* temp = r;
              r=r->lijevi;          //u liniju 69 ili 70 će vratiti/prespojiti izbrisani element
              delete temp;
          }
          else if(r->lijevi == nullptr)  //po jedno dijete
          {
              Cvor* temp=r;
              r=r->desni;
              delete temp;
          }
          else      // dvoje djece
          {
              Cvor *temp=NadjiMax(r->lijevi); //nadjemo maximum u lijevom podstablu i swappamo ga sa elementom koji se brise
              r->key=temp->key;
              r->value=temp->value;     
              r->lijevi=obrisiCvor(r->lijevi, temp->key); //brisemo maximum u lijevom podstablu elementa koji se brise
          }
      }
      return r;
  }
  
  Cvor* dodajCvor(TipKljuca k, TipVrijednosti t, Cvor* &r, Cvor* roditelj)
  {
      if(r==nullptr)
      {
          r=new Cvor(k, t, nullptr, nullptr, r);
          brElemenata++;
          return r;
      }
      else if(k>r->key) return dodajCvor(k, t, r->desni, r); //dodajemo desno od roota
      else return dodajCvor(k,t,r->lijevi, r);              //dodajemo lijevo od roota
  }
  
  void iskopirajMapu(Cvor* &first, Cvor* second, Cvor* roditelj)
  {
      if(second==nullptr) return;
      first=new Cvor(second->key, second->value, nullptr, nullptr, roditelj);
      iskopirajMapu(first->desni, second->desni, first);
      iskopirajMapu(first->lijevi, second->lijevi, first);
  }
  
  
public:

  BinStabloMapa()
  {
      root=nullptr;
      brElemenata=0;
  }
  
  ~BinStabloMapa()
  {
      this->obrisi();
  }
  
  BinStabloMapa(const BinStabloMapa<TipKljuca,TipKljuca> &temp)
  {
      iskopirajMapu(root, temp.root, nullptr);
      brElemenata=temp.brElemenata;
  }
  
  BinStabloMapa& operator=(const BinStabloMapa<TipKljuca,TipVrijednosti> &temp)
  {
      if(this==&temp) return *this;
      this->obrisi();
      iskopirajMapu(root, temp.root, nullptr);
      brElemenata=temp.brElemenata;
      return *this;
  }
  
  void obrisi()
  {
      tempObrisi(root);
      brElemenata=0;
      root=nullptr;
  }
  
  void obrisi(TipKljuca k)
  {
      obrisiCvor(root, k);
      brElemenata--;
  }
  
  TipVrijednosti operator[](const TipKljuca k) const
  {
      Cvor* temp=nadjiCvor(k, root);
      if(temp==nullptr) return TipVrijednosti();
      return temp->value;
  }
  
  TipVrijednosti& operator[](TipKljuca k)
  {
      Cvor* temp=nadjiCvor(k, root);
      if(temp==nullptr) temp = dodajCvor(k, TipVrijednosti(), root, nullptr);
      return temp->value;
  }
  
  int brojElemenata() const
  {
      return brElemenata;
  }
 
};





int main() {
    std::vector<int> randomize;
    for(int i=0; i<=500000; i++) randomize.push_back(rand()%3000);
    BinStabloMapa<int,int> treeMapa;
    AVLStabloMapa<int,int> nMapa;
    
    clock_t tajm1=clock();
    for(int i=0; i<randomize.size(); i++)
    {
      treeMapa[randomize[i]]=i*3;
    }
    clock_t tajm2=clock();
    int sum1=(tajm2-tajm1)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Za dodavanje 500000 elemenata u BinStabloMapu, bilo je potrebno "<<sum1<<" ms.\n";
    
    clock_t tajm3=clock();
    for(int i=0; i<randomize.size(); i++)
    {
      nMapa[randomize[i]]=i*3;
    }
    clock_t tajm4=clock();
    int sum2=(tajm4-tajm3)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Za dodavanje 500000 elemenata u AVLStabloMapu, bilo je potrebno "<<sum2<<" ms.\n";
    
    clock_t tajm5=clock();
    for(int i=0; i<randomize.size(); i++)
    {
      treeMapa[randomize[i]];
    }
    clock_t tajm6=clock();
    int sum3=(tajm6-tajm5)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Za pristup elementima BinStabloMape bilo je potrebno "<<sum3<<" ms.\n";
    
    clock_t tajm7=clock();
    for(int i=0; i<randomize.size(); i++)
    {
      nMapa[randomize[i]];
    }
    clock_t tajm8=clock();
    int sum4=(tajm8-tajm7)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Za pristup elementima AVLStabloMape bilo je potrebno "<<sum4<<" ms.\n";
    
    
    
    
    
    clock_t tajm9=clock();
    for(int i=0; i<randomize.size(); i++)
    {
      treeMapa.obrisi(randomize[i]);
    }
    clock_t tajm10=clock();
    int sum5=(tajm10-tajm9)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Za brisanje elemenata BinStabloMape bilo je potrebno "<<sum5<<" ms.\n";
    
    clock_t tajm11=clock();
    for(int i=0; i<randomize.size(); i++)
    {
      nMapa.obrisi(randomize[i]);
    }
    clock_t tajm12=clock();
    int sum6=(tajm12-tajm11)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Za brisanje elemenata AVLStabloMape bilo je potrebno "<<sum6<<" ms.\n";
    
    //rezultati su ocekivani, razlika je primjetna odnosno uocavamo da je AVLstabloMapa 2x brža od binarnog stabla što se tiče dodavanja i pristupa elementima,
    //razlika bi bila još primjetnija da nismo dodavali random elemente već npr običnu for petlju do 300k, jer bi tada binStabloMapa bila ustvari obična lista
    //dok bi se AVLStabloMapa balansiralo i opet bi ostajalo s kompeksnošću O(logn) za razliku od BinStabloMape koja bi bila O(n)!
    //Izvedba AVL stabla je malo čudna jer sam prvo pokušao rekurzivno pa su padali stres testovi, al sam onda uspio implementirati iterativno
    //i prošli su svi autotestovi, fakat rekurzivna implementacija nije zadovoljavajuća jer je kompleksnost O(log^2(n)) umjesto O(logn).
    //by huso
}
