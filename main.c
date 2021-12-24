#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

int check(int,int**);
int weight(int,int**);
void graph(int,int**);
int main(void){
    char* path=(char*)malloc(255*sizeof(char));
    printf("enter filepath:\n");
    scanf("%s",path);
    FILE* t1=fopen(path,"r");
    int sd=0;
    do{
        if(fgetc(t1)=='\n'){
            sd++;
        }
    }while(!feof(t1));
    fclose(t1);
    int** mtx=(int**)malloc(sd*sizeof(int*));
    for(int c2=0;c2<sd;c2++){
        mtx[c2]=(int*)malloc(sd*sizeof(int));
    }
    FILE* rd=fopen(path,"r");
    char cc;
    int col=0,row=0,c3=1;
    while(c3<sd){
        cc=fgetc(rd);
        if(cc=='\n'){
            c3++;
            row++;
            col=0;
        }else if(isdigit(cc)){
            mtx[row][col]=cc-'0';
            col++;
        }
    }
    fclose(rd);
    free(path);
    graph(sd,mtx);
    if(check(sd,mtx)){
        printf("is a simple cycle\n");
    }else{
        printf("not a simple cycle\n");
    }
    printf("one of the vertices that have the least edges: %d\n",weight(sd,mtx));
    printf("add an edge? y/n\n");
    char tc;
    scanf(" %c",&tc);
    if(tc=='y'){
        int v1,v2;
        printf("vertex 1 2\n");
        scanf("%d %d",&v1,&v2);
        mtx[v1-1][v2-1]=1;
        mtx[v2-1][v1-1]=1;
        graph(sd,mtx);
        printf("one of the vertices that have the least edges: %d\n",weight(sd,mtx));
    }
    for(int c7=0;c7<sd;c7++){
        free(mtx[c7]);
    }
    free(mtx);
    return(0);
}
int check(int ce,int** mtx){
    int dg=0;
    for(int c1=0;c1<ce;c1++){
        dg=0;
        for(int c2=0;c2<ce;c2++){
            dg+=mtx[c1][c2];
            if(dg>2){
                return(0);
            }
        }
    }
    return(1);
}
int weight(int sd,int** mtx){
    int* svd=(int*)malloc(sd*sizeof(int));
    int sum;
    for(int c1=0;c1<sd;c1++){
        sum=0;
        for(int c2=c1;c2<sd;c2++){
            if(mtx[c1][c2]){
                sum++;
            }
        }
        svd[c1]=sum;
    }
    int smol=INT_MAX,num;
    for(int c3=0;c3<sd;c3++){
        if(svd[c3]<smol){
            num=c3;
        }
    }
    free(svd);
    return(num);
}
void graph(int sd, int** mtx){
    FILE* viz=fopen("graph.dot","w");
    fprintf(viz,"graph B{\n");
    for(int c1=0;c1<sd;c1++){
        for(int c2=c1;c2<sd;c2++){
            if(mtx[c1][c2]){
                fprintf(viz,"\t%d -- %d\n",(c1+1),(c2+1));
            }
        }
    }
    fprintf(viz,"}");
    fclose(viz);
    printf("graph.dot done\n");
}
