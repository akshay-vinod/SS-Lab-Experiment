#include <stdio.h>
#include <string.h>
struct store{
    int head;
    int sectorsh,sectorst;
    int requests[100],sortedreq[100];
}here;
int sort(count){
    int temp;
    for(int i=0;i<count;i++){
       for(int j=i+1;j<count;j++){
            if(here.sortedreq[i]>here.sortedreq[j]){
                temp=here.sortedreq[i];
                here.sortedreq[i]=here.sortedreq[j];
                here.sortedreq[j]=temp;
            }
        }
    }
    return 0;
}
int fcfs(count){
    int temp,sum=0;
    for(int i=0;i<count;i++){
        if(i==0)
                temp=here.requests[i]-here.head;
        else
            temp=here.requests[i]-here.requests[i-1];
        if(temp>0){
            sum+=temp;
        }
        else{
            temp=temp*(-1);
            sum+=temp;
        }
    }
    printf("%d",sum);
    return 0;
}
int scan(count){
    int sum;
    sort(count);
    sum=(here.sectorst-here.head)+(here.sectorst-here.sortedreq[0]);
    printf("%d",sum);
    return 0;
}
int cscan(count){
    int index,sum;
    sort(count);
    for(int i=0;i<count;i++){
        if(here.sortedreq[i]>here.head){
            index=i-1;
            break;
        }
    }
    sum=(here.sectorst-here.head)+(here.sectorst-here.sectorsh)+(here.sortedreq[index]-here.sectorsh);
    printf("%d",sum);
    return 0;
}
int main(){
    int intline[100];
    char charline[100];
    char * token;
    int count=0;
    FILE *fptr;
    fptr = fopen("input5.txt","r");
    fgets(charline,100,fptr);
    fgets(charline,100,fptr);
    fgets(intline,100,fptr);
    token = strtok(intline," ");
    while(token != NULL){
        here.head=atoi(token);
        token= strtok(NULL," ");
    }
    fgets(charline,100,fptr);
    token = strtok(charline," ");
    while(token != NULL){
        if(count==3 || count==5){
            if(count==3)
                here.sectorsh=atoi(token);
            else if(count==5)
                here.sectorst=atoi(token);
        }
        token= strtok(NULL," ");
        count++;
    }
    count=0;
    fgets(charline,100,fptr);
    fgets(intline,100,fptr);
    token = strtok(intline," ");
    while(token != NULL){
        here.requests[count]=atoi(token);
        token= strtok(NULL," ");
        count++;
    }
    here.requests[count]='\0';
    for(int i=0;i<count;i++){
        here.sortedreq[i]=here.requests[i];
     }
    printf("Inputs->\n");
    printf("+--------------------------------+\n");
    printf("| Current head position :%d      |\n",here.head);
    printf("| Sectors numbered from %d to %d |\n",here.sectorsh,here.sectorst);
    printf("| Requests are:");
    for(int i=0;i<count;i++){
        printf(" %d ",here.requests[i]);
        if(i==2)
            printf("     |\n|          ");
    }
    printf("|\n");
    printf("+--------------------------------+\n");
    printf("Outputs->\n");
    printf("+---------------+---------------+---------------+\n|  FCFS         |  SCAN         |  CSCAN        |\n");
    printf("+---------------+---------------+---------------+\n");
    printf("| Total head    | Total head    | Total head    |\n|  movement:");
    fcfs(count);
    printf(" |  movement:");
    scan(count);
    printf(" |  movement:");
    cscan(count);
    printf(" |\n+---------------+---------------+---------------+\n");
    return 0;
}
