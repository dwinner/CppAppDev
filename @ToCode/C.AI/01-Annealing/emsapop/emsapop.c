/*
 *  emitSolution()
 *
 *  Emit a solution in chessboard form.
 *
 */

void emitSolution( memberType *member )
{
  char board[MAX_LENGTH][MAX_LENGTH];
  int x, y;

  bzero( (void *)board, MAX_LENGTH * MAX_LENGTH );

  for (x = 0 ; x < MAX_LENGTH ; x++) {
    board[x][member->solution[x]-1] = 'Q';
  }

  printf("board:\n");
  for (y = 0 ; y < MAX_LENGTH ; y++) {
    for (x = 0 ; x < MAX_LENGTH ; x++) {
      if (board[x][y] == 'Q') printf("Q ");
      else printf(". ");
    }
    printf("\n");
  }
  printf("\n\n");
}


/*
 *  computeEnergy()
 *
 *  Calculate the energy of the passed solution.  The energy is the
 *  the number of conflicts on the board.  Note that only diagonals
 *  are checked.  The encoding ensures that no veritical or horizontal
 *  conflicts are possible.
 *
 */

float computeEnergy( memberType *member )
{
  int  i, j, x, y, tempx, tempy;
  char board[MAX_LENGTH][MAX_LENGTH];
  int conflicts;
  const int dx[4] = {-1,  1, -1,  1};
  const int dy[4] = {-1,  1,  1, -1};

  bzero( (void *)board, MAX_LENGTH * MAX_LENGTH );

  for (i = 0 ; i < MAX_LENGTH ; i++) {
    board[i][member->solution[i]-1] = 'Q';
  }

  /* Walk through each of the Queens, and compute the number of conflicts */
  conflicts = 0;

  for (i = 0 ; i < MAX_LENGTH ; i++) {

    x = i; y = member->solution[i]-1;

    /* NOTE: Based upon encoding, horizontal and vertical conflicts will 
     * never occur!!! 
     */

    /* Check diagonals */
    for (j = 0 ; j < 4 ; j++) {

      tempx = x ; tempy = y;
      while(1) {
        tempx += dx[j]; tempy += dy[j];
        if ((tempx < 0) || (tempx >= MAX_LENGTH) ||
               (tempy < 0) || (tempy >= MAX_LENGTH)) break;
        if (board[tempx][tempy] == 'Q') conflicts++;
      }

    }

  }

  return (float)conflicts;
}


/*
 *  simulatedAnnealing()
 *
 *  Perform the simulated annealing algorithm.
 *
 */

int simulateAnnealing( float curTemp )
{
  int member, i;
  memberType tempMember;
  float energy;
  int useNew = 0;
  int solution = -1;

  for (member = 0 ; member < MAX_MEMBERS ; member++) {

    for (i = 0 ; i < MAX_LENGTH ; i++) {
      tempMember.solution[i] = population[member].solution[i];
    }

    tweakSolution( &tempMember );

    energy = computeEnergy( &tempMember );

    useNew = 0;

    if (energy < population[member].energy) {
      useNew = 1;
    } else {
      float test = getSRand();
      float delta = energy - population[member].energy;

      if (exp(-delta/curTemp) > test) {
        useNew = 1;
      }
    }

    if (useNew) {

      for (i = 0 ; i < MAX_LENGTH ; i++) {
        population[member].solution[i] = tempMember.solution[i];
        population[member].energy = energy;
      }

    }

    if (population[member].energy == 0) solution = member;

  }

  return solution;
}


/* 
 *  computeAllEnergy()
 *
 *  Run through the population and compute the energy for each
 *  candidate solution.
 *
 */

void computeAllEnergy( void )
{
  int member;

  for (member = 0 ; member < MAX_MEMBERS ; member++) {
    population[member].energy = computeEnergy( &population[member] );
  }

}


/*
 *  main()
 *
 *  Main function for the simulated annealing demonstration.
 *
 */

int main()
{
  int  step, solution = -1;
  float temperature = INITIAL_TEMPERATURE;

  srand(time(NULL));

  initializePopulation();

  computeAllEnergy();

  while (temperature > FINAL_TEMPERATURE) {

    printf("temperature %f (solution %d)\n", temperature, solution);

    for (step = 0 ; step < STEPS_PER_CHANGE ; step++) {
      solution = simulateAnnealing( temperature );
    }

    temperature -= RATE;
  }

  if (solution == -1) {
    printf("No solution found\n");
  } else {
    emitSolution( &population[solution] );
  }

  return 0;
}
