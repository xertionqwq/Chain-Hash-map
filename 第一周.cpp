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

    //��/��
    void put(int key, int val) {
        int idx = findHash(key);
        //����Ϊ�գ�ֱ���½�
        if (hs[idx].empty()) {
            hs[idx].push_front(Node(key, val));
            size++;
            return;
        }
        //���������鿴�Ƿ��м�ֵ
        for (auto &p : hs[idx]) {
            if (p.key == key) {
                p = Node(key, val);
                return;
            }
        }
        //û�м�ֵ��ѡ��ͷ�巨
        hs[idx].push_front(Node(key, val));
        size++;
    }

    //ɾ
    void remove(int key) {
        auto& list = hs[findHash(key)];

        if (list.empty()) return;
        list.remove_if([key](Node& node) { return node.key == key; });
        size--;
    }

    //��
    int getVal(int key) {
        int idx = findHash(key);

        if (hs[idx].empty())
            return -1;

        for (const auto& p : hs[idx]) {
            if (p.key == key) return p.val;
        }

        return -1;
    }

    //��ӡ��ϣ��
    void PrintHash() {
        printf("\n");
        for (auto& node : hs) {
            if (node.empty()) {
                cout << "�˴�Ϊ��" << endl;
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
        cout << " 1��/�� 2ɾ 3�� 4��ӡ 5��ѯ��С 0�˳� " << endl;
        cin >> m;
        switch (m) {
        case 1:
            cout << "����key and value" << endl;
            cin >> key >> val;
            h.put(key,val);
            break;
        case 2:
            cout << "����key" << endl;
            cin >> key;
            h.remove(key);
            break;
        case 3:
            cout << "����key" << endl;
            cin >> key;
            cout << "��Ӧ��ֵ��Ϊ��" << key << " " << h.getVal(key) << endl;
            break;
        case 4:
            h.PrintHash();
            break;
        case 5:
            cout << "���и�����" << h.getSize() << endl;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    int n;
    cout << "����n������ϣ��" << endl;
    cin >> n;
    Myhash x(n);
    test01(x);

    return 0;
}