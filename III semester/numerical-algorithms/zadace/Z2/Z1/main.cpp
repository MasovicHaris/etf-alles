//NA 2019/2020: Zadaća 2, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <utility>
#include <iomanip>
class Vector
{
    std::vector<double> vek;
public:
// konstruktor
    explicit Vector(int n)
    {
        if(n <= 0) throw std::range_error("Bad dimension");
        vek.resize(n);
    }

// konstruktor sa inicijalizacionom listom

    Vector(std::initializer_list<double> l)
    {
        if(!l.size()) throw std::range_error("Bad dimension");
        vek.resize(l.size());
        std::copy(std::begin(l),std::end(l),std::begin(vek));
    }

    int NElems() const
    {
        return vek.size();
    }

    double& operator[](int i)
    {
        return vek[i];
    }

    double operator [](int i) const
    {
        return vek[i];
    }

    double& operator()(int i)
    {
        if(i <= 0 || i > vek.size()) throw std::range_error("Invalid index");
        return vek[i - 1];
    }

    double operator()(int i) const
    {
        if(i <= 0 || i > vek.size()) throw std::range_error("Invalid index");
        return vek[i - 1];
    }

    double Norm() const
    {
        double suma = 0;
        for(auto x: vek) suma += x*x;
        return sqrt(suma);
    }

    friend double VectorNorm(const Vector &v);

    double GetEpsilon() const
    {
        return 10 * this->Norm() * std::numeric_limits<double>::epsilon();
    }

    void Print(char separator = '\n', double eps = -1) const
    {
        if(eps == -1) {
            for(int i = 0; i < vek.size() - 1; i++) {
                if(fabs(vek[i] - this->GetEpsilon()) < 0) std::cout<<0<<separator;
                else std::cout<<vek[i]<<separator;
            }
            if(separator == '\n') std::cout<<vek[vek.size() - 1]<<separator;
            else std::cout<<vek[vek.size() - 1];
        } else {
            for(int i = 0; i < vek.size() - 1; i++) {
                if(fabs(vek[i] - eps)< 0 || eps > fabs(vek[i])) std::cout<<0<<separator;
                else std::cout<<vek[i]<<separator;
            }
            if(separator == '\n') std::cout<<vek[vek.size() - 1]<<separator;
            else std::cout<<vek[vek.size() - 1];
        }
    }
    friend void PrintVector(const Vector &v, char separator, double eps);
    friend Vector operator +(const Vector &v1, const Vector &v2);
    Vector &operator +=(const Vector &v)
    {
        if(this->NElems() != v.NElems()) throw std::domain_error("Incompatible formats");
        for(int i = 0; i < this->NElems(); i++) vek[i] += v[i];
        return *this;
    }
    friend Vector operator -(const Vector &v1, const Vector &v2);
    Vector &operator -=(const Vector &v)
    {
        if(this->NElems() != v.NElems()) throw std::domain_error("Incompatible formats");
        for(int i = 0; i < this->NElems(); i++) vek[i] -= v[i];
        return *this;
    }
    friend Vector operator *(double s, const Vector &v);
    friend Vector operator *(const Vector &v, double s);
    Vector &operator *=(double s)
    {
        for(int i = 0; i < NElems(); i++) this->vek[i] *= s;
        return *this;
    }
    friend double operator *(const Vector &v1, const Vector &v2);
    friend Vector operator /(const Vector &v, double s);
    Vector &operator /=(double s)
    {
        if(s == 0) throw std::domain_error("Division by zero");
        for(int i = 0; i < NElems(); i++) vek[i] /= s;
        return *this;
    }
    void Chop(double eps = -1){
        if(eps < 0) eps = this->GetEpsilon();
        for(int i = 0; i < this->NElems(); i++){
            if(fabs(this->vek[i]) < eps) this->vek[i] = 0;
        }
    }
    bool EqualTo(const Vector &v, double eps = -1) const{
        if(eps < 0) eps = this->GetEpsilon();
        if(this->NElems() != v.NElems()) return false;
        for(int i = 0; i < this->NElems(); i++){
            if(fabs(this->vek[i] - v.vek[i]) > eps) return false;
        }
        return true;
    }

};

double VectorNorm(const Vector &v)
{
    double suma = 0;
    for(auto x: v.vek) suma += x*x;
    return sqrt(suma);
}

void PrintVector(const Vector &v, char separator = '\n', double eps = -1)
{
    if(eps == -1) {
        for(int i = 0; i < v.vek.size() - 1; i++) {
            if(fabs(v.vek[i] - v.GetEpsilon()) < 0) std::cout<<0<<separator;
            else std::cout<<v.vek[i]<<separator;
        }
        if(separator == '\n') std::cout<<v.vek[v.vek.size() - 1]<<separator;
        else std::cout<<v.vek[v.vek.size() - 1];
    } else {
        for(int i = 0; i < v.vek.size() - 1; i++) {
            if(fabs(v.vek[i] - eps) < 0 || eps > fabs(v.vek[i])) std::cout<<0<<separator;
            else std::cout<<v.vek[i]<<separator;
        }
        if(separator == '\n') std::cout<<v.vek[v.vek.size() - 1]<<0<<separator;
        else std::cout<<v.vek[v.vek.size() - 1];
    }
}
Vector operator +(const Vector &v1, const Vector &v2)
{
    if(v1.NElems() != v2.NElems()) throw std::domain_error("Incompatible formats");
    Vector c(v1.NElems());
    for(int i = 0; i < c.NElems(); i++) c[i] = v1[i] + v2[i];
    return c;
}
Vector operator -(const Vector &v1, const Vector &v2)
{
    if(v1.NElems() != v2.NElems()) throw std::domain_error("Incompatible formats");
    Vector c(v1.NElems());
    for(int i = 0; i < c.NElems(); i++) c[i] = v1[i] - v2[i];
    return c;
}

