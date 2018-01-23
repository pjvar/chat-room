#include"server_include.h"
char buf[128]={128},tmp[128]={0},ms[128]={0};
int sfd;
void *doit(void *arg){
    while(1){
        bzero(ms,128);
        int r=read(sfd,buf,128);
        if(r!=0)
            printf("%s\n",buf);
        bzero(buf,128);
    }
    return (void*)2;
}
void *doit1(void *arg){
    while(1){
        gets(buf);
        strcat(ms,tmp);
        strcat(ms,buf);
        write(sfd,ms,strlen(ms));
        bzero(ms,128);
        bzero(buf,128);
    }
    return (void*)1;

}
int main(){
    void * ret;
    int r,i=0;
    printf("请输入昵称：");
    gets(tmp);
    strcat(tmp,":\n");
	struct sockaddr_in ip_addr;
	ip_addr.sin_family=AF_INET;
	ip_addr.sin_port=htons(8888);
	inet_pton(AF_INET,"127.0.0.1",&ip_addr.sin_addr);
	sfd=Socket(AF_INET,SOCK_STREAM,0);
	Connect(sfd,(struct sockaddr*)&ip_addr,sizeof(ip_addr));
	pthread_t tid,tid1;
        while(1){
            pthread_create(&tid1,NULL,doit1,NULL);
            pthread_create(&tid,NULL,doit,sfd);
            pthread_join(tid1,&ret);
            pthread_join(tid,&ret);
        }
        /*int f=fork();
	while(1){
		if(f!=0){
			while(1){
				gets(buf);
				strcat(ms,tmp);
				strcat(ms,buf);
				write(sfd,ms,strlen(ms));
				bzero(ms,128);
				bzero(buf,128);
			}
		}
		if(f==0){
			while(1){
				int r=read(sfd,buf,128);
				if(r!=0)
				printf("%s\n",buf);
				bzero(buf,128);
			}
		}
	}*/
}
