#include "GRPExtendTableView.h"
#include "GRPDataSourceModel.h"

void GRPExtendTableView::hideRow(int row)
{
    Q_D(GRPExtendTableView);

    if (d->m_isTree || d->m_isGroupMode)
    {
        return;
    }

    GLDTableView::hideRow(row);
}

void GRPExtendTableView::groupChanged(QVector<int> newGroup)
{
    // 将树形交给现存的最靠前的列
    Q_D(GRPExtendTableView);

    int nTreeCol = 0;

    for (int nCol = 0; nCol < d->m_horizontalHeader->count(); ++nCol)
    {
        for (int nGroup = 0; nGroup < newGroup.size(); ++nGroup)
        {
            if (nCol == newGroup.at(nGroup) && nCol <= nTreeCol)
            {
                nTreeCol++;
                break;
            }
        }
    }

    d->m_treeColumn = nTreeCol;
}

GRPExtendTableView::GRPExtendTableView(QWidget *parent) :
    GLDTableView(*new GRPExtendTableViewPrivate, parent)
{
    loadStyleSheet(QString::fromLatin1(":/qsses/GLDTableView.qss"));
}

void GRPExtendTableView::expand(int row, bool emitSignal)
{
    Q_D(GRPExtendTableView);
    d->expand(row, emitSignal);
}

void GRPExtendTableView::collapse(int row, bool emitSignal)
{
    Q_D(GRPExtendTableView);
    d->collapse(row, emitSignal);
}

bool GRPExtendTableView::isRowExpanded(int row)
{
    Q_D(GRPExtendTableView);
    Q_ASSERT(row >= 0);
    return 0 != d->m_drawInfo->m_viewItems[row].expanded;
}

void GRPExtendTableView::expandAll()
{
    Q_D(GRPExtendTableView);

    if (d->m_isTree)
    {
        setState(GlodonAbstractItemView::ExpandingState);

        try
        {
            for (int row = 0; row < d->m_drawInfo->m_viewItems.count(); row++)
            {
                if (0 == d->m_drawInfo->m_viewItems.at(row).expanded)
                {
                    if (!d->m_isTree || row <= -1
                        || d->m_drawInfo->m_viewItems.count() <= row
                        || 0 != d->m_drawInfo->m_viewItems.at(row).expanded)
                    {
                        continue;
                    }

                    d->m_drawInfo->expandItem(row);
                    afterExpandedChanged(row, true, true);
                }
            }
        }
        catch (...)
        {
            d->m_state = GLDTableView::NoState;
            throw;
        }

        d->m_state = GLDTableView::NoState;
        refreshDisplayColRow();
        d->viewport->update();
    }
}

void GRPExtendTableView::collapseAll()
{
    Q_D(GRPExtendTableView);

    if (d->m_isTree)
    {
        setState(GlodonAbstractItemView::CollapsingState);

        try
        {
            for (int row = 0; row < d->m_drawInfo->m_viewItems.count(); row++)
            {
                if (0 != d->m_drawInfo->m_viewItems.at(row).expanded)
                {
                    if (!d->m_isTree || row <= -1
                        || d->m_drawInfo->m_viewItems.count() <= row
                        || 0 == d->m_drawInfo->m_viewItems.at(row).expanded)
                    {
                        continue;
                    }

                    d->m_drawInfo->collapseItem(row);
                    afterExpandedChanged(row, false, true);
                }
            }
        }
        catch (...)
        {
            d->m_state = GLDTableView::NoState;
            throw;
        }

        d->m_state = GLDTableView::NoState;
        refreshDisplayColRow();
        d->viewport->update();
    }
}

void GRPExtendTableView::setRootIndex(const QModelIndex &index)
{
    Q_D(GRPExtendTableView);

    if (index == d->m_root)
    {
        viewport()->update();

        return;
    }

    d->m_verticalHeader->setRootIndex(index);
    d->m_horizontalHeader->setRootIndex(index);

    GlodonAbstractItemView::setRootIndex(index);
}

