/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    if (!t) {return;}
    Node * old_t = t;
    Node * r_subtree = old_t->right;
    Node * r_subtree_left = r_subtree->left;
    t->right = r_subtree_left;
    r_subtree->left = old_t;
    t = r_subtree;
    //heights
    if (t->left)
    t->left->height = 1 + max(heightOrNeg1(t->left->right),
                            heightOrNeg1(t->left->left));
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    if (!t) {return;}
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    if (!t) {return;}
    Node * old_t = t;
    Node * l_subtree = old_t->left;
    Node * l_subtree_right = l_subtree->right;
    old_t->left = l_subtree_right;
    l_subtree->right = old_t;
    t = l_subtree;
    //heights
    if (t->right)
    (t->right->height) = 1 + max(heightOrNeg1(t->right->right),
                                heightOrNeg1(t->right->left));

    t->height = 1 + max(heightOrNeg1(t->right),
                       heightOrNeg1(t->left));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    if (!t) {return;}
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (!subtree) {return;}
    subtree->height = 1 + max(heightOrNeg1(subtree->right),
                              heightOrNeg1(subtree->left));
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    int left_balance = -1, right_balance = -1;
    if (subtree->left) {
        left_balance = heightOrNeg1(subtree->left->right)
            - heightOrNeg1(subtree->left->left);
    } if (subtree->right) {
        right_balance = heightOrNeg1(subtree->right->right)
            - heightOrNeg1(subtree->right->left);
    } if (balance == 2) {
        if (right_balance == 1) {rotateLeft(subtree);}
        else {rotateRightLeft(subtree);}
    } else if (balance == -2) {
        if (left_balance == -1) {rotateRight(subtree);}
        else {rotateLeftRight(subtree);}
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    Node * new_node;
    if (!subtree) {
        new_node = new Node(key, value);
        subtree = new_node;
    } if (key < subtree->key) {
        if(subtree->left) {
            insert(subtree->left, key, value);
        } else {
            new_node = new Node(key, value);
            subtree->left = new_node;
        }
    } else if (key > subtree->key) {
        if(subtree->right) {
            insert(subtree->right, key, value);
        } else {
            new_node = new Node(key, value);
            subtree->right = new_node;
        }
    }

    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (!subtree)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (!(subtree->left) && !(subtree->right)) {
            /* no-child remove */
            // your code here
            delete(subtree);
            subtree = NULL;
        } else if (subtree->left && subtree->right) {
            /* two-child remove */
            // your code here
            //find iop of node
            Node * curr = (subtree->left);
            while ((curr)->right) {
                (curr) = (curr)->right;
            }
            swap(curr, subtree);
            remove(subtree->left, key);
       } else {
            /* one-child remove */
            // your code here
            if (subtree->right) {
                swap(subtree->right, subtree);
                remove(subtree->right , key);
            } else if (subtree->left) {
                swap(subtree->left, subtree);
                remove(subtree->left, key);
            }
        }
    }
    rebalance(subtree);
}
