#include "server.hpp"

int main(int argc, char* argv[]) {
  // TODO: write pid file
  // TODO: use demon process
  // TODO: add log system
  // TODO: use right user
  // TODO: add signal handler
  // TODO: use actor pattern
  // TODO: use thread pool
  // TODO: add multi thread pattern
  // TODO: prase tcp proctol
  //创建套接字
  if (argc < 2) {
    printf(
        "usage: %s ip_address port_number.\n If you do not input them use "
        "default ip(127.0.0.1) and port(8080)\n",
        argv[0]);
  }

  int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  // init server
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;  //使用IPv4地址
  const char* ip = argc < 2 ? "127.0.0.1" : argv[1];
  int port = argc < 2 ? 8080 : atoi(argv[2]);
  serv_addr.sin_addr.s_addr = inet_addr(ip);
  serv_addr.sin_port = htons(port);
  int ret = bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
  assert(ret != -1);
  ret = listen(serv_sock, 20);  // TODO:backlog can config backlog 20
  assert(ret != -1);
  int stop = 0;

  while (!stop) {
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock =
        accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    char str[] = "Hello World!\n";
    write(clnt_sock, str, sizeof(str));
    close(clnt_sock);
  }

  //关闭套接字
  close(serv_sock);
  return 0;
}