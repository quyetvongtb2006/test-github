#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = double;
using ld = long double;
const int TEST_MIN = 1;
const int TEST_MAX = 5;
const string Code_name = ""; // Tên chương trình chạy, đọc input từ file .inp và in ra file .out
// file id.check in ra kết quả và check output của test id.inp
struct Order
{
    int weight, profit;
    int i;
};
struct Truck
{
    int lb, ub;
    int cost, i;

    int penalty(int w)
    {
        if (w >= lb && w <= ub) return 0;
        if (w < lb) return lb - w;
        return w - ub;
    }
};

const int MAX_N = 1e4;
const int MAX_K = 1e3;
const int MAX_UB = 1e3;

int n, k;
Order orders[MAX_N];
Truck trucks[MAX_K];

void solve(int id)
{
    ifstream Copy((to_string(id) + ".inp").c_str()); // Đọc test id.inp
    ofstream Paste(".inp"); // Copy "id.inp" to ".inp"
    Copy >> n >> k;
    for (int i = 0; i < n; i++)
    {
        Copy >> orders[i].weight >> orders[i].profit;
        orders[i].i = i;
    }
    for (int i = 0; i < k; i++)
    {
        Copy >> trucks[i].lb >> trucks[i].ub >> trucks[i].cost;
        trucks[i].i = i;
    }
    // Paste test
    Paste << n << ' ' << k << '\n';
    for (int i = 0; i < n; i++)
    {
        Paste << orders[i].weight << ' ' << orders[i].profit << '\n';
//        orders[i].i = i;
    }
    for (int i = 0; i < k; i++)
    {
        Paste << trucks[i].lb << ' ' << trucks[i].ub << ' ' << trucks[i].cost << '\n';
//        trucks[i].i = i;
    }
    Copy.close();
    Paste.close();
    system((Code_name + ".exe").c_str()); // Chạy chương trình
    // read solution
    ifstream fin(".out");
    ofstream check((to_string(id) + ".check").c_str());
    ofstream fout((to_string(id) + ".out").c_str());
    int m;
    fin >> m;
    fout << m << '\n';
    vector<int> weight(k);
    vector<char> used(k), used_orders(n);

    ll profit = 0;
    for (int i = 0; i < m; i++)
    {
        int order_id, truck_id;
        fin >> order_id >> truck_id;
        fout << order_id << ' ' << truck_id << '\n';
        order_id--;
        truck_id--;

        if (used_orders[order_id])
        {
            check << "Order " << order_id + 1 << " assigned multiple times\n";
            cerr << "Test " << id << ' ' << "Order " << order_id + 1 << " assigned multiple times\n";
//            return 0;
        }

        auto &order = orders[order_id];
        auto &truck = trucks[truck_id];

        profit += order.profit;
        weight[truck_id] += order.weight;
        used[truck_id] = 1;
        used_orders[order_id] = 1;
    }

    for (int i = 0; i < k; i++)
    {
        if (!used[i]) continue;
        auto &truck = trucks[i];
        if (weight[i] < truck.lb || weight[i] > truck.ub)
        {
            check << "Truck " << i + 1 << " has weight " << weight[i] << " out of range [" << truck.lb << ", " << truck.ub << "]\n";
            cerr << "TEST " << id << ' ' << "Truck " << i + 1 << " has weight " << weight[i] << " out of range [" << truck.lb << ", " << truck.ub << "]\n";
//            return 0;
        }
        profit -= truck.cost;
    }
    check << profit << "\n";
    fout.close();
    check.close();
    fin.close();
}
int main()
{
    for (int i = TEST_MIN; i <= TEST_MAX; i++)
        solve(i);
    return 0;
}