QModelIndex GRPExtendTableView::treeIndex(const QModelIndex &index) const
{
    Q_D(const GRPExtendTableView);

    if (d->m_isGroupMode)
    {
        return QModelIndex();
    }

    if (d->m_isTree)
    {
        return static_cast<GlodonTreeModel *>(d->m_model)->treeIndex(index);
    }

    return index;
}

QModelIndex GRPExtendTableView::dataIndex(const QModelIndex &index) const
{
    Q_D(const GRPExtendTableView);

    if (d->m_isGroupMode)
    {
        QModelIndex treeIndex = static_cast<GlodonTreeModel *>(d->m_model)->dataIndex(index);
        QAbstractItemModel *itemModel = const_cast<QAbstractItemModel *>(treeIndex.model());

        return static_cast<GlodonGroupModel *>(itemModel)->dataIndex(treeIndex);
    }

    if (d->m_isTree)
    {
        if (index.model() == d->m_model)
        {
            QModelIndex treeIndex = static_cast<GlodonTreeModel *>(d->m_model)->dataIndex(index);
            const GlodonGroupModel *groupModel = dynamic_cast<const GlodonGroupModel *>(treeIndex.model());

            if (groupModel)
            {
                return groupModel->dataIndex(treeIndex);
            }
            else
            {
                return treeIndex;
            }
        }
    }

    return index;
}

QModelIndex GRPExtendTableView::currentDataIndex() const
{
    Q_D(const GRPExtendTableView);

    if (d->m_isTree)
    {
        const QModelIndex c_index = currentIndex();
        GlodonTreeModel *treeModel = static_cast<GlodonTreeModel *>(d->m_model);
        return treeModel->dataIndex(c_index);
    }

    return QModelIndex();
}

void GRPExtendTableView::setIsTree(bool value)
{
    Q_D(GRPExtendTableView);

    if ((d->m_isTree == value) || (d->m_isGroupMode))
    {
        return;
    }

    doSetIsTree(value);

    if (value)
    {
        if (!d->m_dataModel)
        {
            doSetModel(d->m_model);
        }
    }
    else
    {
        doSetModel(d->m_dataModel);
        setDataModel(0);
    }

    d->viewport->update();
}

bool GRPExtendTableView::isTree() const
{
    Q_D(const GRPExtendTableView);

    return d->m_isTree;
}

void GRPExtendTableView::setIsGroupMode(bool groupModeEnable)
{
    Q_D(GRPExtendTableView);

    if ((groupModeEnable == d->m_isGroupMode) || isDisplayFilter() || totalRowAtFooter())
    {
        return;
    }

    d->m_isGroupMode = groupModeEnable;

    if (groupModeEnable)
    {
        //切换model时如果处于编辑状态，强制退出
        if (d->m_oEditorIndex.isValid())
        {
            forceCloseEditor();
        }

        GlodonGroupHeaderView *cxHeader = new GlodonGroupHeaderView(this);
        setHorizontalHeader(cxHeader);
        doSetModel(d->m_model);

        if (!cxHeader->isVisible())
        {
            cxHeader->show();
        }
    }
    else
    {
        GlodonHeaderView *header = new GlodonHeaderView(Qt::Horizontal, this);
        setHorizontalHeader(header);
        doSetModel(d->m_dataModel);

        if (!header->isVisible())
        {
            header->show();
        }
    }
}

bool GRPExtendTableView::isGroupMode() const
{
    Q_D(const GRPExtendTableView);
    return d->m_isGroupMode;
}

void GRPExtendTableView::setTreeDecorationStyle(TreeDecorationStyle style)
{
    Q_D(GRPExtendTableView);

    if (d->m_treeDecorationStyle != style)
    {
        d->m_treeDecorationStyle = style;
        d->viewport->update();
    }
}

TreeDecorationStyle GRPExtendTableView::treeDecorationStyle() const
{
    Q_D(const GRPExtendTableView);
    return d->m_treeDecorationStyle;
}

