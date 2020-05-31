/* A program to convert NFA to DFA 
Program is implemented for general case

Vainberg Simion FAF-182 Lab2

1. Due to some algorithm "restrictions" states will be represented 
q0 = 2^0 = 1
q1 = 2^1 = 2
q2 = 2^2 = 4
..............

2. Union of states will be represented as - 
q0,q1 = 2^0 + 2^1 = 3
q1, q2 = 2^1 + 2^2 = 6
q0,q1,q2 = 2^0 + 2^1 + 2^2 = 7
.................

*/

#include<stdio.h>
#include<string.h>
#include<math.h>

int ninputs;
int dfa[100][2][100] = {0};
int state[10000] = {0};
char ch[10], str[1000];
int go[10000][2] = {0};
int arr[10000] = {0};

int main(){
     int start_p, fin_p, in, terminal;
     int f[10];
     int i, j=3, s=0, final=0, flag=0, curr1, curr2, k, l;
     int c;
     
     
     printf("\nEnter the number of states: ");
     scanf("%d",&start_p);
     
     printf("\nGive state numbers from 0 to %d",start_p-1);
     
     for(i=0; i<start_p; i++)
     		state[(int)(pow(2,i))] = 1;

     printf("\nEnter number of final states: ");
     scanf("%d",&fin_p);

     printf("\nEnter final states: ");
     for(i=0; i<fin_p; i++)
     {
          scanf("%d",&f[i]);
     }

     int p, q, r, rule;
     
     printf("\nEnter the number of rules in regular grammar: ");
     scanf("%d",&rule);
     
     printf("\n\nDefine rule as \"initial state  input symbol(0/1)  final state\"\n");

     
     
     for(i=0; i<rule; i++)
     {
          scanf("%d%d%d",&p,&q,&r);
		  if (q==0)
		  	dfa[p][0][r] = 1;
		  else 
		  	dfa[p][1][r] = 1;          
     }
     
     printf("\nEnter initial state:");
     scanf("%d",&in);

     in = pow(2,in);

     i=0;
     
     printf("\nDFA presentation\n");
     
     int x=0;
     for(i=0;i<start_p;i++)
     {
     		for(j=0;j<2;j++)
     		{
     				int stf=0;
     				for(k=0;k<start_p;k++)
     				{
     						if(dfa[i][j][k]==1)
     							stf = stf + pow(2,k);
     				}
     				
     				
     				go[(int)(pow(2,i))][j] = stf;
     				printf("%d-%d-->%d\n",(int)(pow(2,i)),j,stf);
     				if(state[stf]==0)
     					arr[x++] = stf;		
     				state[stf] = 1;
     		}
     		
     }

     
     
     
     //for new states
     for(i=0;i<x;i++)
     {
     	
     		for(j=0;j<2;j++)
     		{
     				int new=0;
     				for(k=0;k<start_p;k++)
     				{
     						if(arr[i] & (1<<k))
     						{
     								int h = pow(2,k);
     								
     								if(new==0)
     									new = go[h][j];
     								new = new | (go[h][j]);
     								
     								
     						}
     				}
     				
     				if(state[new]==0)
     				{
     					arr[x++] = new;
     					state[new] = 1;
     				}
     		}
     }
     
     
     
     j=3;
     while(j--)
     {
        printf("\n==Double-checking if DFA is correct==");
     		printf("\nEnter string: ");
			scanf("%s",str);
			l = strlen(str);
			curr1 = in;
			flag = 0;
			printf("\nString takes the following path-->\n");
			printf("%d-",curr1);

			for(i=0;i<l;i++)
			{
				curr1 = go[curr1][str[i]-'0'];
				printf("%d-",curr1);
			}
			
			printf("\nFinal state - %d\n",curr1);
			
			for(i=0;i<fin_p;i++)
			{
					if(curr1 & (1<<f[i]))
					{
							flag = 1;
							break;
					}
			}
			
			if(flag)
				printf("\nString Accepted");
			else
				printf("\nString Rejected"); 		
			     		
	 }
		 
	
	return 0;
}