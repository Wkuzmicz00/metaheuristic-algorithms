#include "../include/ui/BenchmarkDialog.hpp"

BenchmarkDialog::BenchmarkDialog(QWidget* parent) : QWidget(parent) {
  setStyleSheet("background-color: white;");
}

void BenchmarkDialog::Clear() {
  QLayout* currentLayout = this->layout();
  if (currentLayout) {
    QLayoutItem* item;
    while ((item = currentLayout->takeAt(0)) != nullptr) {
      if (item->widget()) {
        delete item->widget();
      }
      delete item;
    }
    delete currentLayout;
  }
}

void BenchmarkDialog::setupUI() {
  QHBoxLayout* listLayout = new QHBoxLayout();
  QVBoxLayout* paramListLayout = new QVBoxLayout();
  QVBoxLayout* mainLayout = new QVBoxLayout(this);

  functionList = new QListWidget(this);
  paramList = new QListWidget(this);

  for (ParamInfo param : algorithm->getParams()) {
    QString value = QString::fromStdString(
        std::format("{}, {}, {}, {}, {}", param.dimensions, param.population,
                    param.lowerBoundary, param.upperBoundary, param.tMax));
    paramList->addItem(value);
  }

  setStyleSheet("QLabel { color: black; } QLineEdit { color: black; }");

  // Path
  QHBoxLayout* pathLayout = new QHBoxLayout();
  QLabel* label = new QLabel("Path:", this);
  QLineEdit* lineEdit = new QLineEdit(this);
  lineEdit->setText(QString::fromStdString(algorithm->getPath()));

  pathLayout->addWidget(label);
  pathLayout->addWidget(lineEdit);

  mainLayout->addLayout(pathLayout);

  // Lists
  QPushButton* addParamButton = new QPushButton("Add Parameters", this);
  connect(addParamButton, &QPushButton::clicked, this,
          &BenchmarkDialog::addParameters);

  QPushButton* removeParamButton = new QPushButton("Remove Parameters", this);
  connect(removeParamButton, &QPushButton::clicked, this,
          &BenchmarkDialog::removeParameters);

  paramListLayout->addWidget(paramList);
  paramListLayout->addWidget(addParamButton);
  paramListLayout->addWidget(removeParamButton);

  listLayout->addLayout(paramListLayout);
  listLayout->addWidget(functionList);

  mainLayout->addLayout(listLayout);

  setLayout(mainLayout);

  move(600, 0);
  resize(600, 400);
}

void BenchmarkDialog::setNewData(std::shared_ptr<AlgorithmData> algorithm) {
  this->algorithm = algorithm;
  Clear();
  setupUI();
}
ParamInfo BenchmarkDialog::openParametersDialog() {
  dialog = new QDialog(this);
  dialog->setWindowTitle("Add Parameters");

  QVBoxLayout* dialogLayout = new QVBoxLayout(dialog);
  int population;
  int dimensions;
  double upperBoundary;
  double lowerBoundary;
  size_t tMax;
  std::vector<std::string> labelNames = {"Dimensions", "Population",
                                         "Upper Boundry", "Lower Boundry",
                                         "Max iterations"};
  std::vector<QLineEdit*> lineEdits;

  for (int i = 0; i < labelNames.size(); ++i) {
    QHBoxLayout* rowLayout = new QHBoxLayout();
    QLabel* label = new QLabel(QString::fromStdString(labelNames[i]), dialog);
    QLineEdit* lineEdit = new QLineEdit(dialog);
    rowLayout->addWidget(label);
    rowLayout->addWidget(lineEdit);
    dialogLayout->addLayout(rowLayout);
    lineEdits.push_back(lineEdit);
  }

  QHBoxLayout* buttonLayout = new QHBoxLayout();
  QPushButton* okButton = new QPushButton("OK", dialog);
  QPushButton* cancelButton = new QPushButton("Cancel", dialog);
  buttonLayout->addWidget(okButton);
  buttonLayout->addWidget(cancelButton);
  dialogLayout->addLayout(buttonLayout);

  connect(okButton, &QPushButton::clicked, dialog, &QDialog::accept);
  connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

  // TO DO - BETTER VALIDATE
  if (dialog->exec() == QDialog::Accepted) {
    QStringList values;
    bool allValid = true;

    for (auto* lineEdit : lineEdits) {
      QString text = lineEdit->text();
      bool ok;
      text.toDouble(&ok);
      if (!ok) {
        allValid = false;
        break;
      }
      values.append(text);
    }

    if (allValid) {
      paramList->addItem(values.join(", "));
      return ParamInfo(values[0].toInt(), values[1].toInt(),
                       values[2].toDouble(), values[3].toDouble(),
                       values[4].toInt());
    } else {
      QMessageBox::warning(this, "Invalid Input",
                           "Please enter valid integers in all fields.");
    }
  }
}

void BenchmarkDialog::addParameters() {
  ParamInfo param = openParametersDialog();
  algorithm->addParams(param);
}

void BenchmarkDialog::removeParameters() {
  QListWidgetItem* currentItem = paramList->currentItem();
  QModelIndex index = paramList->indexFromItem(currentItem);
  size_t rowIndex = index.row();

  algorithm->removeParams(rowIndex);
  delete paramList->takeItem(rowIndex);
}
