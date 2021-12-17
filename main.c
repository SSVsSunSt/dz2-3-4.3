#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int check(int,int**);
int weight(int,int,int**);
void add(int,int,int,int**);
void graph(int,int,int**);
int main(void){
    char* path=(char*)malloc(255*sizeof(char));
    printf("enter filepath:\n");
    scanf("%s",path);
    FILE* t1=fopen(path,"r");
    int c1=0;
    do{
        if(fgetc(t1)=='\n'){
            c1++;
        }
    }while(!feof(t1));
    fclose(t1);
    int** mtx=(int**)malloc(c1*sizeof(int*));
    for(int c2=0;c2<c1;c2++){
        mtx[c2]=(int*)malloc(c1*sizeof(int));
    }
    FILE* rd=fopen(path,"r");
    char cc;
    int col=0,row=0,c3=1;
    while(c3<c1){
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
    graph(c1,c1,mtx);
    if(check(c1,mtx)){
        printf("is a simple cycle\n");
    }else{
        printf("not a simple cycle\n");
    }
    printf("one of the vertexes that have the least edges: %d\n",weight(c1,c1,mtx));
    printf("add an edge? y/n\n");
    char tc;
    scanf(" %c",&tc);
    if(tc=='y'){
        int v1,v2;
        printf("vertex 1 2\n");
        scanf("%d %d",&v1,&v2);
        add(v1,v2,c1,mtx);
        graph(c1,c1+1,mtx);
        printf("one of the vertexes that have the least edges: %d\n",weight(c1,c1+1,mtx));
    }
    free(path);
    for(int c7=0;c7<c1;c7++){
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
int weight(int ce,int cel,int** mtx){
    int* svd=(int*)malloc(ce*sizeof(int));
    int sum;
    for(int c1=0;c1<ce;c1++){
        sum=0;
        for(int c2=0;c2<cel;c2++){
            sum+=abs(mtx[c1][c2]);
        }
        svd[c1]=sum;
    }
    int smol=2147483647,num;
    for(int c3=0;c3<ce;c3++){
        if(svd[c3]<smol){
            num=c3;
        }
    }
    free(svd);
    return(num);
}
void add(int a1,int a2,int ce,int** mtx){
    for(int c1=0;c1<ce;c1++){
        mtx[c1]=(int*)realloc(mtx[c1],(ce+1)*sizeof(int));
    }
    for(int c2=0;c2<ce;c2++){
        mtx[c2][ce]=0;
    }
    mtx[a1-1][ce]=1;
    mtx[a2-1][ce]=1;
}
void graph(int ce,int cel,int** mtx){
    FILE* vizalt=fopen("graph.dot","w");
    fprintf(vizalt,"graph B{\n");
    int* svdg=(int*)malloc(cel*sizeof(int));
    int v1,v2;
    for(int c7=0;c7<cel;c7++){
        svdg[c7]=0;
        v1=0;
        v2=0;
        for(int c8=0;c8<ce;c8++){
            svdg[c7]+=abs(mtx[c8][c7]);
            if(abs(mtx[c8][c7])){
                if(svdg[c7]==1) {
                    v1=c8+1;
                }else{
                    v2=c8+1;
                }
            }
        }
        if(svdg[c7]==1){
            fprintf(vizalt,"\t%d -- %d\n",v1,v1);
        }
        if(svdg[c7]==2){
            fprintf(vizalt,"\t%d -- %d\n",v1,v2);
        }
    }
    fprintf(vizalt,"}");
    fclose(vizalt);
    free(svdg);
    printf("graph.dot done\n");
}
