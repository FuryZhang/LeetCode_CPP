#ifndef GRPEXTENDTABLEVIEW_H
#define GRPEXTENDTABLEVIEW_H

#include "GLDTableView.h"
#include "GLDTableView_p.h"
#include "GRPTableView.h"
#include "GRPExtendGridDataSource.h"

class GRPExtendTableViewPrivate;
class GRPExtendTableView;
class CGRPExtendMatrix;

class GRPExtendTableView : public GLDTableView
{
    Q_OBJECT

public slots:
    /*!
    *隐藏一行
    *@param[in]  row  逻辑行号
    *@return 无
    */
    virtual void hideRow(int row);
    void groupChanged(QVector<int> newGroup);

public:
    explicit GRPExtendTableView(QWidget *parent);

public:
    /*!
    *树形模式下，展开某一行，可指定是否发送信号
    *@param[in]  row         逻辑行号
    *@param[in]  emitSignal  是否发送信号
    *@return 无
    */
    void expand(int row, bool emitSignal);

    /*!
    *树形模式下，折叠某一行，可指定是否发送信号
    *@param[in]  row         逻辑行号
    *@param[in]  emitSignal  是否发送信号
    *@return 无
    */
    void collapse(int row, bool emitSignal);

    /*!
    *树形模式下，判断某一行是否展开
    *@param[in]  row  逻辑行号
    *@return bool
    */
    bool isRowExpanded(int row);

    /*!
    *树形模式下，展开全部节点
    *@return 无
    */
    void expandAll();

    /*!
    *树形模式下，折叠全部节点
    *@return 无
    */
    void collapseAll();

    /*!
    *设置根节点，通常都是QModelIndex()
    *@param[in]  index  一般为QModelIndex()
    *@return 无
    *@see 参见GlodonAbstractItemView::setRootIndex(const QModelIndex &index)
    */
    void setRootIndex(const QModelIndex &index);

    /*!
    *获取格子对应的treeModel中的index
    *@return 无
    */
    virtual QModelIndex treeIndex(const QModelIndex &index) const;

    /*!
    *获取格子对应的dataModel中的index
    *@return 无
    */
    virtual QModelIndex dataIndex(const QModelIndex &index) const;

    /*!
    *树形显示情况下，获取当前格子对应的dataModel中的index
    *@return 无
    */
    QModelIndex currentDataIndex() const;

    /**
    * @brief 设置是否树形结构显示
    *        在setModel后使用
    *        调用该方法，会导致之前设置的行高不起作用
    *        建议先调用该方法，再设置行高
    * @param value
    */
    void setIsTree(bool value);
    bool isTree() const;

    /**
    * @brief 设置是否分组模式显示
    * @param value
    */
    void setIsGroupMode(bool groupModeEnable);

    bool isGroupMode() const;

    /**
    * @brief 设置树形显示下，展开/折叠图标的样式
    * @param style
    */
    void setTreeDecorationStyle(TreeDecorationStyle style);
    TreeDecorationStyle treeDecorationStyle() const;

    void setTreeDrawInfo(GlodonTreeDrawInfo *tableViewDrawInfo);
    GlodonTreeDrawInfo *treeDrawInfo();

    /**
    * @brief 设置卷展栏
    * @param rollOut
    */
    /*void setRollOut(GIntList *rollOut);
    GIntList *rollOut();*/

    /**
    * @brief 在树形结构时，选择折叠的父，是否同时选择子
    * @return
    */
    bool isAddChildToSelection();
    void setAddChildToSelection(bool value);

    /**
    * @brief 设置树形结构所在的列号
    * @param column
    */
    void setTreeColumn(int column);
    int treeColumn();

    protected slots:
    void reBuildTree();

    virtual void dataChanged(const QModelIndex &topLeft,
        const QModelIndex &bottomRight,
        const QVector<int> &roles);

protected:
    explicit GRPExtendTableView(GRPExtendTableViewPrivate &dd, QWidget *parent = 0);

    void doSetIsTree(bool value);
    virtual void doSetModel(QAbstractItemModel *model);

    /*!
    * \brief cellShowTreeWidthOffset
    * \return 为了显示树形的格子的文字区将进行的水平方向的偏移(主要是树干的细线和branch图标占去的宽度)
    */
    int treeCellDisplayHorizontalOffset(int row, int col, bool isOldMinTextHeightCalWay = true) const;

    virtual void onBoolCellPress(QMouseEvent *event);
    virtual void onMousePress(QMouseEvent *event);
    virtual bool event(QEvent *event);

    virtual QAbstractItemModel* itemModel();

private:
    /**
    * @brief 如果当前节点为折叠状态，那么当选择它时，把它所有的子都增加到selection中
    * @param topLeft
    * @param bottomLeft
    * @param selection 当前需要添加到selectionModel中的selection
    * @param isRowSelect 如果是行选状态，则不需要判断该行是否处于折叠
    */
    void setChildSelection(const QModelIndex &topLeft, const QModelIndex &bottomRight,
        QItemSelection &selection, bool isRowSelect);

    void doGMExpand(GLDEvent *event);

    void doGMQueryExpand(GLDEvent *event);

    void doGMCollapse(GLDEvent *event);

    void doGMQueryCollapse(GLDEvent *event);

    void doGMExpandAll(GLDEvent *event);

