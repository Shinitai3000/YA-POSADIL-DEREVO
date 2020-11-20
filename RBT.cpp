#include "main.h"

template<typename Key, typename Value, typename Node = Node<Key, Value>>
class RBT : public BinTree<Key, Value, Node>{
    void Balanced_insert(Key key, Value val){
        Node* N = insert(Key key, Value val);
    }
};

int main() {
    return 0;
}
