#ifndef FILTER_H
#define FILTER_H

#include <QSortFilterProxyModel>
#include <QRegularExpression>

class Filter : public QSortFilterProxyModel {
    Q_OBJECT

public:
    explicit Filter(QObject *parent = nullptr) : QSortFilterProxyModel(parent) {}

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override {
        int columnCount = sourceModel()->columnCount();

        for (int column = 0; column < columnCount; ++column) {
            QModelIndex index = sourceModel()->index(sourceRow, column, sourceParent);
            if (index.isValid()) {
                QString data = index.data().toString();
                if (data.contains(filterRegularExpression())) {
                    return true;
                }
            }
        }
        return false;
    }
};

#endif // FILTER_H
