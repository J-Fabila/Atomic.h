 
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//_/_/_/_/_/_/_/_/_/_/_/_/ atomic.h library _/_/_/_/_/_/_/_/_/_/_/_/_/
//_/_/_/_/_/_/_ For simulation of atoms and molecules _/_/_/_/_/_/_/_/
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

/*
#ifndef HEADER_H
#define HEADER_H

#include<stdlib.h>
#include<string.h>
#include <stdio.h>
#include  <math.h>
#include  <time.h>

#endif
*/
#include<stdlib.h>
#include<string.h>
#include <stdio.h>
#include  <math.h>
#include  <time.h>

/*********** * * * * *  *  *   *   *   *  *  *  * * * ***************/

int Nat;
int i;

/********************************************************************/
/************************* Atom Definition **************************/
/********************************************************************/

struct Atom
{
   char Symbol[3];
   float x[3];
};
typedef struct Atom atoms;

/********************************************************************/
/*********************** Molecule Definition ************************/
/********************************************************************/

struct Molecule
{
   atoms *atom;
   int Nat;
};
typedef struct Molecule molecule;


/********************************************************************/
/************************ Function read_xyz *************************/
/**************** Name_Molecule=read_xyz(File.xyz) ******************/
/********** molecule Cysteine; Cysteine=read_xyz(argv[1]); **********/
/********************************************************************/

molecule read_xyz( char *file )
{
   molecule Mol;
   int aux;

   FILE *za=fopen(file, "r");
   FILE *xe=fopen("command", "w");

   fscanf(za,"%i\n",&aux);
   fprintf(xe,"head -%i %s | tail -%i >> aux \n", aux+2, file, aux);
   fclose(xe);

   system("chmod +x command");
   system("./command");

   atoms *_atoms=(atoms *)malloc(aux*sizeof(atoms));

   FILE *yi =fopen("aux", "r");

   for(i=0;i<aux;i++)
   {
      fscanf(yi,"%s %f %f %f\n", _atoms[i].Symbol, &_atoms[i].x[0], &_atoms[i].x[1], &_atoms[i].x[2]);
   }

   Mol.atom=_atoms;

   fclose(yi);
   fclose(za);
   system("rm aux");
   Mol.Nat=aux;

   return Mol;
}

/************************ Function to_xyz ***************************/
/************ to_xyz(Name_Of_Array,OutputFile.xyz,Nat) **************/
/***** struct Atom Molecule[100]; to_xyz(Molecule,argv[2],14); ******/
/********************************************************************/

void to_xyz(molecule Mol,  char *outputfile)
{
   FILE *ki=fopen(outputfile,"w");
   fprintf(ki,"%i\n\n", Mol.Nat);

   for(i=0;i<Mol.Nat;i++)
   {
      fprintf(ki,"%s %f %f %f\n", Mol.atom[i].Symbol, Mol.atom[i].x[0], Mol.atom[i].x[1], Mol.atom[i].x[2]);
   }
   fclose(ki);
}



/********************* Function NumberOfAtoms ***********************/
/****************** NumberOfAtoms(Molecule.xyz) *********************/
/**************** Nat=NumberOfAtoms(Molecule.xyz) *******************/

int NumberOfAtoms(molecule Mol)
{
   Nat=Mol.Nat;
   return Nat;
}

/************************* Function Move ****************************/
/****** Move(InMolecule,OutMolecule,DeltaX,DeltaY,DeltaZ,Nat) *******/
/******************* Move(Mol,Moved,1,5,3,Nat) **********************/

molecule Move(molecule Molecule,float X, float Y, float Z)
{
   molecule MovedMolecule;
   for(i=0;i<Molecule.Nat;i++)
   {
      MovedMolecule.Nat=Molecule.Nat;
      strcpy(MovedMolecule.atom[i].Symbol,Molecule.atom[i].Symbol);
      MovedMolecule.atom[i].x[0]=Molecule.atom[i].x[0]+X;
      MovedMolecule.atom[i].x[1]=Molecule.atom[i].x[1]+Y;
      MovedMolecule.atom[i].x[2]=Molecule.atom[i].x[2]+Z;
   }
   return MovedMolecule;
}

