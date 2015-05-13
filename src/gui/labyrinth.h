#include <QtGui>
#include <QApplication>

#include <QtWidgets>

#include <QMainWindow>

#include <Qlabel>
#include <QLineEdit>
// #include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>


class Labyrinth : public QWidget {

	Q_OBJECT

	public:
		Labyrinth();
		virtual ~Labyrinth(){};
	

	private slots:
		void setOk();
		void setBla();

	private:
		QVBoxLayout * mainlayout;

		QWidget * connectingpage;
		QVBoxLayout * connectingpagelayout;

		QWidget * waitingpage;
		QVBoxLayout * waitingpagelayout;

		QWidget * nicknamepage;
		QVBoxLayout * nicknamepagelayout;


};