void GRPExtendTableView::setTreeDrawInfo(GlodonTreeDrawInfo *tableViewDrawInfo)
{
    Q_D(GRPExtendTableView);

    if (d->m_drawInfo == tableViewDrawInfo)
    {
        return;
    }
    else if (!d->m_drawInfo)
    {
        d->m_drawInfo = tableViewDrawInfo;
        d->m_drawInfo->m_header = d->m_verticalHeader;
        d->m_drawInfo->setModel(d->m_model);
    }
}

GlodonTreeDrawInfo *GRPExtendTableView::treeDrawInfo()
{
    Q_D(GRPExtendTableView);
    return d->m_drawInfo;
}

void GRPExtendTableView::setRollOut(GIntList *rollOut)
{
    Q_D(GRPExtendTableView);

    if (d->m_drawInfo->m_rollOut && !d->m_drawInfo->m_rollOut->isEmpty())
    {
        d->m_drawInfo->m_rollOut->clear();
    }

    d->m_drawInfo->m_rollOut = rollOut;
}

GIntList *GRPExtendTableView::rollOut()
{
    Q_D(GRPExtendTableView);
    return d->m_drawInfo->m_rollOut;
}

bool GRPExtendTableView::isAddChildToSelection()
{
    Q_D(GRPExtendTableView);
    return d->m_addChildInSelection;
}

void GRPExtendTableView::setAddChildToSelection(bool value)
{
    Q_D(GRPExtendTableView);
    d->m_addChildInSelection = value;
}

void GRPExtendTableView::setTreeColumn(int column)
{
    Q_D(GRPExtendTableView);
    d->m_treeColumn = column;
}

int GRPExtendTableView::treeColumn()
{
    Q_D(GRPExtendTableView);
    return d->m_treeColumn;
}

/********protected slots:*************************************************/
void GRPExtendTableView::reBuildTree()
{
    Q_D(GRPExtendTableView);

    d->m_drawInfo->init(false);
    d->viewport->update();
    d->m_horizontalHeader->update();
    d->m_verticalHeader->update();
}

void GRPExtendTableView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
    const QVector<int> &roles)
{
    Q_D(GRPExtendTableView);

    if (roles.contains(gidrRowExpandedRole))
    {
        if ((-1 == topLeft.row()) || (-1 == bottomRight.row()))
        {
            return;
        }

        for (int i = topLeft.row(); i <= bottomRight.row(); i++)
        {
            QModelIndex oIndex = model()->index(i, 0);
            QVariant varExpanded = model()->data(oIndex, gidrRowExpandedRole);

            if (qvariant_cast<bool>(varExpanded))
            {
                d->doExpand(i, true);
            }
            else
            {
                d->doCollapse(i, true);
            }
        }

        d->viewport->update();

        setState(NoState);
    }
    else
    {
        GlodonAbstractItemView::dataChanged(topLeft, bottomRight, roles);
    }
}
/********protected slots:*************************************************/

/********protected:*******************************************************/
GRPExtendTableView::GRPExtendTableView(GRPExtendTableViewPrivate &dd, QWidget *parent) :
GLDTableView(dd, parent)
{

}

void GRPExtendTableView::doSetIsTree(bool value)
{
    Q_D(GRPExtendTableView);

    //切换model时如果处于编辑状态， 强制退出
    if (d->m_oEditorIndex.isValid())
    {
        forceCloseEditor();
    }

    d->m_isTree = value;
    d->m_verticalHeader->setIsTree(value);
    d->m_horizontalHeader->setIsTree(value);

    if (value)
    {
        if (!d->m_drawInfo)
        {
            GlodonTreeDrawInfo *treeDrawInfo = new GlodonTreeDrawInfo(this);
            treeDrawInfo->setTreeColumn(d->m_treeColumn);
            setTreeDrawInfo(treeDrawInfo);
        }
    }
    else
    {
        d->m_drawInfo = NULL;
    }
}

