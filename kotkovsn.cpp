#include "kotkovsn.h"

/**
 * �������� � ����������
 */
void kotkovsn::lab1()
{
  cout << "hello world!" << endl;
}


/**
 * ����� ������ � ������� �������� ��������
 */
void kotkovsn::lab2()
{
    const double eps = 1e-12;
    for (int i = 0; i < N; i++)
    {
      if (fabs(A[i][i]) < eps)
        for (int j = i + 1; j < N; j++)
        {
          if (fabs(A[j][i]) > eps)
          {
            double *tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;

            double temp = b[i];
            b[i] = b[j];
            b[j] = temp;
            break;
          }
        }

      if (fabs(A[i][i] - 1) > eps)
      {
        for (int j = i + 1; j < N; j++)
          A[i][j] /= A[i][i];
        b[i] /= A[i][i];
        A[i][i] = 1;
      }

      for (int j = 0; j < i; j++)
      {
        for (int k = i + 1; k < N; k++)
          A[j][k] -= A[i][k] * A[j][i];
        b[j] -= b[i] * A[j][i];
        A[j][i] = 0; 
      }

     for (int j = i + 1; j < N; j++)
      {
        for (int k = i + 1; k < N; k++)
          A[j][k] -= A[i][k] * A[j][i];
        b[j] -= b[i] * A[j][i];
        A[j][i] = 0; 
      }
    }

    for (int i = 0; i < N; i++)
      x[i] = b[i];
}


 
/**
 * ����� ��������
 */
void kotkovsn::lab3()
{
  double *alpha = new double[N];
  double *beta = new double[N];

  alpha[0] = A[0][1] / A[0][0];
  beta[0] = b[0] / A[0][0];

  for (int i = 1; i < N; i++)
  {
    alpha[i] = A[i][i + 1] / (A[i][i] - A[i][i - 1] * alpha[i - 1]);
    beta[i] = (b[i] - A[i][i - 1] * beta[i - 1]) / (A[i][i] - A[i][i - 1] * alpha[i - 1]);
  }

  x[N - 1] = beta[N - 1];

  for (int i = N - 2; i >= 0; i--)
    x[i] = beta[i] - alpha[i] * x[i + 1];

  delete []alpha;
  delete []beta;
}



/**
 * ����� ���������
 */
void kotkovsn::lab4()
{
  double **S = new double*[N];
  double **D = new double*[N];
  for (int i = 0; i < N; i++)
  {
    S[i] = new double[N];
    memset(S[i], 0, sizeof(double) * N);
    D[i] = new double[N];
    memset(D[i], 0, sizeof(double) * N);
  }
 
  for (int i = 0; i < N; i++)
  {
    double tmp = A[i][i];
    for (int k = 0; k <= i - 1; k++)
      tmp -= D[k][k] * S[k][i] * S[k][i];

    if (tmp > 0)   D[i][i] = 1;
    else           D[i][i] = -1;

    S[i][i] = sqrt(D[i][i] * tmp);

    for (int j = i + 1; j < N; j++)
    {
      double sum = 0;
      for (int k = 0; k <= j - 1; k++)
        sum += D[k][k] * S[k][i] * S[k][j];
      S[i][j] = (A[i][j] - sum) / (D[i][i] * S[i][i]);
    }
  }
  
  double *y = new double[N];
  for (int i = 0; i < N; i++)
  {
    b[i] /= S[i][i];
    y[i] = b[i];
    for (int j = i + 1; j < N; j++)
      b[j] -= b[i] * S[i][j];
  }

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      S[i][j] *= D[i][i];

  for (int i = N - 1; i >= 0; i--)
  {
    y[i] /= S[i][i];
    x[i] = y[i];
    for (int j = i - 1; j >= 0; j--)
      y[j] -= y[i] * S[j][i];
  }

  delete []y;

  for (int i = 0; i < N; i++)
  {
    delete []S[i];
    delete []D[i];
  }

  delete []S;
  delete []D;
}



/**
 * ����� ����� ��� �������
 */
void kotkovsn::lab5()
{
  const double eps = 1e-18;
  double *z = new double[N];

  for (int k = 0; k < N; k++)
  {
    double y = 0;
    for (int i = 0; i < N; i++)
      y += A[k][i] * x[i];
    z[k] = b[k] - y;
  }

  double zNorm = 0;

  for (int k = 0; k < N; k++)
    zNorm += z[k] * z[k];
    
  while (zNorm > eps * eps)
  {
    for (int k = 0; k < N; k++)
    {
      double sum1 = 0;
      double sum2 = 0;
      for (int j = 0; j < k; j++)
        sum1 += A[k][j] * x[j];

      for (int j = k + 1; j < N; j++)
        sum2 += A[k][j] * x[j];
      
      x[k] = (b[k] - sum1 - sum2) / A[k][k];
    }

    for (int k = 0; k < N; k++)
    {
      double y = 0;
      for (int i = 0; i < N; i++)
        y += A[k][i] * x[i];
      z[k] = b[k] - y;
    }

    zNorm = 0;

    for (int k = 0; k < N; k++)
      zNorm += z[k] * z[k];
  }
  
  delete []z;
}



/**
 * ����� ����������� �������
 */
void kotkovsn::lab6()
{

}



/**
 * ����� ����������� ����������
 */
void kotkovsn::lab7()
{

}


void kotkovsn::lab8()
{

}


void kotkovsn::lab9()
{

}


std::string kotkovsn::get_name()
{
  return "Kotkov S.N.";
}
