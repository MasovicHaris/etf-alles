//NA 2018/2019: Zadaća 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <limits>
class AbstractInterpolator
{
protected:
    std::vector<std::pair<double, double> > tacke;
    mutable int index;
public:
    AbstractInterpolator(const std::vector<std::pair<double, double> > &data)
    {
        index = 1;
        tacke = data;
        std::sort(tacke.begin(), tacke.end(), [](std::pair<double,double> t1, std::pair<double,double> t2) {
            return t1.first < t2.first;
        });
        for(int i = 0; i < tacke.size() - 1; i++) {
            if(std::fabs(tacke[i].first - tacke[i + 1].first) < std::numeric_limits<double>::epsilon())
                throw std::domain_error("Invalid data set");
        }
    }
    virtual double operator()(double x) const = 0;
protected:
    int Locate(double x) const
    {
        if(x <= tacke[0].first) return 0;
        if(x > tacke[tacke.size() - 1].first) return tacke.size();
        if(tacke[index - 1].first <= x && x < tacke[index].first) return index;
        std::pair<double,double> trazi(x,0);
        auto i = std::lower_bound(tacke.begin(), tacke.end(), trazi, [](std::pair<double,double> t1, std::pair<double,double> t2) -> bool {
            return t1.first < t2.first;
        });
        index = i - tacke.begin();
        return index;
    }
};

class LinearInterpolator: public AbstractInterpolator
{
    double povuciLiniju(std::pair<double,double> t1, std::pair<double,double> t2, double x) const
    {
        return ((t2.first - x) / (t2.first - t1.first)) * t1.second + ((x - t1.first) / (t2.first - t1.first)) * t2.second;
    }
public:
    LinearInterpolator(const std::vector<std::pair<double, double>> &data): AbstractInterpolator(data) {}
    double operator()(double x) const override
    {
        int i = Locate(x);
        if(i <= 1) {
            return povuciLiniju(tacke[0],tacke[1],x);
        } else if(i >= tacke.size()) {
            return povuciLiniju(tacke[tacke.size() - 2], tacke[tacke.size() - 1], x);
        } else return povuciLiniju(tacke[i - 1], tacke[i], x);
    }

};

class PolynomialInterpolator: public AbstractInterpolator
{
    std::vector<double> q;
public:
    PolynomialInterpolator(const std::vector<std::pair<double, double>> &data): AbstractInterpolator(data)
    {
        q.resize(tacke.size());
        q[0] = tacke[tacke.size() - 1].second;
        for(int j = 1; j < q.size(); j++) {
            for(int i = q.size(); i >= j + 1; i--) {
                tacke[i - 1].second = (tacke[i - 1].second - tacke[i - 2].second) / (tacke[i - 1].first - tacke[i - j - 1].first);
            }
            q[j] = tacke[tacke.size() - 1].second;
        }
    }
    double operator()(double x) const override{
        double s = tacke[0].second;
        double f = 1;
        for(int j = 1; j < tacke.size(); j++){
            f *= (x - tacke[j - 1].first);
            s += f * tacke[j].second;
        }
        return s;
    }
    void AddPoint(const std::pair<double, double> &p){
        for(int i = 0; i < tacke.size(); i++)
         if(std::fabs(tacke[i].first - p.first) < std::numeric_limits<double>::epsilon())
          throw std::domain_error("Invalid point");
        tacke.emplace_back(p);
        q.resize(tacke.size());
        double t;
        for(int i = 1; i < tacke.size(); i++){
            t = q[i - 1];
            q[i - 1] = tacke[tacke.size() - 1].second;
            tacke[tacke.size() - 1].second = (tacke[tacke.size() - 1].second - t) / (tacke[tacke.size() - 1].first - tacke[tacke.size() - i - 1].first);
        }
        q[q.size() - 1] = tacke[tacke.size() - 1].second;
    }
    std::vector<double> GetCoefficients() const{
        std::vector<double> w(tacke.size() + 1);
        std::vector<double> p(w.size());
        w[0] = 1;
        for(int i = 1; i <= tacke.size(); i++){
            for(int j = 0; j <= i; j++)
             p[j] += tacke[i - 1].second * w[j];
            w[i] = w[i - 1];
            for(int j = i - 1; j > 0; j--)
             w[j] = w[j - 1] - tacke[i - 1].first * w[j];
            w[0] *= (-1) * tacke[i - 1].first; 
        }
        p.resize(p.size() - 1);
        return p;
    }
};

class PiecewisePolynomialInterpolator: public AbstractInterpolator{
  int k;
  public:
  PiecewisePolynomialInterpolator(const std::vector<std::pair<double, double>> &data, int order): AbstractInterpolator(data){
      if(order < 1 || order > data.size()) throw std::domain_error("Invalid order");
      k = order;
  }
  double operator()(double x) const override{
      int i = Locate(x);
      int j;
      int n;
      if(k % 2 == 0){
          j = i - k / 2 - 1;
          n = i + k / 2;
      }
      else{
          j = i - (k - 1) / 2 - 1;
          n = i + (k + 1) / 2;
      }
      if(n >= tacke.size()){
          j = tacke.size() - k - 1;
          n = tacke.size();
      }
      if(j <= 0){
          j = 0;
          n = k + 1;
      }
      double s = 0;
      for(int p = j; p < n; p++){
          double v = tacke[p].second;
          for(int r = j; r < n; r++)
           if(p != r) v *= (x - tacke[r].first) / (tacke[p].first - tacke[r].first);
          s += v; 
      }
      return s;
  }
};

