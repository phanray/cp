mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());

int rand(){
    return uniform_int_distribution<int>(1, INT_MAX)(rd);
}

using type = int;

struct Node{
    type val;
    int weight, sz;
    bool rev;
    Node *left, *right;

    Node(type key) : val(key), weight(rand()), sz(1), rev(false), left(NULL), right(NULL){};
    Node(type key, int pri) : val(key), weight(pri), sz(1), rev(false), left(NULL), right(NULL){};
} *root;

struct Treap{

    int sz(Node *node){
        return node ? node->sz : 0;
    }

    void upd_sz(Node *node){
        if (node)
            node->sz = 1 + sz(node->left) + sz(node->right);
    }

    void heap(Node *node){
        if (!node)
            return;

        Node *priority = node;

        if (node->left && node->left->weight > priority->weight)
            priority = node->left;

        if (node->right && node->right->weight > priority->weight)
            priority = node->right;

        if (priority != node){
            swap(node->weight, priority->weight);

            heap(priority);
        }
    }

    Node *build(int l, int r){
        if (l > r)
            return NULL;

        int mid = l + r >> 1;
        Node *node = new Node(a[mid]);

        node->left = build(l, mid - 1);
        node->right = build(mid + 1, r);

        heap(node);
        upd_sz(node);

        return node;
    }

    void push(Node *node){
        if (node && node->rev){
            node->rev = false;
            swap(node->left, node->right);

            if (node->left)  
                node->left->rev ^= true;

            if (node->right)  
                node->right->rev ^= true;
        }
    }

    void split(Node *node, Node *&left, Node *&right, type key){
        if (!node)
            return void(left = right = NULL);

        push(node);

        if (sz(node->left) < key){
            split(node->right, node->right, right, key - sz(node->left) - 1); 
            left = node;
        }else{
            split(node->left, left, node->left, key); 
            right = node;
        }

        upd_sz(node);
    }

    void merge(Node *&node, Node *left, Node *right){
        push(left);
        push(right);

        if (!left || !right)
            node = left ? left : right;
        else if (left->weight > right->weight)
            merge(left->right, left->right, right), node = left;
        else
            merge(right->left, left, right->left), node = right;

        upd_sz(node);
    }

    void insert(int i, type key){
        Node *t1, *t2;

        split(root, t1, t2, i - 1);
        merge(t1, t1, new Node(key));
        merge(root, t1, t2);
    }

    void erase(int i){
        Node *t1, *t2, *t3;

        split(root, t1, t2, i - 1);
        split(t2, t2, t3, 1);
        merge(root, t1, t3);
    }

    void reverse(int l, int r){
        Node *t1, *t2, *t3;

        split(root, t1, t2, l);
        split(t2, t2, t3, r - l + 1);

        t2->rev ^= true;

        merge(root, t1, t2);
        merge(root, root, t3);
    }

}treap;
