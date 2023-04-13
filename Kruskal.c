#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct data{
    int bobot, awal, akhir, cek, warna;
};

struct salin{
    int bot, wal, hir, war;
};

int main(){
    int jml;
    system("cls");
    printf("Program Algoritma Kruskal\n=========================\n\nMasukkan jumlah edge : ");
    scanf("%d", &jml);
    struct data edge[jml];
    struct salin copy[jml];
    printf("\nMasukkan vertek-vertek yang terhubung beserta bobotnya (vertek vertek bobot)\n");

    // input
    for(int i=0; i<jml; i++){
        scanf("%d %d %d", &edge[i].awal,&edge[i].akhir,&edge[i].bobot);
        edge[i].cek = 0;
        edge[i].warna = 0;
    }

    // sorting
    for(int j=0; j<jml; j++){
        int tanda=0, min=pow(jml,9);
        for(int k=0; k<jml; k++){
            if(edge[k].bobot<min && edge[k].cek==0){
                min = edge[k].bobot;
                tanda = k;
            }
        }
        edge[tanda].cek = j+1;
    }
    int patokan=1;
    for(int l=0; l<jml; l++){
        for(int m=0; m<jml; m++){
            if(edge[m].cek==patokan){
                copy[l].bot = edge[m].bobot;
                copy[l].wal = edge[m].awal;
                copy[l].hir = edge[m].akhir;
                copy[l].war = edge[m].warna;
            }
        }
        patokan++;
    }

    // cycle
    int arr[jml+1], samawal, samahir, count=2, color=1;
    for(int x=0; x<=jml; x++){
        arr[x] = 0;
    }
    for(int n=0; n<jml; n++){
        if(n==0){
            copy[n].war++;
            arr[n] = copy[n].wal;
            arr[n+1] = copy[n].hir;
        }
        else{
            samawal = 0;
            samahir = 0;
            if(copy[n].wal==copy[n-1].wal || copy[n].wal==copy[n-1].hir || copy[n].hir==copy[n-1].wal || copy[n].hir==copy[n-1].hir){
                copy[n].war = copy[n-1].war;
            }
            else{
				color++;
                copy[n].war = color;
			}
            for(int a=0; a<=jml; a++){
                if(copy[n].wal==arr[a]){
                    samawal = 1;
                }
                if(copy[n].hir==arr[a]){
                    samahir = 1;
                }
            }
            if(samawal==0){
                arr[count] = copy[n].wal;
                count++;
            }
            if(samahir==0){
                arr[count] = copy[n].hir;
                count++;
            }
            int ada=0, warna1=0, warna2=0, counter=count;
            if(samawal==0 && samahir==0)
                counter -= 2;
            else if(samawal!=samahir)
                counter -= 1;
            for(int b=0; b<counter; b++){
                if(copy[n].wal==arr[b])
                    ada++;
                if(copy[n].hir==arr[b])
                    ada++;
            }
            if(ada==2){
                for(int c=n-1; c>=0; c--){
                    if(copy[n].wal==copy[c].wal || copy[n].wal==copy[c].hir || copy[n].hir==copy[c].wal || copy[n].hir==copy[c].hir){
                        if(warna1==0)
                            warna1 = copy[c].war;
                        else if(warna1!=0 && warna2==0)
                            warna2 = copy[c].war;
                    }
                }
                if(warna1==warna2){
                    copy[n].war = 0;
                }
                else if(warna1!=warna2){
                    for(int d=n; d>=0; d--){
                        if(copy[d].war==warna1 || copy[d].war==warna2 && copy[d].war!=0)
                            copy[d].war = copy[n].war;
                    }
                }
            }
        }
    }

    // print
    int total=0;
    printf("\nHasil :\n");
    for(int o=0; o<jml; o++){
        if(copy[o].war!=0){
            printf("%d - %d = %d\n", copy[o].wal,copy[o].hir,copy[o].bot);
            total += copy[o].bot;
        }
    }
    printf("----------\nTotal = %d", total);
    return 0;
}