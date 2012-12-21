#ifndef DICOMWINDOW_H
#define DICOMWINDOW_H

#include <QMdiSubWindow>
#include <QTreeView>
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

    DcmDataset *m_dataset;
    DicomTreeModel *m_treeModel;
    QTreeView *m_treeView;
};

#endif // DICOMWINDOW_H
