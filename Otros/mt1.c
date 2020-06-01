#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int i;
struct Mesh
{
float x[100];
float y[100];
float z[100];
};
struct Mesh Meshing(float Ma[3][3], float N, float M, float O)
{
float X[100], Y[100],  Z[100];

float Mt[3][3];
int i,j,k;
struct Mesh mesh;


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
            mesh.x[i]=(Mt[0][0]*X[i])+(Mt[0][1]*Y[j])+(Mt[0][2]*Z[k]);
            mesh.y[j]=(Mt[1][0]*X[i])+(Mt[1][1]*Y[j])+(Mt[1][2]*Z[k]);
            mesh.z[k]=(Mt[2][0]*X[i])+(Mt[2][1]*Y[k])+(Mt[2][2]*Z[k]);
            printf("C %f %f %f \n",mesh.x[i],mesh.y[j],mesh.z[k]);
         }
      }
   }

return mesh;
}


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
struct Mesh mesh;
mesh=Meshing(Ma,N,M,1);
/*
char command[100];
i=10
strcpy(comand,"mkdir ");
strcat(command,i);
*/
return 0;
}
