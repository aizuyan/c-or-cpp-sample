#include <stdio.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <string.h>

char *getargs(int, char**, char *str);

int main(int argc, char *argv[])
{
  char str[500] = {0};
  getargs(argc, argv, str);
  //printf("%s\n", str);
  
  int cfd;
  int recbytes, writebytes;
  char buffer[1024] = {0};
  struct sockaddr_in c_add;
  unsigned short port = 1992;

  cfd = socket(AF_INET, SOCK_STREAM, 0);
  if(-1 == cfd)
  {
    printf("socket failed!\r\n");
    return -1;
  }

  bzero(&c_add, sizeof(struct sockaddr_in));
  c_add.sin_family = AF_INET;
  c_add.sin_addr.s_addr = inet_addr("127.0.0.1");
  c_add.sin_port = htons(port);

  if(-1 == connect(cfd, (struct sockaddr*)(&c_add), sizeof(struct sockaddr)))
  {
    printf("connect failed\r\n");
    return -1;
  }

  writebytes = write(cfd, str, strlen(str));
  if(-1 == writebytes)
  {
    printf("write to server failed!\r\n");
    return -1;
  } 
  printf("write to server length【%d】，【%s】\r\n", writebytes, str);
  
  recbytes = read(cfd, buffer, 1024);
  if(-1 == recbytes)
  {
    printf("read data failed!\r\n");
    return -1;
  }

  buffer[recbytes] = '\0';
  printf("%s\r\n", buffer);

  return 0;
}

char *getargs(int argc, char *argv[], char *str)
{
  int i = 0;
  for(;i<argc;i++)
  {
    strcat(str, argv[i]);
    str[strlen(str)] = '_';
    str[strlen(str) + 1] = '\0';
  }
  str[strlen(str) - 1] = '\0';
  return str;
}