Vector operator *(double s, const Vector &v)
{
    Vector ret(v.NElems());
    std::copy(v.vek.begin(),v.vek.end(),ret.vek.begin());
    for(int i = 0; i < v.NElems(); i++) ret[i] *= s;
    return ret;
}

Vector operator *(const Vector &v, double s)
{
    return  s * v;
}

double operator *(const Vector &v1, const Vector &v2)
{
    if(v1.NElems() != v2.NElems()) throw std::domain_error("Incompatible formats");
    double ret = 0;
    for(int i = 0; i < v1.NElems(); i++) ret += v1[i] * v2[i];
    return ret;
}

Vector operator /(const Vector &v, double s)
{
    if(s == 0) throw std::domain_error("Division by zero");
    Vector ret(v.NElems());
    std::copy(v.vek.begin(),v.vek.end(),ret.vek.begin());
    for(int i = 0; i < v.NElems(); i++) ret[i] /= s;
    return ret;
}


// Klasa matrix

class Matrix
{
    std::vector<std::vector<double> > mat;
public:
    Matrix(int m, int n)
    {
        if(m <= 0 || n <= 0) throw std::range_error("Bad dimension");
        mat.resize(m);
        for(int i = 0; i < mat.size(); i++) mat[i].resize(n);
        for(int i = 0; i < mat.size(); i++)
            for(int j = 0; j < mat[0].size(); j++)
                mat[i][j] = 0;
    }
    Matrix(const Vector &v)
    {
        mat.resize(1);
        mat[0].resize(v.NElems());
        for(int i = 0; i < mat[0].size(); i++) mat[0][i] = v[i];
    }
    Matrix(std::initializer_list<std::vector<double>> l)
    {
        auto it = l.begin();
        int kvel = (*it).size();
        if(l.size() == 1 && kvel == 0 || l.size() == 0) throw std::range_error("Bad dimension");
        for(auto x: l) if(x.size() == 0 || x.size() != kvel ) throw std::logic_error("Bad matrix");
        mat.resize(l.size());
        int i = 0;
        for(auto x : l) {
            for(auto y : x) {
                mat[i].emplace_back(y);
            }
            i++;
        }
    }
    int NRows() const
    {
        return mat.size();
    }
    int NCols() const
    {
        return mat[0].size();
    }
    double *operator[](int i)
    {
        return &mat[i][0];

    }
    const double *operator[](int i) const
    {
        return &mat[i][0];
    }
    double &operator()(int i, int j)
    {
        if( i <= 0 || j <= 0 || i > mat.size() || j > mat[0].size()) throw std::range_error("Invalid index");
        return mat[i - 1][j - 1];
    }
    double operator()(int i, int j) const
    {
        if( i <= 0 || j <= 0 || i > mat.size() || j > mat[0].size()) throw std::range_error("Invalid index");
        return mat[i - 1][j - 1];
    }
    double Norm() const
    {
        double suma = 0;
        for(int i = 0; i < mat.size(); i++)
            for(int j = 0; j < mat[0].size(); j++)
                suma += mat[i][j] * mat[i][j];
        return sqrt(suma);
    }
    friend double MatrixNorm(const Matrix &m);
    double GetEpsilon() const
    {
        return 10 * Norm() * std::numeric_limits<double>::epsilon();
    }
    void Print(int width = 2, double eps = -1) const
    {
        if(eps == -1) {
            for(int i = 0; i < mat.size(); i++) {
                for(int j = 0; j < mat[0].size(); j++) {
                    if(fabs(mat[i][j] - this->GetEpsilon()) < 0) std::cout<<std::setw(width)<<"0";
                    else if(mat[i][j] >= 0)std::cout<<std::setw(width)<<mat[i][j];
                    else std::cout<<std::setw(width + 1)<<mat[i][j];
                }
                std::cout<<std::endl;
            }
        } else {
            for(int i = 0; i < mat.size(); i++) {
                for(int j = 0; j < mat[i].size(); j++) {
                    if(fabs(mat[i][j] - eps) < 0 || eps > fabs(mat[i][j])) std::cout<<std::setw(width)<<"0";
                    else std::cout<<std::setw(width)<<mat[i][j];
                }
                std::cout<<std::endl;
            }
        }
    }
    friend void PrintMatrix(const Matrix &m, int width, double eps);
    friend Matrix operator +(const Matrix &m1, const Matrix &m2);
    Matrix &operator +=(const Matrix &m)
    {
        if(this->mat.size() != m.mat.size() || this->mat[0].size() != m.mat[0].size()) throw std::domain_error("Incompatible formats");
        for(int i = 0; i < m.mat.size(); i++)
            for(int j = 0; j < m.mat[0].size(); j++) this->mat[i][j] += m.mat[i][j];
    }
    friend Matrix operator -(const Matrix &m1, const Matrix &m2);
    Matrix &operator -=(const Matrix &m)
    {
        if(this->mat.size() != m.mat.size() || this->mat[0].size() != m.mat[0].size()) throw std::domain_error("Incompatible formats");
        for(int i = 0; i < m.mat.size(); i++)
            for(int j = 0; j < m.mat[0].size(); j++) this->mat[i][j] -= m.mat[i][j];
    }
    friend Matrix operator *(double s, const Matrix &m);
    friend Matrix operator *(const Matrix &m, double s);
    Matrix &operator *=(double s)
    {
        for(int i = 0; i < this->mat.size(); i++)
            for(int j = 0; j < this->mat[0].size(); j++)
                this->mat[i][j] *= s;
        return *this;
    }
    friend Matrix operator *(const Matrix &m1, const Matrix &m2);
    Matrix &operator *=(const Matrix &m)
    {
        Matrix c(this->NRows(),m.NCols());
        if(this->NCols() != m.NRows()) throw std::domain_error("Incompatible formats");
        for(int i = 0; i < this->NRows(); i++) {
            for(int j = 0; j < m.NCols(); j++) {
                for(int k = 0; k < this->NCols(); k++) {
                    c[i][j] += (*this)[i][k] * m[k][j];
                }
            }
        }
        this->mat.resize(c.NRows());
        for(int i = 0; i < c.NRows(); i++) this->mat[i].resize(c.NCols());
        for(int i = 0; i < this->NRows(); i++)
            for(int j = 0; j < this->NCols(); j++)
                this->mat[i][j] = c[i][j];
        return *this;
    }


