#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
  for(;;){
    setp(1);
  }
  exit(0);
}