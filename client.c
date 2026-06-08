#include"header.h"
/*============ send ==============*/


/*======== recive msg==============*/


int main(){
	int sfd,len,nsfd;

	/*========== Socket ===================*/

	sfd=socket(AF_INET,SOCK_STREAM,0);//(Ipv4 domain,connection oriented,0)

	if(sfd<0){
		perror("socket");
		return 0;
	}

	//perror("socket");


	/*============= connect ============*/

	struct sockaddr_in serverId,clientId;

	serverId.sin_family=AF_INET;
	serverId.sin_port=htons(2000);
	serverId.sin_addr.s_addr=inet_addr("0.0.0.0");
	len=sizeof(serverId);

	if(connect(sfd,(struct sockaddr*)&serverId,len)<0){
		perror("Connect");
		return 0;
	}
	



}