/********************** Function RotateRad **************************/
/************* RotateRad(Molecule,theta(rad), phi(rad)) *************/
/********************* RotateRad(Mol,pi,pi/2) ***********************/

molecule RotateRad(molecule Mol,float theta, float phi)
{
   molecule RotMol;
   float s;
   int l,m;
   float Rot[3][3];

   Rot[0][0]=cos(phi);                   //*************************//
   Rot[0][1]=(-cos(theta)*sin(phi));     //                         //
   Rot[0][2]=sin(phi)*sin(theta);        //                         //
   Rot[1][0]=sin(phi);                   //                         //
   Rot[1][1]=cos(theta)*cos(phi);        //     Rotation Matriz     //
   Rot[1][2]=(-sin(theta)*cos(phi));     //                         //
   Rot[2][0]=0;                          //                         //
   Rot[2][1]=sin(theta);                 //                         //
   Rot[2][2]=cos(theta);                 //*************************//

   RotMol.Nat=Mol.Nat;

   for(i=0;i<Mol.Nat;i++)
   {
      strcpy(RotMol.atom[i].Symbol,Mol.atom[i].Symbol);
      for(l=0;l<3;l++)
      {
         s=0;
         for(m=0;m<3;m++)
         {
            s=s+(Rot[l][m]*(Mol.atom[i].x[m]));
         }

         RotMol.atom[i].x[l]=s;
      }

   }

return RotMol;

}



/********************** Function RotateDeg **************************/
/************* RotateRad(Molecule,theta(deg), phi(deg)) *************/
/********************* RotateRad(Mol,90,45) *************************/

molecule RotateDeg(molecule Mol,float thetadeg, float phideg)
{
   molecule RotMol;
   float s;
   int l,m;
   float Rot[3][3];
   float theta,phi;

   theta=(thetadeg*(3.1415926535/180));
   phi=(phideg*(3.1415926535/180));

   Rot[0][0]=cos(phi);                   //*************************//
   Rot[0][1]=(-cos(theta)*sin(phi));     //                         //
   Rot[0][2]=sin(phi)*sin(theta);        //                         //
   Rot[1][0]=sin(phi);                   //                         //
   Rot[1][1]=cos(theta)*cos(phi);        //     Rotation Matriz     //
   Rot[1][2]=(-sin(theta)*cos(phi));     //                         //
   Rot[2][0]=0;                          //                         //
   Rot[2][1]=sin(theta);                 //                         //
   Rot[2][2]=cos(theta);                 //*************************//

   RotMol.Nat=Mol.Nat;

   for(i=0;i<Mol.Nat;i++)
   {

      strcpy(RotMol.atom[i].Symbol,Mol.atom[i].Symbol);

      for(l=0;l<3;l++)
      {
         s=0;
         for(m=0;m<3;m++)
         {
            s=s+(Rot[l][m]*(Mol.atom[i].x[m]));
         }
         RotMol.atom[i].x[l]=s;
      }
   }

return RotMol;

}


/************************** Function Kick ***************************/
/*********************** Kick(Molecule,Kick) ************************/
/************************ Kick(Cluster,0.8) *************************/

molecule Kick(molecule Mol, float kick)
{

   float DelX, DelY, DelZ;
   molecule Moved;
   srand(time(NULL));
   Moved.Nat=Mol.Nat;

   for(i=0;i<Mol.Nat;i++)
   {
      strcpy(Moved.atom[i].Symbol,Mol.atom[i].Symbol);
      DelX=((double)rand()/((double)RAND_MAX))*kick;
      DelY=((double)rand()/((double)RAND_MAX))*kick;
      DelZ=((double)rand()/((double)RAND_MAX))*kick;

      Moved.atom[i].x[0]=DelX+Mol.atom[i].x[0];
      Moved.atom[i].x[1]=DelY+Mol.atom[i].x[1];
      Moved.atom[i].x[2]=DelZ+Mol.atom[i].x[2];
   }

   return Moved;
}


