#include<iostream>
#include<queue>
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
    // Инициализация
    Node(Value v, Key k){
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        key = k;
        value = v;
        colour = 0;
        height = 1;
    }

    // Вычисляем баланс-фактор
    int getBalance(Node *N){
        if (N == NULL){
            return 0;
        }
        else{
            return height(N->left) - height(N->right);
        }
    }

};


template<typename Key, typename Value>
class BinTree{
public:
    Node* root;
    BinTree(Node* N){
        root = N;
    }
    bool first_put = 1;
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
        if((right == nullptr) && (val > value)){
            right = new Bin;
            right->parent = this;
            right->value = val;
            return;
        }
        // base case
        if ((val < value) & (left != nullptr)){
            left->insert(val);
        }else{
            right->insert(val);
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
                        Node* temp = now->right;
                        Node* par = now->parent;
                        if(now->key > (now->parent)->key){
                            delete now;
                            par->right = temp;
                        }
                        else{
                            delete now;
                            par->left = temp;
                        }

                    }
                    else if (now->right == nullptr) {
                        Node* temp = now->left;
                        Node* par = now->parent;
                        if(now->key > (now->parent)->key){
                            delete now;
                            par->right = temp;
                        }
                        else{
                            delete now;
                            par->left = temp;
                        }
                    else if ((now->right != nullptr ) && now->left != nullptr){
                        Node* templ = now->left;
                        Node* par = now->parent;
                        Node* tepmr = now->right;
                        Node* NOW;
                        NOW = now->right;
                        delete now;
                        while(NOW->left != nullptr){
                            NOW = NOW->left;
                        }
                        NOW->right->parent = NOW->parent;
                        NOW->parent->left= NOW->right;
                        NOW->left = templ;
                        NOW->parent = par;
                        NOW->right = tempr;


                    }


                    }
    }
}


    void print(){
        cout << value<<' ';
    }
};


int main(){

return 0;
}