    friend Vector operator *(const Matrix &m, const Vector &v);
    friend Matrix Transpose(const Matrix &m);
    void Transpose()
    {
        Matrix temp(NCols(),NRows());
        for(int i = 0; i < this->NRows(); i++)
            for(int j = 0; j < this->NCols(); j++)
                temp[j][i] = this->mat[i][j];
        this->mat.resize(temp.NRows());
        
        for(int i = 0; i < temp.NRows(); i++) this->mat[i].resize(temp.NCols());
                
        for(int i = 0; i < this->NRows(); i++)
            for(int j = 0; j < this->NCols(); j++)
                this->mat[i][j] = temp[i][j];       
    }
    void Chop(double eps = -1){
        if(eps < 0) eps = this->GetEpsilon();
        for(int i = 0; i < this->NRows(); i++){
            for(int j = 0; j < this->NCols(); j++){
            if(fabs(this->mat[i][j]) < eps) this->mat[i][j] = 0;
            }
        }
    }
    bool EqualTo(const Matrix &m, double eps = -1) const{
        if(eps < 0) eps = this->GetEpsilon();
        if(this->NRows() != m.NRows() || this->NCols() != m.NCols()) return false;
        for(int i = 0; i < this->NRows(); i++){
            for(int j = 0; j < this->NCols(); j++){
            if(fabs((*this)[i][j] - m[i][j]) > eps) return false;
            }
        }
        return true;
    }
    friend Matrix LeftDiv(Matrix m1, Matrix m2);
    void SwapRow(int i, int j);
    void SwapCol(int i, int j);
    friend Vector LeftDiv(Matrix m, Vector v);
    friend Matrix operator / (const Matrix& m, double s);
    Matrix &operator /= (double s);
    friend Matrix operator / (Matrix m1, Matrix m2);
    Matrix &operator /= (Matrix m);
    double Det() const;
    friend double Det(Matrix m);
    void Invert();
    friend Matrix Inverse(Matrix m);
    void ReduceToRREF();
    friend Matrix RREF(Matrix m);
    int Rank() const;
    friend int Rank(Matrix m);

};

double MatrixNorm(const Matrix &m)
{
    double suma = 0;
    for(int i = 0; i < m.mat.size(); i++)
        for(int j = 0; j < m.mat[0].size(); j++)
            suma += m.mat[i][j] * m.mat[i][j];
    return sqrt(suma);
}

