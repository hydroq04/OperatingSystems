#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

void find(char* root, char* name){
  char buf[512], *p;
  struct dirent de;
  struct stat st;
    //open root
  int fd;
  if((fd = open(root,O_RDONLY)) < 0){
    printf("find: cannot open %s\n",root);
    return;

  }

//kiem tra do sau cua direction
    if(strlen(root) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("find: path %s too long\n", root);
      close(fd);
      return;
    }

    //them dau '/' vao sau duong dan
    strcpy(buf, root);
    p = buf+strlen(buf);
    *p = '/';

//lay stat cua cac muc ben trong thu muc
  while(read(fd,&de,sizeof(de)) == sizeof(de)){
    if(de.inum == 0 || strcmp(de.name,".") == 0 || strcmp(de.name,"..") == 0){
      continue;
    }
    char temp[512], *t;
    strcpy(temp, buf);
    t = temp + strlen(temp);
    memmove(t,de.name,DIRSIZ);
  //stat
  if(stat(temp,&st) < 0){
    return;
    continue;
  }
  switch(st.type){
    case T_DEVICE:
    case T_FILE:    
    if(strcmp(de.name,name) == 0){
      printf("%s\n",temp);
    }
    break;
    case T_DIR:
    find(temp,name);
      break;
    }//end switch/case
  }//end while
    close(fd);
}

int main(int argc, char* argv[]){
    if(argc <= 1){
        printf("usage: find the paths to the file..\n");
        exit(1);
    }
        find(argv[1],argv[2]);
        exit(0);
}
