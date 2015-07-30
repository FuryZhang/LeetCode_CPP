#include "GRPExtendTableView.h"
#include "GRPDataSourceModel.h"

GRPExtendTableView::GRPExtendTableView(QWidget *parent) : GRPBaseTableView(*new GRPExtendTableViewPrivate(), parent)
{
    setIsTree(true);

    this->setFrameStyle(QFrame::Plain);

    setIsMutiSelect(true);  // 支持多选

    horizontalHeader()->hide();
    verticalHeader()->show();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setIsCustomStyle(true);
    setGridLineColor(Qt::black);
//    initTable();
    m_model = NULL;
    GRPDefaultItemDelegate *defaultItemDelegate = new GRPDefaultItemDelegate(this);
    setItemDelegate(defaultItemDelegate);

    defaultItemDelegate->setIsTextEllipse(true);
    setAllowToResize(true);

    connect(defaultItemDelegate, SIGNAL(onQueryIndexDataType(QModelIndex, GlodonDefaultItemDelegate::GDataType &)),
            this, SLOT(queryIndexDataType(QModelIndex, GlodonDefaultItemDelegate::GDataType &)));
}

GRPExtendTableView::~GRPExtendTableView()
{
    m_model = NULL;
}

void GRPExtendTableView::refresh()
{
    Q_D(GRPExtendTableView);
    for (int i = 0; i < m_model->rowCount(); ++i)
    {
        setRowHeight(i, m_model->data(m_model->index(i, 0), gidrRowHeightRole).toInt());
        for (int j = 0; j < m_model->columnCount(); ++j)
        {
            if (d->m_dataSource->matrix()->colVisibles(j))
            {
                setColumnWidth(j, m_model->data(m_model->index(0, j), gidrColWidthRole).toInt());
            }
            else
            {
                setColumnWidth(j, 0);
            }
        }
    }
    if (dynamic_cast<GRPDataSourceModel *>(m_model) != NULL)
        d->m_dataSource = dynamic_cast<GRPExtendGridDataSource *>(((GRPDataSourceModel *)m_model)->dataSource());
}

void GRPExtendTableView::queryIndexDataType(const QModelIndex &index, GlodonDefaultItemDelegate::GDataType &dataType)
{
    Q_D(GRPExtendTableView);
    if (d->m_dataSource->handleSymbol(index.row(), index.column()))
    {
        dataType = GlodonDefaultItemDelegate::GDiaSymbol;
    }
}

void GRPExtendTableView::initTable()
{
    GRPDefaultItemDelegate *defaultItemDelegate = new GRPDefaultItemDelegate(this);
    defaultItemDelegate->setIsTextEllipse(true);
    setItemDelegate(defaultItemDelegate);
    setAllowToResize(true);
}

void GRPExtendTableView::mouseMoveEvent(QMouseEvent *event)
{
    GRect rect = GRect(verticalHeader()->width() - 2, verticalHeader()->y(),
                       verticalHeader()->width() + 2, verticalHeader()->height());
    QPoint point(event->x() + verticalHeader()->width(), event->y());

    if (event->button() == Qt::NoButton && rect.contains(point))
    {
        setCursor(Qt::ArrowCursor);
        setResizeDelay(false);
        setAllowToResize(false);
    }
    else
    {
        setAllowToResize(true);
        GlodonTableView::mouseMoveEvent(event);
    }
}

void GRPExtendTableView::setModel(QAbstractItemModel *model)
{
    GRPBaseTableView::setModel(model);
    if (m_model)
        disconnect(m_model, SIGNAL(modelReset()), this, SLOT(refresh()));
    m_model = model;
    connect(m_model, SIGNAL(modelReset()), this, SLOT(refresh()));
    refresh();
}

void GRPExtendTableView::setExtendMatrix(CGRPExtendMatrix *extendMatrix)
{
    Q_D(GRPExtendTableView);

    bool bNewModel = false;
    if (m_model == NULL)
    {
        m_model = new GRPDataSourceModel(this);
        bNewModel = true;
    }
    if (dynamic_cast<GRPDataSourceModel *>(m_model) != NULL)
    {
        GRPExtendGridDataSource *dataSource =  dynamic_cast<GRPExtendGridDataSource *>(((GRPDataSourceModel *)m_model)->dataSource());

        if (dataSource == NULL)
        {
            dataSource = new GRPExtendGridDataSource();
            ((GRPDataSourceModel *)m_model)->setDataSource(dataSource);
            d->m_dataSource = dataSource;
        }
        dataSource->setMatrix(extendMatrix);
    }
    if (bNewModel)
    {
        setModel(m_model);
    }
    else
    {
        refresh();
    }
}

GRPExtendTableViewPrivate::GRPExtendTableViewPrivate() : GRPBaseTableViewPrivate(), m_dataSource(NULL)
{
    //报表第0列是隐藏列，需要将树型结构画在第1列上面
    m_treeColumn = 1;
}

