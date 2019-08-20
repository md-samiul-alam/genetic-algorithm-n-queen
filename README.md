# Solving N-Queen Problem Using Genetic Algorithm with Davis Crossover 

It was my university project to implement genetic algorithm to solve N-Queen problem.

N-Queen is a popular problem. The target is to place N number of queens on a N*N dimension chess board in such a way that they don't attack each other. Primarily this problem can be solved with back tracking algorithm but it takes a huge computational time to solve.

We can introduce a bit of randomization and based on the fitness calculation of the initial random solutions, we can evolve to get better solutions.

This is where genetic algorithms comes for. Every solutions are translated into a fixed length of genes. Among the best fitted genes, make crossovers between them to produce new genes. Best few genes are choosed based on the fitness of the solutions. In this project, I used Davis Crossover. This process continues untill the maximum number of iteration has reached or the perfect solution is evolved.
