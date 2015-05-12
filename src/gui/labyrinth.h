#include <QtGui>
#include <QApplication>

#include <QtWidgets>

#include <QMainWindow>

#include <Qlabel>
#include <QLineEdit>
// #include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>


class Labyrinth : public QWidget {

	Q_OBJECT

	public:
		Labyrinth();
		virtual ~Labyrinth(){};
	

	private slots:
		setOk();

	private:
		QVBoxLayout * LSelectNick;
		QVBoxLayout * LWaitingRoom;


};