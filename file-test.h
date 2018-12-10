#include <unistd.h>
class FileTest{
  public:
    static void testMmap();
    static void testMmapFamily();
    static void testSocket(int argc, const char* argv[]);
    static void testDup(int argc, const char* argv[]);
  private:
    static struct sockaddr_in transSockAddr(const char* ip, const int port);
    static int getListenFd(struct sockaddr_in address, int num);
    static int getConnectFd(struct sockaddr_in *address,int sock);
};