/************************** Function Swap ***************************/
/******************* Swap(Molecule,TimesToSwap) *********************/
/************************ Move(Cluster,3) *************************/

molecule Swap(molecule Mol, int Nswap)
{
   int a,b,i;
   molecule Swaped;
   char aux[4],aux2[4];
   int M=0;
   int N=Mol.Nat-1;
   Swaped.Nat=Mol.Nat;
   srand(time(NULL));

   for(i=0;i<Mol.Nat;i++)
   {
      strcpy(Swaped.atom[i].Symbol,Mol.atom[i].Symbol);
      Swaped.atom[i].x[0] =Mol.atom[i].x[0];
      Swaped.atom[i].x[1] =Mol.atom[i].x[1];
      Swaped.atom[i].x[2] =Mol.atom[i].x[2];
   }

   i=0;
   for(i=0;i<Nswap;i++)
   {
      a=M+(double)rand() / ((double)RAND_MAX / (N-M+1)+1);
      b=M+(double)rand() / ((double)RAND_MAX / (N-M+1)+1);

      if(strcmp(Swaped.atom[a].Symbol,Mol.atom[b].Symbol) != 0 )
      {
         strcpy(aux,Swaped.atom[a].Symbol);
         strcpy(aux2,Swaped.atom[b].Symbol);

         strcpy(Swaped.atom[b].Symbol,aux);
         strcpy(Swaped.atom[a].Symbol,aux2);
      }
      else
      {
      i--;
      }
   }
   return Swaped;
}

/************************* Function Join  ***************************/
/******* Join("1stFileToJoin", "2ndFileToJoin", "JoinedFile") *******/
/****** Join("Molecule.xyz","Substrate.xyz","Configuration.xyz) *****/

void Join(char *file_1, char *file_2, char *file_3)
{
   char command[90];
   FILE *xr=fopen("command","w");
   fprintf(xr,"N=$(head -1 $1) \n M=$(head -1 $2) \n tot=$(($N+$M)) \n echo $tot >> $3 \n");
   fprintf(xr,"head -$(($N+2)) $1 | tail -$N >> $3 \n  head -$(($M+2)) $2 | tail -$M >> $3 \n ");
   fclose(xr);
   system("chmod +x command");
   strcpy(command,"./command ");
   strcat(command,file_1);
   strcat(command,"  ");
   strcat(command,file_2);
   strcat(command,"  ");
   strcat(command,file_3);
   system(command);
   system("rm command");
}


/*********************** Function Separate  *************************/
/******* Separate("Symbols",inputfile.xyz,out1.xyz,out2.xyz) ********/
/*****Separate("Au,Ir","infile.xyz","remainder.xyz","AuIr.xyz");*****/


void Separete(char *Elements, char *inputfile, char *FirstOutput, char *SecOutput)
{
   char command[100];
   FILE *ax=fopen("Elements", "w");
   fprintf(ax,"%s \n",Elements);
   fclose(ax);
   FILE *ig=fopen("command","w");
   fprintf(ig," cp $1 Coords \n for((i=1;i<20;i++)) \n do \n cut -d \",\" -f $i Elements ");
   fprintf(ig," \n done | grep . >>aux2 \n N=$(($(cat aux2 | wc -l )+1)) \n ");
   fprintf(ig," head -$(($(head -1 Coords)+2)) Coords | tail -$(head -1 Coords) >> coords");
   fprintf(ig," \n  for((i=1;i<$N;i++)) \n do \n S=$(head -$i aux2 | tail -1 | awk '{print $1 }')");
   fprintf(ig, "\n grep \"$S\" Coords >> aux3 \n egrep -v \"$S\" coords >> aux4");
   fprintf(ig, "\n rm coords \n mv aux4  coords \n done \n echo \"$(cat coords | wc -l )\" >> $2");
   fprintf(ig, "\n echo \" \" >> $2 \n cat coords >> $2 \n echo \"$(cat aux3 | wc -l )\" >> $3");
   fprintf(ig, "\n echo \" \" >> $3 \n cat aux3 >> $3 \n rm aux2 aux3  coords Coords \n");
   fclose(ig);
   strcpy(command,"chmod +x command ; ./command  ");
   strcat(command,inputfile);
   strcat(command, "  ");
   strcat(command,FirstOutput);
   strcat(command, "  ");
   strcat(command, SecOutput);
   system(command);
   system("rm command");
   system("rm Elements");
}


