#ifndef __ABOUTWINDOW_H__
#define __ABOUTWINDOW_H__

#include <QDialog>

namespace Ui
{
    class AboutWindow;
}

class MainWindow;

class AboutWindow : public QDialog
{
    Q_OBJECT

public:
    /// @brief ctr
    /// @param [in] parent QWidget* - the parent widget
    explicit AboutWindow(QWidget *parent = 0);
    /// @brief dtr
    ~AboutWindow();
    /// @brief function to initialise the window and connect any signals to the correct slots
    void connectAndInit();
    /// @brief function to set the parent window for this window
    /// @param [in] _parent MainWindow* - the parent main window
    void setParentWindow(MainWindow* _parent);

private:
    /// @brief The UI object for the window
    Ui::AboutWindow *m_ui;
    /// @brief MainWindow pointer to the main window of this window
    MainWindow *m_parentWindow;
    /// @brief Boolean of whether or not the parent window has been set
    bool m_parentWindowConnected;
};

#endif /* __ABOUTWINDOW_H__ */
