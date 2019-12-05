#include<stdio.h>
int quantum,ttat=0,twt=0,tnop;
float atat,awt;
struct round_robin
{
    int p_id;
    int at;
    int bt;
    int tat;
    int wt;
}process[100];
void sort(int burst[],int x)
{
    int i,j,a;
    for(i=1;i<=x;i++)
    {
        for(j=i+1;j<=x;j++)
        {
            if(burst[i]>burst[j])
            {
                a=burst[i];
                burst[i]=burst[j];
                burst[j]=a;
            }
        }
    }
}
void non_preemptive(int x)
{
    int i,y,z,burst[100],burst1[100],queue[100],j,wait[100],turn[100],time=0,count=1;
    for(i=1;i<=x;i++)
    {
        y=process[i].p_id;
        printf("\nPROCESS %d",y);
        printf("\nEnter the burst time of process %d:",y);
        scanf("%d",&process[i].bt);
    }
    printf("\nEnter the time quantum:");
    scanf("%d",&quantum);
    printf("\n\nPROCESS\t\tBURST TIME");
    for(i=1;i<=x;i++)
    {
        printf("\n%d\t\t%d",process[i].p_id,process[i].bt);
    }
    for(i=1;i<=x;i++)
        burst[i]=process[i].bt;
    sort(burst,x);
    for(i=1;i<=x;i++)
        burst1[i]=burst[i];
    for(i=1;i<=x;i++)
    {
        for(j=1;j<=x;j++)
        {
            if(burst[i]==process[j].bt)
            {
                queue[i]=process[j].p_id;
            }
        }
    }
    i=1;
    for(time=0;count!=x+1;time++)
    {
        while(burst[i]==0)
        {
            i=(i+1)%(x+1);
        }
        if(burst[i]>=quantum)
        {
            burst[i]=burst[i]-quantum;
            if(burst[i]==0)
            {
                turn[i]=time+quantum;
                count++;
            }
        }
        else if(burst[i]<quantum)
        {
            z=burst[i];
            burst[i]=burst[i]-burst[i];
            if(burst[i]==0)
            {
                turn[i]=time+z;
                count++;
            }
        }
        i=(i+1)%(x+1);
        if(i==0)
            i=i+1;
    }
    for(i=1;i<=x;i++)
    {
        wait[i]=turn[i]-burst1[i];
    }
    for(i=1;i<=x;i++)
    {
        for(j=1;j<=x;j++)
        {
            if(burst1[i]==process[j].bt)
            {
                process[j].tat=turn[i];
                process[j].wt=wait[i];
            }
        }
    }
    printf("\n\nPROCESS\tBURST TIME\tTURNAROUND TIME\tWAITING TIME");
    for(i=1;i<=x;i++)
    {
        printf("\n%d\t%d\t\t%d\t\t%d",process[i].p_id,process[i].bt,process[i].tat,process[i].wt);
        ttat=ttat+process[i].tat;
        twt=twt+process[i].wt;
    }
    atat=(float)ttat/x;
    awt=(float)twt/x;
    printf("\n");
    printf("\nAverage Turnaround Time:%.1f",atat);
    printf("\nAverage Waiting Time:%.1f",awt);
}
void preemptive(int x)
{
    int count,j,remain,time,time_quantum,i,z,k,a,y,n;
    int at[10],bt[10],rt[10],bt1[10],queue[10],p_id[10],turn[10],wait[10],bt2[10],tat[10],wt[10];
    int ttat=0,twt=0;
    float atat,awt;
    remain=x;
    for(i=1;i<=x;i++)
    {
        y=process[i].p_id;
        printf("\nPROCESS %d",y);
        printf("\nEnter the arrival time of process %d:",y);
        scanf("%d",&process[i].at);
        printf("Enter the burst time of process %d:",y);
        scanf("%d",&process[i].bt);
        rt[i]=process[i].at;
    }
    sort(rt,x);
    for(i=1;i<=x;i++)
    {
        for(j=1;j<=x;j++)
        {
            if(rt[i]==process[j].at)
            {
                queue[i]=process[j].p_id;
                bt1[i]=process[j].bt;
                bt2[i]=process[j].bt;
            }
        }
    }
    printf("\nEnter the time quantum:");
    scanf("%d",&quantum);
    printf("\n\nPROCESS\t\tBURST TIME\tARRIVAL TIME");
    for(i=1;i<=x;i++)
    {
        printf("\n%d\t\t%d\t\t%d",process[i].p_id,process[i].bt,process[i].at);
    }
    for(time=0,count=1,i=1;count!=x+1;time++)
    {
        n=0;
        while(rt[i]>time||bt1[i]==0)
        {
            i=(i+1)%(x+1);
            n=n+1;
            if(n==x)
                break;
        }
        if(n==x)
            continue;
        if(bt1[i]<quantum)
        {
            z=bt1[i];
            bt1[i]=0;
            if(bt1[i]==0)
            {
                turn[i]=time+z-rt[i]-1;
                count++;
                if(turn[i]<bt2[i])
                    turn[i]++;
            }
        }
        else if(bt1[i]>=quantum)
        {
            bt1[i]=bt1[i]-quantum;
            if(bt1[i]==0)
            {
                turn[i]=time+quantum-rt[i]-1;
                count++;
                if(turn[i]<bt2[i])
                    turn[i]++;
            }
        }
        i=(i+1)%(x+1);
        if(i==0)
            i=i+1;
    }
    for(i=1;i<=x;i++)
    {
        wait[i]=turn[i]-bt2[i];
    }
    for(i=1;i<=x;i++)
    {
        for(j=1;j<=x;j++)
        {
            if(bt2[i]==process[j].bt)
            {
                process[j].tat=turn[i];
                process[j].wt=wait[i];
            }
        }
    }
    printf("\n\nPROCESS\tARRIVAL TIME\tBURST TIME\tTURNAROUND TIME\tWAITING TIME");
    for(i=1;i<=x;i++)
    {
        printf("\n%d\t%d\t\t%d\t\t%d\t\t%d",process[i].p_id,process[i].at,process[i].bt,process[i].tat,process[i].wt);
        ttat=ttat+process[i].tat;
        twt=twt+process[i].wt;
    }
    atat=(float)ttat/x;
    awt=(float)twt/x;
    printf("\n");
    printf("\nAverage Turnaround Time:%.1f",atat);
    printf("\nAverage Waiting Time:%.1f",awt);
}
void main()
{
    int i,x,j,y,ch;
    printf("Enter the total number of processes:");
    scanf("%d",&tnop);
    x=tnop;
    for(i=1;i<=x;i++)
    {
        process[i].p_id=i;
    }
    printf("\n1.Non Preemptive Scheduling");
    printf("\n2.Preemptive Scheduling");
    printf("\nWhich type of scheduling do you want to continue with:");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1: non_preemptive(x);
                break;
        case 2: preemptive(x);
                break;
        default:printf("\nOption not in the list!!");
                break;
    }
}
