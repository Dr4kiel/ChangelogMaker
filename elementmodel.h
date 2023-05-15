#ifndef ELEMENTMODEL_H
#define ELEMENTMODEL_H

#include <QStringListModel>

class ElementModel : public QStringListModel
{
public:
    ElementModel(QObject *parent = nullptr);
    bool setData(const QModelIndex &index, const QVariant &value, int role);
};

#endif // ELEMENTMODEL_H
