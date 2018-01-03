
#define MAX_N 200005

class KMP{
public:
    bool match(char *T, char *P,int n, int m){
        buildNext(P, m);
        int i = 0, j = 0;
        
        while(j < m && i < n){
            if(j < 0 || T[i] == P[j]) { //若匹配
                i++; j++; //则携手并进
            }
            else{ // P右移, T不回退
                j = next[j];
            }
        }
        return (i - j) <= (n - m);        
    }

private:
    int next[MAX_N];
    void buildNext(char *P, int m){
        int t = next[0] = -1;
        int j = 0;
        while(j < m - 1){
            if(t < 0 || P[j] == P[t]){
                j++; t++;
                next[j] =  (P[j] != P[t]) ? t : next[t];
            }
            else
                t = next[t];
        }
        return;
    }
};