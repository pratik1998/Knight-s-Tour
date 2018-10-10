#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define F first
#define S second

vector<pair<int,int>> i_node[8][8];
vector<pair<int,int>> e_node[8][8];
vector<pair<int,int>> base_cycle;
int cycle_no[8][8];
bool vis[8][8];
int trace[8][8];
int cnt = 1;

int dx[] = {0, 4, 0, 4};
int dy[] = {0, 0, 4, 4};

int kx[] = {1, 2, -1, -2, 1, 2, -1, -2};
int ky[] = {2, 1, 2, 1, -2, -1, -2, -1};

int getQuadrant(int i, int j){
    return 2 * (i / 4) + (j / 4);
}

void preProcessInternalCycles() {
    base_cycle.pb(mp(1, 0));
    base_cycle.pb(mp(0, 2));
    base_cycle.pb(mp(2, 3));
    base_cycle.pb(mp(3, 1));
    for(int i = 0; i < 4; i++) {
        pair<int,int> cur = base_cycle[i];
        pair<int,int> nxt = base_cycle[(i + 1) % 4];
        for(int j = 0; j < 4; j++){
            int cx = cur.F + dx[j];
            int cy = cur.S + dy[j];
            int nx = nxt.F + dx[j];
            int ny = nxt.S + dy[j];
            cycle_no[cx][cy] = 1;
            i_node[cx][cy].pb(mp(nx, ny));
            i_node[nx][ny].pb(mp(cx, cy));
        }
    }
    base_cycle.clear();
    base_cycle.pb(mp(0, 1));
    base_cycle.pb(mp(1, 3));
    base_cycle.pb(mp(3, 2));
    base_cycle.pb(mp(2, 0));
    for(int i = 0; i < 4; i++) {
        pair<int,int> cur = base_cycle[i];
        pair<int,int> nxt = base_cycle[(i + 1) % 4];
        for(int j = 0; j < 4; j++){
            int cx = cur.F + dx[j];
            int cy = cur.S + dy[j];
            int nx = nxt.F + dx[j];
            int ny = nxt.S + dy[j];
            cycle_no[cx][cy] = 2;
            i_node[cx][cy].pb(mp(nx, ny));
            i_node[nx][ny].pb(mp(cx, cy));
        }
    }
    base_cycle.clear();
    base_cycle.pb(mp(0, 0));
    base_cycle.pb(mp(2, 1));
    base_cycle.pb(mp(3, 3));
    base_cycle.pb(mp(1, 2));
    for(int i = 0; i < 4; i++) {
        pair<int,int> cur = base_cycle[i];
        pair<int,int> nxt = base_cycle[(i + 1) % 4];
        for(int j = 0; j < 4; j++){
            int cx = cur.F + dx[j];
            int cy = cur.S + dy[j];
            int nx = nxt.F + dx[j];
            int ny = nxt.S + dy[j];
            cycle_no[cx][cy] = 3;
            i_node[cx][cy].pb(mp(nx, ny));
            i_node[nx][ny].pb(mp(cx, cy));
        }
    }
    base_cycle.clear();
    base_cycle.pb(mp(3, 0));
    base_cycle.pb(mp(1, 1));
    base_cycle.pb(mp(0, 3));
    base_cycle.pb(mp(2, 2));
    for(int i = 0; i < 4; i++) {
        pair<int,int> cur = base_cycle[i];
        pair<int,int> nxt = base_cycle[(i + 1) % 4];
        for(int j = 0; j < 4; j++){
            int cx = cur.F + dx[j];
            int cy = cur.S + dy[j];
            int nx = nxt.F + dx[j];
            int ny = nxt.S + dy[j];
            cycle_no[cx][cy] = 4;
            i_node[cx][cy].pb(mp(nx, ny));
            i_node[nx][ny].pb(mp(cx, cy));
        }
    }

}

void preProcessExternalCycles() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            for(int k = 0; k < 8; k++){
                int ii = i + kx[k];
                int jj = j + ky[k];
                if(ii >= 0 && ii < 8 && jj >= 0 && jj < 8 && cycle_no[ii][jj] == cycle_no[i][j] && getQuadrant(i, j) != getQuadrant(ii, jj)) {
                    e_node[i][j].pb(mp(ii, jj));
                }
            }
        }
    }

}