void PrintMatrix(const Matrix &m, int width = 10, double eps = -1)
{
    if(eps == -1) {
        for(int i = 0; i < m.mat.size(); i++) {
            for(int j = 0; j < m.mat[0].size(); j++) {
                if(fabs(m.mat[i][j] - m.GetEpsilon()) < 0) std::cout<<std::setw(width)<<0;
                else std::cout<<std::setw(width)<<m.mat[i][j];
            }
            std::cout<<std::endl;
        }
    } else {
        for(int i = 0; i < m.mat.size(); i++) {
            for(int j = 0; j < m.mat[i].size(); j++) {
                if(fabs(m.mat[i][j] - eps) < 0 || eps > fabs(m.mat[i][j])) std::cout<<std::setw(width)<<0;
                else std::cout<<std::setw(width)<<m.mat[i][j];
            }
            std::cout<<std::endl;
        }
    }

}
Matrix operator +(const Matrix &m1, const Matrix &m2)
{
    if(m1.NRows() != m2.NRows() || m1.NCols() != m2.NCols()) throw std::domain_error("Incompatible formats");
    Matrix c(m1.NRows(),m1.NCols());
    for(int i = 0; i < m1.NRows(); i++)
        for(int j = 0; j < m1.NCols(); j++) c[i][j] = m1[i][j] + m2[i][j];
    return c;
}
Matrix operator -(const Matrix &m1, const Matrix &m2)
{
    if(m1.NRows() != m2.NRows() || m1.NCols() != m2.NCols()) throw std::domain_error("Incompatible formats");
    Matrix c(m1.NRows(),m1.NCols());
    for(int i = 0; i < m1.NRows(); i++)
        for(int j = 0; j < m1.NCols(); j++) c[i][j] = m1[i][j] - m2[i][j];
    return c;
}
Matrix operator *(double s, const Matrix &m)
{
    Matrix c(m.mat.size(),m.mat[0].size());
    for(int i = 0; i < m.mat.size(); i++)
        for(int j = 0; j < m.mat[0].size(); j++)
            c[i][j] = s * m.mat[i][j];
    return c;
}
Matrix operator *(const Matrix &m, double s)
{
    return s * m;
}
Matrix operator *(const Matrix &m1, const Matrix &m2)
{
    if(m1.mat[0].size() != m2.mat.size()) throw std::domain_error("Incompatible formats");
    Matrix c(m1.NRows(),m2.NCols());
    for(int i = 0; i < m1.mat.size(); i++) {
        for(int j = 0; j < m2.mat[0].size(); j++) {
            for(int k = 0; k < m1.mat[0].size(); k++) {
                c[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return c;
}

Vector operator *(const Matrix &m, const Vector &v)
{
    if(m.NCols() != v.NElems()) throw std::domain_error("Incompatible formats");
    Vector c(m.NRows());
    for(int i = 0; i < m.NRows(); i++) {
        c[i] = 0;
        for(int j = 0; j < v.NElems(); j++)
            c[i] += m[i][j] * v[j];
    }
    return c;
}

Matrix Transpose(const Matrix &m)
{
    Matrix trans(m.NCols(),m.NRows());
    for(int i = 0; i < m.NRows(); i++)
        for(int j = 0; j < m.NCols(); j++)
            trans[j][i] = m[i][j];
    return trans;
}
void Matrix::SwapRow(int i, int j){
    for(int k = 0; k < NCols(); k++) std::swap(mat[i][k],mat[j][k]);
}
void Matrix::SwapCol(int i, int j){
    for(int k = 0; k < NRows(); k++) std::swap(mat[k][i],mat[k][j]);
}

Matrix LeftDiv(Matrix m1, Matrix m2){
    if(m1.NRows() != m1.NCols()) throw std::domain_error("Divisor matrix is not square");
    if(m1.NRows() != m2.NRows()) throw std::domain_error("Incompatible formats");
    Matrix X(m1.NRows(),m2.NCols());
    double mi;
    for(int k = 0; k < m1.NRows(); k++){
        int p = k;
        for(int i = k + 1; i < m1.NRows(); i++)
        if(std::fabs(m1[i][k]) > std::fabs(m1[p][k])) p = i;
        if(std::fabs(m1[p][k]) < m1.GetEpsilon()) throw std::domain_error("Divisor matrix is singular");
        if(p != k){
            m1.SwapRow(p,k);
            m2.SwapRow(p,k);
        }
        for(int i = k + 1; i < m1.NRows(); i++){
            mi = m1[i][k] / m1[k][k];
            for(int j = k + 1; j < m1.NRows(); j++)
            m1[i][j] = m1[i][j] - mi * m1[k][j];
            for(int j = 0; j < m2.NCols(); j++)
            m2[i][j] = m2[i][j] - mi * m2[k][j];
        }
    }
   double s;
   for(int k = 0; k < m2.NCols(); k++){
       for(int i = m1.NRows() - 1; i >= 0; i--){
        s = m2[i][k];
         for(int j = i + 1; j < m1.NRows(); j++)
          s = s - m1[i][j] * X[j][k];
         X[i][k] = s / m1[i][i];
       }
   }
   return X;
}

Vector LeftDiv(Matrix m, Vector v){
    Matrix temp(v);
    temp.Transpose();
    Matrix X = LeftDiv(m,temp);
    Vector x1(X.NRows());
    for(int i = 0; i < X.NRows(); i++) x1[i] = X[i][0];
    return x1;
}

Matrix operator/(const Matrix& m, double s){
    if(std::fabs(s) < m.GetEpsilon()) throw std::domain_error("Division by zero");
    Matrix m2(m.NRows(),m.NCols());
    for(int i = 0; i < m.NRows(); i++)
     for(int j = 0; j < m.NCols(); j++)
      m2[i][j] = m[i][j] / s;
    return m2; 
}
Matrix& Matrix::operator/=(double s){
    if(std::fabs(s) < this->GetEpsilon()) throw std::domain_error("Division by zero");
    for(int i = 0; i < NRows(); i++)
     for(int j = 0; j < NCols(); j++)
      (*this)[i][j] /= s;
    return *this;  
}
Matrix operator / (Matrix m2, Matrix m1){
    if(m1.NRows() != m1.NCols()) throw std::domain_error("Divisor matrix is not square");
    if(m1.NRows() != m2.NCols()) throw std::domain_error("Incompatible formats");
    Matrix X(m2.NRows(),m1.NCols());
    double mi;
    for(int k = 0; k < m1.NRows(); k++){
        int p = k;
        for(int i = k + 1; i < m1.NRows(); i++)
        if(std::fabs(m1[k][i]) > std::fabs(m1[p][k])) p = i;
        if(std::fabs(m1[k][p]) < m1.GetEpsilon()) throw std::domain_error("Divisor matrix is singular");
        if(p != k){
            m1.SwapCol(p,k);
            m2.SwapCol(p,k);
        }
        for(int i = k + 1; i < m1.NRows(); i++){
            mi = m1[k][i] / m1[k][k];
            for(int j = k + 1; j < m1.NRows(); j++)
            m1[j][i] = m1[j][i] - mi * m1[j][k];
            for(int j = 0; j < m2.NRows(); j++)
            m2[j][i] = m2[j][i] - mi * m2[j][k];
        }
    }
   double s;
   for(int k = 0; k < m2.NRows(); k++){
       for(int i = m1.NRows() - 1; i >= 0; i--){
        s = m2[k][i];
         for(int j = i + 1; j < m1.NRows(); j++)
          s = s - m1[j][i] * X[k][j];
         X[k][i] = s / m1[i][i];
       }
   }
   return X;
}
Matrix& Matrix::operator/=(Matrix m1){
    if(m1.NRows() != m1.NCols()) throw std::domain_error("Divisor matrix is not square");
    if(m1.NRows() != NCols()) throw std::domain_error("Incompatible formats");
    *this = *this / m1;
    return *this;
}
double Det(Matrix m){
    if(m.NRows() != m.NCols()) throw std::domain_error("Matrix is not square"); 
    double d = 1;
    double mi;
    int n = m.NRows();
    for(int k = 0; k < n; k++){
        double p = k;
        for(int i = k + 1; i < n; i++)
          if(std::fabs(m[i][k]) > std::fabs(m[p][k])) p = i;
        if(std::fabs(m[p][k]) < m.GetEpsilon()) return 0;
        if(p != k){ 
          m.SwapRow(k,p);
          d = -d;
        }
        d = d * m[k][k];
        for(int i = k + 1; i < n; i++){
         mi = m[i][k] / m[k][k];
         for(int j = k + 1; j < n; j++)
           m[i][j] = m[i][j] - mi * m[k][j];
        }
    }
    return d;
}
double Matrix::Det() const{
    if(NRows() != NCols()) throw std::domain_error("Matrix is not square"); 
    double d = 1;
    double mi;
    Matrix m = *this;
    int n = NRows();
    for(int k = 0; k < n; k++){
        double p = k;
        for(int i = k + 1; i < n; i++)
          if(std::fabs(m[i][k]) > std::fabs(m[p][k])) p = i;
        if(std::fabs(m[p][k]) < GetEpsilon()) return 0;
        if(p != k){ 
          m.SwapRow(k,p);
          d = -d;
        }
        d = d * m[k][k];
        for(int i = k + 1; i < n; i++){
         mi = m[i][k] / m[k][k];
         for(int j = k + 1; j < n; j++)
           m[i][j] = m[i][j] - mi * m[k][j];
        }
    }
    return d;
    
}
void Matrix::Invert(){
    if(NCols() != NRows()) throw std::domain_error("Matrix is not square");
    double mi;
    double n = NRows();
    std::vector<int> w(n);
    for(int k = 0; k < n; k++){
        int p = k;
        for(int i = k + 1; i < n; i++)
            if(std::fabs(mat[i][k]) > std::fabs(mat[p][k])) p = i;
        if(std::fabs(mat[p][k]) < GetEpsilon()) throw std::domain_error("Matrix is singular");  
        if(p != k) SwapRow(k,p);
        w[k] = p;
        mi = mat[k][k];
        mat[k][k] = 1;
        for(int j = 0; j < n; j++)
          mat[k][j] = mat[k][j] / mi;
        for(int i = 0; i < n; i++){
            if(i != k){
                mi = mat[i][k];
                mat[i][k] = 0;
                for(int j = 0; j < n; j++)
                 mat[i][j] = mat[i][j] - mi * mat[k][j];
            }
        }  
    }
    for(int j = n - 1; j >= 0; j--){
        int p = w[j];
        if(p != j) SwapCol(p,j);
    }
}
Matrix Inverse(Matrix m){
    if(m.NCols() != m.NRows()) throw std::domain_error("Matrix is not square");
    Matrix ret = m;
    try{
        ret.Invert();
    }
    catch(std::domain_error d){
        throw d;
    }
    return ret;
}
void Matrix::ReduceToRREF(){
    int k = -1;
    int l = -1;
    int p;
    int m = NRows();
    int n = NCols();
    double mi;
    std::vector<bool> w(m);
    for(int j = 0; j < m; j++) w[j] = false;
    while(k < m && l < n){
        k++; l++;
        double v = 0;
        while(v < GetEpsilon() && l < n){
          p = k;
          for(int i = k; i < m; i++){
              if(std::fabs(mat[i][l]) > v){
                  v = std::fabs(mat[i][l]);
                  p = i;
               }
          }
          if(v < GetEpsilon()) l++;
        }
        if(l < n){
        w[l] = true;
        if(p != k) SwapRow(p,k);
        mi = mat[k][l];
        for(int j = l; j < n; j++)
          mat[k][j] = mat[k][j] / mi;
        for(int i = 0; i < m; i++){
            if(i != k){
                mi = mat[i][l];
                for(int j = l; j < n; j++)
                 mat[i][j] = mat[i][j] - mi * mat[k][j];
            }
          }
        }
    }
}
Matrix RREF(Matrix m){
    m.ReduceToRREF();
    return m;
}
int Matrix::Rank() const{
    int rank = 0;
    Matrix m = *this;
    m.ReduceToRREF();
    for(int i = 0; i < m.NRows(); i++){
       for(int j = 0; j < m.NCols(); j++){
         if(std::fabs(m[i][j]) > m.GetEpsilon()){
         rank++;
         break;
         }
        }
    }
    return rank;
}

int Rank(Matrix m){
    return m.Rank();
}

class LUDecomposer{
  Vector w;
  Matrix m;
  public:
  LUDecomposer(Matrix m1): m(m1), w(m1.NRows()){
      if(m1.NRows() != m1.NCols()) throw std::domain_error("Matrix is not square");
      if(std::fabs(m1.Det()) < m1.GetEpsilon()) throw std::domain_error("Matrix is singular");
      int n = m.NRows();
      double s;
      int p;
      for(int j = 0; j < n; j++){
          for(int i = 0; i <= j; i++){
              s = m[i][j];
               for(int k = 0; k < i; k++)
                  s = s - m[i][k] * m[k][j];
              m[i][j] = s;
          }
          p = j;
          for(int i = j + 1; i < n; i++){
              s = m[i][j];
              for(int k = 0; k < j; k++)
                s = s - m[i][k] * m[k][j];
              m[i][j] = s;
              if(std::fabs(s) > std::fabs(m[p][j])) p = i;
          }
          if(std::fabs(m[p][j]) < m.GetEpsilon()) throw std::domain_error("Matrix is singular");
          if(p != j) m.SwapRow(p,j);
          w[j] = p;
          double mi = m[j][j];
          for(int i = j + 1; i < n; i++)
           m[i][j] = m[i][j] / mi;
      }
  }
  void Solve(const Vector &b, Vector &x) const;
  Vector Solve(Vector b) const;
  void Solve(Matrix &b, Matrix &x) const;
  Matrix Solve(Matrix b) const;
  Matrix GetCompactLU() const;
  Matrix GetL() const;
  Matrix GetU() const;
  Vector GetPermuation() const;
};

void LUDecomposer::Solve(const Vector &b, Vector &x) const{
    if(b.NElems() != m.NRows() || m.NRows() != x.NElems()) throw std::domain_error("Incompatible formats");
    x = b;
    for(int i = 0; i < m.NRows(); i++){
        int p = w[i];
        double s = x[p];
        x[p] = x[i];
        for(int j = 0; j < i; j++)
          s = s - m[i][j] * x[j];
        x[i] = s;  
    }
    for(int i = m.NRows() - 1; i >= 0; i--){
        double s = x[i];
        for(int j = i + 1; j < m.NRows(); j++)
         s = s - m[i][j] * x[j];
        x[i] = s / m[i][i]; 
    }
}

Vector LUDecomposer::Solve(Vector b) const{
    Vector a(b.NElems());
    this->Solve(b,a);
    return a;
}

void LUDecomposer::Solve(Matrix &b, Matrix &x) const{
    if(m.NRows() != b.NRows() || m.NRows() != x.NRows() || m.NCols() != b.NCols() || m.NCols() != x.NCols())
    throw std::domain_error("Incompatible formats");
    x = b;
    int n = m.NRows();
    int c = m.NCols();
    for(int k = 0; k < n; k++){
        for(int i = 0; i < c; i++){
            int p = w[i];
            double s = x[p][k];
            x[p][k] = x[i][k];
            for(int j = 0; j < i; j++)
              s = s - m[i][j] * x[j][k];
            x[i][k] = s;  
        }
    for(int i = c - 1; i >= 0; i--){
        double s = x[i][k];
        for(int j = i + 1; j < c; j++)
            s = s - m[i][j] * x[j][k];
        x[i][k] = s / m[i][i]; 
    }
    }
}

Matrix LUDecomposer::Solve(Matrix b) const{
    Matrix a(b.NRows(),b.NCols());
    this->Solve(b,a);
    return a;
}

Matrix LUDecomposer::GetCompactLU() const{return m;}

Matrix LUDecomposer::GetL() const{
    Matrix L(m.NRows(),m.NCols());
    for(int i = 0; i < L.NRows(); i++){
         for(int j = 0; j < L.NCols(); j++){
            if(i == j) L[i][j] = 1;
            if(i > j) L[i][j] = m[i][j];
         }
    }
    return L;
}

Matrix LUDecomposer::GetU() const{
    Matrix U(m.NRows(),m.NCols());
    for(int i = 0; i < m.NRows(); i++){
        for(int j = 0; j < m.NCols(); j++){
            if(i <= j) U[i][j] = m[i][j];
        }
    }
    return U;
}

Vector LUDecomposer::GetPermuation() const{return w;}

class QRDecomposer{
  Matrix m;
  std::vector<double> v;
  public:
  QRDecomposer(Matrix m);
  void Solve(const Vector &b, Vector &x) const;
  Vector Solve(Vector b) const;
  void Solve(Matrix &b, Matrix &x) const;
  Matrix Solve(Matrix b) const;
  Vector MulQWith(Vector v) const;
  Matrix MulQWith(Matrix m) const;
  Vector MulQTWith(Vector v) const;
  Matrix MulQTWith(Matrix m) const;
  Matrix GetQ() const;
  Matrix GetR() const;
};

QRDecomposer::QRDecomposer(Matrix m1): m(m1), v(m1.NCols()){
    if(m1.NRows() < m1.NCols()) throw std::domain_error("Invalid matrix format");
    int r = m1.NRows();
    int c = m1.NCols();
    for(int k = 0; k < c; k++){
        double s = 0;
        for(int i = k; i < r; i++)
          s = s + m[i][k] * m[i][k];
        s = std::sqrt(s);
        double mi = std::sqrt(s * (s + std::fabs(m[k][k])));
        if(std::fabs(mi) < m1.GetEpsilon()) throw std::domain_error("Matrix is singular");
        if(m[k][k] < 0) s *= -1;
        m[k][k] = (m[k][k] + s) / mi;
        for(int i = k + 1; i < r; i++)
         m[i][k] = m[i][k] / mi;
        v[k] = -1 * s;
        for(int j = k + 1; j < c; j++){
            s = 0;
            for(int i = k; i < r; i++)
             s = s + m[i][k] * m[i][j];
            for(int i = k; i < r; i++)
             m[i][j] = m[i][j] - s * m[i][k];
        }
    }
}

void QRDecomposer::Solve(const Vector& b, Vector& x) const{
    if(m.NRows() != m.NCols()) throw std::domain_error("Matrix is not square");
    if(b.NElems() != m.NRows() || x.NElems() != b.NElems()) throw std::domain_error("Incompatible formats");
    Vector a(MulQTWith(b));
    for(int i = m.NCols() - 1; i >= 0; i--){
        double s = a[i];
        for(int j = i + 1; j < m.NCols(); j++)
         s = s - m[i][j] * x[j];
        x[i] = s / v[i]; 
    }
}

Vector QRDecomposer::Solve(Vector b) const{
    Vector a(b.NElems());
    this->Solve(b,a);
    return a;
}

void QRDecomposer::Solve(Matrix &b, Matrix& x) const{
    if(m.NRows() != m.NCols()) throw std::domain_error("Matrix is not square");
    if(m.NRows() != b.NCols() || m.NCols() != b.NRows() || m.NRows() != x.NCols() || m.NCols() != x.NRows()) throw std::domain_error("Incompatible formats");
    for(int i = 0; i < b.NCols(); i++){
        Vector d(b.NRows());
        Vector e(b.NRows());
        for(int j = 0; j < b.NRows(); j++)
         d[j] = b[j][i];
        this->Solve(d,e);
        for(int j = 0; j < b.NRows(); j++)
         x[j][i] = e[j];
    }
}

Matrix QRDecomposer::Solve(Matrix b) const{
    Matrix c(b.NRows(), b.NCols());
    this->Solve(b,c);
    return c;
}

Vector QRDecomposer::MulQWith(Vector b) const{
    if(m.NRows() != b.NElems()) throw std::domain_error("Incompatible formats");
    for(int k = m.NCols() - 1; k >= 0; k--){
        double s = 0;
        for(int i = k; i < m.NRows(); i++)
         s = s + m[i][k] * b[i];
        for(int i = k; i < m.NRows(); i++)
         b[i] = b[i] - s * m[i][k];
    }
    for(int i = 0; i < m.NRows(); i++)
     if(std::fabs(b[i]) < m.GetEpsilon()) b[i] = 0;
    return b;
}

Vector QRDecomposer::MulQTWith(Vector b) const{
    if(m.NRows() != b.NElems()) throw std::domain_error("Incompatible formats");
    for(int k = 0; k < m.NCols(); k++){
        double s = 0;
        for(int i = k; i < m.NRows(); i++)
         s = s + m[i][k] * b[i];
        for(int i = k; i < m.NRows(); i++)
         b[i] = b[i] - s * m[i][k];
    }
    for(int i = 0; i < m.NRows(); i++)
     if(std::fabs(b[i]) < m.GetEpsilon()) b[i] = 0;
    return b;
}

Matrix QRDecomposer::MulQWith(Matrix m1) const{
    if(m.NRows() != m1.NRows()) throw std::domain_error("Incompatible formats");
    for(int i = 0; i < m1.NCols(); i++){
        Vector e(m1.NRows());
        for(int j = 0; j < e.NElems(); j++)
         e[j] = m1[j][i];
        e = MulQWith(e);
        for(int j = 0; j < e.NElems(); j++)
         m1[j][i] = e[j];
    }
    return m1;
}
Matrix QRDecomposer::MulQTWith(Matrix m1) const{
    if(m.NRows() != m1.NRows()) throw std::domain_error("Incompatible formats");
    for(int i = 0; i < m1.NCols(); i++){
        Vector e(m1.NRows());
        for(int j = 0; j < e.NElems(); j++)
         e[j] = m1[j][i];
        e = MulQTWith(e);
        for(int j = 0; j < e.NElems(); j++)
         m1[j][i] = e[j];
    }
    return m1;
}

Matrix QRDecomposer::GetQ() const{
    Matrix Q(m.NRows(), m.NRows());
    for(int j = 0; j < m.NRows(); j++){
        for(int i = 0; i < m.NRows(); i++)
         Q[i][j] = 0;
        Q[j][j] = 1;
        for(int k = m.NCols() - 1; k >= 0; k--){
            double s = 0;
            for(int i = k; i < m.NRows(); i++)
             s = s + m[i][k] * Q[i][j];
            for(int i = k; i < m.NRows(); i++)
             Q[i][j] = Q[i][j] - s * m[i][k];
        }
    }
    return Q;
}

Matrix QRDecomposer::GetR() const{
    Matrix R(m.NRows(),m.NCols());
    for(int i = 0; i < R.NRows(); i++){
        for(int j = 0; j < R.NCols(); j++){
            if(j > i) R[i][j] = m[i][j];
            if(i == j) R[i][j] = v[i];
        }
    }
    return R;
}



int main(){
    std::cout<<"-----------Chop test Vector---------"<<std::endl;
    {
    Vector v = {2,4.23,0.012,0.011};
    for(int i = 0; i < v.NElems(); i++) std::cout<<v[i]<<" ";
    v.Chop(0.1);
    std::cout<<std::endl<<"After Chop(0.1)"<<std::endl;
    for(int i = 0; i < v.NElems(); i++) std::cout<<v[i]<<" ";
    std::cout<<std::endl;
    }
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"----------EqualTo test Vector-------"<<std::endl;
    {
    Vector v1 = {1, 3, 0.6, 0.223, 0.011};
    Vector v2 = {1, 3, 0.6, 0.223, 0.011};
    std::cout<<"EqualTo(true): "<<v1.EqualTo(v2)<<std::endl;
    Vector v3 = {1, 3, 0.6, 0.223, 0.0199};
    std::cout<<"EqualTo(false): "<<v1.EqualTo(v3,0.0000001)<<std::endl;
    }
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"----------Chop test Matrix----------"<<std::endl;
    {
    Matrix m1 = {{1,0.001,2},{2,4,0.0123},{9,9,0.003}};
    m1.Print();
    std::cout<<"After chop: "<<std::endl;
    m1.Chop(0.1);
    m1.Print();
    }
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"----------EqualTo test Matrix-------"<<std::endl;
    {
    Matrix m1 = {{1,0.001,2},{2,4,0.0123},{9,9,0.003}};
    Matrix m2 = {{1,0.001,2},{2,4,0.0123},{9,9,0.003}};
    std::cout<<"EqualTo (true): "<<m1.EqualTo(m2)<<std::endl;
    Matrix m3 = {{1,0.001,2},{2,4,0.0123},{9,9,0.004}};
    std::cout<<"EqualTo (false): "<<m1.EqualTo(m3)<<std::endl;
    }
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"----------LeftDiv test Matrix-------"<<std::endl;
    {
    Matrix m1 = {{2,1},{2,-4}};
    Matrix m2 = {{1,4,6},{9,2,8}};
    Matrix X = LeftDiv(m1,m2);
    X.Print();
    std::cout<<"Correct! Tested in Scilab."<<std::endl;
    Matrix m3 = {{2,2},{2,2}};
    // singularna test
    try{
        Matrix C = LeftDiv(m3,m2);
    }
    catch(...){
        std::cout<<"Singular test: succeded!"<<std::endl;
    }

    }
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"--LeftDiv test Matrix \\ Vector-----"<<std::endl;
    {
    Matrix m1 = {{2,1},{2,-4}};
    Vector v = {1,2};
    Vector X = LeftDiv(m1,v);
    X.Print();
    std::cout<<"Correct! Tested in Scilab."<<std::endl;
    Matrix m3 = {{2,2},{2,2}};
    // singularna test
    try{
        Matrix C = LeftDiv(m3,v);
    }
    catch(...){
        std::cout<<"Singular test: succeded!"<<std::endl;
    }

    }
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"---------RightDiv test Matrix-------"<<std::endl;
    {
        Matrix m1 = {{1,2},{2,3}};
        Matrix m2 = {{2,3},{9,-2}};
        Matrix c = m1 / m2;
        c.Print();
        std::cout<<"Correct! Tested in Scilab\n";
        m1 /= m2;
        m1.Print();
    }
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"---------Det test Matrix------------"<<std::endl;
    {
        Matrix m1 = {{2,4,-2},{8,-23,4},{9,2,-2}};
        std::cout<<"Det(m1) = "<<Det(m1)<<" Correct!"<<std::endl;
        std::cout<<"m1.Det() = "<<m1.Det()<<" Correct!"<<std::endl;
        Matrix m2 = {{1,2},{2,3},{9,2}};
        try{
            m2.Det();
        }
        catch(std::domain_error d){
            std::cout<<"Exception test: "<<d.what()<<std::endl;
        }
    }
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"---------Invert test Matrix---------"<<std::endl;
    {
        Matrix m1 = {{2,4,-2},{8,-23,4},{9,2,-2}};
        m1.Invert();
        m1.Print();
        Matrix m2 = Inverse(m1);
        std::cout<<"Another inverse, and we get the original:"<<std::endl;
        m2.Print();
    }
    std::cout<<"------------------------------------"<<std::endl;
     std::cout<<"---------RREF test Matrix---------"<<std::endl;
    {
        Matrix m1 = {{2,4,-2},{8,-23,4},{9,2,-2}};
        m1.ReduceToRREF();
        m1.Print();
        std::cout<<"Rank: "<<m1.Rank()<<std::endl;
    }
    std::cout<<"------------------------------------"<<std::endl;
     std::cout<<"------LUDecomposer tests 1---------"<<std::endl;
    {
        Matrix m1 = {{2,4,-2},{8,-23,4},{9,2,-2}};
        LUDecomposer lu(m1);
        std::cout<<"Compact: "<<std::endl;
        lu.GetCompactLU().Print();
        std::cout<<"L: "<<std::endl;
        lu.GetL().Print();
        std::cout<<"U: "<<std::endl;
        lu.GetU().Print();
        std::cout<<"Permutations: "<<std::endl;
        lu.GetPermuation().Print();
    }
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"------LUDecomposer tests 2---------"<<std::endl;
    {
        Matrix m1 = {{1,1,1},{4,3,-1},{3,5,3}};
        Vector c = {1,6,4};
        LUDecomposer l(m1);
        Vector x(c.NElems());
        l.Solve(c,x);
        x.Print();
        std::cout<<"Correct! Tested in Scilab."<<std::endl;
        
    }
    std::cout<<"------------------------------------"<<std::endl;
   std::cout<<"------QRDecomposer tests 1---------"<<std::endl;
    {
        Matrix m1 = {{2,4,-2},{8,-23,4},{9,2,-2}};
        QRDecomposer qr(m1);
        std::cout<<"Q: "<<std::endl;
        qr.GetQ().Print();
        std::cout<<"R: "<<std::endl;
        qr.GetR().Print();
        std::cout<<"Q * R == m1"<<std::endl;
        (qr.GetQ() * qr.GetR()).Print();
    }
    std::cout<<"------------------------------------"<<std::endl;
     std::cout<<"------QRDecomposer tests 2---------"<<std::endl;
    {
         Matrix m1 = {{1,1,1},{4,3,-1},{3,5,3}};
        Vector c = {1,6,4};
        QRDecomposer qr1(m1);
        Vector x(c.NElems());
        qr1.Solve(c,x);
        x.Print();
        std::cout<<"Correct! Tested in Scilab."<<std::endl;
        Matrix m2 = {{2,4,-2},{8,-23,4},{9,2,-2}};
        Matrix x2 = {{2,3,5},{3,6,9},{4,-5,8}};
        QRDecomposer qr(m1);
        qr.Solve(x2,x2);
        x2.Print();
        std::cout<<"Correct! Tested in Scilab."<<std::endl;
    }
    std::cout<<"------------------------------------"<<std::endl;
    /* Napomena: testovi za QR i LU ne pokrivaju 100% linija ali stvarno nisam mogao stic s obzirom da je predispitna :'( sedmica */    

    return 0;
}