bool GRPExtendTableViewPrivate::hasParent(int row)
{
    if (m_dataSource)
    {
        if (m_dataSource->matrix()->rowLevels(m_dataSource->dataIndex(row)) > 0)
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}

bool GRPExtendTableViewPrivate::hasChildren(int row)
{
    if (m_dataSource)
    {
        CGRPExtendMatrix *matrix = m_dataSource->matrix();
        int nRow = m_dataSource->dataIndex(row);
        if (row < m_dataSource->rowCount() - 1)
        {
            return matrix->rowLevels(nRow) + 1 == matrix->rowLevels(nRow + 1);
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool GRPExtendTableViewPrivate::hasBrother(int row, int col)
{
    bool result = false;
    if (!m_isTree || (m_dataSource == NULL))
        return false;
    CGRPExtendMatrix *matrix = m_dataSource->matrix();
    int nRowCount = m_dataSource->rowCount();
    int nLevel = matrix->rowLevels(m_dataSource->dataIndex(row));
    if ((nLevel > 0) && (row < nRowCount - 1))
    {
        for (int i = row + 1; i < nRowCount; ++i)
        {
            int nReplaceI = m_dataSource->dataIndex(i);
            if (m_dataSource->mergeId(row, col) == m_dataSource->mergeId(i, col))
                continue;
            int nRowLevel = matrix->rowLevels(nReplaceI);
            if ((nRowLevel == -1) || (nRowLevel <= nLevel - 1))
                break;
            if ((matrix->rowHeights(nReplaceI) != 0) && (nRowLevel == nLevel))
            {
                return true;
            }
        }
    }
    return result;
}

bool GRPExtendTableViewPrivate::expanded(int row)
{
    if (NULL == m_dataSource)
    {
        return false;
    }
    else
    {
        return m_dataSource->matrix()->rowExpanded(m_dataSource->dataIndex(row));
    }
}

int GRPExtendTableViewPrivate::findParent(int row)
{
    if ((row < 0) || (!m_isTree))
    {
        return -1;
    }
    CGRPExtendMatrix *matrix = m_dataSource->matrix();
    int nRow = m_dataSource->dataIndex(row);
    int nCurLevel = matrix->rowLevels(nRow);
    int nNewLevel = nCurLevel;
    while ((nNewLevel > 0) && (row > matrix->fixedRows()))
    {
        row--;
        nNewLevel = matrix->rowLevels(m_dataSource->dataIndex(row));
        if (nNewLevel == nCurLevel - 1)
        {
            return row;
        }
    }
    return -1;
}

int GRPExtendTableViewPrivate::level(int row)
{
    if ((m_dataSource == NULL) || !m_isTree)
        return -1;
    return m_dataSource->matrix()->rowLevels(m_dataSource->dataIndex(row));
}

bool GRPExtendTableViewPrivate::expandOrCollapseItemAtPos(const QPoint &pos)
{
    Q_Q(GRPExtendTableView);

    // we want to handle mousePress in EditingState (persistent editors)
    if ((m_state != GlodonAbstractItemView::NoState
            && m_state != GlodonAbstractItemView::EditingState)
            || !viewport->rect().contains(pos))
    {
        return true;
    }

    int nItem = itemDecorationAt(pos);
    if (nItem == -1)
        return false;
    int nDataIndex = m_dataSource->dataIndex(nItem);
    if ((nItem != -1) && 0 != hasChildren(nItem))
    {
        if (m_dataSource->matrix()->rowExpanded(nDataIndex))
        {
            collapse(nItem, true);
            m_dataSource->matrix()->setRowExpanded(nDataIndex, false);
        }
        else
        {
            expand(nItem, true);
            m_dataSource->matrix()->setRowExpanded(nDataIndex, true);
        }

        if (!isAnimating())
        {
            q->updateGeometries();
            viewport->update();
        }

        return true;
    }

    return false;
}

GRPExtendTableViewImpl::GRPExtendTableViewImpl(PtrUInt parent)
{
    m_control = new GRPExtendTableView((QWidget *)parent);
}

GRPExtendTableViewImpl::~GRPExtendTableViewImpl()
{
    //todo
}

void GRPExtendTableViewImpl::setExtendMatrix(IGRPExtendMatrix *extendMatrix)
{
    m_control->setExtendMatrix(dynamic_cast<CGRPExtendMatrix *>(extendMatrix));
}

PtrUInt GRPExtendTableViewImpl::toWidget()
{
    return (PtrUInt)m_control;
}

void GRPExtendTableViewImpl::setFixedRowCount(int fixedRowCount)
{
    m_control->setFixedRowCount(fixedRowCount);
}

void GRPExtendTableViewImpl::setFixedColCount(int fixedColCount)
{
    m_control->setFixedColCount(fixedColCount);
}

HRESULT GRPExtendTableViewImpl::_QueryInterface(const IID &riid, void **ppvObject)
{
    if (riid == __uuidof(IGRPExtendView))
    {
        this->AddRef();
        *ppvObject = static_cast<IGRPExtendView *>(this);
        return NOERROR;
    }
    else
    {
        return GNoRefInterfaceObject::QueryInterface(riid, ppvObject);
    }
}
