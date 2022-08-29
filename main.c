#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <strings.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void dfs(int i,int j,int iw,int ih,unsigned char* mainIm, int* deepfi,int col_num){
    deepfi[iw*i+j]=col_num;
if(i>0 && i<ih && j>0 && j<iw){
if((abs(mainIm[iw*i+j]-mainIm[iw*i+j-1])<=65)&&(deepfi[iw*i+j-1]==0))
    dfs(i,j-1,iw,ih,mainIm,deepfi,col_num);
    }
if(i>2 && i<ih+2 && j>-1 && j<iw-1){
if((abs(mainIm[iw*i+j]-mainIm[iw*(i-2)+j+1])<=65)&&(deepfi[iw*(i-2)+j+1]==0))
    dfs(i-2,j+1,iw,ih,mainIm,deepfi,col_num);
    }
if(i>-2 && i<ih-2 && j>-1 && j<iw-1){
    if((abs(mainIm[iw*i+j]-mainIm[iw*(i+2)+j+1])<=65)&&(deepfi[iw*(i+2)+j+1]==0))
    dfs(i+2,j+1,iw,ih,mainIm,deepfi,col_num);
    }
}
int main(){
    int iw,ih,n,col_num=0,check=0,c;
    unsigned char *idata = stbi_load("hampster.png", &iw, &ih, &n, 0);
if (idata == NULL){
    printf("ERROR: file didn't exist \n");
    return -1;
    }
unsigned char* mainIm = (unsigned char*)malloc(ih*iw*sizeof(unsigned char));
int i,j,k=0;
for (i=0; i<ih*iw*n; i=i+n){
mainIm[k]=idata[i]-1;
k++;
}
for (i=0;i<=ih*iw;i++){     
if(mainIm[i]>180) mainIm[i]=255;
else if(mainIm[i]<92)  mainIm[i]=0;
}
    
int* deepfi=(int*)malloc((iw*ih)*sizeof(int));
for(i=0;i<iw*ih;i++)
deepfi[i]=0;
for (i=1;i<ih;i++){
    for (j=1;j<iw;j++){
        if(deepfi[iw*i+j]==0){
            col_num++;
            dfs(i,j,iw,ih,mainIm,deepfi,col_num);}
        }
    }
unsigned char* fdi=(unsigned char*)malloc(iw*ih*n*sizeof(unsigned char));
k=0;
for (i=0; i<ih*iw*n; i=i+n){
    c=deepfi[k]%20+deepfi[k]%35;
    fdi[i]=4*c-27;
    fdi[i+1]=3*c+11;
    fdi[i+2]=3*c+11;
    fdi[i+3]=255;
    k++;}
    stbi_write_png("outpimg.png", iw, ih, n, fdi, 0);
    stbi_image_free(idata);
    stbi_image_free(mainIm);
    stbi_image_free(fdi);
    return 0;
}