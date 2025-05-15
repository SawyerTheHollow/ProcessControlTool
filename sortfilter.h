#ifndef SORTFILTER_H
#define SORTFILTER_H

#include <QSortFilterProxyModel>
#include <QRegularExpression>

class SortFilter : public QSortFilterProxyModel {
    Q_OBJECT

public:
    explicit SortFilter(QObject *parent = nullptr) : QSortFilterProxyModel(parent) {}

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

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override
    {
        QVariant leftData = sourceModel()->data(left);
        QVariant rightData = sourceModel()->data(right);

        bool leftOk, rightOk;
        double leftNum = leftData.toDouble(&leftOk);
        double rightNum = rightData.toDouble(&rightOk);

        if (leftOk && rightOk)
        {
            return leftNum < rightNum;
        }

        QString leftStr = leftData.toString();
        QString rightStr = rightData.toString();
        return QString::localeAwareCompare(leftStr, rightStr) < 0;
    }
};

#endif // SORTFILTER_H
