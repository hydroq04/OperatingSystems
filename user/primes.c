#include <stdint.h>
#include "kernel/types.h"
#include "user/user.h"

void primes();

int main(int argc, char *argv[]) {

   //tạo các số tự nhiên từ 2 -> 280
   int pL[2];
   pipe(pL);
   int pid = fork();
   if(pid == 0){
      close(pL[1]);
      primes(pL[0]);
   }
   else{
      close(pL[0]);
      for(int i = 2;i<=280;i++){
         if(write(pL[1],&i,sizeof(int)) != sizeof(int)){
            printf("e ro %d\n", i);
            close(pL[1]);
            exit(1);
         }
      }
      close(pL[1]);
      wait(0);
   }
}

void primes(int pL){
   //take prime from fd
   int prime;
   int num;
   if(read(pL,&prime,sizeof(int)) != sizeof(int)){
      close(pL);
      exit(1);
   }
   printf("prime %d\n",prime);

   int pR[2]; //pipeline right
   pipe(pR);
   int pid = fork();

   if(pid == 0){
      close(pL);
      close(pR[1]);
      primes(pR[0]);
   }
   else{
      close(pR[0]);
      while(read(pL,&num,sizeof(int)) == sizeof(int)){
         if(num % prime != 0){
            write(pR[1],&num,sizeof(int));
      }
   }
   close(pL);
   close(pR[1]);
   wait(0);

   }
}
