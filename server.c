#include"header.h"


void *client_handler(void *fd){
		int cfd=*(int *)fd;
		free(fd);
		printf("client is connected:%d\n",cfd);

}


int main(){
	int sfd,nsfd;

	/*======= socket ===========*/
	sfd=socket(AF_INET,SOCK_STREAM,0);//Ipv4 domain, tcp(connection oriented),0

	if(sfd<0){
		perror("socket");
		return 0;
	}
	//perror("socket");



	/*========= bind ==========*/


	struct sockaddr_in serverId,clientId;

	serverId.sin_family=AF_INET;//Ipv4 addr family
	serverId.sin_port=htons(2000);//converting into netwrok to byte address

	serverId.sin_addr.s_addr=inet_addr("0.0.0.0");//system Ipv4 address

	socklen_t len=sizeof(serverId);

	if(bind(sfd,(struct sockaddr*)&serverId,len)<0){
		perror("Bind");
		return 0;
	}

	//perror("Bind");

	/*============ listen =============*/
	if(listen(sfd,5)<0){ //int listen(int sockfd,int backlog);
		perror("Listen");
		return 0;
	}



	/*========== Accept ======================*/

	//printf("waiting for client details\n");
	while(1){
		
		nsfd=accept(sfd,(struct sockaddr *)&clientId,&len);

		if(nsfd<0){
			perror("Accept");
			return 0;
		}
	
	int *p=malloc(sizeof(int));
	*p=nsfd;
		pthread_t tid;
	   pthread_create(&tid,NULL, client_handler,p);
		
	}

}

















