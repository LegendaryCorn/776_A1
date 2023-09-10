#include <iostream>
#include "evaluator.cpp"

using namespace std;

double eval(int *pj);

int* randomSolution(){

  int* newSol = new int[100];

  for(int i = 0; i < 100; i++){
    if(rand() % 2 == 0){ // 1/2 chance
      newSol[i] = 0;
    }
    else{
      newSol[i] = 1;
    }    
  }

  return newSol;
}

int* modify(int *sol){

  int* newSol = new int[100];

  for(int i = 0; i < 100; i++){

    if(rand() % 100 < 1){ // 1/100 chance
      newSol[i] = 1 - sol[i]; // Flip bit
    }
    else{
      newSol[i] = sol[i]; // Keep bit
    }

  }

  return newSol;
}

int main()
{
  int* solutionBase;
  int* solutionNew; 
  double fitnessBase = 0;
  double fitnessNew = 0;

  srand(time(NULL));
  solutionBase = randomSolution();
  fitnessBase = eval(solutionBase);
  int noNewSolutions = 0;

  while(noNewSolutions < 100000){

    solutionNew = modify(solutionBase);
    fitnessNew = eval(solutionNew);

    // For debugging
    //cout << fitnessBase << endl;

    // Fitness is better
    if(fitnessNew > fitnessBase){
      delete solutionBase;
      solutionBase = solutionNew;
      fitnessBase = fitnessNew;
      noNewSolutions = 0; // Reset noNewSolutions if improvement is found
    }

    // Fitness is the same
    else if(fitnessNew == fitnessBase){
      delete solutionBase;
      solutionBase = solutionNew;
      fitnessBase = fitnessNew;
      noNewSolutions++;
    }

    // Fitness is worse
    else{
      delete solutionNew;
      noNewSolutions++;
    }

  }
  
  /*
  long count = 0;
  while(fitnessBase < 100){

    solutionNew = new int[100];
    for(int i = 0; i < 100; i++){
      if(i < 30)
        solutionNew[i] = rand() % 2;
      else
        solutionNew[i] = solutionBase[i];
    }

    if(fitnessNew >= fitnessBase){
      delete solutionBase;
      solutionBase = solutionNew;
      fitnessBase = fitnessNew;
    }

    else{
      delete solutionNew;
      noNewSolutions++;
    }      
    
    cout << count << endl;
    count++;
  }
  */
  

  // Output final chromosome
  string chrom = "";
  for(int i = 0; i < 100; i++){
    chrom += to_string(solutionBase[i]);
  }
  cout << chrom << endl;
  cout << fitnessBase << endl;

  delete solutionBase;
}

