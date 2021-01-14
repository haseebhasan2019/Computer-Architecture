/* 
 * 
 * This code calculates the house price of a house by learing from
 * training data. It uses pseudo inverse of a given matrix to find the 
 * weight of different features.
 * 
 * Predicted Price : Y = W0 + W1*x1 + W2*X2 + W3*X3 + W4*X4
 * Weight Matrix : W = pseudoInv(X)*Y
 * pseudoInv(X) = inverse(transpose(X)*X) * transpose(X)  
 * 
 * weight(w) = pseudoInv(X) * Y
 * 			where	X = Input data matrix
 * 					Y = Target vector
 * 
 */
 
#include<stdio.h>
#include<stdlib.h>

// all methods declarations
double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2);
double** transposeMatrix(double** mat, int row, int col);
double** inverseMatrix(double **matA, int dimension);
void printMatrix(double** mat, int rows, int cols);
void freeMatrix(double** mat, int rows);
double ** allocateMatrix(int rows, int columns);

// main method starts here
int main(int argc, char** argv)
{
    FILE * train = fopen (argv[1], "r");
    int attributes;
    int houses;
    fscanf(train, "%d\n%d", &attributes, &houses);

    //Create matrix X  
    double** matX = malloc(houses * sizeof(double*));
    for (int i = 0; i < houses; i++)
        matX[i] = malloc((attributes+1) * sizeof(double));
    
    //Create matrix Y
    double** matY = malloc(houses * sizeof(double*));
    for (int i = 0; i < houses; i++)
        matY[i] = malloc(sizeof(double));
    
    //Filling Matrices X & Y
    for (int i = 0; i < houses; i++)
    {
        for (int j = 0; j < attributes; j++)
            fscanf(train, "%lf,", &matX[i][j+1]);
        fscanf(train, "%lf\n", &matY[i][0]);
    }
    for (int i = 0; i < houses; i++)
        matX[i][0]=1;

    FILE * test = fopen (argv[2], "r");
    int houses2;
    fscanf(test, "%d\n", &houses2);

    //Create matrix U (Pseudo X)  
    double** matU = malloc(houses2 * sizeof(double*));
    for (int i = 0; i < houses2; i++)
        matU[i] = malloc((attributes+1) * sizeof(double));

    //Filling Matrices U
    for (int i = 0; i < houses2; i++)
    {
        for (int j = 0; j < attributes; j++)
            fscanf(test, "%lf,", &matU[i][j+1]);
        fscanf(test, "\n");
    }
    for (int i = 0; i < houses2; i++)
        matU[i][0]=1;
    // printMatrix(matU, houses2, attributes+1);
    // printf("\n\n");

    //X transpose = Q
    double **matQ = transposeMatrix(matX, houses, attributes+1);
    // printMatrix(matQ, attributes+1, houses);
    // printf("\n\n");
    //Q * X = R
    double **matR = multiplyMatrix(matQ, matX, attributes+1, houses, houses, attributes+1);
    // printMatrix(matR, attributes+1, attributes+1);
    // printf("\n\n");

    //Inverse of R = S
    double **matS = inverseMatrix(matR, attributes+1);
    // printMatrix(matS, attributes+1, attributes+1);
    // printf("\n\n");

    //S * Q = T
    double **matT = multiplyMatrix(matS, matQ, attributes+1, attributes+1, attributes+1, houses);
    // printMatrix(matT, attributes+1, houses);
    // printf("\n\n");

    //T * Y = W (as in weights)
    double **matW = multiplyMatrix(matT, matY, attributes+1, houses, houses, 1);
    // printMatrix(matW, attributes+1, 1);
    // printf("\n\n");

    //U (test matrix x) * W = V (final prices)
    double **matV = multiplyMatrix(matU, matW, houses2, attributes+1, attributes+1, 1);
    // printMatrix(matU, houses2, attributes+1);
    // printf("\n\n");

    //Print Matrix V (final prices) ((Pseudo Y))
    printMatrix(matV, houses2, 1);
    //printf("\n");

    //Free Matrices
    freeMatrix(matX, houses);
    freeMatrix(matY, houses);
    freeMatrix(matQ, attributes+1);
    freeMatrix(matR, attributes+1);
    freeMatrix(matS, attributes+1);
    freeMatrix(matT, attributes+1);
    freeMatrix(matU, houses2);
    freeMatrix(matV, houses2);
    freeMatrix(matW, attributes+1);


	return 0;
}

void printMatrix(double** mat, int rows, int cols)
{
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
            printf("%.0f", mat[i][j]);
        printf("\n");
    }
}

void freeMatrix(double** mat, int rows)
{
    for (int i = 0; i < rows; i++)
        free(mat[i]);
    free(mat);
}

double **allocateMatrix(int rows, int columns){
  double ** matrix = malloc(rows * sizeof(double*));
  for(int i = 0; i < rows; i++)
    matrix[i] = malloc(columns * sizeof(double));
  return matrix;
}

double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2)
{
    double **result = allocateMatrix(r1, c2);
    for(int i =0; i<r1; i++)
    {
        for(int j =0; j<c2; j++)
        {
            double *col = malloc(c1 * sizeof(double*));
            for (int k =0; k<c1; k++)
                col[k] = matA[i][k];

            double *row = malloc(r2 * sizeof(double*));
            for (int k = 0; k<r2; k++)
                row[k] = matB[k][j];

            double sum=0;
            for (int k = 0;k<r2;k++)
                sum = sum+(row[k]*col[k]);
            free(row);
            free(col);
            result[i][j] = sum;
        }
    }
    return result;
}

double** transposeMatrix(double** mat, int row, int col)
{
    double ** matTran = allocateMatrix(col, row);
    for (int i=0; i<row; i++)
        for (int j=0; j<col; j++)
            matTran[j][i] = mat[i][j];
    return matTran;
}

double** inverseMatrix(double **matA, int dimension)
{
   double **matI = malloc(dimension * sizeof(double*));
   for (int i=0; i<dimension; i++)
       matI[i] = malloc(dimension * sizeof(double));

   for(int i=0; i<dimension; i++)
       for(int j = 0; j<dimension; j++)
           if (i==j)
               matI[i][j] = 1;
           else
               matI[i][j] = 0;

   for(int i=0; i<dimension; i++)
       for(int j =0; j< dimension; j++)
           if(i!=j)
           {
               double val = matA[j][i]/matA[i][i];
               for (int k = 0; k<dimension; k++)
               {
                   matA[j][k] = matA[j][k] - val*matA[i][k];
                   matI[j][k] = matI[j][k] - val*matI[i][k];
               }
           }

   for(int i=0; i<dimension; i++)
       for(int j =0; j< dimension; j++)
            matI[i][j] = matI[i][j]/matA[i][i];  

   return matI;

}


