/*
 *  Rules based system interpreter
 *
 *  ./software/ch8/interp.c
 *
 *  mtj@cogitollc.com
 *
 */

#include <stdio.h>
#include "common.h"

extern ruleType ruleSet[MAX_RULES];

/*
 *  interpret()
 *
 *  Walk through the active rules looking for a rule that can fire.
 *
 */

void interpret( void )
{
  int rule;
  int fired = 0;

  extern int checkRule( int );
  extern int debug;

  for (rule = 0 ; rule < MAX_RULES ; rule++) {

    fired = 0;

    if (ruleSet[rule].active) {

      fired = checkRule( rule );

      /* If a rule had some effect on working memory, exit, otherwise test
       * another rule.
       */
      if (fired) break;

    }

  }

  if (debug) {
    if (fired) printf("Fired rule %s (%d)\n", ruleSet[rule].ruleName, rule);
  }

  return;
}
