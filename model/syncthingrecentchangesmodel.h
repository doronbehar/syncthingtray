#ifndef DATA_SYNCTHINGRECENTCHANGESMODEL_H
#define DATA_SYNCTHINGRECENTCHANGESMODEL_H

#include "./syncthingmodel.h"

#include "../connector/syncthingdir.h"

#include <vector>

namespace Data {

struct LIB_SYNCTHING_MODEL_EXPORT SyncthingRecentChange {
    QString directoryId;
    QString directoryName;
    SyncthingFileChange fileChange;
};

class LIB_SYNCTHING_MODEL_EXPORT SyncthingRecentChangesModel : public SyncthingModel {
    Q_OBJECT
public:
    enum SyncthingRecentChangesModelRole {
        Action = Qt::UserRole + 1,
        ActionIcon,
        ModifiedBy,
        DirectoryId,
        DirectoryName,
        Path,
        EventTime,
        ExtendedAction,
        ItemType,
    };

    explicit SyncthingRecentChangesModel(SyncthingConnection &connection, QObject *parent = nullptr);

public Q_SLOTS:
    QHash<int, QByteArray> roleNames() const override;
    const QVector<int> &colorRoles() const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

private Q_SLOTS:
    void fileChanged(const SyncthingDir &dir, int index, const SyncthingFileChange &change);
    void handleConfigInvalidated() override;
    void handleNewConfigAvailable() override;

private:
    std::vector<SyncthingRecentChange> m_changes;
};

} // namespace Data

Q_DECLARE_METATYPE(Data::SyncthingRecentChange)

#endif // DATA_SYNCTHINGRECENTCHANGESMODEL_H