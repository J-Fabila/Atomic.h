#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>

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
typedef struct Atom atom;

/********************************************************************/
/*********************** Molecule Definition ************************/
/********************************************************************/

struct Molecule
{
   struct Atom atom[200];
   int Nat;
   //int *P_Nat;
};
typedef struct Molecule molecule;

/********************************************************************/
/********************** Function ReadMolecule ***********************/
/************** Name_Molecule=ReadMolecule(File.xyz) ****************/
/******** molecule Cysteine; Cysteine=ReadMolecule(argv[1]); ********/
/********************************************************************/

molecule ReadMolecule( char *file )
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

   FILE *yi =fopen("aux", "r");

   for(i=0;i<aux;i++)
   {
      fscanf(yi,"%s %f %f %f\n", Mol.atom[i].Symbol, &Mol.atom[i].x[0], &Mol.atom[i].x[1], &Mol.atom[i].x[2]);
   }

   fclose(yi);
   fclose(za);
   system("rm aux");
   Mol.Nat=aux;

   return Mol;
}

/********************* Function PrintMolecule ***********************/
/******** PrintMolecule(Name_Of_Array,OutputFile.xyz,Nat) ***********/
/** struct Atom Molecule[100]; ReadMolecule(Molecule,argv[2],14); ***/
/********************************************************************/

void PrintMolecule(molecule Mol,  char *outputfile)
{
   FILE *ki=fopen(outputfile,"w");
   fprintf(ki,"%i\n\n", Mol.Nat);

   for(i=0;i<Mol.Nat;i++)
   {
      fprintf(ki,"%s %f %f %f\n", Mol.atom[i].Symbol, Mol.atom[i].x[0], Mol.atom[i].x[1], Mol.atom[i].x[2]);
   }
   fclose(ki);
}




/////////////////////////////////////////////////////////////////////

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

int main()
{
molecule Mol;
molecule It;
Mol=ReadMolecule("Cluster.xyz");
It=Grow(Mol,"Au",1);
PrintMolecule(It,"growed.xyz");
return 0;
}
