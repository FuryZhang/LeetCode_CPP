#ifndef GRPEXTENDTABLEVIEW_H
#define GRPEXTENDTABLEVIEW_H

#include "GLDTableView.h"
#include "GLDTableView_p.h"
#include "GRPTableView.h"
#include "GRPExtendGridDataSource.h"

class GRPExtendTableViewPrivate;
class GRPExtendTableView;

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
    void setRollOut(GIntList *rollOut);
    GIntList *rollOut();

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
    explicit GlodonTableView(GlodonTableViewPrivate &dd, QWidget *parent = 0);

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

public:
    explicit GRPExtendTableView(QWidget *parent);
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
