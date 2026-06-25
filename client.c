
#include"header.h"

/*signal handler (when client press ctrl+c)*/
int sfd;


void Signal_handler(int number){
	
	write(sfd,"//quit",sizeof("//quit"));
	close(sfd);
	_exit(0);

}



/*============ send ==============*/
void *client_send(void *fd){
	int sfd=*(int *)fd;
	free(fd);
	printf("chat started\n");
	
	
	while(1){
	char msg[50];
	scanf("%s",msg);

	//handling the \quit msg by manually typing 
	char *sub_str=NULL;
	if(sub_str=strstr(msg,"\\quit")){
		if(msg==sub_str){
			write(sfd,"\\quit",sizeof("\\quit"));
			close(sfd);
			_exit(0);
		}
	}
//	signal(2,Signal_handler);
	write(sfd,msg,strlen(msg)+1);
	}

	
	//printf("chat is completed\n");
	
	
	
}

/*=========== recive =================*/

void *client_read(void *fd){
	int sfd=*(int *)fd;
	
	while(1){
	char msg[50];
	int j=read(sfd,msg,sizeof(msg));
	printf("%s\n",msg);
		
	}
	

}

/*======== recive msg==============*/


int main(){
	int len;

	/*========== Socket ===================*/

	sfd=socket(AF_INET,SOCK_STREAM,0);//(Ipv4 domain,connection oriented,0)

	if(sfd<0){
		perror("socket");
		return 0;
	}

	//perror("socket");

	signal(SIGINT,Signal_handler);//cltr+c
	signal(SIGTSTP,SIG_IGN);

	/*============= connect ============*/

	struct sockaddr_in serverId,clientId;

	serverId.sin_family=AF_INET;
	serverId.sin_port=htons(2000);
	serverId.sin_addr.s_addr=inet_addr("127.0.0.1");
	len=sizeof(serverId);
	
	if(connect(sfd,(struct sockaddr*)&serverId,len)<0){
		perror("Connect");
		return 0;
	}

	perror("Connect");
	
	

	pthread_t tid,tid1;
	int *p=malloc(sizeof(int));
	*p=sfd;
	pthread_create(&tid,NULL,client_send,p);
	int *p1=malloc(sizeof(int));
	*p1=sfd;
	pthread_create(&tid1,NULL, client_read,p1);
	while(1);

	

}