void GRPExtendTableView::doSetModel(QAbstractItemModel *model)
{
    Q_D(GRPExtendTableView);

    if (d->m_isGroupMode)
    {
        if (!dynamic_cast<GlodonGroupModel *>(model))
        {
            GlodonGroupModel *cxModel;

            if (d->m_isTree)
            {
                GlodonTreeModel *treeModel = dynamic_cast<GlodonTreeModel *>(model);
                cxModel = new GlodonGroupModel(treeModel->model, this);
                d->m_dataModel = treeModel->model;
                treeModel->model = cxModel;
                d->m_drawInfo->setModel(cxModel);
                model = treeModel;
            }
            else
            {
                cxModel = new GlodonGroupModel(model, this);
                d->m_model = cxModel;
                doSetIsTree(true);
                GlodonTreeModel *treeModel = new GlodonTreeModel(cxModel, this);
                treeModel->drawInfo = d->m_drawInfo;
                d->m_dataModel = model;
                model = treeModel;
            }

            connect(dynamic_cast<GlodonGroupHeaderView *>(d->m_horizontalHeader), SIGNAL(groupChanged(QVector<int>)),
                cxModel, SLOT(groupChanged(QVector<int>)));
            connect(dynamic_cast<GlodonGroupHeaderView *>(d->m_horizontalHeader), SIGNAL(groupChanged(QVector<int>)),
                this, SLOT(groupChanged(QVector<int>)));
            connect(cxModel, SIGNAL(modelRebuild()), this, SLOT(reBuildTree()));

        }
    }
    else if (d->m_isTree)
    {
        if (d->m_drawInfo->model != model)
        {
            d->m_drawInfo->setModel(model);
        }

        d->m_dataModel = model;
        GlodonTreeModel *treeModel = new GlodonTreeModel(model, this);
        treeModel->drawInfo = d->m_drawInfo;
        model = treeModel;
    }

    if (model == d->m_model)
    {
        return;
    }

    //let's disconnect from the old model
    if (d->m_model && d->m_model != QAbstractItemModelPrivate::staticEmptyModel())
    {
        disconnect(d->m_model, SIGNAL(rowsInserted(QModelIndex, int, int)),
            this, SLOT(_q_updateSpanInsertedRows(QModelIndex, int, int)));
        disconnect(d->m_model, SIGNAL(columnsInserted(QModelIndex, int, int)),
            this, SLOT(_q_updateSpanInsertedColumns(QModelIndex, int, int)));
        disconnect(d->m_model, SIGNAL(rowsRemoved(QModelIndex, int, int)),
            this, SLOT(_q_updateSpanRemovedRows(QModelIndex, int, int)));
        disconnect(d->m_model, SIGNAL(columnsRemoved(QModelIndex, int, int)),
            this, SLOT(_q_updateSpanRemovedColumns(QModelIndex, int, int)));
        disconnect(d->m_verticalHeader, SIGNAL(scrolled(int)),
            this, SLOT(onScrolled(int)));
        disconnect(d->m_horizontalHeader, SIGNAL(scrolled(int)),
            this, SLOT(onScrolled(int)));
        disconnect(d->m_verticalHeader, &GlodonHeaderView::sectionResizing,
            this, &GRPExtendTableView::sectionResizing);
        disconnect(d->m_horizontalHeader, &GlodonHeaderView::sectionResizing,
            this, &GRPExtendTableView::sectionResizing);
    }

    if (model) //and connect to the new one
    {
        connect(model, SIGNAL(rowsInserted(QModelIndex, int, int)),
            this, SLOT(_q_updateSpanInsertedRows(QModelIndex, int, int)));
        connect(model, SIGNAL(columnsInserted(QModelIndex, int, int)),
            this, SLOT(_q_updateSpanInsertedColumns(QModelIndex, int, int)));
        connect(model, SIGNAL(rowsRemoved(QModelIndex, int, int)),
            this, SLOT(_q_updateSpanRemovedRows(QModelIndex, int, int)));
        connect(model, SIGNAL(columnsRemoved(QModelIndex, int, int)),
            this, SLOT(_q_updateSpanRemovedColumns(QModelIndex, int, int)));
        connect(d->m_verticalHeader, SIGNAL(scrolled(int)),
            this, SLOT(onScrolled(int)));
        connect(d->m_horizontalHeader, SIGNAL(scrolled(int)),
            this, SLOT(onScrolled(int)));
        connect(d->m_verticalHeader, &GlodonHeaderView::sectionResizing,
            this, &GRPExtendTableView::sectionResizing);
        connect(d->m_horizontalHeader, &GlodonHeaderView::sectionResizing,
            this, &GRPExtendTableView::sectionResizing);
    }

    d->m_verticalHeader->setModel(model);
    d->m_horizontalHeader->setModel(model);

    GTableCornerWidget *cornerWidget = dynamic_cast<GTableCornerWidget *>(d->m_cornerWidget);

    if (cornerWidget)
    {
        cornerWidget->setModel(model);
    }

    GlodonAbstractItemView *gView = dynamic_cast<GlodonAbstractItemView *>(d->m_cornerWidget);

    if (gView)
    {
        gView->setModel(model);
    }

    QAbstractItemView *qView = dynamic_cast<QAbstractItemView *>(d->m_cornerWidget);

    if (qView)
    {
        qView->setModel(model);
    }

    GlodonAbstractItemView::setModel(model);

    updateGeometries();
}

