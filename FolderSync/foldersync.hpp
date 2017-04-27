#ifndef FOLDERSYNC_HPP
#define FOLDERSYNC_HPP

#include <QWidget>

namespace Ui {
class FolderSync;
}

class FolderSync : public QWidget
{
    Q_OBJECT

public:
    explicit FolderSync(QWidget *parent = 0);
    ~FolderSync();

private slots:
    void on_source_button_clicked();

    void on_target_button_clicked();

    void on_sync_button_clicked();

private:
    Ui::FolderSync *ui;
};

#endif // FOLDERSYNC_HPP
