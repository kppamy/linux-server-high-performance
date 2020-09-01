1. 
   ```rm a.out && g++ -g objectMemoryModel.cpp && ls -lt a.out|awk '{print "file size: "$5}' && nm  ```
2.  
    * empty class + main + class instance(0 ?):  file size: 4536 ， 3个符号 
    *    empty class + main + class instance(0 ?)+ std::cout: file size  18620 , 文件大小接近4倍, 35个符号  
    * std::cout-> using namespace std;+cout : 文件大小和符号个数没有影响
    * g++ without -g: file size: 15924
     
3. core dump 局限  
    core 文件提供了当前进程的所有线程的堆栈信息，但是也有他的局限性。
   * 由于 core 是对当前进程地址空间的镜像，所以 core 文件一般比较巨大，特别是针对服务器程序。
   这样如果服务器程序自动重启几次，可能就会导致磁盘空间占满。
   另外，由于 core 文件巨大，不删除的话占用大量磁盘空间，下载下来又比较费时。

   * 对于缓冲区溢出导致的 coredump ，进程的调用堆栈已经被覆盖破坏了， core 文件显示的堆栈信息往往错误。

   * 一些信号导致进程崩溃，但是不产生 core 文件，比如 SIGPIPE 。

   * 只能在进程中止时才可以产生 core, 不能实时产生。