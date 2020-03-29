#include<stdio.h>           //standard input and output
#include<pthread.h>        //multithreading purpose    //all header files to be required
#include<stdlib.h>        //general purpose standard library 
#include<unistd.h>  //standard symbolic constraints
#include <time.h>   //time and datefunction
#include <string.h> //string manipulation

pthread_mutex_t writ, mutex;
int Shared_Variable;
int count = 0;

void *ToWrite(void *arg){
        pthread_mutex_lock(&writ);
        int n = rand() % 10;
        int d = ((int)arg);
        printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
        printf("Wait some time WRITER%d \n", d);
        sleep(n);
        printf("No. of time WRITER%d want to write:\n", d);
        int t;
        scanf("%d", &t);
        printf(" WRITER%d is writing...ADDITION...\n", d);
        int j=0;
        while(j<t){
                printf("Give %dth INTEGER value to write:\n", (j+1));
                int u;
                scanf("%d", &u);
                Shared_Variable = Shared_Variable + u;
                j++;
        }
        
        printf("UPDATED value of Shared variable = %d \n", Shared_Variable);
        printf("Number of WRITER  present at current time = %d\n", count);
       
        printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
        pthread_mutex_unlock(&writ);
}

void *ToRead(void *arg){
        
        pthread_mutex_lock(&mutex);
        count++;
        if(count==1)
		{
                pthread_mutex_lock(&writ);  //writer is denied now
        }
        pthread_mutex_unlock(&mutex);
        
        int n = rand() % 10;
        int d = ((int)arg);
        printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
        printf("wait some time READER%d \n", d);
        sleep(n);
        printf("No. of time READER%d want to read:\n", d);
        int t;
        scanf("%d", &t);
        printf("Now READER%d is reading....\n", d);
        int j;
        while(j<t){
                printf("READER%d READING the Shared_Variable = %d\n", d, Shared_Variable);
                j++;
        }
        printf("Number of Readers present = %d\n", count);
        pthread_mutex_lock(&mutex);
        count--;
        if(count==0)
		{   
                pthread_mutex_unlock(&writ);//may be writer come
        }
        pthread_mutex_unlock(&mutex);
}

int main()
{
	    printf("ENTRY OF MAIN PROGRAM STARTS HERE \n");   //main flow of program from here...
        printf("Provide a initial interger value for shared global variable for read and write:- \n");
        scanf("%d", &Shared_Variable);                         //taking global variable value from user
        printf("#############################################################################\n");
        
        printf(" PROVIDE A TOTAl NUMBER OF WRITER....:\n");
        int writer;
        scanf("%d", &writer);  //writer description
            if(writer<0)
		   {
                printf("Enterred invalid no. of writer.You intered negative number\n");
                printf("Program is exiting....\n");
                exit(0);
            }
			else if(writer == 0)
			{
                printf("No WRITER is choosed.Select atlest one writer\n");
                printf(" thread will not be created of writer\n");
                exit(0);
            }
			else
			{
                printf(" Generating of threads....\n");
            }
        int i=1;
        while(i<writer+1)
        {
        	printf("writer number is ->WRITER%d\n",i);
        	i++;
		
		}
		
		printf(" PROVIDE A TOTAl NUMBER OF READER....:\n");
        int reader;
        scanf("%d", &reader);
        if(reader<0)
		   {
                printf("Enterred invalid no. of reader.You intered negative number\n");
                printf("Program is exiting....\n");
                exit(0);
           }
        else if(reader == 0)
			{
                printf("No Reader is choosed.Select atlest one\n");
                printf(" thread will not be created of READER\n");
                exit(0);
            }
			else
			{
                printf(" Generating of threads of READER....\n");
            }
        int j=1;
        while(j<reader+1)
        {
        	printf("Reader number is ->READER%d\n",j);//Reader  description.......
        	j++;
		
		}
		


        printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");


        int k=pthread_mutex_init(&mutex, NULL); //initilation of mutex..
        if(k==0)
		    {
			printf("MUTEX is initilised succesfully\n");   
		    }
		else
		    {
			printf("MUTEX  is not initilised succesfully\n");
		    }
		
		
		     
        int l=pthread_mutex_init(&writ, NULL); //initilation of write
        
        if(l==0)
		    {
			printf("WRITE MUTEX is initilised succesfully\n");  
		    }
		else
		    {
			printf("WRITE MUTEX is not initilised succesfully\n");
		    }
		    
		    
		pthread_t WR1[writer];
		pthread_t RD1[reader];
		
        
        


    printf("#################################################################################\n");
                   int m=0;
              if(writer>0 && reader>0)
			  {
                for(m=0; m<writer; m++)
				{
                        pthread_create(&WR1[m], NULL, &ToWrite, (int *)m);
				}
                for(m=0; m<reader; m++)
				{
                        pthread_create(&RD1[m], NULL, &ToRead, (int *)m);
                }
                for(m=0; m<writer; m++)
				{
                        pthread_join(WR1[m], NULL);
				}
				
                for(m=0; m<reader; m++)
				{
                        pthread_join(RD1[m], NULL);
                }
				}
				 pthread_mutex_destroy(&mutex); 
				 pthread_mutex_destroy(&writ); 
  
    
        printf("@@@@@@@@@@@@@@@@@@@@@@@@@.....THREAD JOINED NOW......@@@@@@@@@@@@@@@@@@@@@@@\n");
        printf("SHARED VARIABLE VALUE AFTER READ WRITE OPERATION= %d\n",Shared_Variable);
        return 0;
        
}
