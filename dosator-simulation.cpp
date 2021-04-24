#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream.h>

#define big_pot 500
#define small_pot 50
#define goal 5000
#define tollerance 50
#define head_count 14
#define heads_combined 4

int head[head_count];
int best_heads_up[heads_combined];
int best_heads_down[heads_combined];
int best_heads_numbers_up[heads_combined];
int best_up=0;
int best_heads_numbers_down[heads_combined];
int best_down=0;
int good_combinations=0;
int br=0;

int rand_pot(void)
{
   //return random(big_pot-small_pot)+small_pot; 											//Returning using randomize();
	return small_pot+((rand()% (big_pot-small_pot+1))); 									//Returning using srand();
}


int sort_function( const void *a, const void *b) 										  	//Sort func for qsort();
{
   if(*(int *)a<*(int *)b)return -1;
   if(*(int *)a==*(int *)b)return 0;
   return 1;
}

int sort(void)  																			//Function for sorting the heads by grams.
{
	qsort((void *)head, head_count, sizeof(head[0]), sort_function);
   return 0;
}

int fill_head(int head_num, int weight_goal, int weight_tol)  								//Func that filles a given head.
{
	if(head[head_num]==0)
   {
		while(head[head_num]<weight_goal-weight_tol)
   		{
       		head[head_num]+=rand_pot(); 													//Adding new item until goal - tolerance is achived.
      	};
   }
   return 0;
}

int grams(void)
{
   int i,k,r,m=1;
	for(i=0;i<head_count;i++)
   {
   	if(head[i]!=0)
      {
     		k+=head[i];
         m++;
      }
   }
   r=k/m-1;
   if(r<goal/heads_combined-100)
   {
     	return -50;
   }
   if(r>goal/heads_combined+100)
   {
     	return 350;
   }
   if(r<goal/heads_combined)
   {
     	return 0;
   }
   if(r>goal/heads_combined)
   {
     	return 300;
   }
   return 150;
}

int fill_all_heads(void) 																	//Func that fills all heads.
{
	for(int a=0;a<head_count;a++)
   	{
  		 	fill_head(a,goal/heads_combined,grams());
      }
   return 0;
}

int print_heads(void) 																		//Func that prints all heads.
{
	for(int i=0;i<head_count;i++)
   	{
      	printf("Head N %d contains - %d grams.\n",i+1,head[i]);
      }
   return 0;
}

int del_head(int head_num) 																	//Func that empty a head.
{
  	head[head_num]=0;
   return 0;
}

int del_all_heads(void) 																	//Func that empty all heads.
{
	for(int i=0;i<head_count;i++)
   	{
      	del_head(i);
      }
   return 0;
}

int print_best_heads(void) 																	//Func that print all good heads grams and the total.
{
	for (int m=0; m<4; m++)
   	{
      	printf("\nHead N %d chosen with %d grams.",m+1, best_heads_up[m]);
      }
   printf("\nActual weight -  %d \n", best_heads_up[0]+best_heads_up[1]+best_heads_up[2]+best_heads_up[3]);
   return 0;
}

int write_used_heads_to_file(int h1, int h2, int h3, int h4)
{
 	ofstream myfile ( "output.txt", ios::ate );
  	myfile << h1 << "\t" << h2 << "\t" << h3 << "\t" << h4 << "\t" << (h1+h2+h3+h4) << "\t" << "|" << "\t";
   myfile.close();
   return 0;
}

int write_all_heads_to_file()
{
 	ofstream myfile ( "output.txt", ios::ate );
   for(int i=0;i<head_count;i++)
   {
  		myfile << head[i] << "\t";
   }
   myfile << "\n";
   myfile.close();
   return 0;
}

int combination(void) 																		//Func that makes all possible combination between all heads.
{
 	int i,j,k,l,b=0;
   for(i=0;i<head_count;i++)
   {
   	for(j=i+1;j<head_count;j++)
      {
      	for(k=j+1;k<head_count;k++)
         	{
            	for(l=k+1;l<head_count;l++)
               {
                 	b=head[i]+head[j]+head[k]+head[l];
                  if(b>=goal && b<=goal+tollerance)
                  	{
                      	best_heads_up[0]=head[i];
                        best_heads_up[1]=head[j];
                        best_heads_up[2]=head[k];
                        best_heads_up[3]=head[l];
                        good_combinations++;
                        //print_best_heads();
                        //write_used_heads_to_file(head[i],head[j],head[k],head[l]);
                     }
               }
            }
      }
   }
   return 0;
}

int del_used_heads(int d)
{
 	for(int i=0;i<heads_combined;i++)
   	{
      	if(d==0)
         	{
            	del_head(best_heads_numbers_down[i]);
         		best_heads_down[i]=0;
				best_heads_up[i]=0;
         	}
         if(d==1)
         	{
            	del_head(best_heads_numbers_up[i]);
         		best_heads_up[i]=0;
				best_heads_down[i]=0;
         	}

      }
      best_up=0;
      best_down=0;
   return 0;
}

int up_or_down()
{
	if(best_up==0 && best_down==0)
   {
    	ofstream myfile ( "output.txt", ios::ate );
  		myfile <<"No" << "\t" << "good" << "\t" << "combination" << "\n";
		myfile.close();
		br++;
		return 1;
   }
   if(best_up==0)
   {
    	return 0;
   }
   if(best_down==0)
   {
    	return 1;
   }
   if(best_up-goal < goal-best_down)
   {
		return 0;
   }
   if(best_up-goal >= goal-best_down)
   {
    	return 1;
   }
   return -1;
}

