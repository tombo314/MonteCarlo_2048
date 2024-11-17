#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define now() chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count()

template <typename T, typename U>
bool chmax(T &a, U b){
    if (a<b){
        a = b;
        return true;
    }
    return false;
}

mt19937 mt(now());
/* [a, b) */
ll rand(ll a, ll b) {
    assert(a<b);
    return mt()%(b-a)+a;
}

// grid coordは1-indexed

const int g_size = 4;
const int turn_num = 50000;
const string dirs = "FBLR";

pair<int, int> dim1to2(vector<vector<int>> &grid, int n){
    int idx = 0;
    for (int i=0; i<g_size; i++){
        for (int j=0; j<g_size; j++){
            if (grid[i][j]==0){
                idx++;
            }
            if (idx==n){
                return {i, j};
            }
        }
    }

    return {-1, -1};
}

// turn_: 現在のターン数
class Node {
    int turn;
    int score = 0;
    vector<vector<int>> grid;
public:
    int first_dir_idx;
    
    Node(int turn_, vector<vector<int>> grid_){
        turn = turn_;
        grid = grid_;
    }

    vector<vector<int>> get_grid(){
        return grid;
    }

    // n: 1-dim coord
    void input(int idx, int val){
        int i, j;
        tie(i, j) = dim1to2(grid, idx);
        grid[i][j] = val;
        turn++;
    }

    // {merge後の配列, 獲得した点数}を返す
    pair<vector<int>, int> merge_num(vector<int> nums, char dir){
        int n = nums.size();
        int score_tmp = 0;

        if (dir=='F'){
            for (int i=0; i<n-1; i++){
                if (nums[i]!=0 && nums[i]==nums[i+1]){
                    nums[i] += nums[i+1];
                    score_tmp += nums[i];
                    nums[i+1] = 0;
                    i++;
                }
            }
        } else if (dir=='B'){
            for (int i=n-1; i>0; i--){
                if (nums[i]!=0 && nums[i]==nums[i-1]){
                    nums[i] += nums[i-1];
                    score_tmp += nums[i];
                    nums[i-1] = 0;
                    i--;
                }
            }
        } else if (dir=='L'){
            for (int i=0; i<n-1; i++){
                if (nums[i]!=0 && nums[i]==nums[i+1]){
                    nums[i] += nums[i+1];
                    score_tmp += nums[i];
                    nums[i+1] = 0;
                    i++;
                }
            }
        } else if (dir=='R'){
            for (int i=n-1; i>0; i--){
                if (nums[i]!=0 && nums[i]==nums[i-1]){
                    nums[i] += nums[i-1];
                    score_tmp += nums[i];
                    nums[i-1] = 0;
                    i--;
                }
            }
        }

        return {nums, score_tmp};
    }

    // 盤面を傾ける
    // scoreを更新する
    // dir : FBLR
    void tilt(char dir){
        int score_tmp = 0;

        // 上
        if (dir=='F'){
            for (int i=0; i<g_size; i++){

                // 0以外を保持する
                vector<int> tmp;
                for (int j=0; j<g_size; j++){
                    if (grid[j][i]!=0){
                        tmp.emplace_back(grid[j][i]);
                        grid[j][i] = 0;
                    }
                }

                // 数を合成する
                int add;
                tie(tmp, add) = merge_num(tmp, dir);
                score_tmp += add;

                // 0を除外する
                vector<int> not_0;
                for (auto x: tmp){
                    if (x!=0){
                        not_0.emplace_back(x);
                    }
                }

                // 上に詰める
                for (int j=0; j<not_0.size(); j++){
                    grid[j][i] = not_0[j];
                }
            }
        }
        // 下
        else if (dir=='B'){
            for (int i=0; i<g_size; i++){

                // 0以外を保持する
                vector<int> tmp;
                for (int j=0; j<g_size; j++){
                    if (grid[j][i]!=0){
                        tmp.emplace_back(grid[j][i]);
                        grid[j][i] = 0;
                    }
                }

                // 数を合成する
                int add;
                tie(tmp, add) = merge_num(tmp, dir);
                score_tmp += add;
                
                // 0を除外する
                vector<int> not_0;
                for (auto x: tmp){
                    if (x!=0){
                        not_0.emplace_back(x);
                    }
                }

                // 下に詰める
                for (int j=0; j<not_0.size(); j++){
                    grid[g_size-1-j][i] = not_0[not_0.size()-1-j];
                }
            }
        }
        // 左
        else if (dir=='L'){
            for (int i=0; i<g_size; i++){

                // 0以外を保持する
                vector<int> tmp;
                for (int j=0; j<g_size; j++){
                    if (grid[i][j]!=0){
                        tmp.emplace_back(grid[i][j]);
                        grid[i][j] = 0;
                    }
                }

                // 数を合成する
                int add;
                tie(tmp, add) = merge_num(tmp, dir);
                score_tmp += add;
                
                // 0を除外する
                vector<int> not_0;
                for (auto x: tmp){
                    if (x!=0){
                        not_0.emplace_back(x);
                    }
                }

                // 左に詰める
                for (int j=0; j<not_0.size(); j++){
                    grid[i][j] = not_0[j];
                }
            }
        }
        // 右
        else if (dir=='R'){
            for (int i=0; i<g_size; i++){

                // 0以外を保持する
                vector<int> tmp;
                for (int j=0; j<g_size; j++){
                    if (grid[i][j]!=0){
                        tmp.emplace_back(grid[i][j]);
                        grid[i][j] = 0;
                    }
                }

                // 数を合成する
                int add;
                tie(tmp, add) = merge_num(tmp, dir);
                score_tmp += add;
                
                // 0を除外する
                vector<int> not_0;
                for (auto x: tmp){
                    if (x!=0){
                        not_0.emplace_back(x);
                    }
                }

                // 右に詰める
                for (int j=0; j<not_0.size(); j++){
                    grid[i][g_size-1-j] = not_0[not_0.size()-1-j];
                }
            }
        }

        score += score_tmp;
    }