void solve(int start_i, int start_j){
    int cycle_i = start_i;
    int cycle_j = start_j;
    int end_i, end_j;
    //Iterating over systems
    for(int i = 0; i < 4; i++){
        //Iterating over all cycles of a system
        for(int j = 0; j < 4; j++){

            end_i = end_j = -1;
            pair<int, int> neigh1 = i_node[cycle_i][cycle_j][0];
            pair<int, int> neigh2 = i_node[cycle_i][cycle_j][1];
            //Visiting The Cycle of a subsystem
            vis[cycle_i][cycle_j] = true;
            vis[neigh1.F][neigh1.S] = true;
            vis[neigh2.F][neigh2.S] = true;
            vis[i_node[neigh2.F][neigh2.S][0].F][i_node[neigh2.F][neigh2.S][0].S] = true;
            vis[i_node[neigh2.F][neigh2.S][1].F][i_node[neigh2.F][neigh2.S][1].S] = true;

            pair<int, int> valid_e_node;
            bool f = false;
            //Check if neighbour 1 is ending point of cycle
            for(pair<int, int> p : e_node[neigh1.F][neigh1.S]){
                if(!vis[p.F][p.S]){
                    valid_e_node = p;
                    f = true;
                    end_i = neigh1.F;
                    end_j = neigh1.S;
                    break;
                }
            }

            trace[cycle_i][cycle_j] = cnt++;
            int ti = cycle_i;
            int tj = cycle_j;
            if(!f){
                //check if neighbour 2 is ending point of cycle
                for(pair<int, int> p : e_node[neigh2.F][neigh2.S]){
                    if(!vis[p.F][p.S]){
                        valid_e_node = p;
                        f = true;
                        end_i = neigh2.F;
                        end_j = neigh2.S;
                        break;
                    }
                }
            }
            if(f){    //changing subsystem
                cycle_i = valid_e_node.F;
                cycle_j = valid_e_node.S;
            }
            else{     //Changing the system

                bool ff = false;
                for(int k = 0; k < 8; k++){
                    int ii = neigh2.F + kx[k];
                    int jj = neigh2.S + ky[k];
                    if(ii >= 0 && ii < 8 && jj >= 0 && jj < 8 && !vis[ii][jj]){
                        cycle_i = ii;
                        cycle_j = jj;
                        end_i = neigh2.F;
                        end_j = neigh2.S;
                        ff = true;
                        break;
                    }
                }
                if(!ff) {
                    for(int k = 0; k < 8; k++){
                        int ii = neigh1.F + kx[k];
                        int jj = neigh1.S + ky[k];
                        if(ii >= 0 && ii < 8 && jj >= 0 && jj < 8 && !vis[ii][jj]){
                            cycle_i = ii;
                            cycle_j = jj;
                            end_i = neigh1.F;
                            end_j = neigh1.S;
                            break;
                        }
                    }
                }
            }
            //Decide the end point of cycle to mark cycle in its order
            if(end_i == neigh1.F && end_j == neigh1.S){
                trace[neigh2.F][neigh2.S] = cnt++;
                if(i_node[neigh2.F][neigh2.S][0] != mp(ti, tj))
                    trace[i_node[neigh2.F][neigh2.S][0].F][i_node[neigh2.F][neigh2.S][0].S] = cnt++;
                else
                    trace[i_node[neigh2.F][neigh2.S][1].F][i_node[neigh2.F][neigh2.S][1].S] = cnt++;
                trace[neigh1.F][neigh1.S] = cnt++;
            }
            else{
                trace[neigh1.F][neigh1.S] = cnt++;
                if(i_node[neigh1.F][neigh1.S][0] != mp(ti, tj))
                    trace[i_node[neigh1.F][neigh1.S][0].F][i_node[neigh1.F][neigh1.S][0].S] = cnt++;
                else
                    trace[i_node[neigh1.F][neigh1.S][1].F][i_node[neigh1.F][neigh1.S][1].S] = cnt++;
                trace[neigh2.F][neigh2.S] = cnt++;
            }

        }
    }
}

void printTrace(){
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            printf("%d\t",trace[i][j]);
        }
        printf("\n");
    }
}

int main() {
    preProcessInternalCycles();
    preProcessExternalCycles();
    int start_i = 5, start_j = 6;
    solve(start_i, start_j);
    printTrace();
    return 0;
}