/************************* Function Grow  ***************************/
/******************** Grow(Mol,Symbol,Range) ************************/
/******************* Grow(Cysteine,"Au",1.50) ***********************/


molecule Grow(molecule Mol, char *Symbol, float epsilon)
{
   int random;
   float criterio=1.5;
   molecule Growed;
   int accepted=0;
   float Mx,Nx,My,Ny,Mz,Nz;
   float x,y,z;
   float Distance;
   srand(time(NULL));

   random=(Mol.Nat-1)+(double)rand()/((double)RAND_MAX/(0-(Mol.Nat-1)+1)+1);

   while(accepted==0)
   {

      Mx=Mol.atom[random].x[0]+epsilon;  //Maximum range for random X
      Nx=Mol.atom[random].x[0]-epsilon;  //Minimun range for random x
      My=Mol.atom[random].x[1]+epsilon;  //Maximum range for random y
      Ny=Mol.atom[random].x[1]-epsilon;  //Minimum range for random y
      Mz=Mol.atom[random].x[2]+epsilon;  //Maximum range for random z
      Nz=Mol.atom[random].x[2]-epsilon;  //Minimum range for randon z

      x=Mx+(double)rand()/((double)RAND_MAX/(Nx-Mx+1)+1);
      y=My+(double)rand()/((double)RAND_MAX/(Ny-My+1)+1);
      z=Mz+(double)rand()/((double)RAND_MAX/(Nz-Mz+1)+1);


      for(i=0;i<Mol.Nat;i++)
      {

         Distance=sqrt(pow(x-Mol.atom[i].x[0],2)+pow(y-Mol.atom[i].x[1],2)+pow(z-Mol.atom[i].x[2],2));

         if(Distance<criterio)
         {
            accepted=0;
            break;
         }
         else
         {
            if((Mol.Nat-1)==i)
            {
               accepted=1;
            }
            else
            {
            continue;
            }
         }
      }
   }

   Growed.Nat=Mol.Nat+1;

   for(i=0;i<Mol.Nat;i++)
   {
      strcpy(Growed.atom[i].Symbol,Mol.atom[i].Symbol);
      Growed.atom[i].x[0]=Mol.atom[i].x[0];
      Growed.atom[i].x[1]=Mol.atom[i].x[1];
      Growed.atom[i].x[2]=Mol.atom[i].x[2];
   }

   strcpy(Growed.atom[Mol.Nat].Symbol,Symbol);
   Growed.atom[Mol.Nat].x[0]=x;
   Growed.atom[Mol.Nat].x[1]=y;
   Growed.atom[Mol.Nat].x[2]=z;


   return Growed;
}




/************************ Function Meshing  *************************/
/**** Meshing(Matrix, Iterations1st,Iterations2nd,Iterations3rd) ****/
/*********************** Meshing(M,10,10,1); ************************/

struct Mesh
{
float x[100];
float y[100];
float z[100];
};
typedef struct Mesh mesh;

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


/********************* Function vasp_to_xyz  ************************/
/************** vasp_to_xyz(inputfile,outputfilet) ******************/
/***************** vasp_to_xyz(argv[1],argv[2]) *********************/


