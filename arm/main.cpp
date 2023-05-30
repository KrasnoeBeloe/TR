#include <QApplication>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QListWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QRandomGenerator>
#include <QInputDialog>
#include "studentmodel.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Создаем модель студентов
    StudentModel model;

    // Добавляем нескольких случайно сгенерированных учеников
    QStringList firstNames = { "Павел", "Кирилл", "Егор", "Василий", "Евгений" };
    QStringList lastNames = { "Петров", "Трефелов", "Галкин", "Смирнов", "Иванов" };
    for (int i = 0; i < 10; ++i) {
        QString firstName = firstNames.at(QRandomGenerator::global()->bounded(firstNames.size()));
        QString lastName = lastNames.at(QRandomGenerator::global()->bounded(lastNames.size()));
        model.addStudent(firstName, lastName);
    }

    // Создаем таблицу и устанавливаем модель
    QTableView tableView;
    tableView.setModel(&model);

    // Создаем кнопки для добавления и удаления учеников
    QPushButton addButton("Добавить ученика");
    QPushButton removeButton("Удалить ученика");

    // Создаем горизонтальный слой для кнопок
    QHBoxLayout buttonLayout;
    buttonLayout.addWidget(&addButton);
    buttonLayout.addWidget(&removeButton);

    // Создаем вертикальный слой для таблицы и кнопок
    QVBoxLayout mainLayout;
    mainLayout.addWidget(&tableView);
    mainLayout.addLayout(&buttonLayout);

    // Создаем виджет и устанавливаем наш вертикальный слой
    QWidget window;
    window.setLayout(&mainLayout);

    // Подключаем слоты для добавления и удаления учеников
    QObject::connect(&addButton, &QPushButton::clicked, [&](){
        QString firstName = QInputDialog::getText(&window, "Имя", "Введите имя:");
        QString lastName = QInputDialog::getText(&window, "Фамилия", "Введите фамилию:");
        model.addStudent(firstName, lastName);
    });

    QObject::connect(&removeButton, &QPushButton::clicked, [&](){
        QModelIndexList selectedIndexes = tableView.selectionModel()->selectedRows();
        if (selectedIndexes.size() > 0) {
            int row = selectedIndexes[0].row();
            model.removeStudent(row);
        }
    });

    window.show();

    return app.exec();

}
