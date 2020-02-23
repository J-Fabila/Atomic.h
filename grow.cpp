
/************************ RandomGenerator ***************************/

/******************** Grow(Mol,Symbol,Range) ************************/
/******************* Grow(Cysteine,"Au",1.50) ***********************/


void Molecule::RandomGenerator(int _Nat, String Symbol_1, int N_Symbol_1, String Symbol_2="AAA", int N_Symbol_2=0, float epsilon)
{
   Nat=_Nat;
   int random;
   float criterio=1.5;
   int accepted=0;
   float Mx,Nx,My,Ny,Mz,Nz;
   float x,y,z;
   float Distance;
   srand(time(NULL));
   atom=new Atom[Nat+1];
   /////////////////////// A mano pone el primer atomo en el origen
   atom[0].Symbol=Symbol_1;
   atom[0].x[0]=0;
   atom[0].x[1]=0;
   atom[0].x[2]=0;
   int cont_S1=1;
   //int cont_S2=0;
   int cont_tot=1; //contador total de atomos

   for(i=0;i<Nat;i++)
   {
   random=(cont_tot-1)+(double)rand()/((double)RAND_MAX/(0-(cont_tot-1)+1)+1);

   while(accepted==0)
   {

      Mx=atom[random].x[0]+epsilon;  //Maximum range for random X
      Nx=atom[random].x[0]-epsilon;  //Minimun range for random x
      My=atom[random].x[1]+epsilon;  //Maximum range for random y
      Ny=atom[random].x[1]-epsilon;  //Minimum range for random y
      Mz=atom[random].x[2]+epsilon;  //Maximum range for random z
      Nz=atom[random].x[2]-epsilon;  //Minimum range for randon z

      x=Mx+(double)rand()/((double)RAND_MAX/(Nx-Mx+1)+1);
      y=My+(double)rand()/((double)RAND_MAX/(Ny-My+1)+1);
      z=Mz+(double)rand()/((double)RAND_MAX/(Nz-Mz+1)+1);


      for(i=0;i<cont_tot;i++)
      {

         Distance=sqrt(pow(x-atom[i].x[0],2)+pow(y-atom[i].x[1],2)+pow(z-atom[i].x[2],2));
         //criterio==criterio(Symbol_1,Symbol_2);
         if(Distance<criterio)
         {
            accepted=0;
            break;
         }
         else
         {
            if((cont_tot-1)==i)
            {
               accepted=1;
            }
            else
            {
            continue;
            }
         }
      }
      cont_tot++;
   } //while
   if(cont_S1<=N_Symbol_1)
   {
   atom[i].Symbol=Symbol_1;
   }
   else
   {
     atom[i].Symbol=Symbol_2;
   }

 } //for

}
