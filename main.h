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
    Node* getGrandDad(){
        if ((this != nullptr) && (this->parent != nullptr)){
            return (this->parent)->parent;
        }
        else{
            return nullptr;
        }
    }
    Node* getUncle(){
        Node* GD = this->getGrandDad();
        if (GD == nullptr)
            return nullptr; // No grandparent means no uncle
        if (this->parent == GD->left)
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
public:
    Node* root;
private:
    bool first_put = 1;

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

    Node* yet_not_insert(Key key, Value val, Node* now){ //recursive support function
        // dead end
        if(first_put == 1){
            root->value = val;
            root->key = key;
            first_put = 0;
            return root;
        }
        if((now->left == nullptr) && (now->key > key)){
            auto left = new Node();
            left->parent = now;
            left->value = val;
            left->key = key;
            return left;
        }
        if((right == nullptr) && (key > now->key)){
            auto right = new Node();
            right->parent = now;
            right->value = val;
            right->key = key;
            return right;
        }
        // base case
        if ((key < now->key) & (now->left != nullptr)){
            (now->left)->insert(val);
        }else{
            (now->right)->insert(val);
        }
    }

    Node* insert(Key key, Value val){
        return yet_not_insert(key, val, root);
    }

    Node* yet_not_find(Key key, Value val, Node* now){
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

    Node* find(Key key, Value val, Node* now){
        return yet_not_find(key, val, root);
    }

   Node * minValueNode(Node* node)
   {
    Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
    current = current->left;

    return current;
    }

    Node* deleteNode(Node* root, Key key, Value val)
    {
        if (root == NULL){
            return root;
        }
        if ( key < root->key ){
            root->left = deleteNode(root->left, key, val);
        }
        else if( key > root->key ){
            root->right = deleteNode(root->right, key, val);
        }
        else
        {
            //„N„u„„ „{„p„{„€„s„€-„„„€ „y„x „t„u„„„u„z
            if( (root->left == NULL) || (root->right == NULL) )
            {
                Node *temp = root->left ?
                root->left :
                root->right;

            //„N„u„„ „t„u„„„u„z
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // „O„t„~„€ „t„y„„„u
                *root = *temp;
                free(temp);
            }
            else
            {
                //„I„‹„u„} „}„y„~„y„}„p„|„Ž„~„€„s„€ „r „„‚„p„r„€„} „„€„t„t„u„‚„u„r„u;
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right,temp->key, team->val);
            }
        }
        if (root == NULL){
            return root;
        }
        //„}„u„~„‘„u„} „r„„ƒ„€„„„
        root->height = 1 + max(height(root->left),
        height(root->right));
        return root;
    }
};