void vasp_to_xyz(char *inputfile, char *outputfile)
{
struct Atom xyz[500];
struct Atom poscar[500];

int i, j, l, m;
char Symbol[500][3];
char command[150];
int N_Symbol[500];
float Factor;
float M[3][3];
float Mi[3][3];
float suma;
int Nat;
float s;
int Ntyp;
int Cartesian;
int Sel;
int Direct;
/*************** Selectivedynamics **********************/
strcpy(command,"cat ");
strcat(command, inputfile);
strcat(command,"  >>  aux");
system(command);
system("grep \"elective\" aux | wc -l >>sel ; rm aux ");

FILE *po=fopen("sel", "r");
fscanf(po,"%i\n",&Sel);
fclose(po);
system("rm sel");
strcpy(command, "");

if(Sel==1)//Si hay selective dynamics)
{
strcpy(command, "tail -$(($(grep -A 500 \"elective\" ");
strcat(command, inputfile);
strcat(command, " | wc -l )-2)) ");
strcat(command, inputfile);
strcat(command, " | grep .  >> selective  ");
FILE *tg=fopen("commandi","w");
fprintf(tg,"%s\n",command);
fclose(tg);
system("chmod +x commandi ");
strcpy(command,"");
strcpy(command," ./commandi  ");
system(command);
strcpy(command, "");
strcpy(command,"Nat=$(cat selective | wc -l  ) " );
system(command);
strcpy(command,"");
//strcat(command,"for((i=0;i<$(($Nat+1));i++));"); //SI da problemas el for quitarlo, igual funcioinara
system(" awk '{print $4 \" \" $5 \" \" $6}' selective | tr 'T' '1' |tr   'F' '0' >>selectivedynamicsaux ");
system( " echo \" \" >> selectivedynamics ; echo \" \" >>selectivedynamics ; cat selectivedynamicsaux >> selectivedynamics");
system("rm selective selectivedynamicsaux");
}
else
{

}
/************************************************/

strcpy(command, "grep \"irect\" ");
strcat(command,inputfile);
strcat(command," | wc -l >> Direct");
system(command);
FILE *x=fopen("Direct", "r");
fscanf(x,"%i\n",&Direct);
fclose(x);
system("rm Direct");
strcpy(command, "");

strcpy(command, "grep \"artesian\" ");
strcat(command,inputfile);
strcat(command," | wc -l >> Cartesian");
system(command);
FILE *xi=fopen("Cartesian", "r");
fscanf(xi,"%i\n",&Cartesian);
fclose(xi);
system("rm Cartesian");

if(Direct==1)
{
strcpy(command, "head -5 ");
strcat(command, inputfile);
strcat(command, " | tail -3 >> Matriz");
system(command);
strcpy(command, "");
strcpy(command, "head -2 ");
strcat(command, inputfile);
strcat(command, " | tail -1 >> Factor");
system(command);
strcpy(command, "");
strcpy(command, "tail -$(($(grep -A 500 \"irect\" ");
strcat(command, inputfile);
strcat(command, " | wc -l )-1)) ");
strcat(command, inputfile);
strcat(command, " | awk '{ print $1 \"  \" $2 \"  \" $3  }' | grep . >> Posiciones ");
//strcat(command, " >> Posiciones  ");
system(command);
strcpy(command, "");
strcpy(command, "head -6 ");
strcat(command, inputfile);
strcat(command, "  | tail -1 >> aux");
system(command);
strcpy(command, "");
strcpy(command, "head -7 ");
strcat(command, inputfile);
strcat(command, "  | tail -1 >> aux2");
system(command);
strcpy(command, "");
strcpy(command, "tr -s '[:blank:]' '\n' < aux >> Simbolos1");
system(command);
strcpy(command, "");
strcpy(command, "tr -s '[:blank:]' '\n' < aux2 >> Numeros");
system(command);
strcpy(command, "");
system("grep  . Simbolos1 >> Simbolos");
system("rm Simbolos1");
system("cat Simbolos | wc -l >>  Ntyp");//Guarda el numero de especies como archivo

FILE *f= fopen("Matriz", "r");
FILE *g= fopen("Factor", "r");
FILE *h= fopen("Posiciones", "r");
FILE *q= fopen("Simbolos", "r");
FILE *r= fopen("Numeros", "r");
FILE *p= fopen("Ntyp", "r");
FILE *o= fopen(outputfile, "w");
fscanf(p,"%i \n", &Ntyp);
for(i=0;i<Ntyp;i++)
{
fscanf(q,"%2s \n", Symbol[i]);
fscanf(r,"%i \n", &N_Symbol[i]);
suma=suma+N_Symbol[i];
}
Nat=suma;
l=0;
for(i=0;i<Ntyp;i++) //Reconoce que tipo de atomo es cada vector posicion
{
for(j=0;j<N_Symbol[i];j++)
{
strcpy( xyz[l].Symbol, Symbol[i] );
l=l+1;
}
}

for(i=0;i<3;i++) //Lee los elementos de matriz
{
fscanf(f,"%f %f %f \n", &Mi[i][0], &Mi[i][1], &Mi[i][2]);
}
/*
for(i=0;i<3;i++)
{
for(j=0;j<3;j++)
{
M[i][j]=Mi[i][j];
}
}
*/
fscanf(g,"%f \n", &Factor);  //Lee el factor de escala
for(i=0;i<3;i++)//Multiplica el factor de escala a la matriz
{
for(j=0;j<3;j++)
{
M[i][j]=Factor*M[j][i];
}
}
for(i=0;i<Nat;i++) //Extrae las coordenadas de Positions
{
fscanf(h,"%f %f %f \n", &poscar[i].x[0], &poscar[i].x[1], &poscar[i].x[2]);
}
/*
for(i=0;i<Nat;i++)//Aplica la matriz  de cambio a cada atomo
{
for(l=0;l<3;l++)
    {
     s=0;
     for(m=0;m<3;m++)
        {
        s=s+(M[l][m]*(poscar[i].x[m]));
        }
     xyz[i].x[l]=s;
    }
}*/
for(i=0;i<Nat;i++)//Aplica la matriz  de cambio a cada atomo
{
for(l=0;l<3;l++)
{
for(m=0;m<3;m++)
{
M[l][m]=poscar[i].x[l]*Mi[l][m];
//printf("%f\t", M[l][m]);
}
//printf(" \n");
}
//printf(" \n");
for(m=0;m<3;m++)
    {
     s=0;
     for(l=0;l<3;l++)
        {
        s=s+M[l][m];
        }
     xyz[i].x[m]=s;
    }
}
system("rm Matriz Factor Posiciones Ntyp Simbolos Numeros aux aux2"); //Borra archivos residuales
fprintf(o,"%i\n\n", Nat); //Imprime el numero de atomos como primera linea del xyz
for(i=0;i<Nat;i++) //Imprime las lineas de atomos
{
fprintf(o,"%s %f %f %f\n", xyz[i].Symbol, xyz[i].x[0], xyz[i].x[1], xyz[i].x[2]);

}
fclose(o);

}//Cierra if/********************************************************/
else{
if(Cartesian==1)
{
strcpy(command, "");
strcpy(command, "tail -$(($(grep -A 500 \"artesian\" ");
strcat(command, inputfile);
strcat(command, " | wc -l )-1)) ");
strcat(command, inputfile);
strcat(command, " | awk '{ print $1 \"  \" $2 \"  \" $3  }' | grep . >> Posiciones ");
//strcat(command, " >> Posiciones  ");
system(command);
system(command);
strcpy(command, "");
strcpy(command, "head -6 ");
strcat(command, inputfile);
strcat(command, "  | tail -1 >> aux");
system(command);
strcpy(command, "");
strcpy(command, "head -7 ");
strcat(command, inputfile);
strcat(command, "  | tail -1 >> aux2");
system(command);
strcpy(command, "");
strcpy(command, "tr -s '[:blank:]' '\n' < aux >> Simbolos1");
system(command);
strcpy(command, "");
strcpy(command, "tr -s '[:blank:]' '\n' < aux2 >> Numeros");
system(command);
strcpy(command, "");
system("grep  . Simbolos1 >> Simbolos");
system("rm Simbolos1");
system("cat Simbolos | wc -l >>  Ntyp");//Guarda el numero de especies como archivo

FILE *hi= fopen("Posiciones", "r");
FILE *qi= fopen("Simbolos", "r");
FILE *ri= fopen("Numeros", "r");
FILE *pi= fopen("Ntyp", "r");
FILE *oi= fopen(outputfile, "w");
fscanf(pi,"%i \n", &Ntyp);
for(i=0;i<Ntyp;i++)
{
fscanf(qi,"%2s \n", Symbol[i]);
fscanf(ri,"%i \n", &N_Symbol[i]);
suma=suma+N_Symbol[i];
}
Nat=suma;
l=0;
for(i=0;i<Ntyp;i++) //Reconoce que tipo de atomo es cada vector posicion
{
for(j=0;j<N_Symbol[i];j++)
{
strcpy( xyz[l].Symbol, Symbol[i] );
l=l+1;
}
}
for(i=0;i<Nat;i++) //Extrae las coordenadas de Positions
{
fscanf(hi,"%f %f %f \n", &poscar[i].x[0], &poscar[i].x[1], &poscar[i].x[2]);
}
system("rm  Posiciones Ntyp Simbolos Numeros aux aux2"); //Borra archivos residuales
fprintf(oi,"%i\n\n", Nat); //Imprime el numero de atomos como primera linea del xyz
for(i=0;i<Nat;i++) //Imprime las lineas de atomos
{
fprintf(oi,"%s %f %f %f\n", xyz[i].Symbol, poscar[i].x[0], poscar[i].x[1], poscar[i].x[2]);

}
fclose(oi);

}//Cierra if cartesian
}//Cierra else

if (Sel==1)
{
strcpy(command,"cat ");
strcat(command,outputfile);
strcat(command," >> aux ;  rm ");
strcat(command,outputfile);
strcat(command," ; paste aux selectivedynamics  >> ");
strcat(command,outputfile);
system(command);
system("rm  aux selectivedynamics");
}
}//Cierra funcion


