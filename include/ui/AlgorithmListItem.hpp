#ifndef LISTITEM_HPP
#define LISTITEM_HPP

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QWidget>
#include <filesystem>
#include <memory>

#include "AlgorithmData.hpp"

class AlgorithmListItem : public QWidget {
  Q_OBJECT
 private:
  size_t index;

  QCheckBox *checkBox;
  QPushButton *editButton;
  QPushButton *deleteButton;
  QLabel *label;
  QHBoxLayout *layout;

 public:
  AlgorithmListItem(std::string text, QWidget *parent);

  // Getters
  bool getStatus() const;
  QString getText() const;
  AlgorithmListItem *getItem();

  // Setters
  void setText(const QString &text);
  void setIndex(size_t idx);

  // QT
 protected:
  void leaveEvent(QEvent *event) override;
  void enterEvent(QEnterEvent *event) override;

 private slots:
  void onDeleteClicked();

 signals:
  void deleteClicked(size_t index);
};

#endif  // LISTITEM_HPP
