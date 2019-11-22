//Sequential header

#include <omp.h>
#include <vector>

using namespace std;

//Find the mean of an mxn matrix column-wise
vector<double> mean_seq(vector<vector<double>> &mat)
{
    vector<double> avg(mat[0].size(),0); //default value of vector is 0
    
    for(int i=0; i<mat.size(); i++)
    {
        for(int j=0; j<mat[0].size(); j++)
        {
            avg[j] += mat[i][j];
        }
    }

    for(int i=0;i<avg.size();i++)
    {
        avg[i] /= mat.size();
    }

    return avg;
}

//Find the sum of two mxn matrices
vector<vector<double>> add_seq(vector<vector<double>> &a, vector<vector<double>> &b)
{
    vector<vector<double>> res(a.size(), vector<double>(a[0].size(),0));
    if((a.size()!=b.size())||(a[0].size()!=b[0].size()))
    {
        return res;
    }

    for(int i=0; i<a.size(); i++)
    {
        for(int j=0; j<a[0].size(); j++)
        {
            res[i][j] = a[i][j] + b[i][j];
        }
    }
    
    return res;
}

//Find the product of an mx1 vector and a 1xm vector
vector<vector<double>> mult_seq(vector<double> &p, vector<double> &q)
{
    vector<vector<double>> res(p.size(),vector<double>(q.size(),0));
    
    if(p.size() != q.size())
    {
        return res;
    }

    for(int i=0; i<p.size(); i++)
    {
        for(int j=0; j<p.size(); j++)
        {
            res[i][j] = p[i] * q[j];
        }
    }

    return res;
}

//Find the covariance of a matrix
vector<vector<double>> covariance_seq(vector<vector<double>> &mat, vector<double> &avg)
{
    vector<vector<double>> res(avg.size(), vector<double>(avg.size(),0));
    vector<vector<double>> prod(avg.size(), vector<double>(avg.size(),0));
    vector<double> diff(avg.size(),0);
    int N = mat.size();
  
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<avg.size(); j++)
        {
            diff[j] = mat[i][j] - avg[j];
        }
        
        prod = mult_seq(diff,diff);
        res = add_seq(res,prod);
    }
    
    for(int i=0; i<res.size(); i++) 
    {
        for(int j=0; j<res[0].size(); j++)
        {
            res[i][j] = res[i][j] / N;
        }
    }
    
    return res;
}

//Finding the determinant of a matrix
/*double det(vector<vector<double>> &mat)
{
    double res;
    
}*/