#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <cstdio>


template <typename key_t, size_t ORDER, bool debug = false>
class Custom_BTree {
/*
 * B-tree https://en.wikipedia.org/wiki/B-tree
 */
public:

    void insert(const key_t& key);
    key_t lower_bound(const key_t& key);
    void erase(const key_t& key);
    bool count(const key_t& key);

    void traverse();

    explicit Custom_BTree();
    Custom_BTree(const Custom_BTree<key_t, ORDER, debug>& tree);
    ~Custom_BTree();

private:

    struct SearchResult;

    struct Node {
        static const bool IS_LEAF_DEFAULT = true;

        bool is_leaf;
        std::vector<key_t> data;
        std::vector<Node*> child;

        void paste(const key_t& key, const int& pos);
        void insert(const key_t& key);
        void remove(const int& pos);
        void erase(const key_t& key, bool is_root = false);

        int search(const key_t& key);
        SearchResult invariant_search(const key_t& key, bool is_root = false);

        bool borrow_left(const int& idx);
        bool borrow_right(const int& idx);

        key_t get_leftmost();
        key_t get_rightmost();

        void traverse();

        void split_child(const int& idx);
        void merge_child(const int& idx);

        explicit Node(const size_t& size);
        Node(const Node& Node);
        Node(const Node& Node_1, const key_t& x_val, const Node& Node_2);
        ~Node();
    };

    struct SearchResult {
        Node* node;
        int idx;
    };

    Node* root;
};

int main() {

    std::ios_base::sync_with_stdio(false);

    const int MOD = static_cast<int>(1e9);
    const size_t DEFAULT_ORDER = 35;

    size_t num_requests = 0;
    char operation = 0;
    int element = 0;

    bool after_next = false;
    int last_answer = 0;

    Custom_BTree<int, DEFAULT_ORDER> set;

    std::cin >> num_requests;

    for (size_t i = 0; i < num_requests; ++i) {

        std::cin >> operation >> element;

        if (operation == '+') {

            if (after_next) {
                set.insert((element + last_answer) % MOD);
            } else {
                set.insert(element);
            }
            after_next = false;

        } else {

            last_answer = set.lower_bound(element);

            std::cout << last_answer << std::endl;

            after_next = true;
        }
    }

    return 0;
}

template <typename key_t, size_t ORDER, bool debug>
Custom_BTree<key_t, ORDER, debug>::Custom_BTree()
    : root(nullptr) {}

template <typename key_t, size_t ORDER, bool debug>
Custom_BTree<key_t, ORDER, debug>::Custom_BTree(const Custom_BTree<key_t, ORDER, debug>& tree) {
    root = new Node(tree.root);
}

template <typename key_t, size_t ORDER, bool debug>
Custom_BTree<key_t, ORDER, debug>::~Custom_BTree() {
    delete root;
}

template <typename key_t, size_t ORDER, bool debug>
Custom_BTree<key_t, ORDER, debug>::Node::Node(const size_t& size)
    : is_leaf(IS_LEAF_DEFAULT), data(std::vector<key_t>(size)),
      child(std::vector<Node*>(size + 1)) {}

template <typename key_t, size_t ORDER, bool debug>
Custom_BTree<key_t, ORDER, debug>::Node::Node(const Custom_BTree<key_t, ORDER, debug>::Node& node)
    : is_leaf(node.is_leaf), data(node.data), child(std::vector<Node*>(node.child.size())) {

    for (size_t i = 0; i < child.size(); ++i) {
        child[i] = new Node(node.child[i]);
    }
}

template <typename key_t, size_t ORDER, bool debug>
Custom_BTree<key_t, ORDER, debug>::Node::Node(const Custom_BTree<key_t, ORDER, debug>::Node &Node_1,
                                                       const key_t &x_val, const Custom_BTree<key_t, ORDER, debug>::Node &Node_2)
                                                       : is_leaf(Node_1.is_leaf & Node_2.is_leaf),
                                                         data(std::vector<key_t>(2 * ORDER - 1)),
                                                         child(std::vector<Node*>(2 * ORDER)) {

    if (Node_1.data.size() != ORDER - 1 ||
        Node_2.data.size() != ORDER - 1) {
        throw std::out_of_range("Trying to build Node of Nodes with incorrect size! (not 2t - 1)\n");
    }

    for (size_t i = 0; i < ORDER - 1; ++i) {
        data[i] = Node_1.data[i];
        child[i] = Node_1.child[i];
    }

    child[ORDER - 1] = Node_1.child[ORDER - 1];
    data[ORDER - 1] = x_val;
    child[ORDER] = Node_2.child[0];

    for (size_t i = ORDER; i < 2 * ORDER - 1; ++i) {
        data[i] = Node_2.data[i - ORDER];
        child[i + 1] = Node_2.child[i + 1 - ORDER];
    }
}

template <typename key_t, size_t ORDER, bool debug>
Custom_BTree<key_t, ORDER, debug>::Node::~Node() {
    for (size_t i = 0; i < child.size(); ++i) {
        delete child[i];
    }
}


