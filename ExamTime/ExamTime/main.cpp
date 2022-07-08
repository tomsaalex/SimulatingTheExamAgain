#include "ExamTime.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RepositoryJoc repo{"InputFile.txt"};
    ValidatorJoc valid;
    ServiceJoc srv(repo, valid);
    ExamTime w{ srv };
    w.show();
    return a.exec();
}
