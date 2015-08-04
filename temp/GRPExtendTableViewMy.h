#ifndef GRPEXTENDTABLEVIEW_H
#define GRPEXTENDTABLEVIEW_H

#include "GLDTableView.h"
#include "GLDTableView_p.h"
#include "GRPTableView.h"
#include "GRPExtendGridDataSource.h"

class GRPExtendTableViewPrivate;
class GRPExtendTableView;

class GRPExtendTableView : public GRPBaseTableView
{
    Q_OBJECT
public:
    GRPExtendTableView(QWidget *parent);
    ~GRPExtendTableView();
    void setModel(QAbstractItemModel *model);
    void setExtendMatrix(CGRPExtendMatrix *extendMatrix);

public Q_SLOTS:
    void refresh();
    void queryIndexDataType(const QModelIndex &index, GlodonDefaultItemDelegate::GDataType &dataType);
private:
    void initTable();
    void mouseMoveEvent(QMouseEvent *event);
private:
    QAbstractItemModel *m_model;
    Q_DECLARE_PRIVATE(GRPExtendTableView)
    Q_DISABLE_COPY(GRPExtendTableView)
};

class GRPExtendTableViewImpl : public GNoRefInterfaceObject, public IGRPExtendView
{
public:
    GRPExtendTableViewImpl(PtrUInt parent);
    virtual ~GRPExtendTableViewImpl();
public:
    DECLARE_IUNKNOWN
    /*IGRPPreview*/
    void GRPMETHODCALLTYPE setExtendMatrix(IGRPExtendMatrix *extendMatrix);
    PtrUInt GRPMETHODCALLTYPE toWidget();
    void GRPMETHODCALLTYPE setFixedRowCount(int fixedRowCount);
    void GRPMETHODCALLTYPE setFixedColCount(int fixedColCount);
protected:
    HRESULT GRPMETHODCALLTYPE _QueryInterface(REFIID riid, void **ppvObject);
private:
    GRPExtendTableView *m_control;
};

class GRPExtendTableViewPrivate : public GRPBaseTableViewPrivate
{
    Q_DECLARE_PUBLIC(GRPExtendTableView)
public:
    GRPExtendTableViewPrivate();
public:
    GRPExtendGridDataSource *m_dataSource;
private:
    bool hasParent(int row);
    bool hasChildren(int row);
    bool hasBrother(int row, int col = 1);
    bool expanded(int row);
    int findParent(int row);
    int level(int row);
    bool expandOrCollapseItemAtPos(const QPoint &pos);
};

#endif // GRPEXTENDTABLEVIEW_H
