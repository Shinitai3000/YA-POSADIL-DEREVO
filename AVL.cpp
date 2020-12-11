#include <iostream>

using namespace std;

class AVL_Tree : public BinTree{
        // Функция взятия высоты
        int height(Node *N){
            if (N == nullptr){
                return 0;
            }
            return N->height;
    }
        //Функция правого поворота, возвращающая новый корень
        void rightRotate(AVL_Node *y){
            AVL_Node *x = y->left;
            AVL_Node *B = x->right;
            x->right = y;
            y->left = B;
            // Меняем высоты после поворота
            y->height = max(height(y->left), height(y->right)) + 1;
            x->height = max(height(x->left), height(x->right)) + 1;
        }
        void leftRotate(AVL_Node *x){
            AVL_Node *y = x->right;
            AVL_Node *B = y->left;
            y->left = x;
            x->rgiht = B;
            y->height = max(height(y->left), height(y->right)) + 1;
            x->height = max(height(x->left), height(x->right)) + 1;
        }

        //Баланс фактор
        int getBalance(Node *N){
            if (N == NULL){
                return 0;
            }
            else{
                return height(N->left) - height(N->right);
            }
        }

        // Функция балансировки после вставки узла в дерево. Вставить вот сразу после вставки в обычным бин.дереве
        void balanced_insert(Key key,Value val){
            Node* now = insert(key, val);
            // вычисляем длину нашего узла
            now->height = 1 + max(height(now->left),height(now->right));
            // и баланс фактор
            int balance = getBalance(now);
            //Нужно перебалансить дерево
            // Высота поддерева слева больше справа, и нужен один поворот
            if (balance > 1 && key < now->left->key)
                rightRotate(now);

            // Высота поддерева справа больше слева, и нужен один поворот
            if (balance < -1 && key > now->right->key)
                 leftRotate(now);

            // Теперь высота поддерева с той же стороны меньше высоты другого поддерва => большой поворот
            if (balance > 1 && key > now->left->key)
            {
                node->left = leftRotate(now->left);
                rightRotate(now);
            }

            //Аналогично
            if (balance < -1 && key < now->right->key)
            {
                now->right = rightRotate(now->right);
                leftRotate(now);
            }
        }



        void delete(Node* root, Key key, Value val){
            delete(root, key, val);
            //Перебалансируем
            int balance = getBalance(root);
            // Left Left Case
            if (balance > 1 && getBalance(root->left) >= 0)
                {return rightRotate(root);}

            // Left Right Case
            if (balance > 1 && getBalance(root->left) < 0)
            {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }

            // Right Right Case
            if (balance < -1 && getBalance(root->right) <= 0){
                return leftRotate(root);
            }
            // Right Left Case
            if (balance < -1 && getBalance(root->right) > 0)
            {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
            return root;

        }

};


