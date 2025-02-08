#include "../include/ui/AlgorithmListItem.hpp"

AlgorithmListItem::AlgorithmListItem(std::string text, QWidget *parent)
    : QWidget(parent),
      checkBox(new QCheckBox(this)),
      deleteButton(new QPushButton(this)),
      label(new QLabel(QString::fromStdString(text), this)),
      layout(new QHBoxLayout(this)) {
  deleteButton->setIcon(QIcon::fromTheme("edit-delete"));

  deleteButton->setVisible(false);

  connect(deleteButton, &QPushButton::clicked, this,
          &AlgorithmListItem::onDeleteClicked);

  layout->addWidget(label);
  layout->addWidget(deleteButton);
  layout->addSpacerItem(
      new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
  layout->addWidget(checkBox);
}

void AlgorithmListItem::enterEvent(QEnterEvent *event) {
  deleteButton->setVisible(true);
  QWidget::enterEvent(event);
}

void AlgorithmListItem::leaveEvent(QEvent *event) {
  if (event->type() == QEvent::Leave) {
    deleteButton->setVisible(false);
  }
  QWidget::leaveEvent(event);
}

// SETTERS
void AlgorithmListItem::setText(const QString &text) { label->setText(text); }

// GETTERS
bool AlgorithmListItem::getStatus() const { return checkBox->isChecked(); }
QString AlgorithmListItem::getText() const { return label->text(); }

// SIGNALS
void AlgorithmListItem::onDeleteClicked() { emit deleteClicked(index); }

void AlgorithmListItem::setIndex(size_t idx) { index = idx; }

AlgorithmListItem *AlgorithmListItem::getItem() { return this; }