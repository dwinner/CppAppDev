/*
 *  WebAgent Main Function
 *
 *  ./software/ch11/main.c
 *
 *  mtj@cogitollc.com
 *
 */

#include <stdio.h>
#include <unistd.h>
#include "protos.h"
#include "prsconf.h"

/*
 *  main()
 *
 *  Main program for WebAgent.
 *
 */

int main()
{
  int timer=0, ret, i;

  extern monitorEntryType monitors[];

  /* Parse the configuration file */
  ret = parseConfigFile( "config" );

  if (ret != 0) {
    printf("Error reading configuration file\n");
    exit(0);
  }

  /* Start the HTTP server */
  initHttpServer();

  while (1) {

    /* Check the news and monitor sites every 10 minutes */
    if ((timer % 600) == 0) {

      printf("Checking News...\n");

      /* Check news from the defined net news server */
      checkNewsSources();

      printf("Monitoring...\n");

      /* Check to see if any defined web-sites have been updated */
      for (i = 0 ; i < MAX_MONITORS ; i++) {
        if (monitors[i].active) monitorSite( i );
      }

      printf("Finished Checking...\n");

    }

    /* Check to see if a client has made a request */
    checkHttpServer();

    timer++;

  }

}
