#include "OrgChart.hpp"

/*
 * this class if for level order Iterator
 */

using namespace std;
namespace ariel
{
    OrgChart::Iterator_level_order::Iterator_level_order(Node *ptr)
    {
        if(ptr != nullptr){
            this->current=ptr;
            this->ordered_node.emplace_back(ptr);
        }else{

            this->current = nullptr;
        }
    }

    string& OrgChart::Iterator_level_order::operator*() const
    {
        return this->current->info;
    }
    string* OrgChart::Iterator_level_order::operator->() const
    {
        return &(this->current->info);
    }
    // add all the subordinate from the last to the first so at the head of the stack will be the lefts subordinate
    OrgChart::Iterator_level_order& OrgChart::Iterator_level_order::operator++() //++i
    {
        if(!this->ordered_node.empty()){
            this->ordered_node.pop_front();
            for(unsigned long i=0;i<this->current->subordinates.size();i++){
                this->ordered_node.emplace_back(this->current->subordinates.at(i));
            }
        }
        if(this->ordered_node.empty()){
            this->current = nullptr;
        }else{
            this->current = this->ordered_node.front();
        }
        return *this;
    }
    OrgChart::Iterator_level_order OrgChart::Iterator_level_order::operator++(int)
    {
        OrgChart::Iterator_level_order temp = *this;
        ++*this;
        return temp;
    }
    bool OrgChart::Iterator_level_order::operator==(const OrgChart::Iterator_level_order& sec_iter) const
    {
        return this->current == sec_iter.current;
    }
    bool OrgChart::Iterator_level_order::operator!=(const OrgChart::Iterator_level_order& sec_iter) const
    {
        return !(*this == sec_iter);
    }
    int OrgChart::Iterator_level_order::size()
    {
        return this->current->info.size();
    }
}