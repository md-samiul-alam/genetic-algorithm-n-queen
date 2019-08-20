// Group 1
// Section: A2
// Md. Samiul Alam (14.02.04.033)

#include <bits/stdc++.h>
using namespace std;

#define read() freopen("input.txt","r",stdin)
#define INF ((1<<29)-1)
#define EPS (1e-9)
#define PI (2*acos(0.0))
#define ll long long
#define ull unsigned ll
#define SIZE ((ll)1e6)+10
#define testcase ll T;cin>>T;for(int t=1;t<=T;t++)
#define printcase() cout<<"Case "<<t<<":\n"
#define pb push_back
#define PAR_SIZE 1000000+10
#define BFS_GRID 1010
#define NL() cout << endl
#define FOR(itt,n) for(int itt=0;itt<n;++itt)
#define FOR1(itt,n) for(int itt=1;itt<=n;++itt)
#define MAX_PRIME 1000010
#define MUTATION_RATE 100


struct Solution{
    pair<int,char>columnIndex[10];
    int fitness;
}solution[100];

int calculateFitness(Solution s){
    int attacks=0;
    FOR(j,8){
        FOR(k,8){
            if(j==k)continue;
            if(s.columnIndex[j].second=='Q'){
                if(s.columnIndex[j].first==s.columnIndex[k].first || abs(j-k)==abs(s.columnIndex[j].first-s.columnIndex[k].first))attacks++;
            }
            if(s.columnIndex[j].second=='B'){
                if(abs(j-k)==abs(s.columnIndex[j].first-s.columnIndex[k].first))attacks++;
            }
        }
    }
    int fitness = 56-attacks;
    return fitness;
}

void generateRandomSolution(int n){
    FOR(i,n){
        int queen = 4;
        int bishop = 4;
        FOR(j,8){
            bool draw = rand()%2; // if draw == true then queen otherwise bishop
            if(draw){
                if(queen){
                    solution[i].columnIndex[j] = make_pair(rand()%8,'Q');
                    --queen;
                }
                else{
                    solution[i].columnIndex[j] = make_pair(rand()%8,'B');
                    --bishop;
                }
            }
            else{
                if(bishop){
                    solution[i].columnIndex[j] = make_pair(rand()%8,'B');
                    --bishop;
                }
                else{
                    solution[i].columnIndex[j] = make_pair(rand()%8,'Q');
                    --queen;
                }
            }
        }

        solution[i].fitness = calculateFitness(solution[i]);
    }

}

void printFirstNSolution(int n){
    FOR(i,n){
        FOR(j,8){
            cout << solution[i].columnIndex[j].first << ' ';
        }
        cout << endl;
        FOR(j,8){
            cout << solution[i].columnIndex[j].second << ' ';
        }
        cout << endl;
        cout << solution[i].fitness;
        cout << endl;
        cout << endl;
    }
}




bool cmp(Solution a, Solution b){
    return a.fitness>b.fitness;
}

void getParentIndex(int parentIndex[], int n){
    int totalFitnessSum=0;
    int cumulativeFitnessSum[n+1];
    bool alreadySelected[n+1];
    int numberOfParent=n>>1;
    memset(alreadySelected,false,sizeof(alreadySelected));
    int k=0;
    FOR(i,n){
        totalFitnessSum+=solution[i].fitness;
        cumulativeFitnessSum[i]=totalFitnessSum;
    }
    while(k<numberOfParent){
        int randomValue = rand()%totalFitnessSum+1;
        FOR(i,n){
            if(randomValue<=cumulativeFitnessSum[i]&&!alreadySelected[i]){
                parentIndex[k++]=i;
                alreadySelected[i]=true;
                break;
            }
        }
    }
}

Solution getMutedChild(Solution child){
    int index1 = rand()%8, index2 = rand()%8;
    int totalSize = max(index1,index2) - min(index1,index2)+1;
    for(int i=0; i<totalSize; i++){
        int randomIndex_1 = min(index1,index2)+rand()%totalSize;
        int randomIndex_2 = min(index1,index2)+rand()%totalSize;
        swap(child.columnIndex[randomIndex_1].first,child.columnIndex[randomIndex_2].first);
    }
    return child;
}

Solution crossOver(Solution a, Solution b, int mutationRate){
    int st = rand()%8;
    int et = rand()%8;
    int temp = st;
    st = min(st,et);
    et = max(temp,et);
    int totalSelectedIndex=0;
    Solution child;
    bool selectedColumnIndex[10];
    memset(selectedColumnIndex,false,sizeof(selectedColumnIndex));


    for(int i=st; i<=et; i++){
        child.columnIndex[i].first = a.columnIndex[i].first;
        selectedColumnIndex[a.columnIndex[i].first]=true;
        ++totalSelectedIndex;
    }
    int childRestIndex = et+1;
    while(totalSelectedIndex<8){
        ++et;
        if(!selectedColumnIndex[b.columnIndex[et%8].first]){
            child.columnIndex[childRestIndex%8]=b.columnIndex[et%8];
            ++totalSelectedIndex;
            ++childRestIndex;
        }
    }

    int queen = 4;
    int bishop = 4;
    FOR(j,8){
        bool draw = rand()%2; // if draw == true then queen otherwise bishop
        if(draw){
            if(queen){
                child.columnIndex[j].second = 'Q';
                --queen;
            }
            else{
                child.columnIndex[j].second = 'B';
                --bishop;
            }
        }
        else{
            if(bishop){
                child.columnIndex[j].second = 'B';
                --bishop;
            }
            else{
                child.columnIndex[j].second = 'Q';
                --queen;
            }
        }
    }

    if(rand()%100<=mutationRate)child = getMutedChild(child);

    child.fitness = calculateFitness(child);
    return child;
}

void showSolution(Solution s){
    FOR(i,8){
        FOR(j,8){
            if(j==s.columnIndex[i].first)cout << s.columnIndex[i].second << ' ';
            else cout << '.' << ' ';
        }
        cout << endl;
    }
}


int main()
{
    #ifdef pinanzo
        //read();
        //freopen("output.txt","w",stdout);
    #endif // pinanzo
    //ios_base::sync_with_stdio(0);
    //cin.tie(NULL);
    //cout.tie(NULL);
    int n;
    int totalIteration;
    int mutationRate;
    int it=1;
    int crossOverRate;
    cout << "Initial Population: "; cin >> n;
    cout << "Total number of iteration: "; cin >> totalIteration;
    cout << "Mutation Rate (on a scale of 100): "; cin >> mutationRate;
    cout << "Cross Over Rate (on a scale of 100): "; cin >> crossOverRate;
    //cin >> n >> totalIteration >> mutationRate >> crossOverRate;

    generateRandomSolution(n);
    sort(solution,solution+n, cmp);

    for(it=1; it<=totalIteration; ++it){
        if(rand()%100<=crossOverRate)continue;
        int parentIndex[100];
        getParentIndex(parentIndex,n);
        int numberOfChild = n>>1;
        for(int i=0; i<numberOfChild; i+=2){
            solution[n+i]=crossOver(solution[parentIndex[i]],solution[parentIndex[i+1]], mutationRate);
            solution[n+i+1]=crossOver(solution[parentIndex[i+1]],solution[parentIndex[i]], mutationRate);
        }
        sort(solution,solution+n+(n>>1), cmp);
        if(calculateFitness(solution[0])==56)break;
    }
    cout << "Solution found on " << it << " iteration" << endl;
    //printFirstNSolution(n+(n>>1));
    showSolution(solution[0]);


    return 0;
}

