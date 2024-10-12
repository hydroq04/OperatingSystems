#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

void find(char* path, char* fname) {
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(path, O_RDONLY)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  if (st.type != T_DIR) {
    printf("%s is not a directory. Proceeds to exit...\n", path);
    sleep(2);
    printf("Usage: find [fname]\n");
    sleep(2);
    printf("Usage: find [dir] [fname1] [fname2] ...\n");
    return;
  }
  else {
    
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    find(".", argv[1]);
  }
  else for (int i = 2; i < argc; ++i) {
    find(argv[1], argv[i]);
  }
  exit(0);
}
