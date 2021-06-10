#include <iostream>

enum Color {RED, BLACK};

template <typename tip>
struct Cvor {
    int data;
    Color color;
    Cvor *left, *right, *parent;

    Cvor(tip data) {
        this->data = data;
        left = right = parent = nullptr;
        this->color = RED;
    }
    ~Cvor(){
        delete left;
        left = nullptr;
        delete right;
        right = nullptr;
    }
};



template <typename tip>
class RBStablo {
    Cvor<tip> *root;

    Cvor<tip>* umetniCvor(Cvor<tip>* &root, Cvor<tip> *z)
    {
        Cvor<tip> *y = nullptr;
        Cvor<tip> *x = root;

        while(x != nullptr) {
            y = x;
            if(z->data < x->data) x = x->left;
            else x = x->right;
        }

        z->parent = y;

        if(y == nullptr) root = z;
        else if (z->data < y->data) y->left = z;
        else y->right = z;

        z->left = nullptr;
        z->right = nullptr;
        z->color = RED;

        return root;
    }
    void popraviDrvo(Cvor<tip>* &root, Cvor<tip> *z) {
        // samo se desava fixanje ako imamo 2 reda zaredom
        while(z != root && z->color != BLACK && z->parent->color == RED) {
            if(z->parent == z->parent->parent->left) {
                Cvor<tip> *y = z->parent->parent->right;
                if(y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if(z == z->parent->right){
                        z = z->parent;
                        leftRotate(root, z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(root, z->parent->parent);
                }
            }
            else {
                Cvor<tip> *y = z->parent->parent->left;
                if(y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if(z == z->parent->left){
                        z = z->parent;
                        rightRotate(root, z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(root, z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void inOrderRun(Cvor<tip>* &root) {
        if (root == nullptr) return;
        inOrderRun(root->left);
        std::cout << root->data << " ";
        inOrderRun(root->right);
    }

    void rbTransplant(Cvor<tip>* &root, Cvor<tip>* u, Cvor<tip>* v) {
        if(u != nullptr && u->parent == nullptr) root = v;
        else if(u != nullptr && u->parent != nullptr && u == u->parent->left) u->parent->left = v;
        else if(u != nullptr && u->parent != nullptr) u->parent->right = v;

        if(v != nullptr && u != nullptr) v->parent = u->parent;
        
    }

    void rbDeleteFixStablo(Cvor<tip> * &x) {
        while(x != nullptr && x != this->root && x->color == BLACK) {
            if(x->parent != nullptr && x == x->parent->left){
                Cvor<tip>* w = x->parent->right;
                if(w->color == RED){
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(this->root, x->parent);
                    w = x->parent->right;
                }
                if(w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(this->root, w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(this->root, x->parent);
                    x = this->root;
                }
            }
            else {
                Cvor<tip>* w = x->parent->left;
                if(w->color == RED){
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(this->root, x->parent);
                    w = x->parent->left;
                }
                if(w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(this->root, w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(this->root, x->parent);
                    x = this->root;
                }
            }
        }
    }

    Cvor<tip>* treeMinimum(Cvor<tip>* poc) {
        while (poc->left != nullptr) poc = poc->left;
        return poc;
    }

    void rbDelete(Cvor<tip>* z) {
        Cvor<tip>* x;
        Cvor<tip>* y = z;
        Color yOriginalColor = y->color;
        if(z->left == nullptr){
            x = z->right;
            rbTransplant(this->root, z, z->right);
        }else if(z->right == nullptr) {
            x = z->left;
            rbTransplant(this->root, z, z->left);
        } else {
            y = treeMinimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if(y->parent == z && x != nullptr) x->parent = y;
            else {
                rbTransplant(this->root, y, y->right);
                y->right = z->right;
                if(y->right != nullptr) y->right->parent = y;
            }
            rbTransplant(this->root, z, y);
            y->left  = z->left;
            if(y->left != nullptr) y->left->parent = y;
            y->color = z->color;
        }
        if(yOriginalColor == BLACK) rbDeleteFixStablo(x);
        
        // brisanje z-a tj. dealociranje memorije
        z->right = nullptr;
        z->left = nullptr;
        delete z;
    }

    void findValueAndDeleteIt(Cvor<tip> * cvor, tip value) {
        if(cvor == nullptr) return;

        if(cvor->data == value) {
            rbDelete(cvor);
            return;
        }
        if(value < cvor->data) findValueAndDeleteIt(cvor->left, value);
        else findValueAndDeleteIt(cvor->right, value);
    }


public:
    RBStablo() { root = nullptr; }

    ~RBStablo() {
        delete root;
        root = nullptr;
    }
    void leftRotate(Cvor<tip> *&root, Cvor<tip> *x) {
        Cvor<tip> *y = x->right;

        x->right = y->left;

        if (y->left != nullptr) y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Cvor<tip> *&root, Cvor<tip> *y) {
        Cvor<tip> *x = y->left;

        y->left = x->right;

        if (y->left != nullptr) y->left->parent = y;

        x->parent = y->parent;

        if (y->parent == nullptr) root = x;

        else if (y == y->parent->left) y->parent->left = x;

        else y->parent->right = x;

        x->right = y;
        y->parent = x;
    }

    void insertCvor(tip value) {
        Cvor<tip> *novi = new Cvor<tip>(value);
        // umetanje cvora
        this->root = umetniCvor(this->root, novi);
        // popravke
        popraviDrvo(this->root, novi);
    }

    void deleteCvor(tip value) {
        findValueAndDeleteIt(this->root, value);
    }

    void inOrderIspis() {
        inOrderRun(this->root);
    }
};


int main() {

    RBStablo<int> stablo;

    /*
    // test iz postavke
    stablo.insertCvor(6);
    stablo.insertCvor(11);
    stablo.insertCvor(10);
    stablo.insertCvor(2);
    stablo.insertCvor(9);
    stablo.insertCvor(7);
    stablo.insertCvor(5);
    stablo.insertCvor(13);
    stablo.insertCvor(22);
    stablo.insertCvor(27);
    stablo.insertCvor(36);
    stablo.insertCvor(12);
    stablo.insertCvor(31);

    stablo.inOrderIspis();
    std::cout << std::endl << "Nakon brisanja 5,27,36,12,11: " << std::endl;

    stablo.deleteCvor(5);
    stablo.deleteCvor(27);
    stablo.deleteCvor(36);
    stablo.deleteCvor(12);
    stablo.deleteCvor(11);

    stablo.inOrderIspis(); 
    */
    
    int opcija;
    do {
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << "Izaberite opciju -" << std::endl;
        std::cout << "1) Umetanje novog cvora" << std::endl;
        std::cout << "2) Inorder ispis" << std::endl;
        std::cout << "3) Brisanje cvora" << std::endl;
        std::cout << "4) Izlaz" << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cin >> opcija;
        switch (opcija){
            case 1:
                int broj;
                std::cout << "Unesite cvor: ";
                std::cin >> broj;
                stablo.insertCvor(broj);
                break;
            case 2:
                std::cout << "Inorder ispis: ";
                stablo.inOrderIspis();
                std::cout << std::endl;
                break;
            case 3:
                std::cout << "Unesite cvor koji zelite obrisati: ";
                std::cin >> broj;
                stablo.deleteCvor(broj);
            case 4:
            default:
                break;
        }
    } while (opcija != 4); 

    return 0;
}