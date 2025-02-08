#include "../include/ui/Window.hpp"

Window::Window(QWidget* parent, const char* title) : QWidget(parent) {
  setWindowTitle(title);
  resize(1200, 800);

  benchmarkDialog = new BenchmarkDialog(this);
  benchmarkDialog->setVisible(false);

  listWidget = new AlgorithmList(this);

  QPushButton* addButton = new QPushButton("Add Item", this);
  addButton->setGeometry(125, 550, 100, 50);

  connect(addButton, &QPushButton::clicked, [this]() {
    bool ok;
    QString text =
        QInputDialog::getText(this, tr("Add Item"), tr("Enter algorithm path:"),
                              QLineEdit::Normal, QString(), &ok);

    if (ok && !text.isEmpty()) {
      std::filesystem::path fileName = text.toStdString();
      listWidget->addItem(fileName);
    }
  });  // poprawic i zconnetowac, dodac do algorithmDialog?

  connect(listWidget, &AlgorithmList::itemSelectionChanged, this,
          &Window::showBenchmarkDialog);

  QPushButton* button = new QPushButton("Run", this);
  button->setGeometry(300, 550, 100, 50);

  connect(button, &QPushButton::clicked, this, &Window::runBenchmarks);
}

void Window::runBenchmarks() { benchmark.Run(listWidget->getAlgorithms()); }

void Window::showBenchmarkDialog() {
  if (listWidget->isAlgorithmSelected()) {
    benchmarkDialog->setNewData(listWidget->getCurrentItem());
    benchmarkDialog->setVisible(true);
  }
}
