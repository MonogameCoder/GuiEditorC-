#include "gridLL.h"

GridLL::GridLL()

{
    _head = nullptr;
}

GridLL::~GridLL()
{
    Node* pivot = _head;
    Node* tmp = nullptr;
    pivot = forwardColumns(pivot);

    while (pivot != nullptr)
    {
        while (pivot != nullptr)
        {
            tmp = pivot;   
            pivot = pivot->_left;
           
            if (pivot == _head)
            {
                break;
            }

            delete tmp;            
            tmp = nullptr;
        }
        tmp = _head;
        _head = _head->_down;
        pivot = _head;
       
        if (pivot != nullptr)
        {
            pivot = forwardColumns(pivot);
        }
      
        delete tmp;
        tmp = nullptr;
       
    }
    _head = nullptr;

}

float GridLL::getXMax(Node* current)
{
    Node* temp = current;
    temp = rewindRows(temp);
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
        temp = rewindRows(current);
        if (temp->_up == nullptr && temp->_right != nullptr)
        {
            _head = temp->_right;
        }
        deleteColumn(temp);
        return 0;
    }
    return _max->_data->pItem->width();
}

float GridLL::getXMaxExcept(Node* current)

{
    Node* temp = current;
    temp = rewindRows(temp);
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

float GridLL::getYMax(Node* current)

{
    Node* temp = current;
    temp = rewindColumns(temp);
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
        temp = rewindColumns(current);
        if (temp->_up == nullptr && temp->_down != nullptr)
        {
            _head = temp->_down;
        }
        deleteRow(temp);
        return 0;
    }
    return _max->_data->pItem->height();
}

float GridLL::getYMaxExcept(Node* current)

