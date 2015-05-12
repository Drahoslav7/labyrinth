#include "labyrinth.h"

int main(int argv, char **args)
{
	QApplication app(argv, args);
	Labyrinth labyrinth;

	// QTextEdit *textEdit = new QTextEdit;
	// QPushButton *quitButton = new QPushButton("&Quit");
	// QPushButton *setNickButton = new QPushButton("Set Nick");

	// QVBoxLayout *chooseNickLayout = new QVBoxLayout;
	// QVBoxLayout *waitingRoom = new QVBoxLayout;

	// QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
	//QObject::connect(setNickButton, SIGNAL(clicked()), qApp, SLOT(setNickname(window, waitingRoom)));

	// waitingRoom->addWidget(quitButton);


	// chooseNickLayout->addWidget(textEdit);
	// chooseNickLayout->addWidget(setNickButton);
	// chooseNickLayout->addWidget(quitButton);

	// window.setLayout(chooseNickLayout);
	labyrinth.show();

	return app.exec();
}