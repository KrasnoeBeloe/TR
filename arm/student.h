#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student {
public:
    Student(const QString& firstName, const QString& lastName);

    QString getFirstName() const;
    QString getLastName() const;
    int getGrade(int index) const;
    double getAverageGrade() const;
    double getMathGrade() const;
    double getPhysicsGrade() const;
    double getChemistryGrade() const;

    void setGrade(int index, int grade);

private:
    QString m_firstName;
    QString m_lastName;
    int m_grades[5];
    double m_mathGrade;
    double m_physicsGrade;
    double m_chemistryGrade;
};

#endif // STUDENT_H
