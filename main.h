#include<iostream>
using namespace std;

 template<typename Key, typename Value>
 struct Node{
    Node* parent; //  previous
    Node* left;    //left value
    Node* right; //right value
    Key key;
    Value value;
    bool colour;
    int height;
    Node(Value v, Key k){
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        key = k;
        value = v;
        colour = 0;
        height = 1;
    }

    int getBalance(Node* N){
        if (N == nullptr){
            return 0;
        }
        else{
            return height(N->left) - height(N->right);
        }
    }
    Node* getGrandDad(Node* N){
        if ((N != nullptr) && (N->parent != nullptr)){
            return (N->parent)->parent;
        }
        else{
            return nullptr;
        }
    }

    Node* getUncle(Node* N){
        Node* GD = getGrandDad(N);
        if (GD == nullptr)
            return nullptr; // No grandparent means no uncle
        if (N->parent == GD->left)
            return GD->right;
        else
            return GD->left;
    }

    void print(){
        cout << value<<' ';
    }

};


template<typename Key, typename Value, typename Node = Node<Key, Value>>
class BinTree{
private:
    Node* root;
    bool first_put = 1;

    BinTree(Key key, Value val){
        root->key = key;
        root->value = val;
    }

    void rotate_left(Node *N){
        Node* pivot = N->right;

        pivot->parent = N->parent; //  G->N->pivot changed into G->pivot
        if (N->parent != nullptr){ //check N was not root
            if ((N->parent)->left == N){ // if N was left child
                (N->parent)->left = pivot;// pivot become left child instead of N
            }
            else{
                (N->parent)->right = pivot; // same
            }
        }

        N->right = pivot->left; // pl<-pivot->pr changed into N->pl
        if (pivot->left != nullptr){
            (pivot->left)->parent = N; // N is parent for pl
        }
        N->parent = pivot;
        pivot->left = N;
}

    void rotate_right(Node* N){
        Node* pivot = N->left;

        pivot->parent = N->parent;
        if (N->parent != nullptr){
            if ((N->parent)->left == N){
                (N->parent)->left = pivot;
            }
            else{
                (N->parent)->right = pivot;
            }
        }

        N->left = pivot->right;
        if (pivot->right != nullptr){
            (pivot->right)->parent = N;
        }
        N->parent = pivot;
        pivot->right = N;
    }




    void insert(Key key, Value val, Node* now){
        // dead end
        if(first_put == 1){
            now->value = val;
            now->key = key;
            first_put = 0;
            return;
        }
        if((now->left == nullptr) && (now->key > key)){
            auto left = new Node();
            left->parent = now;
            left->value = val;
            left->key = key;
            return;
        }
        if((right == nullptr) && (key > now->key)){
            auto right = new Node();
            right->parent = now;
            right->value = val;
            right->key = key;
            return;
        }
        // base case
        if ((key < now->key) & (now->left != nullptr)){
            (now->left)->insert(val);
        }else{
            (now->right)->insert(val);
        }
    }

    Node* find(Key key, Value val, Node* now){
                if ((key == now->key) && (val == now->value)) {
                    return now;
                }
                else if (key < now->key) {
                    if (now->left != nullptr){
                       return find(key, val, now->left);
                    }
                    else{
                        return nullptr;
                    }
                }
                else if (key > now->key) {
                    if (now->right != nullptr){
                       return find(key, val, now->right);
                    }
                    else{
                        return nullptr;
                    }
                }
    }

    void Delete(Key key, Value val, Node* now){
                if(find(key, val, now)!= nullptr){
                    // node with only one child or no child
                    if (now->left == nullptr) {
                        if(now->key > (now->parent)->key){
                            now->parent->right = now->right;
                            delete now;
                        }
                        else{
                            now->parent->left = now->right;
                            delete now;

                        }

                    }
                    else if (now->right == nullptr) {
                        if(now->key > (now->parent)->key){
                            now->parent->right = now->left;
                            delete now;
                        }
                        else{
                            now->parent->left = now->left;
                            delete now;
                        }
                    }
                    else if ((now->right != nullptr ) && now->left != nullptr){
                        Node* templ = now->left;
                        Node* par = now->parent;
                        Node* tempr = now->right;
                        Node* NOW;
                        NOW = now->right;
                        delete now;
                        //find the less (NOW) in right tree
                        while(NOW->left != nullptr){
                            NOW = NOW->left;
                        }
                        //Now's parent become Now's right son's parent
                        NOW->right->parent = NOW->parent;
                        NOW->parent->left= NOW->right;
                        // Go to deleted place
                        NOW->left = templ;
                        NOW->parent = par;
                        NOW->right = tempr;
                    }
                }
    }
};
