#include "../include/ui/AlgorithmList.hpp"

#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
AlgorithmList::AlgorithmList(QWidget *parent)
    : QWidget(parent), listWidget(new QListWidget(this)) {
  listWidget->setGeometry(0, 0, 600, 500);

  setAcceptDrops(true);

  QPalette palette = listWidget->palette();
  palette.setColor(QPalette::Base, Qt::white);
  palette.setColor(QPalette::Text, Qt::black);
  listWidget->setPalette(palette);

  connect(listWidget, &QListWidget::itemSelectionChanged, this,
          &AlgorithmList::onItemSelectionChanged);
}

AlgorithmList::~AlgorithmList() {}

void AlgorithmList::addItem(std::filesystem::path filePath) {
  std::shared_ptr<AlgorithmData> algorithm =
      std::make_shared<AlgorithmData>(filePath);

  AlgorithmListItem *widget = new AlgorithmListItem(algorithm->getName(), this);
  algorithms.push_back(algorithm);

  connect(widget, &AlgorithmListItem::deleteClicked, this,
          &AlgorithmList::onItemDeleteClicked);

  listWidget->addItem(new QListWidgetItem());
  QListWidgetItem *item = listWidget->item(listWidget->count() - 1);
  item->setSizeHint(widget->sizeHint());
  size_t index = listWidget->indexFromItem(item).row();
  widget->setIndex(index);
  listWidget->setItemWidget(item, widget);
}

void AlgorithmList::onItemDeleteClicked(size_t index) {
  qDebug() << index;
  QListWidgetItem *item = listWidget->item(index);
  AlgorithmListItem *widget =
      qobject_cast<AlgorithmListItem *>(listWidget->itemWidget(item));

  algorithms.erase(algorithms.begin() + index);
  delete widget;
  delete listWidget->takeItem(index);
}

std::shared_ptr<AlgorithmData> AlgorithmList::getCurrentItem() {
  QListWidgetItem *currentItem = listWidget->currentItem();
  QModelIndex index = listWidget->indexFromItem(currentItem);
  size_t rowIndex = index.row();

  return algorithms.at(rowIndex);
}

bool AlgorithmList::isAlgorithmSelected() {
  return listWidget->currentItem() != nullptr;
}

void AlgorithmList::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasUrls()) {
    event->acceptProposedAction();
  }
}

void AlgorithmList::dragMoveEvent(QDragMoveEvent *event) {
  if (event->mimeData()->hasUrls()) {
    event->acceptProposedAction();
  }
}

void AlgorithmList::dropEvent(QDropEvent *event) {
  const QList<QUrl> urls = event->mimeData()->urls();
  for (const QUrl &url : urls) {
    if (url.isLocalFile()) {
      QString filePath = url.toLocalFile();
      addItem(filePath.toStdString().c_str());
    }
  }
}

void AlgorithmList::onItemSelectionChanged() {
  QListWidgetItem *currentItem = listWidget->currentItem();
  if (currentItem) {
    emit itemSelectionChanged();
  }
}

std::vector<std::shared_ptr<AlgorithmData>> AlgorithmList::getAlgorithms() {
  std::vector<std::shared_ptr<AlgorithmData>> result;
  for (int i = 0; i < listWidget->count(); ++i) {
    QListWidgetItem *item = listWidget->item(i);
    AlgorithmListItem *widget =
        qobject_cast<AlgorithmListItem *>(listWidget->itemWidget(item));

    if (widget->getStatus()) {
      result.push_back(algorithms.at(i));
    }
  }

  return result;
}
