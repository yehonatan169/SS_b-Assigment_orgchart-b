#include "OrgChart.hpp"
/*
 * this class if for preorder Iterator
 */

using namespace std;
namespace ariel
{
    OrgChart::Iterator_preorder::Iterator_preorder(Node *ptr)
    {
        if(ptr != nullptr){
            this->current=ptr;
            this->ordered_node.push(ptr);
        }else{

            this->current = nullptr;
        }
    }

    string& OrgChart::Iterator_preorder::operator*() const
    {
        return this->current->info;
    }
    string* OrgChart::Iterator_preorder::operator->() const
    {
        return &(this->current->info);
    }

    // add all the subordinate from the last to the first so at the head of the stack will be the lefts subordinate
    OrgChart::Iterator_preorder& OrgChart::Iterator_preorder::operator++() //++i
    {
        if(!this->ordered_node.empty()){
          this->ordered_node.pop();
          for(unsigned long i=this->current->subordinates.size();i>0;i--){
              this->ordered_node.push(this->current->subordinates.at(i-1));
          }
        }
        if(this->ordered_node.empty()){
            this->current = nullptr;
        }else{
            this->current = this->ordered_node.top();
        }
        return *this;
    }
    OrgChart::Iterator_preorder OrgChart::Iterator_preorder::operator++(int)
    {
        OrgChart::Iterator_preorder temp = *this;
        ++*this;
        return temp;
    }
    bool OrgChart::Iterator_preorder::operator==(const OrgChart::Iterator_preorder& sec_iter) const
    {
        return this->current == sec_iter.current;
    }
    bool OrgChart::Iterator_preorder::operator!=(const OrgChart::Iterator_preorder& sec_iter) const
    {
        return !(*this == sec_iter);
    }
    int OrgChart::Iterator_preorder::size()
    {
        return this->current->info.size();
    }
}