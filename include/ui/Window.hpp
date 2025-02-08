#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QInputDialog>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "AlgorithmList.hpp"
#include "Benchmark.hpp"
#include "BenchmarkDialog.hpp"

class Window : public QWidget {
  Q_OBJECT
 public:
  Window(QWidget* parent, const char* title = "");
  ~Window() = default;

 private:
  void showBenchmarkDialog();
  void runBenchmarks();

    Benchmark benchmark;
  AlgorithmList* listWidget;
  BenchmarkDialog* benchmarkDialog;
};

#endif  // WINDOW_HPP
