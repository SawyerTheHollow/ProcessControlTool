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
        // Получаем количество колонок в исходной модели
        int columnCount = sourceModel()->columnCount();

        // Проверяем каждую колонку на соответствие фильтру
        for (int column = 0; column < columnCount; ++column) {
            QModelIndex index = sourceModel()->index(sourceRow, column, sourceParent);
            if (index.isValid()) {
                QString data = index.data().toString();
                if (data.contains(filterRegularExpression())) {
                    return true; // Если хотя бы одна колонка соответствует, возвращаем true
                }
            }
        }
        return false; // Если ни одна колонка не соответствует, возвращаем false
    }
};

#endif // FILTER_H
