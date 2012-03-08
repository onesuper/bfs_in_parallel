/********************************************************************
filename: util.cc
author: onesuper
email: onesuperclark@gmail.com

some utilities

*********************************************************************/
#include <stdio.h>

void gen_log(void)
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



