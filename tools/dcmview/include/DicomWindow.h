#ifndef DICOMWINDOW_H
#define DICOMWINDOW_H

#include <QMdiSubWindow>
#include <QTabWidget>
#include <QTreeView>
#include <QWidget>
#include "DcmDataset.h"
#include "DicomTreeModel.h"

class DicomWindow : public QMdiSubWindow
{
    Q_OBJECT

public:

    DicomWindow(DcmDataset *dataset, QWidget *parent = 0);
    ~DicomWindow();

private:

    Q_DISABLE_COPY(DicomWindow)

    QWidget *createDicomImageWidget();

    DcmDataset *m_dataset;
    DicomTreeModel *m_treeModel;
    QTreeView *m_treeView;
    QWidget *m_imageView;
    QTabWidget *m_tabWidget;
};

#endif // DICOMWINDOW_H