int GRPExtendTableView::treeCellDisplayHorizontalOffset(int row, int col, bool isOldMinTextHeightCalWay) const
{
    int nOffset = 0;

    if (isTree() && col == d_func()->m_treeColumn)
    {
        if (isOldMinTextHeightCalWay)
        {
            GlodonTreeModel *treeModel = dynamic_cast<GlodonTreeModel *>(model());
            nOffset = (treeModel->drawInfo->m_viewItems.at(row).treeLevel + 1) * c_Indent + 2 * c_HalfWidth;
        }
        else
        {
            const GTreeViewItem &viewItem = d_func()->m_drawInfo->m_viewItems[row];
            const int c_levelCenterOffset = CON_INDENT * viewItem.treeLevel + CON_HALF_DECORATION_WIDTH + 2;
            nOffset = qMin((c_levelCenterOffset + CON_HALF_DECORATION_WIDTH + 3),
                d_func()->m_horizontalHeader->sectionSize(col));
        }
    }

    return nOffset;
}
void GRPExtendTableView::onBoolCellPress(QMouseEvent *event)
{
    //    Q_D(GRPExtendTableView);

    QModelIndex currIndex = indexAt(event->pos());
    QRect rect = visualRect(currIndex);
    QRect boolRect(rect.center().rx() - 6,
        rect.center().ry() - 6,
        13, 13);

    //    if (d->m_isTree && currIndex.column() == d->m_treeColumn)
    //    {
    //        //如果是第一级且没有子的情况下，应与非树形结构时区域一致
    //        const GTreeViewItem &viewItem = d->m_drawInfo->m_viewItems.at(currIndex.row());

    //        if (!((viewItem.parentIndex == -1) && viewItem.hasChildren != 1))
    //        {
    //            QRect textRect(rect.left() + CON_INDENT * (viewItem.treeLevel + 1) + 2, rect.top(),
    //                           rect.width() - CON_INDENT * (viewItem.treeLevel + 1) - 2, rect.height());
    //            boolRect = QRect(textRect.center().rx() - 6, textRect.center().ry() - 6, 13, 13);
    //        }
    //    }

    if (boolRect.contains(event->pos()))
    {
        setBoolEditValue(currIndex);
    }
}

void GRPExtendTableView::onMousePress(QMouseEvent *event)
{
    Q_D(GRPExtendTableView);

    if (d->m_isTree)
    {

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))

        if (event->type() == QEvent::MouseButtonPress)
#else
        if (style()->styleHint(QStyle::SH_Q3ListViewExpand_SelectMouseType, 0, this) == QEvent::MouseButtonPress)
#endif
        {
            bool bhandled = d->expandOrCollapseItemAtPos(event->pos());

            if (bhandled)
            {
                return;
            }
        }

        QModelIndex currIndex = indexAt(event->pos());

        int nChildCount = -1;

        if (currIndex.isValid())
        {
            nChildCount = d->m_drawInfo->m_viewItems[currIndex.row()].hasChildren;
        }

        if (-1 != nChildCount && d->itemDecorationAt(event->pos()) != -1)
        {
            return;
        }
    }

    GLDTableView::onMousePress(event);
}

