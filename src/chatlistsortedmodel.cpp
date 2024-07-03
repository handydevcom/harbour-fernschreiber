/*
    Copyright (C) 2020 Sebastian J. Wolf and other contributors

    This file is part of Fernschreiber.

    Fernschreiber is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Fernschreiber is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Fernschreiber. If not, see <http://www.gnu.org/licenses/>.
*/

#include "chatlistsortedmodel.h"
#include "chatlistmodel.h"

#define DEBUG_MODULE ChatListSortingModel
#include "debuglog.h"

ChatListSortedModel::ChatListSortedModel(QObject *parent) : QSortFilterProxyModel(parent)
{

}

void ChatListSortedModel::setSource(QObject *model)
{
    setSourceModel(qobject_cast<QAbstractItemModel*>(model));
}

void ChatListSortedModel::setSourceModel(QAbstractItemModel *model)
{
    if (sourceModel() != model) {
        LOG(model);
        QSortFilterProxyModel::setSourceModel(model);
        emit sourceChanged();
        sort(0, Qt::DescendingOrder);
    }
}

bool ChatListSortedModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const {
    QMap<int, QVariant> l = sourceModel()->itemData(source_left);
    QMap<int, QVariant> r = sourceModel()->itemData(source_right);
    return l[ChatListModel::RoleLastMessageDate] < r[ChatListModel::RoleLastMessageDate];
}

