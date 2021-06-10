#include <iostream>
#include <list>
#include <vector>
#include <cmath>

template <typename tip>
struct Cvor {
    int key;
    int degree;
    Cvor<tip>* parent;
    Cvor<tip>* child;
    Cvor<tip>* left;
    Cvor<tip>* right;
    bool mark;

    Cvor(tip value){
        parent = left = right = child = nullptr;
        degree = 0;
        key = value;
        mark = false;
    }
};

template <typename tip>
class FGomila {
    int n;
    Cvor<tip> *min;
public:
    FGomila(){
        n = 0;
        min = nullptr;
    }

    void gInsert(Cvor<tip>* x){
        x->degree = 0;
        x->parent = nullptr;
        x->mark = false;

        if (min == nullptr) {
            x->left = x;
            x->right = x;
            min = x;
        }
        else {
            min->left->right = x;
            x->right = min;
            x->left = min->left;
            min->left = x;
            if(x->key < min->key) min = x;
        };
        n = n + 1;
    }

    FGomila gUnion(FGomila h1, FGomila h2){
        FGomila h3 = FGomila();
        h3.min = h1.min;

        if(h2.min != nullptr && h3.min != nullptr) {
            (h3.min)->left->right = h2.min;
            (h2.min)->left->right = h3.min;
            Cvor<tip> *np = (h3.min)->left;
            (h3.min)->left = (h2.min)->left;
            (h2.min)->left = np;
        }

        if(h1.min == nullptr || (h2.min != nullptr && h2.min->key < h1.min->key)) h3.min = h2.min;
        h3.n = h1.n + h2.n;
        return h3;
    }


    Cvor<tip>* gExtractMin(){
        Cvor<tip>* z = min;
        if(z != nullptr){
            auto x = z->child;

            // ubacivanje djece
            if (x != nullptr)
            {
                Cvor<tip> *np;
                Cvor<tip> *ptr = x;
                do
                {
                    np = x->right;
                    (min->left)->right = x;
                    x->right = min;
                    x->left = min->left;
                    min->left = x;
                    if (x->key < min->key) min = x;
                    x->parent = nullptr;
                    x = np;
                }
                while (np != ptr);
            }

            min->left->right = min->right;
            min->right->left = min->left;

            if(z == z->left && z->child == nullptr) min = nullptr;
            else {
                min = z->right;
                gConsolidate();
            }
            n = n - 1;
        }
        return z;
    }


    void gConsolidate(){
        int D = log2(n) + 1;
        std::vector<Cvor<tip>*> A(D, nullptr);
        Cvor<tip>* x = min;
        do {
            int d = x->degree;
            while (A[d] != nullptr){
                Cvor<tip>* y = A[d];
                if(x->key > y->key){
                    auto b = x;
                    x = y;
                    y = b;
                }
                if (y == min) min = x;
                gHeapLink(y, x);
                if (x->right == x) min = x;
                A[d] = nullptr;
                d = d + 1;
            }
            A[d] = x;
            x = x->right;
        } while (x != min);

        min = nullptr;
        for (int j = 0; j < D; j++){
            if (A[j] != nullptr){
                A[j]->left = A[j];
                A[j]->right =A[j];
                if (min != nullptr){
                    (min->left)->right = A[j];
                    A[j]->right = min;
                    A[j]->left = min->left;
                    min->left = A[j];
                    if (A[j]->key < min->key) min = A[j];
                }
                else min = A[j];
                if(min == nullptr) min = A[j];
                else if (A[j]->key < min->key) min = A[j];
            }
        }
    }

    void gHeapLink(Cvor<tip>* y, Cvor<tip>* z){
        (y->left)->right = y->right;
        (y->right)->left = y->left;
        if (z->right == z) min = z;

        y->left = y;
        y->right = y;
        y->parent = z;

        if (z->child == nullptr) z->child = y;
        y->right = z->child;
        y->left = (z->child)->left;
        ((z->child)->left)->right = y;
        (z->child)->left = y;

        if (y->key < (z->child)->key) z->child = y;
        z->degree++;
    }

};

void testInsert() {
    FGomila<int> fg = FGomila<int>();
    // insert u praznu gomilu
    auto novi = new Cvor<int>(5);
    fg.gInsert(novi);

    // insert u nepraznu gomilu
    auto novi2 = new Cvor<int>(2);
    fg.gInsert(novi2);
    delete novi;
    novi = nullptr;
    delete novi2;
    novi2 = nullptr;
}


void testUnion2Pune() {
    FGomila<int> fg1 = FGomila<int>();
    auto novi1 = new Cvor<int>(5);
    auto novi2 = new Cvor<int>(2);
    auto novi3 = new Cvor<int>(6);
    auto novi4 = new Cvor<int>(7);
    fg1.gInsert(novi1);
    fg1.gInsert(novi2);

    FGomila<int> fg2 = FGomila<int>();
    fg2.gInsert(novi3);
    fg2.gInsert(novi3);

    FGomila<int> fg3 = fg1.gUnion(fg1, fg2);
    delete novi1;
    delete novi2;
    delete novi3;
    delete novi4;
}

void testUnion1Prazna() {
    FGomila<int> fg1 = FGomila<int>();
    auto novi1 = new Cvor<int>(5);
    auto novi2 = new Cvor<int>(2);
    fg1.gInsert(novi1);
    fg1.gInsert(novi2);

    FGomila<int> fg2 = FGomila<int>();

    FGomila<int> fg3 = fg1.gUnion(fg1, fg2);
    delete novi1;
    delete novi2;
}


void testUnion2Prazne() {
    FGomila<int> fg1 = FGomila<int>();
    FGomila<int> fg2 = FGomila<int>();
    FGomila<int> fg3 = fg1.gUnion(fg1, fg2);
}


void testExtractMin() {
    auto novi1 = new Cvor<int>(1);
    auto novi2 = new Cvor<int>(2);
    auto novi3 = new Cvor<int>(3);
    auto novi4 = new Cvor<int>(4);
    auto novi5 = new Cvor<int>(5);
    FGomila<int> fg = FGomila<int>();
    fg.gInsert(novi1);
    fg.gInsert(novi2);
    fg.gInsert(novi3);
    fg.gInsert(novi4);
    fg.gInsert(novi5);

    // extract min kad se nema djece
    Cvor<int>* b = fg.gExtractMin();
    std::cout << "Izbaceni: " << b->key << std::endl;

    // extract min kad se ima djece
    Cvor<int>* c = fg.gExtractMin();
    std::cout << "Izbaceni: " << c->key << std::endl;
    
    delete novi1;
    delete novi2;
    delete novi3;
    delete novi4;
    delete novi5;
} 


int main() {
    testInsert();
    testUnion2Pune();
    testUnion1Prazna();
    testUnion2Prazne();
    testUnion2Pune();
    testExtractMin();
    return 0;
}