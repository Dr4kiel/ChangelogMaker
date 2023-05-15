#include "elementmodel.h"

ElementModel::ElementModel(QObject *parent) {}

bool ElementModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole && value.toString().isEmpty()) {
        QStringListModel::removeRow(index.row(), index.parent());
        return true;
    }
    return QStringListModel::setData(index, value, role);
}
