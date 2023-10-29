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
    GridLL()
    {
        _head = nullptr;
    }
    ~GridLL()
    {

        /* deref head_ref to get the real head */
        Node* current = _head;
        Node* next = nullptr;

        while (current != nullptr)
        {
            next = current->_right;
            delete current;
            current = next;
        }

        _head = nullptr;

    }
    float GetXMax(Node* current)
    {
        Node* temp = current;
        temp = RewindRows(temp);
        Node* _max = nullptr;

        while (temp != nullptr)
        {
            if (temp->_data->pItem != nullptr)
            {
                if (_max == nullptr)
                {
                    _max = temp;
                }
                if (temp->_data->pItem->defaultWidth() > _max->_data->pItem->defaultWidth())
                {
                    _max = temp;
                }
            }
            temp = temp->_down;
        }
        if (_max == nullptr)
        {
            temp = RewindRows(current);
            if (temp->_up == nullptr && temp->_right != nullptr)
            {
                _head = temp->_right;
            }
            DeleteColumn(temp);
            return 0;
        }
        return _max->width;
    }
    float GetXMaxExcept(Node* current)
    {
        Node* temp = current;
        temp = RewindRows(temp);
        Node* _max = nullptr;

        while (temp != nullptr)
        {
            if (temp->_data->pItem != nullptr)
            {
                if (temp != current)
                {
                    if (_max == nullptr)
                    {
                        _max = temp;
                    }
                    if (temp->_data->pItem->defaultWidth() > _max->_data->pItem->defaultWidth())
                    {
                        _max = temp;
                    }
                }

            }
            temp = temp->_down;
        }
        if (_max == nullptr)
        {
            _max = current;
        }
        return _max->_data->pItem->defaultWidth();
    }
    float GetYMax(Node* current)
    {
        Node* temp = current;
        temp = RewindColumns(temp);
        Node* _max = nullptr;


        while (temp != nullptr)
        {
            if (temp->_data->pItem != nullptr)
            {
                if (_max == nullptr)
                {
                    _max = temp;
                }
                if (temp->_data->pItem->defaultHeight() > _max->_data->pItem->defaultHeight())
                {
                    _max = temp;
                }
            }
            temp = temp->_right;
        }
        if (_max == nullptr)
        {
            temp = RewindColumns(current);
            if (temp->_up == nullptr && temp->_down != nullptr)
            {
                _head = temp->_down;
            }
            DeleteRow(temp);
            return 0;
        }
        return _max->height;
    }
    float GetYMaxExcept(Node* current)
    {
        Node* temp = current;
        temp = RewindColumns(temp);
        Node* _max = nullptr;

        while (temp != nullptr)
        {
            if (temp->_data->pItem != nullptr)
            {
                if (temp != current)
                {
                    if (_max == nullptr)
                    {
                        _max = temp;
                    }
                    if (temp->_data->pItem->defaultHeight() > _max->_data->pItem->defaultHeight())
                    {
                        _max = temp;
                    }
                }

            }
            temp = temp->_right;
        }
        if (_max == nullptr)
        {
            _max = current;
        }
        return _max->_data->pItem->defaultHeight();
    }
    void Insert(Container::Slot* data)
    {
        if (data->pItem != nullptr)
        {
            data->pItem->setPosition((sf::Vector2f)data->mPosition);
        }

        Node* _newNode = new Node(data);

        if (_head == nullptr)
        {
            _head = _newNode;

        }
        else
        {
            Node* temp = _head;
            while (temp != nullptr)
            {
                if (data->pItem->getPosition().x < mFrameRect.getPosition().x +  temp->_data->mPosition.x)
                {
                    while (temp->_down != nullptr && data->pItem->getPosition().y > mFrameRect.getPosition().y +  temp->_data->mPosition.y + temp->height)
                    {
                        temp = temp->_down;
                    }
                    _newNode->_right = temp;
                    _newNode->_left = temp->_left;

                    if (temp->_left != nullptr)
                    {
                        temp->_left->_right = _newNode;
                    }

                    temp->_left = _newNode;

                    Node* _current = RewindRows(temp);
                    _current = CreateColumnBefore(_current, _newNode);
                    _current = RewindRows(temp);


                    while (_current->_down != nullptr)
                    {
                        _current->_left->_down = _current->_down->_left;
                        _current->_left->_down->_up = _current->_left;

                        _current = _current->_down;
                    }

                    _current = RewindRows(temp);
                    _current = RewindColumns(_current);

                    _head = _current;
                    break;


                }
                else if (temp->_right == nullptr && data->pItem->getPosition().x >= mFrameRect.getPosition().x +  temp->_data->mPosition.x + temp->width - MIN_SPACE)
                {
                    while (temp->_down != nullptr && data->pItem->getPosition().y > mFrameRect.getPosition().y +  temp->_data->mPosition.y + temp->height)
                    {
                        temp = temp->_down;
                    }

                    _newNode->_left = temp;
                    _newNode->_right = temp->_right;
                    temp->_right = _newNode;


                    Node* _current = RewindRows(temp);
                    _current = CreateColumnAfter(_current, _newNode);

                    _current = RewindRows(temp);
                    while (_current->_down != nullptr)
                    {
                        _current->_right->_down = _current->_down->_right;
                        _current->_down->_right->_up = _current->_right;
                        _current = _current->_down;
                    }
                    break;
                }
                else
                {
                    if (data->pItem->getPosition().x >= mFrameRect.getPosition().x +  temp->_data->mPosition.x - MIN_SPACE && data->pItem->getPosition().x <= mFrameRect.getPosition().x +  temp->_data->mPosition.x + temp->width - MIN_SPACE)
                    {
                        while (temp->_right != nullptr && data->pItem->getPosition().x > mFrameRect.getPosition().x +  temp->_data->mPosition.x + temp->width)
                        {
                            temp = temp->_right;
                        }

                        if (data->pItem->getPosition().y + data->pItem->height() <= mFrameRect.getPosition().y +  temp->_data->mPosition.y)
                        {
                            temp->_up = _newNode;
                            _newNode->_down = temp;

                            Node* _current = RewindColumns(temp);
                            _current = CreateRowAbove(_current, _newNode);

                            _current = RewindColumns(temp);

                            while (_current->_right != nullptr)
                            {
                                _current->_up->_right = _current->_right->_up;
                                _current->_right->_up->_left = _current->_up;
                                _current = _current->_right;
                            }
                            _current = RewindRows(_current);
                            _current = RewindColumns(_current);
                            _head = _current;
                            break;

                        }
                        else
                        {

                            while (temp->_down != nullptr && data->pItem->getPosition().y > mFrameRect.getPosition().y +  temp->_data->mPosition.y + temp->height)
                            {
                                temp = temp->_down;
                            }


                            if (data->pItem->getPosition().y <= temp->_data->mPosition.y + temp->height && temp->_data->pItem == nullptr)
                            {

                                //Node colBefore = temp.prev_column;
                                //Node colAfter = temp.next_column;
                                //Node rowBefore = temp.prev_row;
                                //Node rowAfter = temp.next_row;

                                _newNode->_down = temp->_down;
                                _newNode->_up = temp->_up;
                                _newNode->_left = temp->_left;
                                _newNode->_right = temp->_right;

                                if (temp->_down != nullptr)
                                {
                                    temp->_down->_up = _newNode;
                                }
                                if (temp->_up != nullptr)
                                {
                                    temp->_up->_down = _newNode;
                                }
                                if (temp->_left != nullptr)
                                {
                                    temp->_left->_right = _newNode;
                                }
                                if (temp->_right != nullptr)
                                {
                                    temp->_right->_left = _newNode;
                                }


                                if (temp == _head)
                                {
                                    _head = _newNode;
                                }


                                break;
                            }
                            else
                            {
                                _newNode->_down = temp->_down;
                                _newNode->_up = temp;

                                if (temp->_down != nullptr)
                                {
                                    temp->_down->_up = _newNode;
                                }
                                temp->_down = _newNode;

                                Node* _current = temp;

                                _current = RewindColumns(_current);
                                _current = CreateRowBelow(_current, _newNode);
                            }

                            temp = _head;
                            Node* column = temp;
                            while (column != nullptr)
                            {

                                temp = column;
                                Node* _colAfter = temp->_right;

                                while (temp != nullptr && _colAfter != nullptr)
                                {

                                    temp->_right = _colAfter;
                                    _colAfter->_left = temp;

                                    temp = temp->_down;
                                    _colAfter = _colAfter->_down;
                                }

                                column = column->_right;
                            }
                            break;
                        }
                    }
                }
                temp = temp->_right;
            }

        }
        FixToBounds();
        SetRowsColsDim();
        RearrangeList();

    }
    Node* CreateDummyNode(Node* current)
    {
        Container::Slot* _dummyslot = new Container::Slot(sf::Vector2i(), nullptr);

        Node* _dummyNode = new Node(_dummyslot);

        _dummyNode->width = current->width;
        _dummyNode->height = current->height;

        return _dummyNode;
    }

    Node* CreateColumnAfter(Node* current, Node* newNode)
    {
        while (current != nullptr)
        {
            if (current->_right != newNode)
            {
                Node* dummyNode = CreateDummyNode(current);
                dummyNode->_right = current->_right;
                dummyNode->_left = current;

                current->_right = dummyNode;

            }
            current = current->_down;
        }
        return current;
    }
    Node* CreateColumnBefore(Node* current, Node* newNode)
    {
        while (current != nullptr)
        {
            if (current->_left != newNode)
            {
                Node* dummyNode = CreateDummyNode(current);

                dummyNode->_right = current;
                dummyNode->_left = current->_left;


                if (current->_left != nullptr)
                {
                    current->_left->_right = dummyNode;
                }

                current->_left = dummyNode;

            }
            current = current->_down;
        }
        return current;
    }
    Node* CreateRowAbove(Node* current, Node* newNode)
    {
        while (current != nullptr)
        {
            if (current->_up != newNode)
            {

                Node* _dummyNode = CreateDummyNode(current);
                _dummyNode->width = current->width;

                _dummyNode->_down = current;
                _dummyNode->_up = current->_up;
                current->_up = _dummyNode;

            }
            current = current->_right;
        }
        return current;
    }
    Node* CreateRowBelow(Node* current, Node* newNode)
    {
        while (current != nullptr)
        {

            if (current->_down != newNode)
            {

                Node* _dummyNode = CreateDummyNode(current);
                _dummyNode->width = current->width;

                _dummyNode->_up = current;
                _dummyNode->_down = current->_down;

                if (current->_down != nullptr)
                {
                    current->_down->_up = _dummyNode;
                }

                current->_down = _dummyNode;


            }
            current = current->_right;
        }
        return current;
    }
    Node* RewindRows(Node* row)
    {
        while (row->_up != nullptr)
        {
            row = row->_up;
        }
        return row;
    }
    Node* RewindColumns(Node* column)
    {
        while (column->_left != nullptr)
        {
            column = column->_left;
        }
        return column;
    }

    void SetRowsColsDim()
    {
        Node* temp = _head;
        while (temp != nullptr)
        {

            Node* tmp = temp;
            while (tmp != nullptr)
            {
                tmp->height = GetYMax(tmp);
                tmp->width = GetXMax(tmp);

                tmp = tmp->_down;
            }
            temp = temp->_right;
        }

    }
    void ResetSizes()
    {
        Node* temp = _head;
        while (temp != nullptr)
        {
            Node* tmp = temp;
            while (tmp != nullptr)
            {
                if (tmp->_data->pItem != nullptr)
                {
                    tmp->height = tmp->_data->pItem->defaultHeight();
                    tmp->width = tmp->_data->pItem->defaultWidth();
                    /************************************************
                    ******** TO BE IMPLEMENTED **********************
                    *************************************************/
                    tmp->_data->pItem->resetSize();
                }

                tmp = tmp->_down;
            }
            temp = temp->_right;
        }
    }
    void SetExpandPolicies()
    {
        Node* temp = _head;
        while (temp != nullptr)
        {
            Node* tmp = temp;
            while (tmp != nullptr)
            {
                if (tmp->_data->pItem != nullptr)
                {
                    // tmp._data.Item.ResetSize();

                      /************************************************
                    ******** TO BE IMPLEMENTED **********************
                    *************************************************/
                    /*   if (tmp._data.Item.XPolicy == UIObject.SizePolicy.EXPAND)
                       {
                           int _delta = GetXMax(tmp) - tmp._data.Item.Width;

                           if (_delta > 0)
                           {
                               tmp._data.Item.Resize(new Point(_delta, 0));
                           }

                       }
                       if (tmp._data.Item.YPolicy == UIObject.SizePolicy.EXPAND)
                       {
                           int _delta = GetYMax(tmp) - tmp._data.Item.Height;

                           if (_delta > 0)
                           {
                               tmp._data.Item.Resize(new Point(0, _delta));
                           }
                       }*/

                }
                tmp = tmp->_down;
            }
            temp = temp->_right;
        }
    }
    void FixToBounds()
    {
        ResetSizes();


        float _totalXSize = GetColumnsTotalSize(GetWidestRow());
        while (_totalXSize > mFrameRect.width - MIN_SPACE * 2)
        {
            ResizeHorizontal();
            _totalXSize = GetColumnsTotalSize(GetWidestRow());
        }

        float totalYSize = GetRowsTotalSize(GetHeighestColumn());
        while (totalYSize > mFrameRect.height - MIN_SPACE * 2)
        {
            ResizeVertical();
            totalYSize = GetRowsTotalSize(GetHeighestColumn());
        }

        SetExpandPolicies();
    }
    int GetCountX()
    {
        Node* temp = _head;
        int _count = 0;
        while (temp != nullptr)
        {
            temp = temp->_right;
            _count++;
        }

        return _count;
    }
    int GetCountY()
    {
        Node* temp = _head;
        int _count = 0;
        while (temp != nullptr)
        {
            temp = temp->_down;
            _count++;
        }

        return _count;
    }
    float GetColumnsTotalSize(Node* current)
    {
        float totalWidth = 0;
        float spacesSum = 0;

        if (current != nullptr)
        {
            Node* temp = RewindColumns(current);

            while (temp != nullptr)
            {
                totalWidth += GetXMax(temp);
                temp = temp->_right;

            }

            spacesSum = MIN_SPACE * (GetCountX() + 1);
        }
        return totalWidth + spacesSum;
    }
    float GetRowsTotalSize(Node* current)
    {
        float totalHeight = 0;
        float spacesSum = 0;

        if (current != nullptr)
        {
            Node* temp = RewindRows(current);

            while (temp != nullptr)
            {
                totalHeight += GetYMax(temp);
                temp = temp->_down;

            }

            spacesSum = MIN_SPACE * (GetCountY() + 1);
        }

        return totalHeight + spacesSum;
    }
    Node* GetWidestRow()
    {
        Node* temp = _head;
        Node* _max = nullptr;
        while (temp != nullptr)
        {
            if (_max == nullptr)
            {
                _max = temp;
            }
            if (GetColumnsTotalSize(temp) >= GetColumnsTotalSize(_max))
            {
                _max = temp;
            }
            temp = temp->_down;
        }
        return _max;
    }
    Node* GetHeighestColumn()
    {
        Node* temp = _head;
        Node* _max = nullptr;
        while (temp != nullptr)
        {
            if (_max == nullptr)
            {
                _max = temp;
            }
            if (GetRowsTotalSize(temp) >= GetRowsTotalSize(_max))
            {
                _max = temp;
            }
            temp = temp->_right;
        }
        return _max;
    }
    void ResizeHorizontal()
    {

        Node* temp = _head;

        while (temp != nullptr)
        {

            Node* tmp = temp;
            while (tmp != nullptr)
            {
                float _newSizeX = GetXMax(tmp);
                if (GetWidestRow()->width > tmp->width)
                {
                    float ratio = tmp->width / (float)GetWidestRow()->width;
                    _newSizeX = (tmp->width * (ONE_PER * ratio));
                }
                else
                {
                    _newSizeX = ceil(_newSizeX * ONE_PER);
                }
                if (tmp->_data->pItem != nullptr)
                {
                    //tmp._data.Item.ResetSize();   

                    if (_newSizeX > 0)
                    {
                        tmp->_data->pItem->resize(sf::Vector2f(-_newSizeX, 0));
                        tmp->width = tmp->_data->pItem->width();
                    }
                }
                else
                {
                    if (_newSizeX > 0)
                    {
                        tmp->width += -_newSizeX;
                    }
                }

                tmp = tmp->_right;

            }
            temp = temp->_down;
        }
    }
    void ResizeVertical()
    {
        Node* temp = _head;

        while (temp != nullptr)
        {

            Node* tmp = temp;
            while (tmp != nullptr)
            {

                float _newSizeY = GetYMax(tmp);
                if (GetHeighestColumn()->height > tmp->height)
                {
                    float ratio = tmp->height / (float)GetHeighestColumn()->height;
                    _newSizeY = (tmp->height * (ONE_PER * ratio));
                }
                else
                {
                    _newSizeY = ceil(_newSizeY * ONE_PER);
                }
                if (tmp->_data->pItem != nullptr)
                {
                    //tmp._data.Item.ResetSize();                    

                    if (_newSizeY > 0)
                    {
                        tmp->_data->pItem->resize(sf::Vector2f(0, -_newSizeY));
                        tmp->height = tmp->_data->pItem->height();
                    }
                }
                else
                {
                    if (_newSizeY > 0)
                    {
                        tmp->height += -_newSizeY;
                    }
                }
                tmp = tmp->_down;

            }
            temp = temp->_right;
        }
    }
    void RearrangeList()
    {
        Node* temp = _head;
        if (temp != nullptr)
        {
            temp->_data->mPosition = sf::Vector2i(mFrameRect.width / 2 - temp->width / 2, mFrameRect.height / 2 - temp->height / 2);
            temp->_data->mPosition = sf::Vector2i(temp->_data->mPosition.x - GetTotalXSizeExcept(temp) / 2, mFrameRect.height / 2 - temp->height / 2);

            while (temp->_right != nullptr)
            {

                temp->_right->_data->mPosition = sf::Vector2i(temp->_data->mPosition.x + temp->width + MIN_SPACE, mFrameRect.height / 2 - temp->height / 2);
                temp = temp->_right;
            }

        }

        temp = _head;
        while (temp != nullptr)
        {
            Node* tmp = temp;

            tmp = RewindRows(tmp);

            if (tmp->_down != nullptr)
            {
                tmp->_data->mPosition = sf::Vector2i(tmp->_data->mPosition.x, mFrameRect.height / 2 - tmp->height / 2);

                tmp->_data->mPosition = sf::Vector2i(tmp->_data->mPosition.x, tmp->_data->mPosition.y - GetTotalYSizeExcept(tmp) / 2);

                while (tmp->_down != nullptr)
                {
                    tmp->_down->_data->mPosition = sf::Vector2i(tmp->_data->mPosition.x, tmp->_data->mPosition.y + tmp->height + MIN_SPACE);
                    tmp = tmp->_down;
                }
            }
            temp = temp->_right;
        }
    }
    void UpdateLayout()
    {
        FixToBounds();
        SetRowsColsDim();
        RearrangeList();
    }
    float GetTotalXSizeExcept(Node* current)
    {
        Node* temp = _head;
        float totalWidth = 0;
        float spacesSum = 0;
        while (temp != nullptr)
        {
            if (temp != current)
            {
                totalWidth += GetXMax(temp);
            }
            temp = temp->_right;
        }

        spacesSum = MIN_SPACE * GetCountX();

        return totalWidth + spacesSum;
    }

    float GetTotalYSizeExcept(Node* current)
    {
        Node* temp = current;
        float totalHeight = 0;
        float spacesSum = 0;
        while (temp != nullptr)
        {
            if (temp != current)
            {
                totalHeight += GetYMax(temp);

            }
            temp = temp->_down;
        }

        spacesSum = MIN_SPACE * GetCountY(current);

        return totalHeight + spacesSum;
    }
    int GetCountY(Node* current)
    {
        Node* temp = current;
        int _count = 0;
        while (temp != nullptr)
        {
            temp = temp->_down;
            _count++;
        }

        return _count;
    }

    bool RowHasItems(Node* row)
    {
        Node* current = row;
        row = RewindColumns(row);
        while (row != nullptr)
        {
            if (row != current && row->_data->pItem != nullptr)
            {
                return true;
            }
            row = row->_right;
        }
        return false;
    }
    bool ColumnHasItems(Node* column)
    {
        Node* current = column;
        column = RewindRows(column);
        while (column != nullptr)
        {
            if (column != current && column->_data->pItem != nullptr)
            {
                return true;
            }
            column = column->_down;
        }
        return false;
    }

    void DeleteRow(Node* row)
    {
        row = RewindColumns(row);
        while (row != nullptr)
        {
            if (row->_up != nullptr)
            {
                row->_up->_down = row->_down;
            }
            if (row->_down != nullptr)
            {
                row->_down->_up = row->_up;
            }
            row = row->_right;
        }
    }

    void DeleteColumn(Node* column)
    {
        column = RewindRows(column);
        while (column != nullptr)
        {

            if (column->_right != nullptr)
            {
                column->_right->_left = column->_left;
            }
            if (column->_left != nullptr)
            {
                column->_left->_right = column->_right;
            }

            column = column->_down;
        }
    }
    void DeleteNodebyKey(Container::Slot* key)
    {
        Node* temp = _head;

        /* if (MouseGUI.Focus == null)
         {
             key.Item.ResetSize();
         }*/
        if (temp != nullptr && temp->_data == key)
        {

            Node* _dummyNode = CreateDummyNode(temp);
            _dummyNode->_right = temp->_right;
            _dummyNode->_left = temp->_left;
            _dummyNode->_down = temp->_down;
            _dummyNode->_up = temp->_up;
            _dummyNode->width = GetXMaxExcept(temp);
            _dummyNode->height = GetYMaxExcept(temp);
            _dummyNode->_data->mPosition = temp->_data->mPosition;

            if (temp->_down != nullptr)
            {
                temp->_down->_up = _dummyNode;
            }
            if (temp->_right != nullptr)
            {
                temp->_right->_left = _dummyNode;
            }

            _head = _dummyNode;

            Node* _nextColumn = _head->_right;
            Node* _nextRow = _head->_down;

            if (!RowHasItems(_head))
            {
                DeleteRow(_head);
                _head = _nextRow;
            }

            else if (!ColumnHasItems(_head))
            {
                DeleteColumn(_head);
                _head = _nextColumn;
            }

        }
        else
        {
            while (temp != nullptr)
            {
                Node* tmp = temp;
                while (tmp != nullptr)
                {
                    if (tmp->_data == key)
                    {
                        Node* _dummyNode = CreateDummyNode(tmp);
                        _dummyNode->_left = tmp->_left;
                        _dummyNode->_right = tmp->_right;
                        _dummyNode->_up = tmp->_up;
                        _dummyNode->_down = tmp->_down;
                        _dummyNode->_data->mPosition = tmp->_data->mPosition;

                        _dummyNode->width = GetXMaxExcept(tmp);
                        _dummyNode->height = GetYMaxExcept(tmp);

                        if (tmp->_left != nullptr)
                        {
                            tmp->_left->_right = _dummyNode;
                        }
                        if (tmp->_right != nullptr)
                        {
                            tmp->_right->_left = _dummyNode;
                        }
                        if (tmp->_up != nullptr)
                        {
                            tmp->_up->_down = _dummyNode;
                        }
                        if (tmp->_down != nullptr)
                        {
                            tmp->_down->_up = _dummyNode;
                        }

                        if (!RowHasItems(tmp))
                        {
                            Node* _row = RewindColumns(tmp);

                            DeleteRow(tmp);
                            if (_row->_up == nullptr)
                            {
                                _head = _row->_down;
                            }

                        }

                        else if (!ColumnHasItems(tmp))
                        {
                            Node* _col = RewindRows(tmp);
                            DeleteColumn(tmp);
                            if (_col->_left == nullptr)
                            {
                                _head = _col->_right;
                            }
                        }

                        break;

                    }
                    tmp = tmp->_down;
                }
                temp = temp->_right;
            }
        }


    }
    void setRectangle(int left, int top, int width, int height)
    {
        mFrameRect.left = left;
        mFrameRect.top = top;
        mFrameRect.width = width;
        mFrameRect.height = height;
    }
private:
    sf::IntRect mFrameRect;

};
#endif // !GRIDLL