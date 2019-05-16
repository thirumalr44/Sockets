// Thirumala Reddy Potlapati
// U55049337

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys.socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define port 1050
#define IP "131.247.3.8"
#define buffer_l 100

sem_t mutex;
int server, length;
int on =1;
struct sockaddr_in s_address;
int accept_v;
char buffer[buffer_l];
int file, l;

void * thread1(void *arg)
{
	sem_wait(&mutex);
	if((file = open("infile", O_RDONLY)) < 0)
	{
		perror("Error in Opening File");
		exit(1);
	}	
	
	l = recv(accept_v, buffer, buffer_l, 0);
	write(0, buffer, l);
    
	sleep(2);
	
	if(send(server, buffer, l, 0) < 0)
	{
		perror("Error in Sending");
		exit(1);
	}	
	
	sem_post(&mutex);
	
	close(file);
	close(server);
	
return(NULL);
}

main()
{
	pthread_t	tid1[3];   
    pthread_attr_t	attr[1];	
	
	pthread_attr_init(&attr[0]);
    pthread_attr_setscope(&attr[0], PTHREAD_SCOPE_SYSTEM);

	
	if ((server = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Failed to connect Socket");
		exit(1);
	}
	
	 if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on)) < 0)
          {
                perror("Stream Socket option set failed.");
                exit(1);
            
          }
		  
		  s_address.sin_family = AF_INET;
		  s_address.sin_port = htons(port);
		  s_address.sin_addr.s_addr = inet_addr(IP).
		  
	if(bind(server, (struct sockaddr*)&s_address, sizeof(s_adress)) < 0)	
    {
		perror("Binding Error");
		exit(1);
	}		
	if(listen(server, 10) <  0)
	{
		perror("Error in Listening");
		exit(1);
	}
    	
	for(int a=0; a<3; a++)
    {
		length = sizeof(s_adress);
		accept_v = accept(server, (struct sockaddr*)&s_address, (socklen_t*)&length);
		if(accept_v >= 0)
		{
			pthread_create(&tid[a], &attr[0], thread1, &accept_v);
		}
		else
		{
			perror("Error in accepting the client");
			exit(1);
		}
	}		
	
    for(int b=0; b<3; b++)
    {
		pthread_join(tid[b], NULL);
	}		
	 
	}