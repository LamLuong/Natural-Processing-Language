/* file interface.cpp
   author
   date
*/
#include <iostream>
#include <QtGui>
#include <QBoxLayout>
#include <time.h>
#include "include/interface.h"

FindDialog::FindDialog(QWidget *parent) : QDialog(parent) {



  setGeometry(100, 100, 600, 280);
  text_edit = new QTextEdit;
  line_edit = new QLineEdit;

  text_edit->setReadOnly(true);

  suggest_button =  new QPushButton(tr("&Suggest"));
  close_button =  new QPushButton(tr("&Close"));

  connect(close_button, SIGNAL(clicked()), this, SLOT(close()));

//  connect(suggest_button, SIGNAL(clicked()), this, SLOT(ShowSuggestion()));

  connect(text_edit, SIGNAL(cursorPositionChanged()),
                    this, SLOT(MouseClickTextBox()));

  QVBoxLayout *left_layout = new QVBoxLayout;
  left_layout->addWidget(line_edit);
  left_layout->addWidget(text_edit);

  QVBoxLayout *right_layout = new QVBoxLayout;
  right_layout->addWidget(suggest_button);
  right_layout->addWidget(close_button);
  right_layout->addStretch();

  QHBoxLayout *main_layout = new QHBoxLayout;
  main_layout->addLayout(left_layout);
  main_layout->addLayout(right_layout);
  setLayout(main_layout);

  setWindowTitle(tr("Natural Language Processing"));
}


void FindDialog::keyReleaseEvent(QKeyEvent *event) {
  if(event->key()==Qt::Key_Space) {
    clock_t begin =0;
    clock_t end = 0;
    begin = clock();
    QString patten_qs = line_edit->text();
    if (patten_qs.isEmpty()) return;

    std::string patten_str = patten_qs.toUtf8().constData();

    std::vector<suggestion_index> list;
    Dictionary *dic_ = new Dictionary("dictionary/wiki.simple");

    dic_->Suggest(patten_str, list);

    std::string suggest_string;
    if (list.size() > 0) {
      if (list.size() >= 5) {
        for (unsigned i = 0; i < 5; i++) {
          suggest_string += list[i].patten + "\n";
        }
      } else if (list.size() < 5) {
        for (unsigned i = 0; i < list.size(); i++) {
          suggest_string += list[i].patten + "\n";
        }
      }

      QString str = QString::fromUtf8(suggest_string.c_str());
      text_edit->setText(str);
    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << time_spent << "(s)" << std::endl;
      list.clear();
    } else {
      dic_->Write(patten_str);
    }
    delete dic_;
  }
}

void FindDialog::MouseClickTextBox() {
    QTextCursor cursor;
    QString text;
 
    cursor = text_edit->textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    text = cursor.selectedText();

    if (text_edit->toPlainText().isEmpty()) {
      line_edit->setText(text);
    } else {
      line_edit->insert(text);
    }
}













