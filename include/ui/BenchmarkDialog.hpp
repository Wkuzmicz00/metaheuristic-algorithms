#ifndef BENCHMARKDIALOG_HPP
#define BENCHMARKDIALOG_HPP

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>
#include <QWidgetItem>

#include "AlgorithmData.hpp"

class BenchmarkDialog : public QWidget {
  Q_OBJECT
 public:
  BenchmarkDialog(QWidget* parent);

  void Clear();
  void setNewData(std::shared_ptr<AlgorithmData> algorithm);

  ParamInfo openParametersDialog();

  void addParameters();

  void removeParameters();

 private:
  std::shared_ptr<AlgorithmData> algorithm;
  void setupUI();

  QDialog* dialog;
  QListWidget* paramList;
  QListWidget* functionList;
};

#endif  // BENCHMARKDIALOG_HPP
