//NA 2019/2020: Zadaća 1, Zadatak 1
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
    void Print(int width = 10, double eps = -1) const
    {
        if(eps == -1) {
            for(int i = 0; i < mat.size(); i++) {
                for(int j = 0; j < mat[0].size(); j++) {
                    if(fabs(mat[i][j] - this->GetEpsilon()) < 0) std::cout<<std::setw(width)<<0;
                    else std::cout<<std::setw(width)<<mat[i][j];
                }
                std::cout<<std::endl;
            }
        } else {
            for(int i = 0; i < mat.size(); i++) {
                for(int j = 0; j < mat[i].size(); j++) {
                    if(fabs(mat[i][j] - eps) < 0 || eps > fabs(mat[i][j])) std::cout<<std::setw(width)<<0;
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
    Matrix c(m1.mat.size(),m2.mat[0].size());
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




int main ()
{
	try{
	 Vector v2(8);
	 Vector v3 = {4,5,7,2,8};
	 v2.Print();
	 v3.Print(',');
	 std::cout<<v3.NElems()<<std::endl;
	 std::cout<<v3[0]<<" "<<v3[2]<<std::endl;
	 std::cout<<v3(1)<<" "<<v3(3)<<std::endl;
	 v3[0] = 7;
	 std::cout<<v3[0]<<std::endl;
	 v3(1) = 77;
	 std::cout<<v3(1)<<std::endl;
	 std::cout<<v3.Norm()<<std::endl;
	 Vector v4 = {5,6,7,8};
	 Vector v5 = {3,4,5,6};
	 (v4 + v5).Print();
	 (v4 - v5).Print();
	 v4 += v5;
	 v4.Print();
	 v4 -= v5;
	 v4.Print();
	 std::cout<<"Skalarni produkt: "<<v4*v5;
	(5 * v3).Print();
	(v3 / 5).Print();
	(v3 * 2).Print();
	v3 /= 2;
	v3.Print();
	v3 *= 3;
	v3.Print('%');
	std::cout<<v3.GetEpsilon()<<std::endl;
	
	// Matrix
	
	Matrix m1(2,2);
	m1.Print();
	Matrix m2 = {{1,2},{3,4}};
	m2.Print();
	std::cout<<m2.NRows()<<" "<<m2.NCols()<<std::endl;
	std::cout<<m2[1][1]<<std::endl;
	m2[1][1] = 88;
	std::cout<<m2[1][1]<<std::endl;
	std::cout<<m2(1,2)<<std::endl;
	std::cout<<m2.Norm()<<std::endl;
	Matrix c = m1 + m2;
	PrintMatrix(c);
	(c - m2).Print();
	c += m2;
	c.Print();
	c -= m2;
	c.Print();
	(4 * c).Print();
	(c * 3).Print();
	c *= 10;
	c.Print();
	Matrix m4 = {{2,3,4},{8,3,4}};
	Matrix m5 = {{3,4},{3,88},{3,2}};
	(m4 * m5).Print();
	m4 *= m5;
	m4.Print();
	Matrix m6 = {{3,4},{9,8},{2,3},{9,1}};
	Vector vek = {1.36,2.22};
	(m6 * vek).Print();
	Matrix mat = {{1,2,3},{1,2,3},{1,2,3}};
	mat.Transpose();
	mat.Print();
	

	}
	catch(std::range_error e){
	   std::cout<<e.what()<<std::endl; 
	}
	catch(std::domain_error d){
	    std::cout<<d.what()<<std::endl;
	}
	catch(std::logic_error l){
	    std::cout<<l.what()<<std::endl;
	}
	
	try{
	   Vector v1(-2);
	   
	}
	catch(std::range_error e){
	   std::cout<<e.what()<<std::endl; 
	}
	try{
	    Vector v = {};
	}
	catch(std::range_error d){
	    std::cout<<d.what();
	}
	try{
	    Vector v(8);
	    v(-1);
	}
	catch(std::range_error d){
	     std::cout<<d.what()<<std::endl;
	}
	try{
	    Vector v = {8,3,4};
	    v /= 0;
	}
	catch(std::domain_error d){
	     std::cout<<d.what()<<std::endl;
	}
	try{
	    Vector v = {8,3,4};
	    Vector v1 = {8,3,4,3};
	    v += v1;
	}
	catch(std::domain_error d){
	     std::cout<<d.what()<<std::endl;
	}
	try{
	    Vector v = {8,3,4};
	    Vector v1 = {8,3,4,3};
	    v -= v1;
	}
	catch(std::domain_error d){
	     std::cout<<d.what()<<std::endl;
	}
	try{
	    Matrix m(-1,2);
	}
	catch(std::range_error d){
	     std::cout<<d.what()<<std::endl;
	}
	try{
	    Matrix m = {{}};
	}
	catch(std::range_error d){
	     std::cout<<d.what()<<std::endl;
	}
	try{
	    Matrix m ={{2,3},{2,4}};
	    Matrix m2 = {{1},{2}};
	    m += m2;
	}
	catch(std::domain_error d){
	     std::cout<<d.what()<<std::endl;
	}
	try{
	    Matrix m ={{2,3},{2,4}};
	    Matrix m2 = {{1},{2}};
	    m -= m2;
	}
	catch(std::domain_error d){
	     std::cout<<d.what()<<std::endl;
	}
	try{
	    Matrix m ={{2,3},{2,4}};
	    Matrix m2 = {{1},{2}};
	    m *= m2;
	}
	catch(std::domain_error d){
	     std::cout<<d.what()<<std::endl;
	}
	try{
	    Matrix m ={{2,3},{2,4}};
	    Matrix m2 = {{1},{2}};
	    m = m * m2;
	}
	catch(std::domain_error d){
	     std::cout<<d.what()<<std::endl;
	}
	try{
	    Matrix m ={{2,3},{2,4}};
	    Vector v = {2,4,5,9};
	    auto p = m * v;
	}
	catch(std::domain_error d){
	     std::cout<<d.what()<<std::endl;
	}
	

}