    void doGMQueryExpandAll(GLDEvent *event);

    void doGMCollapseAll(GLDEvent *event);

    void doGMQueryCollapseAll(GLDEvent *event);

//     void setModel(QAbstractItemModel *model);
//     void setExtendMatrix(CGRPExtendMatrix *extendMatrix);
// 
// public Q_SLOTS:
//     void refresh();
//     void queryIndexDataType(const QModelIndex &index, GlodonDefaultItemDelegate::GDataType &dataType);
private:
//     void initTable();
//     void mouseMoveEvent(QMouseEvent *event);
private:
//     QAbstractItemModel *m_model;
    Q_DECLARE_PRIVATE(GRPExtendTableView)
    Q_DISABLE_COPY(GRPExtendTableView)
};

/*
class GRPExtendTableViewImpl : public GNoRefInterfaceObject, public IGRPExtendView
{
public:
    GRPExtendTableViewImpl(PtrUInt parent);
    virtual ~GRPExtendTableViewImpl();
public:
    DECLARE_IUNKNOWN
    / *IGRPPreview* /
    void GRPMETHODCALLTYPE setExtendMatrix(IGRPExtendMatrix *extendMatrix);
    PtrUInt GRPMETHODCALLTYPE toWidget();
    void GRPMETHODCALLTYPE setFixedRowCount(int fixedRowCount);
    void GRPMETHODCALLTYPE setFixedColCount(int fixedColCount);
protected:
    HRESULT GRPMETHODCALLTYPE _QueryInterface(REFIID riid, void **ppvObject);
private:
    GRPExtendTableView *m_control;
};
*/



struct GTreeViewItem;

#define CON_INDENT 10
#define CON_HALF_DECORATION_WIDTH 6

const int c_nTreeDecorationLeftMargin = 2;
const int c_nTreeDecorationRightMargin = 3;
const int c_rightSelectedDashLineWidth = 1;

class GRPExtendTableViewPrivate : public GLDTableViewPrivate
{
    Q_DECLARE_PUBLIC(GRPExtendTableView)
public:
    GRPExtendTableViewPrivate() :
        m_isTree(false),
        m_isGroupMode(false),
        m_addChildInSelection(true),
        m_treeColumn(0),
        m_drawInfo(NULL),
        m_treeDecorationStyle(NormalStyle) { }

    virtual bool drawTree(QPainter *painter, QStyleOptionViewItem &option, const QModelIndex &index);

    virtual bool expandOrCollapseItemAtPos(const QPoint &pos);

    int itemDecorationAt(const QPoint &pos);

    QRect itemDecorationRect(int row);

    void expand(int item, bool emitSignal);

    void collapse(int item, bool emitSignal);

    void doExpand(int item, bool emitSignal);

    void doCollapse(int item, bool emitSignal);

    void drawOSStyle(QPainter *painter, QStyleOptionViewItem &option, const QModelIndex &index, const GTreeViewItem &viewItem);
    void drawBranch(QPainter *painter, const QRect &rect, const QModelIndex &index, const GTreeViewItem &viewItem);

    void drawNormalStyle(
        QPainter *painter, QStyleOptionViewItem &option, const QModelIndex &index,
        const GTreeViewItem &viewItem);
    void drawNormalStyleTreeDecoration(
        QPainter *painter, const QRect &rect, bool expanded, const QStyleOptionViewItem &option);
    void drawNormalStyleLines(
        const GTreeViewItem &viewItem, int ngridWidth, QPoint levelCenter,
        const QModelIndex &index, QRect rect, QPainter *painter);

    QPen normalStylePen(QStyleOptionViewItem &option);
    QRect beforeTextRect(const QRect &cellRect, int indentation);

    inline QRect afterDecorationRect(const QPoint &decorationCenter, const QRect &cellRect, const QRect &beforeTextRect)
    {
        return QRect(decorationCenter.x() + CON_HALF_DECORATION_WIDTH + 2, cellRect.top(),
            cellRect.width() - beforeTextRect.width() + 1, cellRect.height());
    }

    inline QPoint decorationCenter(const QRect &cellRect, int indentation)
    {
        return QPoint(cellRect.left() + indentation + CON_HALF_DECORATION_WIDTH + c_nTreeDecorationLeftMargin,
            (cellRect.top() + cellRect.bottom()) / 2);
    }

    inline QRect decorationRect(const QPoint &decorationRect)
    {
        return QRect(decorationRect.x() - CON_HALF_DECORATION_WIDTH,
            decorationRect.y() - CON_HALF_DECORATION_WIDTH,
            2 * CON_HALF_DECORATION_WIDTH + 1,
            2 * CON_HALF_DECORATION_WIDTH + 1);
    }

protected:
    virtual void itemDelegatePaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index);
    virtual void doSelect(const QModelIndex& tl, const QModelIndex& br, QItemSelectionModel::SelectionFlags command, bool isRowSelect);

public:
    bool m_isTree;
    bool m_isGroupMode;
    bool m_addChildInSelection;     //树形结构时，是否把选中且折叠的子加入到selection中
    int m_treeColumn;               //显示树形结构的列

    CGRPExtendMatrix *m_drawInfo;
    TreeDecorationStyle m_treeDecorationStyle;

};

#endif // GRPEXTENDTABLEVIEW_H