int best_combination(void) 																	 	//Func that makes all possible combination between all heads.
{
 	int i,j,k,l,b=0,c=0,best_comb_up=10000,best_comb_down=0;
   for(i=0;i<head_count;i++)
   {
   	for(j=i+1;j<head_count;j++)
      {
      	for(k=j+1;k<head_count;k++)
         	{
            	for(l=k+1;l<head_count;l++)
               {
                 	b=head[i]+head[j]+head[k]+head[l];
                  if(b>=goal)
                  {
                  	if(b<=best_comb_up)
                     {
                     	best_heads_up[0]=head[i];
                        best_heads_up[1]=head[j];
                        best_heads_up[2]=head[k];
                        best_heads_up[3]=head[l];
                        best_heads_numbers_up[0]=i;
                        best_heads_numbers_up[1]=j;
                        best_heads_numbers_up[2]=k;
                        best_heads_numbers_up[3]=l;
                        best_comb_up=b;
                        best_up=b;
                     }
                  }
                  else
                  {
                   	if(b>=best_comb_down)
                     {
                     	best_heads_down[0]=head[i];
                        best_heads_down[1]=head[j];
                        best_heads_down[2]=head[k];
                        best_heads_down[3]=head[l];
                        best_heads_numbers_down[0]=i;
                        best_heads_numbers_down[1]=j;
                        best_heads_numbers_down[2]=k;
                        best_heads_numbers_down[3]=l;
                        best_comb_down=b;
                        best_down=b;
                     }
                  }
               }
            }
      }
   }
   return 0;
}

int first_combination(void) 																				//Func that makes all possible combination between all heads.
{
 	int i,j,k,l,b=0;
   for(i=0;i<head_count;i++)
   {
   	for(j=i+1;j<head_count;j++)
      {
      	for(k=j+1;k<head_count;k++)
         	{
            	for(l=k+1;l<head_count;l++)
               {
                 	b=head[i]+head[j]+head[k]+head[l];
                  if(b>=goal-tollerance && b<=goal+tollerance)
                  	{
                      	best_heads_up[0]=head[i];
                        best_heads_up[1]=head[j];
                        best_heads_up[2]=head[k];
                        best_heads_up[3]=head[l];
                        best_heads_numbers_up[0]=i;
                        best_heads_numbers_up[1]=j;
                        best_heads_numbers_up[2]=k;
                        best_heads_numbers_up[3]=l;
                        return 0;
                        //print_best_heads();
                        //write_used_heads_to_file(head[i],head[j],head[k],head[l]);
                     }
               }
            }
      }
   }
   return 0;
}

int worst_combination(void) 																				//Func that makes all possible combination between all heads.
{
 	int i,j,k,l,b=0,best_comb_up=goal,best_comb_down=goal;
   for(i=0;i<head_count;i++)
   {
   	for(j=i+1;j<head_count;j++)
      {
      	for(k=j+1;k<head_count;k++)
         	{
            	for(l=k+1;l<head_count;l++)
               {
                 	b=head[i]+head[j]+head[k]+head[l];
                  if(b>=goal)
                  {
                  	if(b>=best_comb_up && b<=goal+tollerance)
                     {
                     	best_heads_up[0]=head[i];
                        best_heads_up[1]=head[j];
                        best_heads_up[2]=head[k];
                        best_heads_up[3]=head[l];
                        best_heads_numbers_up[0]=i;
                        best_heads_numbers_up[1]=j;
                        best_heads_numbers_up[2]=k;
                        best_heads_numbers_up[3]=l;
                        best_comb_up=b;
                        best_up=b;
                     }
                  }
                  else
                  {
                   	if(b<=best_comb_down && b>=goal-tollerance)
                     {
                     	best_heads_down[0]=head[i];
                        best_heads_down[1]=head[j];
                        best_heads_down[2]=head[k];
                        best_heads_down[3]=head[l];
                        best_heads_numbers_down[0]=i;
                        best_heads_numbers_down[1]=j;
                        best_heads_numbers_down[2]=k;
                        best_heads_numbers_down[3]=l;
                        best_comb_down=b;
                        best_down=b;
                     }
                  }
               }
            }
      }
   }
   return 0;
}

int bad_comb_cycle(int cycles)
{  int a,t=0;
 	for(a=0;a<cycles;a++)
  	{
		fill_all_heads();
   	//sort();
   	//print_heads();
   	combination();
   	//printf("\n Dobri Kombinacii - %d", good_combinations);
   	if(good_combinations==0)
   		{
   			t++;
   		}
   	//printf("\n%d. Nulevi kombinacii - %d\n",a,t);
   	//scanf("%d",&b);
   	good_combinations=0;
   	del_all_heads();                                                         	
  }
  return t;
}

int real_cycle()
{  	int i;
	fill_all_heads();
	for(i=0;i<1000;i++)
   	{
   		worst_combination();
   		//write_used_heads_to_file(best_heads_up[0],best_heads_up[1],best_heads_up[2],best_heads_up[3]);
        //write_used_heads_to_file(best_heads_down[0],best_heads_down[1],best_heads_down[2],best_heads_down[3]);
        //write_all_heads_to_file();
        del_used_heads(up_or_down());
        fill_all_heads();
    }
	return 0;
}

int main(void)
{  	int b;
	double p=0;
	srand (time(NULL));  																			//Seeding random numners.
	//randomize();
	for(int i=0;i<100;i++)
	{
		ofstream myfile1 ( "output.txt", ios::trunc );  										//Deleting everything from file.
		myfile1.close();                                										//Closing file.
		//printf("\nNulevi kombinacii - %d\n",bad_comb_cycle(100));
		real_cycle();
		printf("%d", br);
		p=p+br;
		br=0;
	}
	printf("\n");
	cout << "Sredna stoinost na shibani kombinacii: " << p/100;
	scanf("%d",&b);
	return 0;
};