template <typename key_t, size_t ORDER, bool debug>
int Custom_BTree<key_t, ORDER, debug>::Node::search(const key_t& key) {

    int l_idx = 0;
    int r_idx = data.size();
    int m_idx = 0;

    while (l_idx < r_idx) {

        m_idx = (l_idx + r_idx) / 2;

        if (data[m_idx] < key) {
            l_idx = m_idx + 1;
        } else {
            r_idx = m_idx;
        }
    }

    return l_idx;
}

template <typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::Node::paste(const key_t& key, const int& pos) {

    if (data.size() == 2 * ORDER - 1) {
        throw std::logic_error("Pasting to the full Node!\n");
    }

    if (!is_leaf && child.size() - data.size() != 1) {

        throw std::logic_error("Node (data size) != (child size + 1) !\n");
    }

    child.push_back(child[child.size() - 1]);

    if (!data.empty()) {
        data.push_back(data[data.size() - 1]);
    } else {
        data.resize(1);
    }

    for (int i = data.size() - 2; i > pos; --i) {
        data[i] = data[i - 1];
        child[i + 1] = child[i];
    }
    data[pos] = key;
}

template <typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::Node::remove(const int& pos) {

    if (data.size() == ORDER - 1) {
        throw std::logic_error("Can't erase from node! It already has T - 1 keys!\n");
    }
    if (child.size() - data.size() != 1) {

        throw std::logic_error("Node (data size) != (child size + 1) !\n");
    }

    for (int i = pos; i < data.size() - 1; --i) {
        data[i] = data[i + 1];
        child[i + 1] = child[i + 2];
    }
    data.pop_back();
    child.pop_back();
}

template <typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::Node::split_child(const int& idx) {

    if (child[idx]->data.size() != 2 * ORDER - 1) {
        throw std::logic_error("Splitting non-full child!\n");
    } else if (data.size() == 2 * ORDER - 1) {
        throw std::logic_error("Splitting child of full node!\n");
    }

    auto suffix = new Node(ORDER - 1);

    suffix->is_leaf = child[idx]->is_leaf;

    key_t sep = child[idx]->data[ORDER - 1];

    for (size_t i = ORDER; i < 2 * ORDER - 1; ++i) {
        suffix->data[i - ORDER] = child[idx]->data[i];
    }
    for (size_t i = ORDER; i < 2 * ORDER; ++i) {
        suffix->child[i - ORDER] = child[idx]->child[i];
    }

    paste(sep, idx);

    child[idx + 1] = suffix;

    child[idx]->data.resize(ORDER - 1);
    child[idx]->child.resize(ORDER);
}

template <typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::Node::merge_child(const int& idx) {

    if (child[idx]->data.size()     != ORDER - 1 ||
        child[idx + 1]->data.size() != ORDER - 1) {
        throw std::logic_error("Merging nodes with more than T - 1 elements!\n");
    }

    child[idx]->data.resize(2 * ORDER - 1);
    child[idx]->child.resize(2 * ORDER);

    child[idx]->data[ORDER - 1] = data[idx];
    for (size_t i = ORDER; i < 2 * ORDER - 1; ++i) {
        child[idx]->data[i] = child[idx + 1]->data[i - ORDER];
    }
    for (size_t i = ORDER; i < 2 * ORDER; ++i) {
        child[idx]->child[i] = child[idx + 1]->child[i - ORDER];
        child[idx + 1]->child[i - ORDER] = nullptr;
    }

    delete child[idx + 1];

    remove(idx);
}

template <typename key_t, size_t ORDER, bool debug>
bool Custom_BTree<key_t, ORDER, debug>::Node::borrow_left(const int& idx) {

    if (idx == 0 || (idx > 0 && child[idx - 1]->data.size() == ORDER - 1)) {
        return false;
    }

    size_t brother_size = child[idx - 1]->data.size();

    child[idx]->paste( data[idx - 1], 0 );
    child[idx]->child[0] = child[idx - 1]->child[brother_size];
    data[idx - 1] = child[idx - 1]->data[brother_size - 1];

    child[idx - 1]->remove(brother_size - 1);

    return true;
}

template <typename key_t, size_t ORDER, bool debug>
bool Custom_BTree<key_t, ORDER, debug>::Node::borrow_right(const int& idx) {

    if (idx == data.size() || (idx < data.size() && child[idx + 1]->data.size() == ORDER - 1)) {
        return false;
    }

    child[idx]->paste( data[idx], ORDER - 1 );
    child[idx]->child[ORDER] = child[idx + 1]->child[0];
    data[idx] = child[idx + 1]->data[0];

    child[idx - 1]->remove(0);

    return true;
}

template <typename key_t, size_t ORDER, bool debug>
key_t Custom_BTree<key_t, ORDER, debug>::Node::get_leftmost() {

    if (is_leaf) {

        return data[0];
    }

    return child[0]->get_leftmost();
}

template <typename key_t, size_t ORDER, bool debug>
key_t Custom_BTree<key_t, ORDER, debug>::Node::get_rightmost() {

    if (is_leaf) {

        return data[data.size() - 1];
    }

    return child[child.size() - 1]->get_rightmost();
}


