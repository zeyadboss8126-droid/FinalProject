#include "ModelPartList.h"
#include "ModelPart.h"

ModelPartList::ModelPartList(const QString& data, QObject* parent)
    : QAbstractItemModel(parent)
{
    Q_UNUSED(data);

    rootItem = new ModelPart({ tr("Part"), tr("Visible?"), tr("Colour (R,G,B)") });
}

ModelPartList::~ModelPartList()
{
    delete rootItem;
}

int ModelPartList::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return rootItem->columnCount();
}

QVariant ModelPartList::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    ModelPart* item = static_cast<ModelPart*>(index.internalPointer());
    if (!item)
        return QVariant();

    // Display text
    if (role == Qt::DisplayRole)
    {
        return item->data(index.column());
    }

    // Checkbox for Visible column
    if (index.column() == 1 && role == Qt::CheckStateRole)
    {
        return item->visible() ? Qt::Checked : Qt::Unchecked;
    }

    return QVariant();
}

Qt::ItemFlags ModelPartList::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    if (index.column() == 1)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

bool ModelPartList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    ModelPart* item = static_cast<ModelPart*>(index.internalPointer());
    if (!item)
        return false;

    if (index.column() == 1 && role == Qt::CheckStateRole)
    {
        bool visible = (value.toInt() == Qt::Checked);
        item->setVisible(visible);

        emit dataChanged(index, index);
        return true;
    }

    return false;
}

QVariant ModelPartList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex ModelPartList::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    ModelPart* parentItem = nullptr;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ModelPart*>(parent.internalPointer());

    if (!parentItem)
        return QModelIndex();

    ModelPart* childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);

    return QModelIndex();
}

QModelIndex ModelPartList::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    ModelPart* childItem = static_cast<ModelPart*>(index.internalPointer());
    if (!childItem)
        return QModelIndex();

    ModelPart* parentItem = childItem->parentItem();

    if (!parentItem || parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int ModelPartList::rowCount(const QModelIndex& parent) const
{
    if (parent.column() > 0)
        return 0;

    ModelPart* parentItem = nullptr;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ModelPart*>(parent.internalPointer());

    if (!parentItem)
        return 0;

    return parentItem->childCount();
}

ModelPart* ModelPartList::getRootItem()
{
    return rootItem;
}

QModelIndex ModelPartList::appendChild(QModelIndex& parent, const QList<QVariant>& data)
{
    ModelPart* parentPart = nullptr;

    if (parent.isValid())
        parentPart = static_cast<ModelPart*>(parent.internalPointer());
    else {
        parentPart = rootItem;
        parent = createIndex(0, 0, rootItem);
    }

    if (!parentPart)
        return QModelIndex();

    int newRow = parentPart->childCount();

    beginInsertRows(parent, newRow, newRow);

    ModelPart* childPart = new ModelPart(data, parentPart);
    parentPart->appendChild(childPart);

    endInsertRows();

    return createIndex(newRow, 0, childPart);
}
