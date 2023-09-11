---------------
-  Compiling  -
---------------

The program must be compiledd with a blackbox evaluator. Since both evaluators have the same funciton name, one must be chosen to be compiled with main.cpp.
You can use the following commands to compile the program: 

g++ main.cpp eval.o
g++ main.cpp eval1.of

This will generate a file a.out. This file will be used for running the different evaluator functions.

---------------
-   Running   -
---------------

The program has two runtime arguments; these arguments must be set or else the program will not run.

./a.out [EVAL] [SEED] 

The eval argument decides which evaluator you want to use.

- 0 uses the black box evaluator that was used for the build.
- 1 uses the easy evaluator found in evaluator.cpp. The hill climber should be able to solve this one.
- 2 uses the hard evaluator found in evaluator.cpp. The hill climber typically reaches a local maxima and doesn't solve this one.

The seed is an integer that will determine the random functions of the hill climber. It is used here so that consistent results can be viewed.
For all experiments, I used seeds 0-29.