#include "student.h"
#include <QRandomGenerator>

Student::Student(const QString& firstName, const QString& lastName) :
    m_firstName(firstName),
    m_lastName(lastName),
    m_grades{0, 0, 0, 0, 0},
    m_mathGrade(qrand() % 4 + 2),
    m_physicsGrade(qrand() % 4 + 2),
    m_chemistryGrade(qrand() % 4 + 2)
{
    // Случайно генерируем оценки для каждого ученика
    QRandomGenerator* generator = QRandomGenerator::global();
    for (int i = 0; i < 5; i++) {
        m_grades[i] = generator->bounded(2, 6);
    }
}

QString Student::getFirstName() const {
    return m_firstName;
}

QString Student::getLastName() const {
    return m_lastName;
}

int Student::getGrade(int index) const {
    return m_grades[index];
}

double Student::getAverageGrade() const {
    int sum = 0;
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (m_grades[i] > 0) {
            sum += m_grades[i];
            count++;
        }
    }
    if (count > 0) {
        return static_cast<double>(sum) / count;
    } else {
        return 0.0;
    }
}

double Student::getMathGrade() const {
    return m_mathGrade;
}

double Student::getPhysicsGrade() const {
    return m_physicsGrade;
}

double Student::getChemistryGrade() const {
    return m_chemistryGrade;
}

void Student::setGrade(int index, int grade) {
    m_grades[index] = grade;
}
