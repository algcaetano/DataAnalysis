#include <iostream>
#include <vector>
#include<fstream>

using namespace std;

//functions declarations
double prior(const double& pdf);
double likeHood(const double& H, const int& N, const int& R);
double power(const double& base, const int& exp);
void post(std::vector<double>& post, const vector<double>& prior, const std::vector<double>& bias, const int& N, const int& R);
double findMax(const std::vector<double>& input);

int main()
{
    //is this a fair coin?

    int numH = 1001; //number of divisions on H
    double dp = 1.0/(numH-1); //increment on H
    std::vector<double> H(numH); //vector of H
    for (int i = 0; i < numH; i++)
    {
        H[i] = i*dp;
    }
    std::vector<double> prior(numH, 1.0); //a priori distribution
    std::vector<double> posterior(numH, 0.0); //posteriori distribution

    int N = 100; //number of throws
    int R = 70; //number of heads
    post(posterior, prior, H, N, R); //calculation os posteriori

    ofstream myfile;
    myfile.open ("posteriori.txt");
    for (unsigned int i = 0; i < posterior.size(); i++)
    {
        myfile << H[i] << " " << posterior[i] << "\n";
    }
    myfile.close();

    return 0;
}

double prior(const double& pdf)
{
    return (pdf>=0 && pdf<=1)?1:0;
}

double likeHood(const double& H, const int& N, const int& R)
{
    return power(H,R)*power((1-H),(N-R));
}

double power(const double& base, const int& exp)
{
    double result = 1;
    for (int i = 0; i < exp; i++)
    {
        result*=base;
    }
    return result;
}

void post(std::vector<double>& post, const vector<double>& prior, const std::vector<double>& H, const int& N, const int& R)
{
    for (unsigned int i = 0; i < H.size(); i++)
    {
        post[i] = prior[i]*likeHood(H[i], N, R);
    }
    double maximum = findMax(post);
    for (unsigned int i = 0; i < post.size(); i++)
    {
        post[i]/=maximum;
    }
}

double findMax(const std::vector<double>& input)
{
    double result = input[0];
    for (unsigned int i = 0; i < input.size(); i++)
    {
        if(input[i]>result)
        {
            result = input[i];
        }
    }
    return result;
}
