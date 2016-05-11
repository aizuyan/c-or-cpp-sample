#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/in.h>

int main()
{
  int sfp, nfp;
  struct sockaddr_in s_add, c_add;
  unsigned short port = 1992;

  sfp = socket(AF_INET, SOCK_STREAM, 0);
  if(-1 == sfp) 
  {
    printf("socket failed!\r\n");
    return -1;
  }

  bzero(&s_add, sizeof(struct sockaddr_in));
  s_add.sin_family = AF_INET;
  s_add.sin_addr.s_addr = htonl(INADDR_ANY);
  s_add.sin_port = htons(port);

  if(-1 == bind(sfp, (struct sockaddr*)(&s_add), sizeof(struct sockaddr)))
  {
    printf("bind failed!\r\n");
    return -1;
  }

  if(-1 == listen(sfp, 10))
  {
    printf("listen failed\r\n");
    return -1;
  }

  int sockaddr_size = sizeof(struct sockaddr);
  int recbytes;
  char buffer[1024] = {0};
  while(1)
  {
    nfp = accept(sfp, (struct sockaddr*)(&c_add), &sockaddr_size);
    if(-1 == nfp)
    {
      printf("accept failed\r\n");
      break;
    }
    
    recbytes = read(nfp, buffer, 1024);
    if(-1 == recbytes)
    {
      printf("read from client failed!\r\n");
      return -1;
    }
    printf("get from client【%s】，length【%d】\r\n", buffer, strlen(buffer));

    const char *str = "hello, welcome to my server \r\n";
    if(-1 == write(nfp, str, strlen(str)))
    {
      printf("write failed！\r\n");
      break;
    }
    close(nfp);
  }

  close(sfp);
  return 0;

  return 0;
}
