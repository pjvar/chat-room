#include"server_include.h"
int Socket(int domain,int type,int protocol){
    int sfd=socket(domain,type,protocol);
    if(sfd==-1){
        perror("socket");
        return -1;
    }
    return sfd;
}
int Bind(int socket,const struct sockaddr *address,socklen_t address_len){
    int b=bind(socket,address,address_len);
    if(b==-1){
        perror("bing");
        return -1;
    }
    return 0;
}
int Listen(int socket,int backlog){
    int l=listen(socket,backlog);
    if(l==-1){
        perror("listen");
        return -1;
    }
    return 0;
}
int Accept(int s,struct sockaddr *addr,socklen_t *addrlen){
    int a=accept(s,addr,addrlen);
    if(a==-1){
        perror("accept");
        return -1;
    }
    return a;
}
int Connect(int sockfd,const struct sockaddr *addr,socklen_t addrlen){
    int c=connect(sockfd,addr,addrlen);
    if(c==-1){
        perror("connect");
        return -1;
    }
    return 0;
}
int Open(const char *pathname, int flags){
	int fd=open(pathname,flags);
	if(fd==-1){
		perror("open");
		return -1;
	}
	return fd;
}








