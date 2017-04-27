#include "syncsummary.hpp"
#include "ui_syncsummary.h"

#include<QDirIterator>
#include <algorithm>
#include <QDebug>
#include <QDateTime>
#include <QFontDatabase>

SyncSummary::SyncSummary(const QString& source, const QString& target, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SyncSummary), _source(source), _target(target)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":/fonts/resources/JuraDemiBold.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont jura(family);

    ui->new_files_text->setFont(jura);
    ui->updated_files_text->setFont(jura);

    QDir source_dir(source);
    source_dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
    std::vector<QString> sources = list_files(source_dir);

    QDir target_dir(target);
    target_dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
    std::vector<QString> targets = list_files(target_dir);

    for(QString file: sources)
    {
        if(std::find(targets.begin(), targets.end(), file) == targets.end())
        {
            ui->new_files_widget->layout()->addWidget(new QCheckBox(file));
            ((QCheckBox*)ui->new_files_widget->layout()->itemAt(ui->new_files_widget->layout()->count()-1)->widget())->setChecked(true);
            ((QCheckBox*)ui->new_files_widget->layout()->itemAt(ui->new_files_widget->layout()->count()-1)->widget())->setFont(jura);
        }
        else
        {
            if(QFileInfo(source+file).lastModified()>QFileInfo(target+file).lastModified())
            {
                ui->updated_files_widget->layout()->addWidget(new QCheckBox(file));
                ((QCheckBox*)ui->updated_files_widget->layout()->itemAt(ui->updated_files_widget->layout()->count()-1)->widget())->setChecked(true);
                ((QCheckBox*)ui->updated_files_widget->layout()->itemAt(ui->updated_files_widget->layout()->count()-1)->widget())->setFont(jura);
            }
        }
    }
}

SyncSummary::~SyncSummary()
{
    delete ui;
}

std::vector<QString> SyncSummary::list_files(QDir root)
{
    std::vector<QString> files;
    QDirIterator it(root, QDirIterator::Subdirectories);
    while(it.hasNext())
    {
        files.emplace_back(it.next().replace(root.path(), ""));
    }
    return files;
}

void SyncSummary::on_upgrade_button_clicked()
{
    for(int i=0; i<ui->new_files_widget->layout()->count(); ++i)
    {
        if(((QCheckBox*)ui->new_files_widget->layout()->itemAt(i)->widget())->isChecked())
        {
            QString file =((QCheckBox*)ui->new_files_widget->layout()->itemAt(i)->widget())->text();
            if(QFileInfo(_source + file).isDir())
            {
                QDir().mkdir(_target + file);
            }
            else
            {
                QFile::copy(_source + file, _target + file);
            }
        }
    }
    for(int i=0; i<ui->updated_files_widget->layout()->count(); ++i)
    {
        if(((QCheckBox*)ui->updated_files_widget->layout()->itemAt(i)->widget())->isChecked())
        {
            QString file =((QCheckBox*)ui->updated_files_widget->layout()->itemAt(i)->widget())->text();
            QFile::remove(_target + file);
            QFile::copy(_source + file, _target + file);
        }
    }
    QDialog::accept();
}
