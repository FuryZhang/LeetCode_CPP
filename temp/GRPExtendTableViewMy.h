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
    *����һ��
    *@param[in]  row  �߼��к�
    *@return ��
    */
    virtual void hideRow(int row);
    void groupChanged(QVector<int> newGroup);

public:
    explicit GRPExtendTableView(QWidget *parent);

public:
    /*!
    *����ģʽ�£�չ��ĳһ�У���ָ���Ƿ����ź�
    *@param[in]  row         �߼��к�
    *@param[in]  emitSignal  �Ƿ����ź�
    *@return ��
    */
    void expand(int row, bool emitSignal);

    /*!
    *����ģʽ�£��۵�ĳһ�У���ָ���Ƿ����ź�
    *@param[in]  row         �߼��к�
    *@param[in]  emitSignal  �Ƿ����ź�
    *@return ��
    */
    void collapse(int row, bool emitSignal);

    /*!
    *����ģʽ�£��ж�ĳһ���Ƿ�չ��
    *@param[in]  row  �߼��к�
    *@return bool
    */
    bool isRowExpanded(int row);

    /*!
    *����ģʽ�£�չ��ȫ���ڵ�
    *@return ��
    */
    void expandAll();

    /*!
    *����ģʽ�£��۵�ȫ���ڵ�
    *@return ��
    */
    void collapseAll();

    /*!
    *���ø��ڵ㣬ͨ������QModelIndex()
    *@param[in]  index  һ��ΪQModelIndex()
    *@return ��
    *@see �μ�GlodonAbstractItemView::setRootIndex(const QModelIndex &index)
    */
    void setRootIndex(const QModelIndex &index);

    /*!
    *��ȡ���Ӷ�Ӧ��treeModel�е�index
    *@return ��
    */
    virtual QModelIndex treeIndex(const QModelIndex &index) const;

    /*!
    *��ȡ���Ӷ�Ӧ��dataModel�е�index
    *@return ��
    */
    virtual QModelIndex dataIndex(const QModelIndex &index) const;

    /*!
    *������ʾ����£���ȡ��ǰ���Ӷ�Ӧ��dataModel�е�index
    *@return ��
    */
    QModelIndex currentDataIndex() const;

    /**
    * @brief �����Ƿ����νṹ��ʾ
    *        ��setModel��ʹ��
    *        ���ø÷������ᵼ��֮ǰ���õ��и߲�������
    *        �����ȵ��ø÷������������и�
    * @param value
    */
    void setIsTree(bool value);
    bool isTree() const;

    /**
    * @brief �����Ƿ����ģʽ��ʾ
    * @param value
    */
    void setIsGroupMode(bool groupModeEnable);

    bool isGroupMode() const;

    /**
    * @brief ����������ʾ�£�չ��/�۵�ͼ�����ʽ
    * @param style
    */
    void setTreeDecorationStyle(TreeDecorationStyle style);
    TreeDecorationStyle treeDecorationStyle() const;

    void setTreeDrawInfo(GlodonTreeDrawInfo *tableViewDrawInfo);
    GlodonTreeDrawInfo *treeDrawInfo();

    /**
    * @brief ���þ�չ��
    * @param rollOut
    */
    /*void setRollOut(GIntList *rollOut);
    GIntList *rollOut();*/

    /**
    * @brief �����νṹʱ��ѡ���۵��ĸ����Ƿ�ͬʱѡ����
    * @return
    */
    bool isAddChildToSelection();
    void setAddChildToSelection(bool value);

    /**
    * @brief �������νṹ���ڵ��к�
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
    * \return Ϊ����ʾ���εĸ��ӵ������������е�ˮƽ�����ƫ��(��Ҫ�����ɵ�ϸ�ߺ�branchͼ��ռȥ�Ŀ��)
    */
    int treeCellDisplayHorizontalOffset(int row, int col, bool isOldMinTextHeightCalWay = true) const;

    virtual void onBoolCellPress(QMouseEvent *event);
    virtual void onMousePress(QMouseEvent *event);
    virtual bool event(QEvent *event);

    virtual QAbstractItemModel* itemModel();

private:
    /**
    * @brief �����ǰ�ڵ�Ϊ�۵�״̬����ô��ѡ����ʱ���������е��Ӷ����ӵ�selection��
    * @param topLeft
    * @param bottomLeft
    * @param selection ��ǰ��Ҫ��ӵ�selectionModel�е�selection
    * @param isRowSelect �������ѡ״̬������Ҫ�жϸ����Ƿ����۵�
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
    bool m_addChildInSelection;     //���νṹʱ���Ƿ��ѡ�����۵����Ӽ��뵽selection��
    int m_treeColumn;               //��ʾ���νṹ����

    CGRPExtendMatrix *m_drawInfo;
    TreeDecorationStyle m_treeDecorationStyle;

};

#endif // GRPEXTENDTABLEVIEW_H
