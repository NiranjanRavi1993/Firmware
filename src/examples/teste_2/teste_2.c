#include <nuttx/config.h>
#include <stdio.h>
#include <errno.h>
#include <uORB/topics/teste_receive.h>

  __EXPORT int teste_2_main(int argc, char * argv[]);
int teste_2_main(int argc, char * argv[]) {
  printf("teste_2.c---Inicio\n");
  bool updated;
  struct teste_receive_s test;
  static int topic_handle;
  topic_handle = orb_subscribe(ORB_ID(teste_receive));
  printf("\n\rtopic handle value is here %d", topic_handle);
  if (topic_handle == ERROR) {
    printf("Error orb_subscribe (ERROR)=%d\n", errno);
    printf("Error from Teste2 File");
    sleep(10);
    topic_handle = orb_subscribe(ORB_ID(teste_receive));
  } else if (topic_handle == -1) {
    printf("Error orb_subscribe (-1)=%d\n", errno);
    printf("Error from Teste2 File when topic_handle is -1");
    sleep(10);
    topic_handle = orb_subscribe(ORB_ID(teste_receive));
  }
  if (orb_set_interval(topic_handle, 0) == ERROR) {
    printf("Error orb_set_interval =%d\n", errno);
    printf("Error from Teste2 File when interval is error");
    return ERROR;
  }
  printf("recebido with pointer added =%d\n", *&test.inc);
  printf("recebido without pointer added =%d\n",  test.inc);
  if (orb_copy(ORB_ID(teste_receive),topic_handle,&test) == ERROR) {
    printf("Error orb_copy =%d\n", errno);
    printf("Error from Teste2 File during orb copying");
   if (orb_copy(ORB_ID(teste_receive),topic_handle,&test) == ERROR) {
      printf("Error orb_copy =%d\n", errno);
      printf("Error from Teste2 File during orb copying");
      return ERROR;
    }
  }
  printf("recebido with pointer added =%d\n", *&test.inc);
  printf("recebido without pointer added =%d\n",  test.inc);
  printf("\ngoing here");
  int i = 0;
  printf("\ngoing here as well");
  while (i < 10) {
    sleep(1);
    printf("\nll see here");
    //printf("While-i=%d\n",i);
    if (orb_check(topic_handle, & updated) == ERROR) {
      printf("Error orb_check =%d\n", errno);
      printf("Error from Teste2 File during orb update");
      if (orb_check(topic_handle, & updated) == ERROR) {
        printf("Error orb_check =%d\n", errno);
        printf("Error from Teste2 File during orb update");
        return ERROR;
      }
    }
    if (updated) {
      if (orb_copy(ORB_ID(teste_receive), topic_handle, & test) == ERROR) {
        printf("Error orb_copy =%d\n", errno);
        printf("Error from Teste2 File during orb update after copying");
        if (orb_copy(ORB_ID(teste_receive), topic_handle, & test) == ERROR) {
          printf("Error orb_copy =%d\n", errno);
          printf("Error from Teste2 File during orb copying after copying");
          return ERROR;
        }
      }
      printf("recebido=%d\n", test.inc);
      i = test.inc;
    }
  }
  printf("teste_2.c---Fim\n");
  return OK;
}
