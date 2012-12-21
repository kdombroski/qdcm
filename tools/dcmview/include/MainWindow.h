#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QSignalMapper>

/*! Main application window.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void moveToDesktopCenter();

protected:

    void closeEvent(QCloseEvent *event);

private slots:

    void onOpenAction();

    /// Update list of windows in the menu.
    void updateWindowMenu();

    /// Activate a sub-window widget.
    void setActiveSubWindow(QWidget *widget);

private:

    Q_DISABLE_COPY(MainWindow)

    void createActions();
    void createMenus();
    void createToolBars();

    /// Returns pointer to an active MDI window.
    QMdiSubWindow* activeMdiChild();

    QMdiArea *m_mdiArea;    ///< MDI area.

    QSignalMapper *m_windowsMapper;

    // Top level menus
    QMenu *m_fileMenu;
    QMenu *m_windowMenu;

    // Tool bars
    QToolBar *m_fileToolBar;

    // File menu actions
    QAction *m_openAction;
    QAction *m_exitAction;

    // Window menu actions
    QAction *m_closeAction;
    QAction *m_closeAllAction;
    QAction *m_tileAction;
    QAction *m_cascadeAction;
    QAction *m_nextAction;
    QAction *m_previousAction;
    QAction *m_separatorAction;
};

#endif // MAINWINDOW_H