{
    Node* temp = current;
    temp = rewindColumns(temp);
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

void GridLL::insert(Container::Slot* data)
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
            if (data->pItem->getPosition().x < mFrameRect.getPosition().x + temp->_data->mPosition.x)
            {
                while (temp->_down != nullptr && data->pItem->getPosition().y > mFrameRect.getPosition().y + temp->_data->mPosition.y + temp->height)
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

                Node* _current = rewindRows(temp);
                _current = createColumnBefore(_current, _newNode);
                _current = rewindRows(temp);


                while (_current->_down != nullptr)
                {
                    _current->_left->_down = _current->_down->_left;
                    _current->_left->_down->_up = _current->_left;

                    _current = _current->_down;
                }

                _current = rewindRows(temp);
                _current = rewindColumns(_current);

                _head = _current;
                break;


            }
            else if (temp->_right == nullptr && data->pItem->getPosition().x >= mFrameRect.getPosition().x + temp->_data->mPosition.x + temp->width - MIN_SPACE)
            {
                while (temp->_down != nullptr && data->pItem->getPosition().y > mFrameRect.getPosition().y + temp->_data->mPosition.y + temp->height)
                {
                    temp = temp->_down;
                }

                _newNode->_left = temp;
                _newNode->_right = temp->_right;
                temp->_right = _newNode;


                Node* _current = rewindRows(temp);
                _current = createColumnAfter(_current, _newNode);

                _current = rewindRows(temp);
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
                if (data->pItem->getPosition().x >= mFrameRect.getPosition().x + temp->_data->mPosition.x - MIN_SPACE && data->pItem->getPosition().x <= mFrameRect.getPosition().x + temp->_data->mPosition.x + temp->width - MIN_SPACE)
                {
                    while (temp->_right != nullptr && data->pItem->getPosition().x > mFrameRect.getPosition().x + temp->_data->mPosition.x + temp->width)
                    {
                        temp = temp->_right;
                    }

                    if (data->pItem->getPosition().y + data->pItem->height() <= mFrameRect.getPosition().y + temp->_data->mPosition.y)
                    {
                        temp->_up = _newNode;
                        _newNode->_down = temp;

                        Node* _current = rewindColumns(temp);
                        _current = createRowAbove(_current, _newNode);

                        _current = rewindColumns(temp);

                        while (_current->_right != nullptr)
                        {
                            _current->_up->_right = _current->_right->_up;
                            _current->_right->_up->_left = _current->_up;
                            _current = _current->_right;
                        }
                        _current = rewindRows(_current);
                        _current = rewindColumns(_current);
                        _head = _current;
                        break;

                    }
                    else
                    {

                        while (temp->_down != nullptr && data->pItem->getPosition().y > mFrameRect.getPosition().y + temp->_data->mPosition.y + temp->height)
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

                            _current = rewindColumns(_current);
                            _current = createRowBelow(_current, _newNode);
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
    fixToBounds();
    setRowsColsDim();
    rearrangeList();

}

GridLL::Node* GridLL::createDummyNode(Node* current)
{
    Container::Slot* _dummyslot = new Container::Slot(sf::Vector2i(), nullptr);

    Node* _dummyNode = new Node(_dummyslot);

    _dummyNode->width = current->width;
    _dummyNode->height = current->height;

    return _dummyNode;
}

GridLL::Node* GridLL::createColumnAfter(Node* current, Node* newNode)
{
    while (current != nullptr)
    {
        if (current->_right != newNode)
        {
            Node* _dummyNode = createDummyNode(current);
            _dummyNode->width = current->width;
            _dummyNode->height = current->height;
            _dummyNode->_right = current->_right;
            _dummyNode->_left = current;

            current->_right = _dummyNode;

        }
        current = current->_down;
    }
    return current;
}

GridLL::Node* GridLL::createColumnBefore(Node* current, Node* newNode)
{
    while (current != nullptr)
    {
        if (current->_left != newNode)
        {
            Node* _dummyNode = createDummyNode(current);

            _dummyNode->width = current->width;
            _dummyNode->height = current->height;

            _dummyNode->_right = current;
            _dummyNode->_left = current->_left;


            if (current->_left != nullptr)
            {
                current->_left->_right = _dummyNode;
            }

            current->_left = _dummyNode;

        }
        current = current->_down;
    }
    return current;
}

GridLL::Node* GridLL::createRowAbove(Node* current, Node* newNode)
{
    while (current != nullptr)
    {
        if (current->_up != newNode)
        {

            Node* _dummyNode = createDummyNode(current);
            _dummyNode->width = current->width;
            _dummyNode->height = current->height;
            _dummyNode->_down = current;
            _dummyNode->_up = current->_up;
            current->_up = _dummyNode;

        }
        current = current->_right;
    }
    return current;
}

GridLL::Node* GridLL::createRowBelow(Node* current, Node* newNode)
{
    while (current != nullptr)
    {

        if (current->_down != newNode)
        {

            Node* _dummyNode = createDummyNode(current);
            _dummyNode->width = current->width;
            _dummyNode->height = current->height;
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

GridLL::Node* GridLL::rewindRows(Node* row)
{
    while (row->_up != nullptr)
    {
        row = row->_up;
    }
    return row;
}

GridLL::Node* GridLL::rewindColumns(Node* column)
{
    while (column->_left != nullptr)
    {
        column = column->_left;
    }
    return column;
}

GridLL::Node* GridLL::forwardColumns(Node* column)
{
    Node* pivot = column;
    while (pivot->_right != nullptr)
    {
        pivot = pivot->_right;
    }
    return pivot;
}

void GridLL::setRowsColsDim()
{
    Node* temp = _head;
    while (temp != nullptr)
    {

        Node* tmp = temp;
        while (tmp != nullptr)
        {
            tmp->height = getYMax(tmp);
            tmp->width = getXMax(tmp);

            tmp = tmp->_down;
        }
        temp = temp->_right;
    }

}

void GridLL::resetSizes()
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
                //tmp->_data->pItem->resetSize();
            }

            tmp = tmp->_down;
        }
        temp = temp->_right;
    }
}

void GridLL::setExpandPolicies()
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
                       int _delta = getXMax(tmp) - tmp._data.Item.Width;

                       if (_delta > 0)
                       {
                           tmp._data.Item.Resize(new Point(_delta, 0));
                       }

                   }
                   if (tmp._data.Item.YPolicy == UIObject.SizePolicy.EXPAND)
                   {
                       int _delta = getYMax(tmp) - tmp._data.Item.Height;

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

void GridLL::fixToBounds()
{
    resetSizes();


    float _totalXSize = getColumnsTotalSize(getWidestRow());
    while (_totalXSize > mFrameRect.width - MIN_SPACE * 2)
    {
        resizeHorizontal();
        _totalXSize = getColumnsTotalSize(getWidestRow());
    }

    float totalYSize = getRowsTotalSize(getHeighestColumn());
    while (totalYSize > mFrameRect.height - MIN_SPACE * 2)
    {
        resizeVertical();
        totalYSize = getRowsTotalSize(getHeighestColumn());
    }

    setExpandPolicies();
}

int GridLL::getCountX()
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

int GridLL::getCountY()
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

float GridLL::getColumnsTotalSize(Node* current)
{
    float totalWidth = 0;
    float spacesSum = 0;

    if (current != nullptr)
    {
        Node* temp = rewindColumns(current);

        while (temp != nullptr)
        {
            totalWidth += getXMax(temp);
            temp = temp->_right;

        }

        spacesSum = MIN_SPACE * (getCountX() + 1);
    }
    return totalWidth + spacesSum;
}

float GridLL::getRowsTotalSize(Node* current)
{
    float totalHeight = 0;
    float spacesSum = 0;

    if (current != nullptr)
    {
        Node* temp = rewindRows(current);

        while (temp != nullptr)
        {
            totalHeight += getYMax(temp);
            temp = temp->_down;

        }

        spacesSum = MIN_SPACE * (getCountY() + 1);
    }

    return totalHeight + spacesSum;
}

GridLL::Node* GridLL::getWidestRow()
{
    Node* temp = _head;
    Node* _max = nullptr;
    while (temp != nullptr)
    {
        if (_max == nullptr)
        {
            _max = temp;
        }
        if (getColumnsTotalSize(temp) >= getColumnsTotalSize(_max))
        {
            _max = temp;
        }
        temp = temp->_down;
    }
    return _max;
}

GridLL::Node* GridLL::getHeighestColumn()
{
    Node* temp = _head;
    Node* _max = nullptr;
    while (temp != nullptr)
    {
        if (_max == nullptr)
        {
            _max = temp;
        }
        if (getRowsTotalSize(temp) >= getRowsTotalSize(_max))
        {
            _max = temp;
        }
        temp = temp->_right;
    }
    return _max;
}

void GridLL::resizeHorizontal()
{

    Node* temp = _head;

    while (temp != nullptr)
    {

        Node* tmp = temp;
        while (tmp != nullptr)
        {
            float _newSizeX = getXMax(tmp);
            if (getWidestRow()->width > tmp->width)
            {
                float ratio = tmp->width / (float)getWidestRow()->width;
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

void GridLL::resizeVertical()
{
    Node* temp = _head;

    while (temp != nullptr)
    {

        Node* tmp = temp;
        while (tmp != nullptr)
        {

            float _newSizeY = getYMax(tmp);
            if (getHeighestColumn()->height > tmp->height)
            {
                float ratio = tmp->height / (float)getHeighestColumn()->height;
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

void GridLL::rearrangeList()
{
    Node* temp = _head;
    if (temp != nullptr)
    {
        temp->_data->mPosition = sf::Vector2i(mFrameRect.width / 2 - temp->width / 2, mFrameRect.height / 2 - temp->height / 2);
        temp->_data->mPosition = sf::Vector2i(temp->_data->mPosition.x - getTotalXSizeExcept(temp) / 2, mFrameRect.height / 2 - temp->height / 2);

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

        tmp = rewindRows(tmp);

        if (tmp->_down != nullptr)
        {
            tmp->_data->mPosition = sf::Vector2i(tmp->_data->mPosition.x, mFrameRect.height / 2 - tmp->height / 2);

            tmp->_data->mPosition = sf::Vector2i(tmp->_data->mPosition.x, tmp->_data->mPosition.y - getTotalYSizeExcept(tmp) / 2);

            while (tmp->_down != nullptr)
            {
               
                tmp->_down->_data->mPosition = sf::Vector2i(tmp->_data->mPosition.x, tmp->_data->mPosition.y + tmp->height + MIN_SPACE);
                tmp = tmp->_down;
            }
        }
        temp = temp->_right;
    }
    
}

void GridLL::updateLayout()
{
    fixToBounds();
    setRowsColsDim();
    rearrangeList();
}

float GridLL::getTotalXSizeExcept(Node* current)
{
    Node* temp = _head;
    float totalWidth = 0;
    float spacesSum = 0;
    while (temp != nullptr)
    {
        if (temp != current)
        {
            totalWidth += getXMax(temp);
        }
        temp = temp->_right;
    }

    spacesSum = MIN_SPACE * getCountX();

    return totalWidth + spacesSum;
}

float GridLL::getTotalYSizeExcept(Node* current)
{
    Node* temp = current;
    float totalHeight = 0;
    float spacesSum = 0;
    while (temp != nullptr)
    {
        if (temp != current)
        {
            totalHeight += getYMax(temp);

        }
        temp = temp->_down;
    }

    spacesSum = MIN_SPACE * getCountY(current);

    return totalHeight + spacesSum;
}

int GridLL::getCountY(Node* current)
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

bool GridLL::rowHasItems(Node* row)
{
    Node* current = row;
    row = rewindColumns(row);
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

bool GridLL::columnHasItems(Node* column)
{
    Node* current = column;
    column = rewindRows(column);
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

void GridLL::deleteRow(Node* row)
{
    Node* temp = row;
    row = rewindColumns(row);

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

void GridLL::deleteColumn(Node* column)
{
    Node* temp = column;
    column = rewindRows(column);
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

void GridLL::deleteNodebyKey(Container::Slot* key)
{
    Node* temp = _head;

    /* if (MouseGUI.Focus == null)
     {
         key.Item.ResetSize();
     }*/
    if (temp != nullptr && temp->_data == key)
    {

        Node* _dummyNode = createDummyNode(temp);
        _dummyNode->_right = temp->_right;
        _dummyNode->_left = temp->_left;
        _dummyNode->_down = temp->_down;
        _dummyNode->_up = temp->_up;
        _dummyNode->width = getXMaxExcept(temp);
        _dummyNode->height = getYMaxExcept(temp);
        _dummyNode->_data->mPosition = temp->_data->mPosition;

        if (temp->_down != nullptr)
        {
            temp->_down->_up = _dummyNode;
        }
        if (temp->_right != nullptr)
        {
            temp->_right->_left = _dummyNode;
        }

        //_head = _dummyNode;

        Node* _nextColumn = _head->_right;
        Node* _nextRow = _head->_down;

        if (!rowHasItems(_head))
        {
            deleteRow(_head);
            _head = _nextRow;
        }

        else if (!columnHasItems(_head))
        {
            deleteColumn(_head);
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
                    Node* _dummyNode = createDummyNode(tmp);
                    _dummyNode->_left = tmp->_left;
                    _dummyNode->_right = tmp->_right;
                    _dummyNode->_up = tmp->_up;
                    _dummyNode->_down = tmp->_down;
                    _dummyNode->width = getXMaxExcept(tmp);
                    _dummyNode->height = getYMaxExcept(tmp);

                    _dummyNode->_data->mPosition = tmp->_data->mPosition;

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

                    if (!rowHasItems(tmp))
                    {
                        Node* _row = rewindColumns(tmp);

                        deleteRow(tmp);
                        if (_row->_up == nullptr)
                        {
                            _head = _row->_down;
                        }

                    }

                    else if (!columnHasItems(tmp))
                    {
                        Node* _col = rewindRows(tmp);
                        deleteColumn(tmp);
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

void GridLL::setRectangle(int left, int top, int width, int height)
{
    mFrameRect.left = left;
    mFrameRect.top = top;
    mFrameRect.width = width;
    mFrameRect.height = height;
}


