#include "studentmodel.h"
#include <QRandomGenerator>
#include <QInputDialog>
#include <QTableView>

StudentModel::StudentModel(QObject* parent) : QAbstractTableModel(parent) {}

int StudentModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent)
    return m_students.size();
}

int StudentModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent)
    return 11;
}

QVariant StudentModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (index.column() == 0) {
            return m_students[index.row()].getFirstName();
        } else if (index.column() == 1) {
            return m_students[index.row()].getLastName();
        } else if (index.column() == 2) {
            return m_students[index.row()].getAverageGrade();
        } else if (index.column() >= 3 && index.column() <= 7) {
            return m_students[index.row()].getGrade(index.column() - 3);
        } else if (index.column() == 8) {
            return m_students[index.row()].getMathGrade();
        } else if (index.column() == 9) {
            return m_students[index.row()].getPhysicsGrade();
        } else if (index.column() == 10) {
            return m_students[index.row()].getChemistryGrade();
        }

    } else if (role == Qt::BackgroundColorRole) {
        // Устанавливаем цвет фона ячейки в зависимости от оценки
        if (index.column() >= 3 && index.column() < 8) {
            int grade = m_students[index.row()].getGrade(index.column() - 3);
            if (grade == 5) {
                return QColor(Qt::green);  // Зеленый цвет для оценки 5
            } else if (grade == 4) {
                return QColor(255, 165, 0);  // Оранжевый цвет для оценки 4
            } else if (grade == 3) {
                return QColor(Qt::yellow);  // Желтый цвет для оценки 3
            } else {
                return QColor(Qt::red);  // Красный цвет для оценки 2
            }
        }
    }

    return QVariant();
}

QVariant StudentModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Имя");
            case 1:
                return tr("Фамилия");
            case 2:
                return tr("Средний балл");
            case 3:
                return tr("Оценка 1");
            case 4:
                return tr("Оценка 2");
            case 5:
                return tr("Оценка 3");
            case 6:
                return tr("Оценка 4");
            case 7:
                return tr("Оценка 5");
            case 8:
                return tr("Ср/б по математике");
            case 9:
                return tr("Ср/б по физике");
            case 10:
                return tr("Ср/б по химии");
        }
    }

    return QVariant();
}

bool StudentModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (index.isValid() && (role == Qt::EditRole || role == Qt::DisplayRole)) {
        if (index.column() >= 3 && index.column() < 8) {
            int grade = value.toInt();
            if (grade >= 2 && grade <= 5) {
                m_students[index.row()].setGrade(index.column() - 3, grade);
                emit dataChanged(index, index);

                // Обновление данных для отображения среднего балла после изменения оценки
                QModelIndex averageGradeIndex = createIndex(index.row(), 2);
                emit dataChanged(averageGradeIndex, averageGradeIndex);

                return true;
            }
        }
    }

    return false;
}

Qt::ItemFlags StudentModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) {
        return Qt::ItemIsEnabled;
    }

    if (index.column() >= 3 && index.column() < 8) {
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }

    return QAbstractTableModel::flags(index);
}

void StudentModel::addStudent(const QString& firstName, const QString& lastName) {
    beginInsertRows(QModelIndex(), m_students.count(), m_students.count());
    m_students.append(Student(firstName, lastName));
    endInsertRows();
}

void StudentModel::addStudentManually() {
    QString firstName = QInputDialog::getText(nullptr, tr("Введите имя"), tr("Имя:"));
    QString lastName = QInputDialog::getText(nullptr, tr("Введите фамилию"), tr("Фамилия:"));
    if (!firstName.isEmpty() && !lastName.isEmpty()) {
        addStudent(firstName, lastName);
    }
}

bool StudentModel::insertRows(int row, int count, const QModelIndex& parent) {
    beginInsertRows(parent, row, row + count - 1);

    for (int i = 0; i < count; ++i) {
        m_students.insert(row, Student("Имя", "Фамилия"));
    }

    endInsertRows();
    return true;
}

bool StudentModel::removeRows(int row, int count, const QModelIndex& parent) {
    beginRemoveRows(parent, row, row + count - 1);

    for (int i = 0; i < count; ++i) {
        m_students.removeAt(row);
    }

    endRemoveRows();
    return true;
}

void StudentModel::removeStudent(int row) {
    beginRemoveRows(QModelIndex(), row, row);
    m_students.removeAt(row);
    endRemoveRows();
}