/********************* Function xyz_to_vasp  ************************/
/** xyz_to_vasp(InFile,OutFile,Title,ScaleFactor,Matrix(3x3Array) ***/
/******float M[3][3]; xyz_to_vasp(mol.xyz,POSCAR,"Title",1,M);*******/



void XYZtoPOSCAR(char *inputfile,char *outputfile,char *Titulo, float Factor, float M[3][3])
{
int i,j;
int Selective;
char command[100];
FILE *hj=fopen(outputfile,"w");
fprintf(hj,"%s\n",Titulo); //Imprime Titulo
fprintf(hj,"%f\n",Factor); //Imprime Factor de escala
for(i=0;i<3;i++)           //Imprime Matriz de vectores
{
for(j=0;j<3;j++)
{
fprintf(hj,"%f\t",M[i][j]);
}
fprintf(hj,"\n");
}
fclose(hj);

////////////////////////////||||||||||||||||||
strcpy(command,"cat ");
strcat(command,inputfile);
strcat(command," >> selective.txt");
system(command);
system("head -$(($(head -1 selective.txt )+2)) selective.txt | tail -$(head -1 selective.txt) | awk '{print $5}'");
strcpy(command,"");
strcpy(command,"awk '{print $5 }'  selective.txt");  //OJO ACA: selective.txt contiene las fixed etc
strcat(command," | grep . | wc -l >> sel");
system(command);


FILE *iy=fopen("sel", "r");
fscanf(iy,"%i\n",&Selective);
//printf("%i\n",Selective);
fclose(iy);
system("rm sel");
if(Selective>0)
{
system("head -$(($(head -1 selective.txt )+2)) selective.txt | tail -$(head -1 selective.txt) | awk '{print $5  \" \" $6 \" \" $7 }'  | tr  '0' 'T'  >> aux");
system("rm selective.txt ; cat aux >> selective.txt ; rm aux ");
}
/////////////////////////////////||||||||||||

FILE *pl=fopen("command","w");
fprintf(pl,"#!/bin/bash\n");
fprintf(pl,"N=$(head -1 $1)\n");
fprintf(pl,"head -$(($N+2)) $1 | tail -$N |  awk '{print $1 }' | sort -u >> aux\n");
fprintf(pl,"M=$(wc -l aux | awk '{ print $1 }')\n");
fprintf(pl,"for ((i=1;i<$(($M+1));i++))\n");
fprintf(pl,"do\n");
fprintf(pl,"echo -n \"$(head -$i aux | tail -1  )  \" >>$2\n");
fprintf(pl,"done\n");
fprintf(pl,"echo \" \" >>$2\n");


fprintf(pl,"for ((i=1;i<$(($M+1));i++))\n");
fprintf(pl,"do\n");
fprintf(pl,"echo -n \"$( grep \"$(head -$i aux | tail -1 )\" $1 | wc -l )  \">> $2\n");
fprintf(pl,"done\n");
fprintf(pl,"echo \" \" >>$2\n");


if(Selective>0) //Lo que significa que hay al menos una linea seleccionada
{
fprintf(pl,"echo \"Selective dynamics\" >>$2 \n");
}
fprintf(pl,"echo \"Cartesian\">>$2 \n");


fprintf(pl,"rm aux\n");
fprintf(pl,"head -$(($N+2)) $1 | tail -$N |  sort -u | awk '{print $2 \"  \"$3 \"  \" $4  }'  >> aux1\n");
fprintf(pl,"head -$(($N+2)) $1 | tail -$N |  sort -u | awk '{print $5 \"  \"$6 \"  \" $7  }'  >> aux2\n");
if(Selective>0) //Lo que significa que hay al menos una linea seleccionada
{
fprintf(pl,"Nl=$(cat aux2 | wc -l ) \n for((i=1;i<$(($N+1)); i++)) \n do \n cont=$(head -$i aux2 | tail -1 | tr '0' 'F' | tr '1' 'T' ) \n");
fprintf(pl," ki=$(echo $cont | wc -c) \n if [ $ki -gt 1 ] \n then echo \"$cont\" >>aux3 \n else \n echo \" T   T   T \" >> aux3 \n ");
fprintf(pl,"fi \n done \n paste aux1 aux3 >> $2 \n rm aux1 aux2   aux3 ");
}
else 
{
fprintf(pl,"paste aux1 aux2 >>$2 ; rm aux2 aux1  ");
}
fclose(pl);
system("chmod +x command");
strcpy(command,"");
strcpy(command,"./command  ");
strcat(command,inputfile);
strcat(command, " ");
strcat(command,outputfile);
//printf("%s\n",command);
system(command);
//system("rm command");
/*if(Selective>0) //Lo que significa que hay al menos una linea seleccionada
{
FILE *wee=fopen("sel.txt","w");
//for(i=0;i<9;i++)
//{
fprintf(wee,"\n\n\n\n\n\n\n\n\n");
//}
fclose(wee);
system("cat selective.txt >> sel.txt");
strcpy(command,"paste ");
strcat(command,outputfile );
strcat(command," sel.txt >> auxi");
system(command);
strcpy(command,"rm  ");
strcat(command, outputfile);
system(command);
strcpy(command, "cat auxi >> ");
strcat(command,outputfile);
system(command);
system("rm sel.txt auxi");
}
*/
system("rm selective.txt command");
}
