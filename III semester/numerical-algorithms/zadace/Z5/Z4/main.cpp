//NA 2017/2018: Zadaća 5, Zadatak 4
#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <complex>

bool stepenDvojke(int x){
    double y = std::log(x)/std::log(2);
    return std::fabs(y - (int)y) < 1e-8;
}

void FFT(std::vector<double>& x, std::vector<std::complex<double>>& xline, int N,int s=0, int d=0,int t=1){
    if(N==1){
        xline.at(d) = x.at(s);
    }else{
        FFT(x,xline,N/2,s,d,2*t);
        FFT(x,xline,N/2,s+t,d+N/2,2*t);
        
        std::complex<double> mi = 1;
        std::complex<double> w = {std::cos(2*4*std::atan(1)/N),-std::sin(2*4*std::atan(1)/N)};
        std::complex<double> u,v;
        for(int k = d; k<= d + N/2-1; k++){
            u = xline.at(k);
            v = mi * xline.at(k+N/2);
            xline.at(k) = u + v;
            xline.at(k + N/2) = u - v;
            mi = mi*w;
        }
    }
}
void InvFFT(std::vector<std::complex<double>>& xline, std::vector<std::complex<double>>& x, int N, int s=0, int d=0, int t=1){
    if(N==1){
        x.at(d) = xline.at(s);
    }else{
        InvFFT(xline,x,N/2,s,d,2*t);
        InvFFT(xline,x,N/2,s+t,d+N/2,2*t);
        
        std::complex<double> mi = 1.;
        std::complex<double> w = std::polar(1.,(2*4*std::atan(1))/N);
        std::complex<double> u,v;
        
        for(int k=d;k<=d+N/2-1;k++){
            u = x.at(k);
            v = mi * x.at(k+N/2);
            x.at(k) = (u+v)/2.;
            x.at(k+N/2) = (u-v)/2.;
            mi = mi*w;
        }
    }
}

std::vector<double> LossyCompress(std::vector<double> data, int new_size){
    if(!(new_size>1 && new_size<=data.size())){
        throw std::range_error("Bad new size");
    }
    
    int N = data.size();
    
    if(!stepenDvojke(N)){
        throw std::range_error("Data size must be a power of two");
    }
    
    std::vector<double> y(N);
    
    for(int i=0;i<N;i++){
        if(i<N/2){
            y.at(i) = data.at(2*i);
        }else{
            y.at(i) = data.at(2*(N-i)-1);
        }
    }
    
    std::vector<std::complex<double>> yline(N);
    
    FFT(y,yline,N);
    
    std::vector<double> xline(new_size);
    
    for(int k=0;k<new_size-1;k++){
        xline.at(k) = std::real(std::polar(1.,-(4*atan(1)*k)/(2*N))*yline.at(k));
    }
    
    xline.at(new_size-1) = N;
    return xline;
    
    ;
}

std::vector<double> LossyDecompress(std::vector<double> compressed){
    int N = compressed.at(compressed.size()-1);
    compressed.at(compressed.size()-1) = 0;
    
    if(!stepenDvojke(N) || N<compressed.size()){
        throw std::logic_error("Bad compressed sequence");
    }
    
    compressed.resize(N);
    
    std::vector<std::complex<double>> yline(N);
    
    yline.at(0) = compressed.at(0);
    
    for(int k=1; k<N; k++){
        yline.at(k) = 2. * std::polar(1., (4*std::atan(1)*k)/(2*N)) * compressed.at(k);
    }
    
    std::vector<std::complex<double>> y(N);
    
    InvFFT(yline,y,N);
    
    std::vector<double> x(N);
    
    for(int n=0;n<N;n++){
        if(n%2==0){
            x.at(n) = std::real(y.at(n/2));
        }else{
            x.at(n) = std::real(y.at(N - (n+1)/2));
        }
    }
    
    return x;
}

int main ()
{
   
	return 0;
}