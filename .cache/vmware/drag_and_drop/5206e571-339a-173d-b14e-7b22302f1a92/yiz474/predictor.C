#include <math.h>
#include "predictor.h"
/*
* Table initilization
*/ 
#define n 16		// should be power of 2
#define m 16		// should be power of 2
#define h 15
int weight_width=8;
bool GHR[h];		// the size of GHR table:h bits
int GA[h];		// the size of GA (address):log2(m)*h bits
int W[n][m][h+1];	// the size of perceptron weights table:n*m*(h+1)*8 bits
//Total size=h+log2(m)*h+n*m*(h+1)*8=32843(bits) < 33024(32K+256)(bits)  
/*
* Parameters initilization
*/
int upperb=127;		// upper bound  
int lowerb=-128;	// lower bound  
// int threshold=(int)(floor(1.93*(h)+14))(HPCA 01, TOCS 2002 paper)
int threshold=33;	// try  
int output=0;		// variable to collect weights and then make prediction correspondingly  
bool predict=false;	// current prediction 
void init_predictor ()	
{
  for (int i=0;i<h;i++)	// GHR initialized to zero
  {
    GA[i]=0;
    GHR[i]=false;
  }
  for (int i=0;i<n;i++)	// perceptron weights initialized to zero
  {
    for (int j=0;j<m;j++)
    { 
      for (int k=0;k<h+1;k++)
        W[i][j][k]=0;
    } 
  }
}

bool make_prediction (unsigned int pc) 
{ 
  int address=pc%n;		// hash to the weight array
  output=W[address][0][0];	// output is initiated to bias weight 
  for (int i=0;i<h;i++)		// find the sum of weights chosen
  {
    if (GHR[i]==true)		// using the addresses of the last h branches
      output+=W[address][GA[i]][i+1];	// add the chosen weight
    else
      output-=W[address][GA[i]][i+1];	// otherwise subtract it
  }
  if (output>=0)	// predict the branch taken if the output is at least 0
    predict=true;
  else
    predict=false;
  return predict;
}

void train_predictor (unsigned int pc, bool outcome)
{
  int address=pc%n;			// hash to the weight array 
  if ((predict!=outcome) || ((output<threshold) && (output>-threshold)))
// if magnitude  of output is less than threshold or prediction was incorrect
  { 
    if (outcome == true)// if branch was taken, then increment the bias weight
    {
      if (W[address][0][0]<upperb)	// upper bound check to go up  
        W[address][0][0]+=1;
    } 
    else 				// otherwise decrement it
    { 
      if (W[address][0][0]>lowerb)	// lower bound check to go down   
        W[address][0][0]-=1; 	
    }
    for(int i=0;i<h;i++)		// for each address and branch outcome in the recent history
    {
      int ga=GA[i];		// branch address hash to the weight array 
      if (GHR[i]==outcome)
      {
        if (W[address][ga][i+1]<upperb)// upper bound check to go up
          W[address][ga][i+1]+=1;
      }
      else
      {
        if (W[address][ga][i+1]>lowerb)// lower bound check to go down  
          W[address][ga][i+1]-=1;
      }
    }
  }  
  for (int i=h-1;i>=1;i--)
  {
    GA[i]=GA[i-1];// shift the current address into the global address array
    GHR[i]=GHR[i-1];// shift the current outcome into the global history register
  }
  GA[0]=address;
  GHR[0]=outcome;
}
