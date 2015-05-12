// #include <QApplication>
// #include <QTextEdit>

// int main(int argv, char **args)
// {
// 	QApplication app(argv, args);

// 	QTextEdit textEdit;
// 	textEdit.show();
// 	return app.exec();
// }

#include <QtGui>
#include <QApplication>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argv, char **args)
{
	QApplication app(argv, args);
	QTextEdit *textEdit = new QTextEdit;
	QPushButton *quitButton = new QPushButton("&Quit");
	QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(textEdit);
	layout->addWidget(quitButton);
	QWidget window;
	window.setLayout(layout);
	window.show();
	return app.exec();
}