#include<bits/stdc++.h>
using namespace std;

//시간복잡도: min( O(Ef), O(VE^2) )
#define n 1000      //점의 개수
int start, finish;      //시작점, 끝점
int capacity[n][n], flow[n][n];     //각각 용량, 현재 유량

int Ford_Fulkerson(){
    int maxflow = 0;
    while(true) {       //증가 경로가 없을 때까지 bfs 돌리기

        vector<int> parent (n, -1);
        queue<int> q;
        parent[start] = start;

        q.push(start);
        while(!q.empty() && parent[finish] == -1) {
            int here = q.front();
            q.pop();

            for ( int next = 0 ; next < n ; ++next ) {
                //용량이 남고, 미방문일 때
                if ( capacity[here][next] - flow[here][next]
                > 0 && parent[next] == -1 ) {
                    parent[next] = here;
                    q.push(next);
                }
            }
        }

        if ( parent[finish] == -1 ) {       //증가 경로가 없다
            break;
        }

        int amount = INT_MAX;           //이 경로를 통해 증가할 유량 정하기
        for ( int p = finish ; p != start ; p = parent[p]) {
            amount = min( capacity[ parent[p] ][p]
             - flow[ parent[p] ][p] , amount );
        }

        //정했으니 증가시키자
        for ( int p = finish ; p != start ; p = parent[p]) {
            flow[ parent[p] ][p] += amount;
            flow[p][ parent[p] ] -= amount;
        }

        //전제 유량에 더해주자
        maxflow += amount;
    }
    return maxflow;
}