template <typename key_t, size_t ORDER, bool debug>
typename Custom_BTree<key_t, ORDER, debug>::SearchResult Custom_BTree<key_t, ORDER, debug>::Node::invariant_search(const key_t& key,
        const bool is_root) {

    if (!is_root && data.size() == ORDER - 1) {
        throw std::logic_error("Invariant search :: invariant is broken!\n");
    }

    int search_idx = search(key);

    if (search_idx < data.size() && data[search_idx] == key) {

        SearchResult result = {this, search_idx};
        return result;

    } else if (is_leaf && ((search_idx < data.size() && data[search_idx] != key) || search_idx == data.size())) {

        SearchResult result = {nullptr, 0};
        return result;

    }

    if (child[search_idx]->data.size() == ORDER - 1) {

        if (borrow_left(search_idx) || borrow_right(search_idx)) {

            return child[search_idx]->invariant_search(key);

        } else {

            if (search_idx != data.size()) {

                merge_child(search_idx);
                return child[search_idx]->invariant_search(key);

            } else {

                merge_child(search_idx - 1);
                return child[search_idx - 1]->invariant_search(key);

            }

        }

    } else {

        return child[search_idx]->invariant_search(key);

    }

}

template <typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::Node::traverse() {

    std::cout << "[ ";
    for (size_t i = 0; i < data.size(); ++i) {
        if (!is_leaf) {
            child[i]->traverse();
        }
        std::cout << data[i] << " ";
    }

    if (!is_leaf) {
        child[data.size()]->traverse();
    }
    std::cout << "]";
}

template <typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::traverse() {

    if (!root) {
        std::cout << "Tree is empty\n";
        return;
    }

    root->traverse();
}

template <typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::Node::insert(const key_t& key) {

    if (data.size() == 2 * ORDER - 1) {
        throw std::logic_error("Inserting to the full node!\n");
    }

    int search_idx = search(key);

    if (search_idx < data.size() && data[search_idx] == key) {
        return;
    }

    if (is_leaf) {

        paste(key, search_idx);

    } else {

        if (child[search_idx]->data.size() == 2 * ORDER - 1) {

            split_child(search_idx);
            if(key > data[search_idx]) {
                ++search_idx;
            }
        }
        child[search_idx]->insert(key);
    }
}

template <typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::insert(const key_t& key) {

    if (!root) {

        root = new Node(1);
        root->data[0] = key;

    } else {

        if (root->data.size() == 2 * ORDER - 1) {

            auto new_root = new Node(0);
            new_root->is_leaf = false;

            new_root->child[0] = root;
            new_root->split_child(0);

            if (key < new_root->data[0]) {
                new_root->child[0]->insert(key);
            } else {
                new_root->child[1]->insert(key);
            }

            root = new_root;
        } else {
            root->insert(key);
        }
    }
}

template <typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::Node::erase(const key_t& key, const bool is_root) {

    SearchResult result = invariant_search(key, is_root);

    if (!result.node) {
        throw std::logic_error("Removing nonexistent key!\n");
    }

    if (result.node->is_leaf) {

        result.node->remove(result.idx);

    } else {

        if (result.node->child[result.idx]->data.size() >= ORDER) {

            key_t rightmost = result.node->child[result.idx]->get_rightmost();
            result.node->data[result.idx] = rightmost;
            result.node->child[result.idx]->erase(rightmost);

        } else if (result.node->child[result.idx + 1]->data.size() >= ORDER) {

            key_t leftmost = result.node->child[result.idx + 1]->get_leftmost();
            result.node->data[result.idx] = leftmost;
            result.node->child[result.idx + 1]->erase(leftmost);

        } else {

            result.node->merge_child(result.idx);
            result.node->child[result.idx]->erase(key);

        }

    }
}

template <typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::erase(const key_t& key) {

    if (!root) {
        return;
    }

    root->erase(key);

    if (root->data.size() == 0) {

        Node* tmp = root;

        if (root->is_leaf) {
            root = nullptr;
        } else {
            root = root->child[0];
        }

        delete tmp;
    }
}

template <typename key_t, size_t ORDER, bool debug>
key_t Custom_BTree<key_t, ORDER, debug>::lower_bound(const key_t& key) {

    if (!root) {
        return -1;
    }

    Node* curr_node = root;

    int search_idx = curr_node->search(key);

    key_t answer = -1;

    while (!curr_node->is_leaf) {

        if (search_idx != curr_node->data.size() && curr_node->data[search_idx] >= key) {
            answer = curr_node->data[search_idx];
        }

        curr_node = curr_node->child[search_idx];
        search_idx = curr_node->search(key);
    }

    if (search_idx != curr_node->data.size()) {
        answer = curr_node->data[search_idx];
    }

    return answer;
}

template <typename key_t, size_t ORDER, bool debug>
bool Custom_BTree<key_t, ORDER, debug>::count(const key_t& key) {

    if (!root) {
        return false;
    }

    SearchResult result = root->invariant_search(key, true);

    return result.node != nullptr;
}








