#pragma once
#ifndef GRIDLL
#define GRIDLL
#include "container.h"
#include "object.h"
#include <iostream>

class GridLL
{
public:
    struct Node
    {

    public:
        Node* _right;
        Node* _left;
        Node* _down;
        Node* _up;
        Container::Slot* _data;
        float width;
        float height;
        Node(Container::Slot* data)
            :height(0),
            width(0)
        {
            _data = data;
            _right = nullptr;
            _left = nullptr;
            _down = nullptr;
            _up = nullptr;

            if (data->pItem != nullptr)
            {
                width = data->pItem->width();
                height = data->pItem->height();
            }

        }
        bool operator==(const Node& rhs) const
        {
            return _data->pItem == rhs._data->pItem;
        }
        bool operator!=(const Node& rhs) const
        {
            return !(*this == rhs);
        }
    };
private:
    Node* _head;
    const float MIN_SPACE = 7;
    const float ONE_PER = 0.01f;
    const float TWO_PER = 0.02f;

public:
    GridLL();
    ~GridLL();
    void insert(Container::Slot* data);
    void deleteNodebyKey(Container::Slot* key);
    void setRectangle(int left, int top, int width, int height);
    void updateLayout();

private:
    float getXMax(Node* current);
  
    float getXMaxExcept(Node* current);
    float getYMax(Node* current);
    float getYMaxExcept(Node* current);
    Node* createDummyNode(Node* current);

    Node* createColumnAfter(Node* current, Node* newNode);
    Node* createColumnBefore(Node* current, Node* newNode);
    Node* createRowAbove(Node* current, Node* newNode);

    Node* createRowBelow(Node* current, Node* newNode);
    Node* rewindRows(Node* row);
    Node* rewindColumns(Node* column);
    Node* forwardColumns(Node* column);

    void setRowsColsDim();    
    void resetSizes();
    void setExpandPolicies();    
    void fixToBounds();
    
    int getCountX();    
    int getCountY();    
    float getColumnsTotalSize(Node* current);    
    float getRowsTotalSize(Node* current);
    
    Node* getWidestRow();    
    Node* getHeighestColumn();
    
    void resizeHorizontal();   
    void resizeVertical();    
    void rearrangeList();    
   
    
    float getTotalXSizeExcept(Node* current);
    float getTotalYSizeExcept(Node* current);    
    int getCountY(Node* current);
    bool rowHasItems(Node* row);    
    bool columnHasItems(Node* column);
    void deleteRow(Node* row);
    void deleteColumn(Node* column);    
      
private:
    sf::IntRect mFrameRect;

};
#endif // !GRIDLL