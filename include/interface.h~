/* file interface
   author
   date
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QDialog>
#include <QCheckBox>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>


#include <QMouseEvent>
#include <QMessageBox>

#include "include/dictionary.h"


class FindDialog : public QDialog {
  Q_OBJECT
 public:
  FindDialog(QWidget *parent = 0);

  void abc(std::string x) {
    std::cout << x << std::endl;
  }

	void keyReleaseEvent(QKeyEvent *event);

 private slots:
//  void ShowSuggestion();
  void MouseClickTextBox();

 private:
 
  QPushButton *suggest_button;
  QPushButton *close_button;

  QTextEdit *text_edit;
  QLineEdit *line_edit;
};

#endif //end file interface.h
