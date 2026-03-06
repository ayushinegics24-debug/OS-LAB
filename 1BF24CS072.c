#include<stdio.h>
int main(){
int n,i;
int burst[20],waiting[20],turnaround[20];
float total_wt =0,total_tat=0;
printf("enter no. of processes");
scanf("%d",&n);
printf("burst time");
for(i=0;i<n;i++){
    printf("p%d", i+1);
    scanf("%d",&burst[i]);
}
waiting[0]=0;
for(i=0;i<n;i++){
    waiting[i]=waiting[i-1]+burst[i-1];
}
for(i=0;i<0;i++){
    turnaround[i]=waiting[i]+burst[i];
    total_wt += waiting[i];
    total_tat+= turnaround[i];
}
printf("\n process\t burst time\twaiting time \t turnaround time \n");
for(i=0;i<n;i++){
    printf("p%d\t%d\t\t%d\t\t%d", i+1,burst[i], waiting[i],turnaround[i]);
}
printf("\n average waiting time = %.2f", total_wt/n);
printf("\n average turnaround time = %.2f", total_tat/n);
return 0;
}
