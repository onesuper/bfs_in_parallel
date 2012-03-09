/********************************************************************
filename: util.cpp
author: onesuper
email: onesuperclark@gmail.com

some utilities

*********************************************************************/
#include <stdio.h>


void gen_level_log(void)
{
	 FILE* fp = fopen("./level.log", "w");
	 if (!fp) {
		  printf("log file cannot be opened.\n");
		  return;
	 }

	 for (int i=1; i<MAX_LEVEL; i++) {
		  if(counter[i] == 0) {
			   break;
		  }
		  fprintf(fp, "%d\n", counter[i]);
	 }

	 fclose(fp);
	 return;
}


void gen_test_log(float time_used) 
{
	 FILE* fp = fopen("./../test.log", "a");
	 if (!fp) {
		  printf("Cannot open the test.log.\n");
		  return;
	 }
	 
	 fprintf(fp, "%u %u %f\n", num_of_nodes, num_of_edges, time_used);
	 
	 fclose(fp);
	 return;
}
