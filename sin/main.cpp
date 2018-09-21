#include "widget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Widget w;
	w.InitSinGrid();
	w.UpdateData();
	w.show();
	return a.exec();
}
