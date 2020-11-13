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
    Node(Value v, Key k){
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        key = k;
        value = v;
        colour = 0;
        height = 1;
    }

    int getBalance(Node *N){
        if (N == NULL){
            return 0;
        }
        else{
            return height(N->left) - height(N->right);
        }
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
                        //Node* temp = now->right;
                        //Node* par = now->parent;
                        if(now->key > (now->parent)->key){
                            //par->right = temp;
                            now->parent->right = now->right;
                            delete now;
                        }
                        else{
                            //par->left = temp;
                            now->parent->left = now->right;
                            delete now;

                        }

                    }
                    else if (now->right == nullptr) {
                        //Node* temp = now->left;
                        //Node* par = now->parent;
                        if(now->key > (now->parent)->key){
                            //par->right = temp;
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
                        Node* tepmr = now->right;
                        Node* NOW;
                        NOW = now->right;
                        delete now;
                        //Ќаходит наименьший элемент в правом поддереве - NOW
                        while(NOW->left != nullptr){
                            NOW = NOW->left;
                        }
                        // родитель NOW становитс€ родителем его правого сына
                        NOW->right->parent = NOW->parent;
                        NOW->parent->left= NOW->right;
                        // ј сам он становитс€ на место удаленного звена
                        NOW->left = templ;
                        NOW->parent = par;
                        NOW->right = tempr;

                    }


                    }
    }
};


    void print(){
        cout << value<<' ';
    }
};


int main(){

return 0;
}
