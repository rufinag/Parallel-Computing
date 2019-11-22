//PDC assignment main body

#include <iostream>
#include <omp.h>
#include <vector>
#include "parallel.h"
#include "sequential.h"

using namespace std;

main()
{
    int n,m;
    double x;
    cout << "Enter no. of rows n: ";
    cin >> n;
    cout << "Enter no. of columns m: ";
    cin >> m;

    vector<vector<double>> a(n);
    vector<vector<double>> b(m);
    vector<double> avg(m);
    
    cout << "Enter scaling factor: ";
    cin >> x;
    //cout << "Enter " << m*n << " elements: ";
    cout << "Computing matrix elements" << endl;

    for(int i=0;i<n;i++)
    {
        a[i] = vector<double>(m);
        for(int j=0;j<m;j++)
        {
            //cin >> a[i][j];
            a[i][j] = (i+j)*x;
        }
    }

    cout << "Generated matrix: " << endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0; j<a[i].size() ;j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    //Parallel execution
    double timer_start = omp_get_wtime();
    avg = mean(a);
    b = covariance(a,avg);
    double time_parallel = omp_get_wtime() - timer_start;
    cout << "Parallel time elapsed: " << time_parallel << endl;

    cout << "Mean vector:" << endl;
    for(int i=0; i<avg.size();i++)
    {
        cout << avg[i] << " ";
    }
    cout << endl;

    cout << "Covariance matrix using parallel execution: " << endl;
    for(int i=0;i<m;i++)
    {
        for(int j=0; j<b[i].size() ;j++)
        {
            cout << b[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Max number of threads used: " << omp_get_max_threads() << endl;

    //Sequential execution
    timer_start = omp_get_wtime();
    avg = mean_seq(a);
    b = covariance_seq(a,avg);
    double time_seq = omp_get_wtime() - timer_start;
    cout << "Sequential time elapsed: " << time_seq << endl;

    cout << "Covariance matrix using sequential execution: " << endl;
    for(int i=0;i<m;i++)
    {
        for(int j=0; j<b[i].size() ;j++)
        {
            cout << b[i][j] << " ";
        }
        cout << endl;
    }

    double speedup;
    speedup = time_seq / time_parallel;

    cout << "Speedup: " << speedup << endl;

    system("pause");
}