class SplineInterpolator: public AbstractInterpolator{
  std::vector<double> v1;
  std::vector<double> v2;
  std::vector<double> v3;
  public:
  SplineInterpolator(const std::vector<std::pair<double, double>> &data): AbstractInterpolator(data){
      v1.resize(tacke.size());
      v2.resize(v1.size());
      v3.resize(v1.size());
      v1[0] = 0;
      v1[v1.size() - 1] = 0;
      for(int i = 1; i < v1.size() - 1; i++){
          v2[i] = 2 * (tacke[i + 1].first - tacke[i - 1].first);
          v1[i] = 3 * ((tacke[i + 1].second - tacke[i].second) / (tacke[i + 1].first - tacke[i].first) - (tacke[i].second - tacke[i - 1].second) / (tacke[i].first - tacke[i - 1].first));
      }
      double mi;
      for(int i = 1; i < v1.size() - 2; i++){
          mi = (tacke[i + 1].first - tacke[i].first) / v2[i];
          v2[i + 1] -= mi * (tacke[i+1].first - tacke[i].first);
          v1[i + 1] -= mi * v1[i];
      }
      v1[v1.size() - 2] /= v2[v2.size() - 2];
      for(int i = v1.size() - 3; i >= 1; i--)
       v1[i] = (v1[i] - (tacke[i + 1].first - tacke[i].first) * v1[i + 1]) / v2[i];
      double t;
      for(int i = 0; i < v1.size() - 1; i++){
          t = tacke[i + 1].first - tacke[i].first;
          v2[i] = (v1[i + 1] - v1[i]) / (3 * t);
          v3[i] = (tacke[i + 1].second - tacke[i].second) / t - t * (v1[i + 1] + 2 * v1[i]) / 3;
      } 
      
  }
  double operator()(double x) const override{
      int i = Locate(x);
      if(i <= 0) i = 1;
      if(i >= tacke.size()) i = tacke.size() - 1;
      double t = x - tacke[i - 1].first;
      return tacke[i - 1].second + t * (v3[i - 1] + t * (v1[i - 1] + v2[i - 1]*t));
  }
};

class BarycentricInterpolator: public AbstractInterpolator{
    int d;
    std::vector<double> w;
    public:
    BarycentricInterpolator(const std::vector<std::pair<double, double>> &data, int order): AbstractInterpolator(data){
        if(order > tacke.size() || order < 0) throw std::domain_error("Invalid order");
        d = order;
        w.resize(tacke.size());
        double p;
        for(int i = 0; i < w.size(); i++){
            w[i] = 0;
            int m, l;
            if(i - d > 1) m = i - d;
            else m = 1;
            if(i < tacke.size() - d) l = i;
            else l = tacke.size() - d - 1;
            for(int k = m - 1; k < l + 1; k++){
                p = 1;
                for(int j = k; j < k + d; j++)
                 if(j != i) p /= (tacke[i].first - tacke[j].first);
                if(k % 2 == 1) p *= (-1); 
            }
            w[i] += p;
        }
    }
    double operator()(double x) const override{
        double p = 0;
        double q = 0;
        double a;
        for(int i = 0; i < tacke.size(); i++){
            if(std::fabs(x - tacke[i].first) < std::numeric_limits<double>::epsilon()) return tacke[i].second;
        a = w[i] / (x - tacke[i].first);
        p += a * tacke[i].second;
        q += a;
        }
        return p / q;
    }
    std::vector<double> GetWeights() const {return w;}
    
};
/*
class TestAbstractInterpolator : public AbstractInterpolator {
public:
  TestAbstractInterpolator(const std::vector<std::pair<double, double>> &data)
    : AbstractInterpolator(data) {}
  int Locate(double x) const { return AbstractInterpolator::Locate(x); }
  double operator()(double x) const override { return 0; }
};
*/

int main ()
{
    // LinearInteroolator test
    try{
        LinearInterpolator l ({{1,2},{1,2}});
    }
    catch(std::domain_error e){
        std::cout << e.what() << "Dobar!" << std::endl;
    }
    try{
        LinearInterpolator l ({{1,2},{2,4},{3,6},{4,8}});
        std::cout << l(1.5) << " " << l(2.5) << " " << l(3.5) << std::endl;
    }
    catch(...){
        std::cout << "Ne valja!" << std::endl;
    }
    // PolynominialInterpolator test
    try{
        PolynomialInterpolator p({{0,0},{2,4},{6,36},{7,49}});
        std::cout << p(1) << " " << p(3) << " " << p(5) << std::endl;
        p.AddPoint({-2,4});
        p.AddPoint({-3,9});
        std::cout << p(-1) << " " << p(2.5) << std::endl;
        std::vector<double> w = p.GetCoefficients();
        for(auto x: w) std::cout << x << " ";
        std::cout << std::endl;
    }
    catch(...){
        std::cout << "Ne valja!" << std::endl;
    }
    
    // PiecewisePolynomialInterpolator test
    try{
        PiecewisePolynomialInterpolator p({{1,4},{2,8},{3,9},{5,14}},2);
        std::cout << p(4) << " " << p(1.5) << p(2.3) << std::endl;
    }
    catch(...){
        std::cout << "Ne valja!" << std::endl;
    }
    
    //SplineInterpolator test
    try{
        SplineInterpolator s({{0,0},{2,8},{3,27},{6,216}});
        std::cout << s(1) << " " << s(4) << " " << s(5.5) << std::endl;
    }
    catch(...){
                std::cout << "Ne valja!" << std::endl;

    }
    // BarycentricInterpolator test
    try{
        BarycentricInterpolator b({{2,5},{8,8},{4,7},{6,6}},1);
        std::cout << b(3) << " " << b(5) << " " << b(1) << std::endl;
        std::vector<double> w = b.GetWeights();
        for(auto x: w) std::cout << x << " ";
        std::cout << std::endl;
    }
    catch(...){
        std::cout << "Ne valja!" << std::endl;
    }
 
    return 0;
}
