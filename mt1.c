#include<stdio.h>
#include<stdlib.h>
/*
struct Mesh
{
float x[100];
float y[100];
float z[100];
};
struct Meshing(float M, float Min_1,float Max_1, float Min_2, float Max_2, float Min_3, float Max_3)
{
struct Mesh mesh;

return mesh;
}
*/

int main()
{
int N=3; //Numero de pasos en X
int M=3; //Numero de pasos en Y
int O=1; //Numero de pasos en z; NB: Cambiar por otra letra???
int i, j, k;
float X[100], Y[100],  Z[100];
float Xt[100],Yt[100],Zt[100];
float Ma[3][3], Mt[3][3];

FILE *xy=fopen("Matriz","r");

   for(i=0;i<3;i++)
   {
      fscanf(xy,"%f %f %f\n",&Ma[i][0], &Ma[i][1], &Ma[i][2]);
   }
   fclose(xy);
   for(i=0;i<3;i++)
   {
      for(j=0;j<3;j++)
      {
         Mt[i][j]=Ma[j][i];
      }
   }

   for(i=0;i<N ;i++)
   {
      for(j=0;j<M;j++)
      {
         for(k=0;k<O;k++)
         {
            X[i]= (float)i / N;
            Y[j]= (float)j / M;
            Z[k]= (float)k / O;
            Xt[i]=(Mt[0][0]*X[i])+(Mt[0][1]*Y[j])+(Mt[0][2]*Z[k]);
            Yt[j]=(Mt[1][0]*X[i])+(Mt[1][1]*Y[j])+(Mt[1][2]*Z[k]);
            Zt[k]=(Mt[2][0]*X[i])+(Mt[2][1]*Y[k])+(Mt[2][2]*Z[k]);
//            printf("%f %f %f \n",X[i],Y[j],Z[k]);
            printf("C %f %f %f \n",Xt[i],Yt[j],Zt[k]);
         }
      }
   }


return 0;
}