    // ルールベースで盤面を評価する
    int evaluate(){
        return score;
    }

    // 貪欲法によって次の手を得る
    char get_greedy_dir(){
        char ret = '-';

        // B 増える
        for (int i=0; i<g_size-1; i++){
            for (int j=0; j<g_size; j++){
                if (grid[i][j]!=0 && grid[i][j]==grid[i+1][j]){
                    ret = 'B';
                }
            }
        }

        // L or R 増える
        if (ret=='-'){
            for (int i=0; i<g_size; i++){
                for (int j=0; j<g_size-1; j++){
                    if (grid[i][j]!=0 && grid[i][j]==grid[i][j+1]){
                        int rd = rand(0, 2);
                        if (rd==0){
                            ret = 'L';
                        } else {
                            ret = 'R';
                        }
                    }
                }
            }
        }

        // B 空きがある
        if (ret=='-'){
            for (int i=0; i<g_size-1; i++){
                for (int j=0; j<g_size; j++){
                    if (grid[i][j]!=0 && grid[i+1][j]==0){
                        ret = 'B';
                    }
                }
            }
        }

        // L or R 空きがある
        if (ret=='-'){
            set<char> s;
            for (int i=0; i<g_size; i++){
                for (int j=0; j<g_size-1; j++){
                    if (grid[i][j]==0 && grid[i][j+1]!=0){
                        s.insert('L');
                    }
                    if (grid[i][j]!=0 && grid[i][j+1]==0){
                        s.insert('R');
                    }
                }
            }
            vector<char> c;
            for (auto x: s){
                c.emplace_back(x);
            }
            if (c.size()>0){
                int rd = rand(0, c.size());
                ret = c[rd];
            }
        }

        if (ret=='-'){
            ret = 'F';
        }

        return ret;
    }

    int get_turn(){
        return turn;
    }

    // 貪欲プレイアウトをする
    // ランダムに数字をを置くところから
    void playout_greedy(){

        for (int t=turn; t<turn_num; t++){
            // 空き座標を数える
            int cnt_free = 0;
            for (int i=0; i<g_size; i++){
                for (int j=0; j<g_size; j++){
                    if (grid[i][j]==0){
                        cnt_free++;
                    }
                }
            }
            
            // 座標を乱択する
            if (cnt_free==0){
                break;
            }
            int next_coord = rand(1, cnt_free+1);

            // 盤面に数字を配置する
            vector<int> candy{2, 2, 2, 4};
            int rd = rand(0, candy.size());
            int next_val = candy[rd];

            input(next_coord, next_val);

            if (t==turn_num-1){
                return;
            }

            // 貪欲法に従って方向を得る
            char dir = get_greedy_dir();

            // // ランダムに傾ける
            // char dir = dirs[rand(0, dirs.size())];

            // 傾けられなくなったら終了
            if (dir=='-'){
                break;
            }

            // 傾ける
            tilt(dir);
        }
    }

