#ifndef LIST_HPP
#define LIST_HPP

#include <QListWidget>
#include <QMimeData>
#include <QWidget>

#include "AlgorithmListItem.hpp"

class AlgorithmList : public QWidget {
  Q_OBJECT
 public:
  AlgorithmList(QWidget *parent);
  ~AlgorithmList();

  void addItem(std::filesystem::path filePath);

  std::shared_ptr<AlgorithmData> getCurrentItem();

  bool isAlgorithmSelected();

  std::vector<std::shared_ptr<AlgorithmData>> getAlgorithms();

 protected:
  void dragEnterEvent(QDragEnterEvent *event) override;
  void dragMoveEvent(QDragMoveEvent *event) override;
  void dropEvent(QDropEvent *event) override;

 private slots:
  void onItemDeleteClicked(size_t index);
  void onItemSelectionChanged();

 signals:
  void itemSelectionChanged();

 private:
  std::vector<std::shared_ptr<AlgorithmData>> algorithms;
  QListWidget *listWidget;
};

#endif  // LIST_HPP
