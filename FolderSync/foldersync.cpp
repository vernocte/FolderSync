#include "foldersync.hpp"
#include "ui_foldersync.h"

#include<QFontDatabase>
#include<QFileDialog>

#include "syncsummary.hpp"

FolderSync::FolderSync(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FolderSync)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":/fonts/resources/JuraDemiBold.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont jura(family);

    ui->source_edit->setFont(jura);
    ui->target_edit->setFont(jura);
    ui->status_label->setFont(jura);
}

FolderSync::~FolderSync()
{
    delete ui;
}

void FolderSync::on_source_button_clicked()
{
    QFileDialog f;
    f.setFileMode(QFileDialog::Directory);
    f.setOption(QFileDialog::ShowDirsOnly);
    if(f.exec())
    {
        ui->source_edit->setText(f.selectedFiles().first());
    }
}

void FolderSync::on_target_button_clicked()
{
    QFileDialog f;
    f.setFileMode(QFileDialog::Directory);
    f.setOption(QFileDialog::ShowDirsOnly);
    if(f.exec())
    {
        ui->target_edit->setText(f.selectedFiles().first());
    }
}

void FolderSync::on_sync_button_clicked()
{
    SyncSummary summary(ui->source_edit->text(), ui->target_edit->text(), this);
    summary.exec();
}
