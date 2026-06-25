#include"header.h"
#define MAX_CLIENTS 50
int client_fd[MAX_CLIENTS];


void *client_handler(void *fd){
	int cfd=*(int *)fd;
	free(fd);
	printf("client is connected:%d\n",cfd);

	while(1){
		char msg[500];
		read(cfd,msg,sizeof(msg));

		char* temp=NULL;
		if(temp=strstr(msg,"//quit")){
			if(temp==msg){
				//printf("Client is dissconnected:%d\n",cfd);
				for(int i=0;i<MAX_CLIENTS;i++){

					if(client_fd[i]!=cfd && client_fd[i]!=0){
						sprintf(msg,"client %d disconnected",cfd);
						write(client_fd[i],msg,strlen(msg)+1);
					}

					if(client_fd[i]==cfd){
						client_fd[i]=0;
						close(cfd);
						break;
					}
				}
			}
		}

		else{
			for(int i=0;i<MAX_CLIENTS;i++){
				if(client_fd[i]!=cfd && client_fd[i]!=0){
					write(client_fd[i],msg,strlen(msg)+1);
				}
			}


		}


	}
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

	memset(client_fd,0,sizeof(client_fd));

	/*========== Accept ======================*/

	//printf("waiting for client details\n");
	while(1){

		nsfd=accept(sfd,(struct sockaddr *)&clientId,&len);

		if(nsfd<0){
			perror("Accept");
			return 0;
		}


		for(int i=0;i<MAX_CLIENTS;i++){
			if(client_fd[i]==0){
				client_fd[i]=nsfd;
				break;
			}


			if(i>=MAX_CLIENTS){
				printf("unable to connect\n");
				continue;

			}
		}

		int *p=malloc(sizeof(int));
		*p=nsfd;

		pthread_t tid;
		pthread_create(&tid,NULL, client_handler,p);

	}


}
