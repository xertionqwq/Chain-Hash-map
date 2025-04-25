#include<iostream>
#include<list>
#include<vector>
#include<algorithm>

using namespace std;

class Myhash {
    struct Node {
        int key;
        int val;
        Node(int k, int v) :key(k), val(v) {}
    };

private:
    vector<list<Node>>hs;
    int size;

public:
    Myhash(int n) {
        hs.resize(n);
        size = 0;
    }

    ~Myhash() {}

    //增/改
    void put(int key, int val) {
        int idx = findHash(key);
        //链表为空，直接新建
        if (hs[idx].empty()) {
            hs[idx].push_front(Node(key, val));
            size++;
            return;
        }
        //遍历链表，查看是否有键值
        for (auto &p : hs[idx]) {
            if (p.key == key) {
                p = Node(key, val);
                return;
            }
        }
        //没有键值，选择头插法
        hs[idx].push_front(Node(key, val));
        size++;
    }

    //删
    void remove(int key) {
        auto& list = hs[findHash(key)];

        if (list.empty()) return;
        list.remove_if([key](Node& node) { return node.key == key; });
        size--;
    }

    //查
    int getVal(int key) {
        int idx = findHash(key);

        if (hs[idx].empty())
            return -1;

        for (const auto& p : hs[idx]) {
            if (p.key == key) return p.val;
        }

        return -1;
    }

    //打印哈希表
    void PrintHash() {
        printf("\n");
        for (auto& node : hs) {
            if (node.empty()) {
                cout << "此处为空" << endl;
                continue;
            }
            for (auto& p : node) {
                cout << "key=" << p.key << " value=" << p.val << " -> ";
            }
            printf("\n");
        }
        printf("\n");
    }

    int getSize() const{
        return size;
    }

private:
    int findHash(int key) const {
        int idx = key % hs.capacity();
        return idx;
    }
};

static void test01(Myhash& h) {
    int m = 1;
    while (m) {
        int key, val;
        cout << " 1增/改 2删 3查 4打印 5查询大小 0退出 " << endl;
        cin >> m;
        switch (m) {
        case 1:
            cout << "输入key and value" << endl;
            cin >> key >> val;
            h.put(key,val);
            break;
        case 2:
            cout << "输入key" << endl;
            cin >> key;
            h.remove(key);
            break;
        case 3:
            cout << "输入key" << endl;
            cin >> key;
            cout << "对应键值对为：" << key << " " << h.getVal(key) << endl;
            break;
        case 4:
            h.PrintHash();
            break;
        case 5:
            cout << "已有个数：" << h.getSize() << endl;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    int n;
    cout << "输入n创建哈希表" << endl;
    cin >> n;
    Myhash x(n);
    test01(x);

    return 0;
}