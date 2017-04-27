#ifndef SYNCSUMMARY_HPP
#define SYNCSUMMARY_HPP

#include <QDialog>
#include <QDir>
#include <vector>
#include <QCheckBox>

namespace Ui {
class SyncSummary;
}

class SyncSummary : public QDialog
{
    Q_OBJECT

public:
    explicit SyncSummary(const QString &source, const QString &target, QWidget *parent = 0);
    ~SyncSummary();

private slots:
    void on_upgrade_button_clicked();

private:
    Ui::SyncSummary *ui;
    std::vector<QString> list_files(QDir rootDir);
    QString _source;
    QString _target;
};

#endif // SYNCSUMMARY_HPP
