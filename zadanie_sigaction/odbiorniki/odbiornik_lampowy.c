#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<signal.h>


volatile int to_juz_koniec; 
char * t_opis = "ten sygnał mnie nie wzmocni\n",
     * i_opis = "\n<dziabnął mnie!… >\n";
int t_oplen, i_oplen;

void S_terminator( int _ ) {
  write(2,t_opis,t_oplen);
  to_juz_koniec = 1;
}

void S_informator( int _ ) {
  write(2,i_opis,i_oplen);
}

int main() {
  printf("%d\n",getpid());
  int i = 1;
  t_oplen = strlen(t_opis);
  i_oplen = strlen(i_opis);
  signal(SIGUSR2,S_terminator);
  signal(SIGUSR1,S_informator);
  for( ; ! to_juz_koniec ; i++ ) {
    fprintf(stdout,"--%d ",i);
    if( ! i % 33 ) fputc('\n',stdout);
    else fflush(stdout);
    sleep(1);
  }
  return 0;
}


