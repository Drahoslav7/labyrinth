#include "labyrinth.h"

Labyrinth::Labyrinth(){
	setWindowTitle(tr("Labyrinth"));

	QLabel * label = new QLabel(tr("Your Nickname:"));
	QLineEdit *	lineEdit = new QLineEdit();
	QPushButton * okButton = new QPushButton("OK");

	LSelectNick = new QVBoxLayout;
	LSelectNick->addWidget(label);
	LSelectNick->addWidget(lineEdit);
	LSelectNick->addWidget(okButton);

	setLayout(LSelectNick);
}

