#include <stdio.h>
#include <string.h>
struct store{
    int NOP;
    int NOR;
    char Process[100], Resource[100];
    int max[50],allocated[50],avail[100];
    int  need[50],f[100];
    char temp[100];
    int NOREQ;
    int REQPRO;
}st[30];
//structure for requesting processes
struct process{
    char reqProcess[100];
    char Process[100], Resource[100];
    int max[50],allocated[50],temp_avail[100],avail[100];
    int  need[50],f[100];
}p[10];
void request(process_No,location){
   int need_flag,avail_flag,j=0;
   int num =process_No;
   printf("::::Processing REQUEST%d::::\n",location+1);
   //comparing need and request and printing need for request to proceed
   for(int i=0;i<(st[0].NOR);i++){
        if((st[num].need[i])>=(p[location].reqProcess[i])){
            need_flag=0;
        }
        else{
            need_flag=1;
            break;
        }
   }
        if(need_flag==1){
            printf("REQUEST DENIED\n");
        }
        else{
            j=0;
            for(int k=0; k<(st[0].NOR);k++){
                    p[num].need[k]=p[num].need[k]-p[location].reqProcess[k];
            }
             printf("\n*******NEED*******\n\n");
            printf("      ");
            for(int i=0;i<(st[0].NOR);i++){
                printf("%s   ",p[i].Resource);
            }
            printf("\n");
            for(int i=0;i<(st[0].NOP);i++){
                j=0;
                printf("%s->  ",p[i].Process);
                while( j<(st[0].NOR) ) {
                    printf("%d   ",p[i].need[j]);
                    j++;
                }
                printf("\n");
            }
            printf("\n");

        }
        //comparing available and request
        for(int i=0;i<(st[0].NOR);i++){
                p[0].avail[i]=p[0].temp_avail[i];
                if((p[0].avail[i])>=(p[location].reqProcess[i])){
                    avail_flag=0;
                }
                else{
                    avail_flag=1;
                    break;
                }
        }
        if(avail_flag==1){
            printf("REQUEST DENIED");
        }
        else{
                //updating available and allocated data for requested process
                for(int i=0;i<(st[0].NOR);i++){
                    p[0].avail[i]=p[0].avail[i]-p[location].reqProcess[i];
                    p[num].allocated[i]=p[num].allocated[i]+p[location].reqProcess[i];
                }
                //initializing flag value 0 for all process
                int ans[st[0].NOP], ind = 0;
                for (int k = 0; k < (st[0].NOP); k++) {
                    p[0].f[k] = 0;
                }
                //computing safe sequence
                int y = 0;
                int b_break=0;
                int break_flag;
                //performing safe sequence st[0].NOP times
                for (int k = 0; k < (st[0].NOP); k++) {
                    break_flag=0;
                    //checking full process list whether it is safe or not
                    for (int a=0; a < (st[0].NOP); a++) {
                        //checking process already not in  safe state list
                        if (p[0].f[a] == 0) {
                            int flag = 0;
                            for (j = 0; j < (st[0].NOR); j++) {
                                //checking eligibility of process for adding in safe state
                                if (p[a].need[j] > p[0].avail[j]){
                                        flag = 1;
                                        break;
                                }
                            }
                            if (flag == 0) {
                                //adding process to safe state list
                                ans[ind++] = a;
                                for (y = 0; y < (st[0].NOR); y++)
                                    p[0].avail[y] += p[a].allocated[y];
                                p[0].f[a] = 1;
                            }
                            else{
                                break_flag++;
                            }
                        }
                    }
                    //if all process not fulfilled  safe state the break the loop
                    if(break_flag==5){
                           b_break=1;
                           break;
                    }
                }
                if(b_break==1){
                    printf("REQUEST DENIED\n");
                }
                else{
                    printf("\n______SAFE Sequence_______\n");
                    for (int i = 0; i <(st[0].NOP-1); i++){
                    printf("P%d -> ", ans[i]);}
                    printf(" P%d", ans[(st[0].NOP)- 1]);
                    printf("\n\n");
                }

        }
        //reinitializing updated need and allocated for requested process
        for(int k=0; k<(st[0].NOR);k++){
                    p[num].need[k]=st[num].need[k];
                    p[num].allocated[k]=st[num].allocated[k];
            }
}
main(){
    int intline[100];
    char charline[100];
    int j=0;
    FILE *fptr;
    fptr = fopen("input4.txt","r");
    fgets(charline,100,fptr);
    fgets(intline,100,fptr);
    char * token = strtok(intline, " ");
    st[0].NOP=atoi(token);
    fgets(charline,100,fptr);
    fgets(intline,100,fptr);
    token = strtok(intline, " ");
    st[0].NOR=atoi(token);
    fgets(charline,100,fptr);
    fgets(charline,100,fptr);
    token = strtok(charline, " ");
    while( token != NULL ) {
                strcpy(st[j].Process,token);
                strcpy(p[j].Process,token);
                token = strtok(NULL, " ");
                st[j].Process[2]='\0';
                p[j].Process[2]='\0';
                j++;
    }
    j=0;
    fgets(charline,100,fptr);
    fgets(charline,100,fptr);
    token = strtok(charline, " ");
    while( token != NULL ) {
                strcpy(st[j].Resource,token);
                strcpy(p[j].Resource,token);
                token = strtok(NULL, " ");
                st[j].Resource[1]='\0';
                p[j].Resource[1]='\0';
                j++;
    }
    j=0;
    fgets(charline,100,fptr);
    for(int i=0;i<(st[0].NOP);i++){
        j=0;
        fgets(intline,100,fptr);
        token = strtok(intline, " ");
        while( token != NULL ) {
                st[i].max[j]=atoi(token);
                p[i].max[j]=atoi(token);
                token = strtok(NULL, " ");
                j++;
        }
    }
    j=0;
    fgets(charline,100,fptr);
    for(int i=0;i<(st[0].NOP);i++){
        j=0;
        fgets(intline,100,fptr);
        token = strtok(intline, " ");
        while( token != NULL ) {
                st[i].allocated[j]=atoi(token);
                p[i].allocated[j]=atoi(token);
                token = strtok(NULL, " ");
                j++;
        }
    }
    j=0;
    //need matrix calculation
    for(int i=0;i<(st[0].NOP);i++){
        for(int k=0; k<(st[0].NOR);k++){
            st[i].need[k]=st[i].max[k]-st[i].allocated[k];
            p[i].need[k]=p[i].max[k]-p[i].allocated[k];
        }
    }
    printf("\n*******NEED*******\n\n");
    printf("      ");
    for(int i=0;i<(st[0].NOR);i++){
        printf("%s   ",st[i].Resource);
    }
    printf("\n");
    for(int i=0;i<(st[0].NOP);i++){
        j=0;
        printf("%s->  ",st[i].Process);
        while( j<3 ) {
                printf("%d   ",st[i].need[j]);
                j++;
        }
        printf("\n");
    }
    j=0;
    fgets(charline,100,fptr);
    fgets(intline,100,fptr);
    token = strtok(intline, " ");
    //finding remaining avail
    while( token != NULL ) {
                st[0].avail[j]=atoi(token);
                p[0].avail[j]=st[0].avail[j];
                p[0].temp_avail[j]=st[0].avail[j];
                token = strtok(NULL, " ");
                j++;
    }
    j=0;
    int ans[st[0].NOP], ind = 0;
    //initializing flag value 0 for all process
    for (int k = 0; k < (st[0].NOP); k++) {
        st[0].f[k] = 0;
    }
    //computing safe sequence
    int y = 0;
    int b_break=0;
    int break_flag;
    //performing safe sequence st[0].NOP times
    for (int k = 0; k < (st[0].NOP); k++) {
        break_flag = 0;
        //checking full process list whether it is safe or not
        for (int i = 0; i < (st[0].NOP); i++) {
             //checking process already not in  safe state list
            if (st[0].f[i] == 0) {
                int flag = 0;
                for (j = 0; j < (st[0].NOR); j++) {
                    //checking eligibility of process for adding in safe state
                    if (st[i].need[j] > st[0].avail[j]){
                        flag = 1;
                         break;
                    }
                }

                if (flag == 0) {
                    //adding process to safe state list
                    ans[ind++] = i;
                    for (y = 0; y < (st[0].NOR); y++)
                        st[0].avail[y] += st[i].allocated[y];
                    st[0].f[i] = 1;
                }
                else{
                    break_flag++;
                }
            }
        }
        //if all process not fulfilled  safe state the break the loop
        if(break_flag==5){
            b_break=1;
            break;
        }
    }
    if(b_break==1){
        printf("REQUEST DENIED\n");
    }
    else{
        printf("\n______SAFE Sequence_______\n");
        for (int i = 0; i <(st[0].NOP-1); i++){
            printf("P%d -> ", ans[i]);}
            printf(" P%d", ans[(st[0].NOP)- 1]);
            printf("\n\n");
    }
    //reading no of request
    fgets(charline,100,fptr);
    fgets(intline,100,fptr);
    token = strtok(intline, " ");
    st[0].NOREQ=atoi(token);
    for(int i=0;i<(st[0].NOREQ);i++){
        //reading request process no
        fgets(charline,100,fptr);
        fgets(charline,100,fptr);
        token = strtok(charline, " ");
        j=0;
        while(token!=NULL ){
            strcpy(st[j].temp,token);
            token = strtok(NULL, " ");
            j++;
        }
        j=0;
        //converting string to integer
        st[i].REQPRO=st[0].temp[1] - '0';
        //reading request
        fgets(intline,100,fptr);
        token = strtok(intline, " ");
        while( token != NULL ) {
                p[i].reqProcess[j]=atoi(token);
                token = strtok(NULL, " ");
                j++;
        }
        j=0;
        //passing process No and location of process
        request(st[i].REQPRO,i);
        printf("%d Request Remaining\n\n",((st[0].NOREQ)-(i+1)));
    }
}
