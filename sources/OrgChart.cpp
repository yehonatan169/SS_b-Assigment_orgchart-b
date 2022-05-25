
#include "../sources/OrgChart.hpp"
/*
 * the idea of using the concept of BFS at to delete_tree, is_exist deep_copy_tree function I got from yarin hindi
 * */

using namespace std;

namespace ariel {

    OrgChart::OrgChart() {
        this->root = nullptr;
    }

    OrgChart::OrgChart(const OrgChart &tree) : root(nullptr) { // deep copy
        deep_copy_tree(tree);
    }

    OrgChart::OrgChart(OrgChart &&tree)noexcept {
        this->root = tree.root;
        tree.root = nullptr;
    }

    OrgChart::~OrgChart() {
        delete_tree();
    }

    // make deep copy of the tree
    void OrgChart::deep_copy_tree(const OrgChart &tree) { // we use hear the concept of BFS
        if (tree.root == nullptr) {
            this->root = nullptr;
            return;
        }
        deque < Node * > node_to_copy;
        this->root = nullptr;
        node_to_copy.push_back(tree.root);
        this->add_root(tree.root->info);
        Node *temp = nullptr;
        while (!node_to_copy.empty()) {
            temp = node_to_copy.front();
            node_to_copy.pop_front();
            node_to_copy.emplace_back(temp);
            for (unsigned int i = 0; i < temp->subordinates.size(); i++) {
                this->add_sub(temp->info, temp->subordinates.at(i)->info);
                node_to_copy.emplace_back(temp->subordinates.at(i));
            }
        }
    }

    // delete all the node of the tree
    void OrgChart::delete_tree() const { // we use hear the concept of BFS
        if (this->root == nullptr) {
            return;
        }
        vector < Node * > node_to_delete;
        deque < Node * > node_to_take;

        node_to_take.push_back(this->root);
        Node *temp = nullptr;
        while (!node_to_take.empty()) {
            temp = node_to_take.front();
            node_to_delete.push_back(temp);
            node_to_take.pop_front();
            for (unsigned int i = 0; i < temp->subordinates.size(); i++) {
                node_to_take.emplace_back(temp->subordinates.at(i));
            }
        }
        for (unsigned int i = 0; i < node_to_delete.size(); ++i) {
            delete node_to_delete.at(i);
        }
    }

    // add root to the tree
    OrgChart &OrgChart::add_root(const string &info) {
        if (info.empty()) {
            throw std::runtime_error("name can't be empty!");
        }
        if (this->root != nullptr) {
            this->root->info = info;
            return *this;
        }
        Node *my_root = new Node(info, 0);
        this->root = my_root;
        return *this;
    }

    // adding worker(sub) to the tree under master
    OrgChart &OrgChart::add_sub(const string &master, const string &sub) {

        if (this->root == nullptr) {
            throw invalid_argument("The tree has no root!");
        }
        if (master.empty() || sub.empty()) {
            throw invalid_argument("name can't be empty!");
        }

        Node *my_boss = is_exist(master);
        if (my_boss != nullptr) {
            Node *new_worker = new Node(sub, my_boss->rank + 1);
            my_boss->subordinates.emplace_back(new_worker);
            new_worker->boss = my_boss;
            return *this;
        }
        throw invalid_argument("there is no master in the tree");
    }

    Node *OrgChart::is_exist(const string &master) const { // we use here the concept of BFS
        if (this->root == nullptr) { // if the tree is empty
            throw invalid_argument("the orgchart is empty");
        }
        deque < Node * > search_list;
        search_list.push_back(this->root);
        while (!search_list.empty()) {
            Node *temp = search_list.front();
            if (temp->info == master) { // check if that is the master
                return temp;
            }
            search_list.pop_front();
            for (unsigned int i = 0; i < temp->subordinates.size(); i++) { // add the subordinates to the search list
                search_list.push_back(temp->subordinates.at(i));
            }
        }
        return nullptr; // the master isn't in the tree

    }

    OrgChart &OrgChart::operator=(const OrgChart &tree) {
        if (this != &tree) {
            delete_tree(); // we delete it first, so we will free the node that are now in use
            deep_copy_tree(tree);
        }
        return *this;
    }

    OrgChart &OrgChart::operator=(OrgChart &&tree)noexcept {
        this->root = tree.root;
        tree.root = nullptr;
        return *this;
    }

    OrgChart::Iterator_level_order OrgChart::begin_level_order() const {
        if (this->root == nullptr) {
            throw invalid_argument("the orgchart is empty");
        }
        Iterator_level_order temp{this->root};
        return temp;
    }

    OrgChart::Iterator_level_order OrgChart::end_level_order() const {
        if (this->root == nullptr) {
            throw invalid_argument("the orgchart is empty");
        }
        Iterator_level_order temp{nullptr};
        return temp;
    }

    OrgChart::Iterator_reverse_level_order OrgChart::begin_reverse_order() const {
        if (this->root == nullptr) {
            throw invalid_argument("the orgchart is empty");
        }
        Iterator_reverse_level_order rev_ord_itr{this->root};
        return rev_ord_itr;
    }

    OrgChart::Iterator_reverse_level_order OrgChart::reverse_order() const {
        if (this->root == nullptr) {
            throw invalid_argument("the orgchart is empty");
        }
        Iterator_reverse_level_order rev_ord_itr{nullptr};
        return rev_ord_itr;
    }

    OrgChart::Iterator_preorder OrgChart::begin_preorder() const {
        if (this->root == nullptr) {
            throw invalid_argument("the orgchart is empty");
        }
        Iterator_preorder pre_itr{this->root};
        return pre_itr;
    }

    OrgChart::Iterator_preorder OrgChart::end_preorder() const {
        if (this->root == nullptr) {
            throw invalid_argument("the orgchart is empty");
        }
        Iterator_preorder pre_itr{nullptr};
        return pre_itr;
    }

    OrgChart::Iterator_level_order OrgChart::begin() const {
        if (this->root == nullptr) {
            throw invalid_argument("the orgchart is empty");
        }
        Iterator_level_order temp{this->root};
        return temp;
    }

    OrgChart::Iterator_level_order OrgChart::end() const {
        if (this->root == nullptr) {
            throw invalid_argument("the orgchart is empty");
        }
        Iterator_level_order temp{nullptr};
        return temp;
    }

    // print the stack at level order
    ostream &operator<<(ostream &output, const OrgChart &org) {
        for (auto itr = org.begin_level_order(); itr != org.end_level_order(); itr++) {
            cout << (*itr) << ",";
        }
        return output;
    }

}