    // 盤面を表示する
    void show_grid(){
        for (int i=0; i<g_size; i++){
            for (int j=0; j<g_size; j++){
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

double get_ucb1(int score, int trial_num, int trial_num_all){
    const double c = 70000;
    return (double)score/trial_num+c*sqrt(2*log(trial_num_all)/trial_num);
}

bool is_valid_dir(vector<vector<int>> &grid, char dir){
    bool ok = false;

    if (dir=='F'){
        for (int i=0; i<g_size-1; i++){
            for (int j=0; j<g_size; j++){
                if (grid[i][j]!=0 && grid[i][j]==grid[i+1][j]){
                    ok = true;
                }
                if (grid[i][j]==0 && grid[i+1][j]!=0){
                    ok = true;
                }
            }
        }
    } else if (dir=='B'){
        for (int i=0; i<g_size-1; i++){
            for (int j=0; j<g_size; j++){
                if (grid[i][j]!=0 && grid[i][j]==grid[i+1][j]){
                    ok = true;
                }
                if (grid[i][j]!=0 && grid[i+1][j]==0){
                    ok = true;
                }
            }
        }
    } else if (dir=='L'){
        for (int i=0; i<g_size; i++){
            for (int j=0; j<g_size-1; j++){
                if (grid[i][j]!=0 && grid[i][j]==grid[i][j+1]){
                    ok = true;
                }
                if (grid[i][j]==0 && grid[i][j+1]!=0){
                    ok = true;
                }
            }
        }
    } else if (dir=='R'){
        for (int i=0; i<g_size; i++){
            for (int j=0; j<g_size-1; j++){
                if (grid[i][j]!=0 && grid[i][j]==grid[i][j+1]){
                    ok = true;
                }
                if (grid[i][j]!=0 && grid[i][j+1]==0){
                    ok = true;
                }
            }
        }
    }

    return ok;
}

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    // 初期化
    vector grid_init(g_size, vector(g_size, 0));
    cout << "input the grid except any one square:" << endl;

    for (int i=0; i<g_size; i++){
        for (int j=0; j<g_size; j++){
            cin >> grid_init[i][j];
        }
    }

    // 盤面のインスタンス
    Node node{0, grid_init};

    cout << "input the excepted square and start." << endl;

    // 自動で乱択して入力する
    const bool auto_mode = true;

    // ターン開始
    for (int turn=0; turn<turn_num; turn++){

        cout << "turn : " << turn << endl;

        int coord, val;

        // 自動でプレイする
        if (auto_mode){
            vector<vector<int>> grid_debug = node.get_grid();
            int cnt_free = 0;
            for (int i=0; i<g_size; i++){
                for (int j=0; j<g_size; j++){
                    if (grid_debug[i][j]==0){
                        cnt_free++;
                    }
                }
            }
            coord = rand(1, cnt_free+1);
            vector<int> rd_val{2, 2, 2, 4};
            int rd = rand(0, rd_val.size());
            val = rd_val[rd];
        } else {
            cin >> coord >> val;
        }

        // 数字を置く
        node.input(coord, val);

        vector<vector<int>> grid_tmp = node.get_grid();
        string dirs_tmp;
        for (auto x: dirs){
            if (is_valid_dir(grid_tmp, x)){
                dirs_tmp += x;
            }
        }

        // ノードを3層展開する
        int dir_num = dirs_tmp.size();
        int cand_num = pow(dir_num, 3);
        vector<Node> nodes(cand_num, Node{-1, grid_tmp});
        int nodes_idx = 0;
        for (int i=0; i<dir_num; i++){
            for (int j=0; j<dir_num; j++){
                for (int k=0; k<dir_num; k++){
                    nodes[nodes_idx] = node;
                    nodes[nodes_idx].tilt(dirs_tmp[i]);
                    nodes[nodes_idx].tilt(dirs_tmp[j]);
                    nodes[nodes_idx].tilt(dirs_tmp[k]);
                    nodes[nodes_idx].first_dir_idx = i;
                    nodes_idx++;
                }
            }
        }
        
        vector<int> scores(cand_num);
        vector<int> trial_nums(cand_num);
        
        // 各ノード1回ずつシミュレーションする
        for (int i=0; i<cand_num; i++){
            Node node_selected = nodes[i];
            node_selected.playout_greedy();
            scores[i] += node_selected.evaluate();
            trial_nums[i]++;
        }

        const int simulation_num = 10000;
        const int simulation_num_border = 3000;

        // UCB1に基づいてノードを決定して、
        // モンテカルロシミュレーションを行う
        for (int simulation_cnt=0; simulation_cnt<simulation_num; simulation_cnt++){

            // ucb1が最大のノードを選ぶ
            int mx_score = 0;
            int mx_cand = -1;
            for (int i=0; i<cand_num; i++){
                double ucb1 = get_ucb1(scores[i], trial_nums[i], max(1, simulation_cnt));
                if (chmax(mx_score, ucb1)){
                    mx_cand = i;
                }
            }
            // ゲーム終了
            if (mx_cand==-1){
                node.show_grid();
                cout << "Game Over" << endl;
                return 0;
            }
            Node node_selected = nodes[mx_cand];

            // 貪欲プレイアウトを行う
            node_selected.playout_greedy();

            // 盤面を評価してスコアを更新する
            scores[mx_cand] += node_selected.evaluate();

            // 試行回数を更新する
            trial_nums[mx_cand]++;

            // 試行回数が閾値を超えたら終了
            if (trial_nums[mx_cand]>=simulation_num_border){
                break;
            }
        }

        // ucb1が最大の手を選ぶ
        int mx_score = 0;
        int mx_cand;
        for (int i=0; i<cand_num; i++){
            double ucb1 = scores[i]/trial_nums[i];
            if (chmax(mx_score, ucb1)){
                mx_cand = nodes[i].first_dir_idx;
            }
        }

        // 答えを選ぶ
        char operation = dirs_tmp[mx_cand];

        // 盤面を傾ける
        node.tilt(operation);

        // 答えを出力する
        cout << "dir  : " << operation << endl;

        // スコアを出力する
        cout << "score: " << node.evaluate() << endl;

        // 盤面を出力する
        node.show_grid();
    }
}

/*

0 0 2 2
0 0 0 0
0 0 0 0
0 0 0 0

*/