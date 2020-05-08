#include <cstdio>
#include <unistd.h>

int main(){
  char hostname[100];
  int ncpus;

  gethostname(hostname, 100);
  ncpus = sysconf(_SC_NPROCESSORS_ONLN);

  printf("Hello world! I am running on host %s with %d logical CPUs. \n",
         hostname, ncpus);
}
