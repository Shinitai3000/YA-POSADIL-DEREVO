#include "main.h"

template<typename Key, typename Value, typename Node = Node<Key, Value>>
class RBT : public BinTree<Key, Value, Node>{

    ~RBT(){
        destroy(this->root);
    }
    //to prevent leak of memory
    void destroy(Node* N){
        if(N->left != nullptr){
            destroy(N->left);
        }
        if(N->right != nullptr){
            destroy(N->right);
        }
        delete N;
    }

    void Balanced_insert(Key key, Value val){
        Node* N = insert(key, val);

        if (N == this->root ){
            return;
        }
        N->colour = 1;

        auto parent = N->parent;
        while (N != this->root && parent->colour == 1){
            auto GD = N->getGrandDad();
            auto Un = N->getUncle();
            auto parent = N->parent;

			if (GD->left == N->parent){// if parent is left child
                if (Un == nullptr){
					if (parent->right == N) { // if we are right son
						rotate_left(parent); //swap
					}
					rotate_right(GD);
					GD->colour = 1;
					N->colour = 0;
					break; // GD and N has the same colour so no need to check further
				}
                else if (Un->colour == 1) {// if red uncle
					parent->colour = 0;
					Un->colour = 0;
					GD->colour = 1;

					N = GD;
					parent = N->parent;
				}

			}
			else{// parent is right child
                if(Un == nullptr){
					if (parent->left == N) {
						rotate_right(parent);
					}
					rotate_left(GD);
					GD->colour = 1;
					N->colour = 0;
					break;
				}else if(Un->color == 1) {
					GD->colour = 1;
					parent->colour = 0;
					Un->colour = 0;
					N = GD;
					parent = N->parent;
				}
			}
			(this->root)->colour = 0; // due it could be changed
		}
    }

};

int main() {
    return 0;
}
