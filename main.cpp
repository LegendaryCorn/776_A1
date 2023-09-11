#include <iostream>
#include "evaluator.cpp"

using namespace std;

// The blackbox call; needs a blackbox .o file.
double eval(int *pj);

// Evaluates a chromosome. The evaluator is chosen with the e parameter.
double evaluate(int *sol, int e) {
  switch (e)
  {
    // Black Box
    case 0:
      return eval(sol);
      break;
    
    // Easy
    case 1:
      return eval_easy(sol);
      break;

    // Hard
    case 2:
      return eval_hard(sol);
      break;
    
    // Invalid
    default:
      std::cerr << "Invalid evaluator selection parameter." << endl;
      abort();
      break;
  }
}

// Generates a random solution; each bit is assigned a random value.
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

// Modifies a solution by looking through the entire string and modifying each bit through random chance.
// Multiple bits can be modified. Rarely, no bits will be modified.
int* modify(int *sol){

  int* newSol = new int[100];

  for(int i = 0; i < 100; i++){

    if(rand() % 20 < 1){ // 0.05 chance
      newSol[i] = 1 - sol[i]; // Flip bit
    }
    else{
      newSol[i] = sol[i]; // Keep bit
    }

  }

  return newSol;
}

int main(int argc, char* argv[])
{
  unsigned int seed;
  int eval_num;

  try
  {
    if(argc != 3)
      throw(exception());

    eval_num = stoi(argv[1]);
    seed = stoi(argv[2]);
  }
  catch(const std::exception& e)
  {
    std::cerr << "Invalid command line arguments." << endl;
    abort();
  }
  

  int* solutionBase;
  int* solutionNew; 
  
  double fitnessBase = 0;
  double fitnessNew = 0;
  
  int noNewSolutions = 0;
  long iterations = 0;

  srand(seed);

  // Initialize the solutions
  solutionBase = randomSolution();
  fitnessBase = evaluate(solutionBase, eval_num);

  while(noNewSolutions < 20000){

    solutionNew = modify(solutionBase);
    fitnessNew = evaluate(solutionNew, eval_num);
    iterations += 1;

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

  // Output final chromosome
  string chrom = "";
  for(int i = 0; i < 100; i++){
    chrom += to_string(solutionBase[i]);
  }
  std::cout << "Final String: " << chrom << endl;
  std::cout << "Fitness: " << fitnessBase << endl;
  std::cout << "Iterations: " << iterations << endl;

  delete solutionBase;

  return 0;
}

