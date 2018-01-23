#include"server_include.h"
#include<stdlib.h>
#include<pthread.h>
#include <fcntl.h>
#include<string.h>
char arr[20]={0};
char message[512]={0};
static void *doit(void *arg){
	struct flock fok;
	fok.l_type=F_WRLCK;//F_UNLCK
	fok.l_whence=SEEK_SET;
	fok.l_start=0;
	fok.l_len=128;
	fok.l_pid=-1;
	char NO[128]={0};
	while(1){
		char buf[128]={0},tmp[128]={0},bb[20]={0};
		int fd=Open("one.txt",O_RDWR);
    	int f=fcntl(fd,F_SETLKW,&fok);
		int r=read(fd,buf,128);
		sscanf(buf,"%s\n",bb);
		int ss=strcmp(bb,arr);
		if(strlen(buf)>0&&ss!=0){
			write(*((int*)arg),buf,strlen(buf));
			lseek(fd,0,SEEK_SET);
			write(fd,NO,128);
		//	fd=Open("one.txt",O_TRUNC);
		//	close(fd);
		}
		fok.l_type=F_UNLCK;
    	fcntl(fd,F_SETLKW,&fok);	
		close(fd);
	}

}
void openfile(int cfd){
	struct flock fok;
	fok.l_type=F_WRLCK;
	fok.l_whence=SEEK_SET;
	fok.l_start=0;
	fok.l_len=128;
	fok.l_pid=-1;
	char buf[128]={0},tmp[128]={0};
	int r=read(cfd,buf,128);
	sscanf(buf,"%s\n",arr);
	int fd=Open("one.txt",O_RDWR);
    int f=fcntl(fd,F_SETLKW,&fok);
	write(fd,buf,r);
	fok.l_type=F_UNLCK;
    fcntl(fd,F_SETLKW,&fok);	
	close(fd);
}
int main(){
        //创建套接字文件与绑定
    char buf[1024]={0},IP[128]={0},tmp[1024]={0};
    pthread_t tid;
    void *ret;
    int cfd,sfd,f,fd;
    struct sockaddr_in ip_addr;
    ip_addr.sin_family=AF_INET;
    ip_addr.sin_port=htons(8888);
    ip_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    sfd=Socket(AF_INET,SOCK_STREAM,0);
    Bind(sfd,(struct sockaddr*)&ip_addr,sizeof(ip_addr));
    Listen(sfd,4);//监听
        //阻塞等待消息传入
	while(1){
        socklen_t len_t=sizeof(ip_addr);
        cfd=Accept(sfd,(struct sockaddr*)&ip_addr,&len_t);
		f=fork();
		if(f==0){
			close(sfd);
			pthread_create(&tid,NULL,doit,(void*)&cfd);
			while(1){
				openfile(cfd);
			}
			close(cfd);
			pthread_join(tid,&ret);
			exit(0);
		}
		else{
            close(cfd);
          //  wait(NULL);
        }
	}
}
