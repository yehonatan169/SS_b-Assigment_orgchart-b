#pragma once

#include <vector>
#include "Node.hpp"
#include <stack>
#include <deque>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;
namespace ariel {
    class OrgChart {
    public:
        Node *root;

        OrgChart();

        OrgChart(const OrgChart &tree);//deep copy

        OrgChart(OrgChart &&tree) noexcept;

        ~OrgChart();

        void deep_copy_tree(const OrgChart &tree);

        void delete_tree() const;

        OrgChart &add_root(const string &info);

        OrgChart &add_sub(const string &master, const string &sub);

        OrgChart & operator=(const OrgChart &tree); // deep

        OrgChart & operator=(OrgChart &&tree) noexcept;

        Node* is_exist(const string &master) const;

        class Iterator_level_order {
        private:
            deque<Node *> ordered_node; // Note-this deque isn't keeping the all tree but every time we use the operator ++ we add him the subordinates of the first element in the dequw and the we pop him out
            Node *current;

        public:
            Iterator_level_order(Node *ptr);//

            string &operator*() const;

            string *operator->() const;

            Iterator_level_order &operator++(); //++i

            Iterator_level_order operator++(int);

            bool operator==(const Iterator_level_order &iter) const;

            bool operator!=(const Iterator_level_order &iter) const;

            int size();
        };

        class Iterator_reverse_level_order {
        private:
            stack<Node *> ordered_node;
            Node *current;

        public:
            Iterator_reverse_level_order(Node *ptr);

            void update_list();

            string &operator*() const;

            string *operator->() const;

            Iterator_reverse_level_order &operator++(); //++i
            Iterator_reverse_level_order operator++(int);

            bool operator==(const Iterator_reverse_level_order &iter) const;

            bool operator!=(const Iterator_reverse_level_order &iter) const;

            int size();
        };

        class Iterator_preorder {
        private:
            stack<Node *> ordered_node;
            Node *current;

        public:
            Iterator_preorder(Node *ptr);

            string &operator*() const;

            string *operator->() const;

            Iterator_preorder &operator++(); //++i
            Iterator_preorder operator++(int);

            bool operator==(const Iterator_preorder &sec_iter) const;

            bool operator!=(const Iterator_preorder &sec_iter) const;

            int size();
        };


        Iterator_level_order begin_level_order() const;// level order
        Iterator_level_order end_level_order() const;

        Iterator_reverse_level_order begin_reverse_order() const;// reverse level order
        Iterator_reverse_level_order reverse_order() const; // end_revers_order

        Iterator_preorder begin_preorder() const; //preorder
        Iterator_preorder end_preorder() const;

        Iterator_level_order begin() const;

        Iterator_level_order end() const;

        friend ostream &operator<<(ostream &out, const OrgChart &org); // print the tree
    };
}