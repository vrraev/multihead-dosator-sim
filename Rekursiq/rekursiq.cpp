#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream.h>

int head[12]={1234,1245,1246,1243,1244,1253,1233,1265,1298,1276,1285,1253};
int c=0,sum=0;

int write(int a)
{
 	ofstream myfile ( "output.txt", ios::ate );
  	myfile << a << "\n";
   myfile.close();
   return 0;
}

int writer(int a)
{
 	ofstream myfile ( "output_rekursiq.txt", ios::ate );
  	myfile << a << "\n";
   myfile.close();
   return 0;
}

int comb_rek(int k)
{
   for(int i=k;i<12;i++)
   {
    	sum+=head[i];
      c++;
      if(c==4)
      {
      	writer(sum);
       	sum-=head[i];
         c--;
      }
      else
      {
       	comb_rek(i+1);
      }
   }
   sum-=head[k-1];
   c--;
   return 0;
}


int comb(void) 																						//Funkciq koqto pravi vsichki vyzmojni kombinacii mejdu vsichki glavi.
{
 	int i,j,k,l;
   for(i=0;i<12;i++)
   {
   	for(j=i+1;j<12;j++)
      {
      	for(k=j+1;k<12;k++)
         	{
            	for(l=k+1;l<12;l++)
               {
                	write(head[i]+head[j]+head[k]+head[l]);
               }
            }
      }
   }
   return 0;
}

int main(void)
{
 	ofstream myfile1 ( "output_rekursiq.txt", ios::trunc );  										//Otvarqm faila i iztrivam vsichko ot nego.
   myfile1.close();
   comb();
   comb_rek(0);
}