bool GRPExtendTableView::event(QEvent *event)
{
    GLDEvent *gldEvent = dynamic_cast<GLDEvent *>(event);

    if (gldEvent == NULL)
    {
        return GLDTableView::event(event);
    }

    bool result = GlodonAbstractItemView::event(event);

    switch (gldEvent->type())
    {
    case GM_EXPAND:
    {
        doGMExpand(gldEvent);
        break;
    }

    case GM_QUERYEXPAND:
    {
        doGMQueryExpand(gldEvent);
        break;
    }

    case GM_COLLAPSE:
    {
        doGMCollapse(gldEvent);
        break;
    }

    case GM_QUERYCOLLAPSE:
    {
        doGMQueryCollapse(gldEvent);
        break;
    }

    case GM_EXPANDALL:
    {
        doGMExpandAll(gldEvent);
        break;
    }

    case GM_QUERYEXPANDALL:
    {
        doGMQueryExpandAll(gldEvent);
        break;
    }

    case GM_COLLAPSEALL:
    {
        doGMCollapseAll(gldEvent);
        break;
    }

    case GM_QUERYCOLLAPSEALL:
    {
        doGMQueryCollapseAll(gldEvent);
        break;
    }

    default:
    {
        // nothing
        break;
    }
    }

    return result;
}

QAbstractItemModel *GRPExtendTableView::itemModel()
{
    Q_D(GRPExtendTableView);

    QAbstractItemModel *dm = GLDTableView::itemModel();

    if (d->m_isTree)
    {
        dm = dataModel();
    }

    return dm;
}
/********protected:*******************************************************/

/********private:*********************************************************/
void GRPExtendTableView::setChildSelection(const QModelIndex &topLeft, const QModelIndex &bottomRight,
    QItemSelection &selection, bool isRowSelect)
{
    Q_D(GRPExtendTableView);

    if (!isRowSelect)
    {
        d->m_oTopLeftSelectIndex = topLeft;
        d->m_oBottomRightSelectIndex = bottomRight;
        return;
    }

    if (!selection.isEmpty())
    {
        selection.clear();
    }

    QModelIndex tl;
    QModelIndex br;
    for (int row = topLeft.row(); row <= bottomRight.row(); ++row)
    {
        int nbottomRow = d->m_drawInfo->lastChildRow(row);
        tl = d->m_model->index(row, topLeft.column(), d->m_root);
        br = d->m_model->index(nbottomRow, bottomRight.column(), d->m_root);

        if (!selection.contains(tl) && !selection.contains(br))
        {
            selection.append(QItemSelectionRange(tl, br));
        }
    }

    d->m_oTopLeftSelectIndex = topLeft;
    d->m_oBottomRightSelectIndex = br;
}

void GRPExtendTableView::doGMExpand(GLDEvent *event)
{
    expand(currentIndex().row(), true);
    G_UNUSED(event);
}

void GRPExtendTableView::doGMQueryExpand(GLDEvent *event)
{
    Q_D(GRPExtendTableView);
    event->setResult(d->m_model->rowCount(currentIndex()) > 0);
    G_UNUSED(event);
}

void GRPExtendTableView::doGMCollapse(GLDEvent *event)
{
    collapse(currentIndex().row(), true);
    G_UNUSED(event);
}

void GRPExtendTableView::doGMQueryCollapse(GLDEvent *event)
{
    Q_D(GRPExtendTableView);
    event->setResult(d->m_model->rowCount(currentIndex()) > 0);
    G_UNUSED(event);
}

void GRPExtendTableView::doGMExpandAll(GLDEvent *event)
{
    expandAll();
    G_UNUSED(event);
}

void GRPExtendTableView::doGMQueryExpandAll(GLDEvent *event)
{
    event->setResult(isTree());
    G_UNUSED(event);
}

void GRPExtendTableView::doGMCollapseAll(GLDEvent *event)
{
    collapseAll();
    G_UNUSED(event);
}

void GRPExtendTableView::doGMQueryCollapseAll(GLDEvent *event)
{
    event->setResult(isTree());
    G_UNUSED(event);
}
/********private:*********************************************************/
