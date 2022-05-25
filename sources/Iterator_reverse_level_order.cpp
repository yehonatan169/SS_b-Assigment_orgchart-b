#include "../sources/OrgChart.hpp"
#include <map>
/*
 * this class if for level order Iterator
 */
using namespace std;
namespace ariel {
    OrgChart::Iterator_reverse_level_order::Iterator_reverse_level_order(Node *ptr) {
        if (ptr != nullptr) {
            this->current = ptr;
            update_list();
        } else {
            this->current = nullptr;
        }
    }

    // add all the subordinate to the stck so the lowest rank will be at the head tof the stack and the root is at the bottom
    void OrgChart::Iterator_reverse_level_order::update_list() {

        map<int, vector<Node *>> nodeMap;
        deque < Node * > q;
        q.push_front(this->current);
        while (!q.empty()) {
            Node *current = q.front();
            q.pop_front();
            nodeMap[current->rank].push_back(current);
            for (auto *node: current->subordinates) {
                q.push_front(node);
            }
        }

        for (auto const &level: nodeMap) {

            for (auto *node: level.second) {

                this->ordered_node.push(node);
            }
        }
        this->current = this->ordered_node.top();
        this->ordered_node.pop();

    }

    string &OrgChart::Iterator_reverse_level_order::operator*() const {
        return this->current->info;
    }

    string *OrgChart::Iterator_reverse_level_order::operator->() const {
        return &(this->current->info);
    }

    OrgChart::Iterator_reverse_level_order &OrgChart::Iterator_reverse_level_order::operator++() //++i
    {
        if (!this->ordered_node.empty()) {
            this->current = this->ordered_node.top();
            this->ordered_node.pop();
        } else {
            this->current = nullptr;
        }
        return *this;
    }

    OrgChart::Iterator_reverse_level_order OrgChart::Iterator_reverse_level_order::operator++(int) {
        OrgChart::Iterator_reverse_level_order temp = (++*this);
        return temp;
    }

    bool
    OrgChart::Iterator_reverse_level_order::operator==(const OrgChart::Iterator_reverse_level_order &sec_iter) const {
        return this->current == sec_iter.current;
    }

    bool
    OrgChart::Iterator_reverse_level_order::operator!=(const OrgChart::Iterator_reverse_level_order &sec_iter) const {
        return !(*this == sec_iter);
    }

    int OrgChart::Iterator_reverse_level_order::size() {
        return this->current->info.size();
    }
}