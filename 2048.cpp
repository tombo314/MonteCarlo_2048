#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, a, b) for (ll i=a; i<b; i++)
#define rrep(i, a, b) for (ll i=a; i>b; i--)
#define now() chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count()

template <typename T, typename U>
bool chmax(T &a, U b){
    if (a<b){
        a = b;
        return true;
    }
    return false;
}

template <typename T, typename U>
bool chmin(T &a, U b){
    if (a>b){
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
const int turn_num = 10000;
const string dirs = "FBLR";

pair<ll, ll> dim1to2(vector<vector<ll>> &grid, ll n){
    ll idx = 0;
    rep(i, 0, g_size){
        rep(j, 0, g_size){
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
    ll turn;
    vector<vector<ll>> grid;
public:
    Node(ll turn_, vector<vector<ll>> grid_){
        turn = turn_;
        grid = grid_;
    }

    vector<vector<ll>> get_grid(){
        return grid;
    }

    // n: 1-dim coord
    void input(ll idx, ll val){
        ll i, j;
        tie(i, j) = dim1to2(grid, idx);
        grid[i][j] = val;
        turn++;
    }

    vector<ll> merge_num(vector<ll> nums, char dir){
        int n = nums.size();

        if (dir=='F'){
            for (int i=0; i<n-1; i++){
                if (nums[i]!=0 && nums[i]==nums[i+1]){
                    nums[i] += nums[i+1];
                    nums[i+1] = 0;
                    i++;
                }
            }
        } else if (dir=='B'){
            for (int i=n-1; i>0; i--){
                if (nums[i]!=0 && nums[i]==nums[i-1]){
                    nums[i] += nums[i-1];
                    nums[i-1] = 0;
                    i--;
                }
            }
        } else if (dir=='L'){
            for (int i=0; i<n-1; i++){
                if (nums[i]!=0 && nums[i]==nums[i+1]){
                    nums[i] += nums[i+1];
                    nums[i+1] = 0;
                    i++;
                }
            }
        } else if (dir=='R'){
            for (int i=n-1; i>0; i--){
                if (nums[i]!=0 && nums[i]==nums[i-1]){
                    nums[i] += nums[i-1];
                    nums[i-1] = 0;
                    i--;
                }
            }
        }

        return nums;
    }

    // 盤面を傾ける
    // dir : FBLR
    void tilt(char dir){
        // 上
        if (dir=='F'){
            rep(i, 0, g_size){

                // キャンディーを保持する
                vector<ll> tmp;
                rep(j, 0, g_size){
                    if (grid[j][i]!=0){
                        tmp.emplace_back(grid[j][i]);
                        grid[j][i] = 0;
                    }
                }

                // 数を合成する
                tmp = merge_num(tmp, dir);

                // 0を除外する
                vector<ll> not_0;
                for (auto x: tmp){
                    if (x!=0){
                        not_0.emplace_back(x);
                    }
                }

                // 上に詰める
                rep(j, 0, not_0.size()){
                    grid[j][i] = not_0[j];
                }
            }
        }
        // 下
        else if (dir=='B'){
            rep(i, 0, g_size){

                // キャンディーを保持する
                vector<ll> tmp;
                rep(j, 0, g_size){
                    if (grid[j][i]!=0){
                        tmp.emplace_back(grid[j][i]);
                        grid[j][i] = 0;
                    }
                }

                // 数を合成する
                tmp = merge_num(tmp, dir);
                
                // 0を除外する
                vector<ll> not_0;
                for (auto x: tmp){
                    if (x!=0){
                        not_0.emplace_back(x);
                    }
                }

                // 下に詰める
                rep(j, 0, not_0.size()){
                    grid[g_size-1-j][i] = not_0[not_0.size()-1-j];
                }
            }
        }
        // 左
        else if (dir=='L'){
            rep(i, 0, g_size){

                // キャンディーを保持する
                vector<ll> tmp;
                rep(j, 0, g_size){
                    if (grid[i][j]!=0){
                        tmp.emplace_back(grid[i][j]);
                        grid[i][j] = 0;
                    }
                }

                // 数を合成する
                tmp = merge_num(tmp, dir);
                
                // 0を除外する
                vector<ll> not_0;
                for (auto x: tmp){
                    if (x!=0){
                        not_0.emplace_back(x);
                    }
                }

                // 左に詰める
                rep(j, 0, not_0.size()){
                    grid[i][j] = not_0[j];
                }
            }
        }
        // 右
        else if (dir=='R'){
            rep(i, 0, g_size){

                // キャンディーを保持する
                vector<ll> tmp;
                rep(j, 0, g_size){
                    if (grid[i][j]!=0){
                        tmp.emplace_back(grid[i][j]);
                        grid[i][j] = 0;
                    }
                }

                // 数を合成する
                tmp = merge_num(tmp, dir);
                
                // 0を除外する
                vector<ll> not_0;
                for (auto x: tmp){
                    if (x!=0){
                        not_0.emplace_back(x);
                    }
                }

                // 右に詰める
                rep(j, 0, not_0.size()){
                    grid[i][g_size-1-j] = not_0[not_0.size()-1-j];
                }
            }
        }
    }

    // ルールベースで盤面を評価する
    ll evaluate(){
        ll score = 0;
        for (int i=0; i<g_size; i++){
            for (int j=0; j<g_size; j++){
                score += pow(grid[i][j], 2);
            }
        }
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

    ll get_turn(){
        return turn;
    }

    // 貪欲プレイアウトをする
    // ランダムにキャンディーを置くところから
    void playout_greedy(){

        rep(t, turn, turn_num){
            // 空き座標を数える
            ll cnt_free = 0;
            rep(i, 0, g_size){
                rep(j, 0, g_size){
                    if (grid[i][j]==0){
                        cnt_free++;
                    }
                }
            }
            
            // 座標を乱択する
            if (cnt_free==0){
                break;
            }
            ll next_coord = rand(1, cnt_free+1);

            // 盤面にキャンディーを配置する
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

            // // debug
            // // グリッドを表示する
            // show_grid();
        }
    }

    // 盤面を表示する
    void show_grid(){
        rep(i, 0, g_size){
            rep(j, 0, g_size){
                cerr << grid[i][j] << " ";
            }
            cerr << endl;
        }
        cerr << endl;
    }
};

double get_ucb1(ll score, ll trial_num, ll trial_num_all){
    const double c = 3000'0000;
    return (double)score/trial_num+c*sqrt(2*log(trial_num_all)/trial_num);
}

ll debug_simulation_cnt = 0;

bool is_valid_dir(vector<vector<ll>> &grid, char dir){
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
    vector grid_init(g_size, vector(g_size, 0LL));
    cout << "input the grid except any one square:" << endl;

    for (int i=0; i<g_size; i++){
        for (int j=0; j<g_size; j++){
            cin >> grid_init[i][j];
        }
    }

    // 盤面のインスタンス
    Node node{0, grid_init};

    cout << "input the excepted square and start." << endl;

    const bool auto_mode = false;

    // ターン開始
    rep(turn, 0, turn_num){

        ll coord, val;

        if (auto_mode){
            // debug
            vector<vector<ll>> grid_debug = node.get_grid();
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

        // キャンディーを置く
        node.input(coord, val);

        vector<vector<ll>> grid_tmp = node.get_grid();
        string dirs_tmp;
        for (auto x: dirs){
            if (is_valid_dir(grid_tmp, x)){
                dirs_tmp += x;
            }
        }

        // ノードを展開する
        ll cand_num = dirs_tmp.size();
        vector<Node> nodes(cand_num, Node{-1, grid_tmp});
        rep(i, 0, cand_num){
            nodes[i] = node;
            nodes[i].tilt(dirs_tmp[i]);
        }

        vector<ll> scores(cand_num);
        vector<ll> trial_nums(cand_num);
        
        // 各ノード1回ずつシミュレーションする
        rep(i, 0, cand_num){
            Node node_selected = nodes[i];
            node_selected.playout_greedy();
            scores[i] += node_selected.evaluate();
            trial_nums[i]++;
        }

        const ll simulation_num = 2000;
        const ll simulation_num_border = 500;

        // UCB1に基づいてノードを決定して、
        // モンテカルロシミュレーションを行う
        rep(simulation_cnt, 0, simulation_num){

            debug_simulation_cnt++;

            // ucb1が最大のノードを選ぶ
            ll mx_score = 0;
            ll mx_cand;
            rep(i, 0, cand_num){
                double ucb1 = get_ucb1(scores[i], trial_nums[i], max(1LL, simulation_cnt));
                if (chmax(mx_score, ucb1)){
                    mx_cand = i;
                }
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
        ll mx_score = 0;
        ll mx_cand;
        rep(i, 0, cand_num){
            double ucb1 = scores[i]/trial_nums[i];
            if (chmax(mx_score, ucb1)){
                mx_cand = i;
            }
        }

        // 答えを選ぶ
        char operation = dirs_tmp[mx_cand];

        // 盤面を傾ける
        node.tilt(operation);

        // 答えを出力する
        cout << operation << endl;

        // 盤面を出力する
        node.show_grid();
    }

    cerr << "loop_num: " << debug_simulation_cnt << endl;
}

/*

操作をキャンセルできるようにする

*/