
#include<iostream>
#include<curses.h>
using namespace std;

int at[50], bt[50], ct[50]={0}, qt, rqi[50]={0}, c=0, st, flg=0, tm=0, num_of_e=0, pnt=0, btm[50]={0}, tt, wt,rt[50],temp=0;
float att, awt;

void gothroughs1(int pnt,int tm){
    for(int x=pnt+1;x<5;x++){
       if(at[x]<=tm){
          rqi[num_of_e]=x+1;
          num_of_e++;}
    }
}

void gothroughs2(int pnt, int tm){
    for(int x=pnt+1;x<5;x++){
       int fl=0;
       for(int y=0;y<num_of_e;y++){
          if(rqi[y]==x+1){
             fl++;}}
       if(at[x]<=tm && fl==0 && btm[x]!=0){
          rqi[num_of_e]=x+1;
          num_of_e++;}
    }
}

void AddQue(int pnt){
    rqi[num_of_e]=pnt+1;
    num_of_e++;
}

int main(){
cout<<"Enter Number of Processes\n";
int num_processes;
cin>>num_processes;
for(int x=0;x<num_processes;x++){
    cout<<"\nProcess ID p"<<x+1;
    cout<<"\nArrival Time:";
    cin>>at[x];
    cout << "Burst Time:";
    cin>>bt[x];
    btm[x]=bt[x];
    if(at[x]==0){
        rt[x]=-1;
    }
}

cout<<"\nTime quantum=";
cin>>qt;

cout<<endl<<"GANTT CHART"<<endl<<at[0];
do{
    if(flg==0){
       st=at[0];
       if(btm[0]<=qt){
          tm=st+btm[0];
          btm[0]=0;
          gothroughs1(pnt,tm);}
       else{
          btm[0]=btm[0]-qt;
          tm=st+qt;
          gothroughs1(pnt,tm);
          AddQue(pnt);}
    }
 
    else{
       pnt=rqi[0]-1;
       st=tm;
       for(int x=0;x<num_of_e && num_of_e!=1;x++){
          rqi[x]=rqi[x+1];}
       num_of_e--;
       if(btm[pnt]<=qt){
          tm=st+btm[pnt];
          btm[pnt]=0;
          gothroughs2(pnt, tm);}
       else{
         btm[pnt]=btm[pnt]-qt;
          tm=st+qt;
          gothroughs2(pnt, tm);
          AddQue(pnt);}
    }

    if(btm[pnt]==0){
       ct[pnt]=tm;
    }

   flg++;
   cout<<"<-P"<<pnt+1<<"->"<<tm;
   if(rt[pnt]==0){
       rt[pnt]=temp;
   }
   temp=tm;
   
   

}while(num_of_e!=0);

cout<<"\n\nPROCESS\t AT\t BT\t CT\t RT\t TT\t WT\n";
for(int x=0;x<5;x++){
    tt=ct[x]-at[x];
    wt=tt-bt[x];
    if(rt[x]==-1){
        rt[x]=0;
    }
    cout<<"P"<<x+1<<" \t "<<at[x]<<" \t "<<bt[x]<<" \t "<<ct[x]<<" \t "<<rt[x]-at[x]<<" \t "<<tt<<" \t "<<wt<<"\n";
    awt=awt+wt;
    att=att+tt;
}

cout<<"\nAverage Turnaround Time: "<<att/5<<"\nAverage Waiting Time: "<<awt/5;
return 0;
}

