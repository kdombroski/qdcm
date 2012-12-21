#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "DicomWindow.h"

DicomWindow::DicomWindow(DcmDataset *dataset, QWidget *parent)
    : QMdiSubWindow(parent)
{
    Q_ASSERT(dataset);
    m_dataset = dataset;
    m_treeModel = new DicomTreeModel(m_dataset, this);
    m_treeView = new QTreeView();
    m_treeView->setModel(m_treeModel);
    m_treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_treeView->header()->setDefaultAlignment(Qt::AlignCenter);
    m_treeView->expandAll();
    m_treeView->resizeColumnToContents(0);
    m_treeView->resizeColumnToContents(1);

    QVBoxLayout *rootLayout = new QVBoxLayout();
    rootLayout->setMargin(0);
    QWidget *rootWidget = new QWidget();

    rootLayout->addWidget(m_treeView);
    rootWidget->setLayout(rootLayout);

    layout()->addWidget(rootWidget);
}

DicomWindow::~DicomWindow()
{
    delete m_dataset;
}
