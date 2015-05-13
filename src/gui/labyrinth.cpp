#include "labyrinth.h"

Labyrinth::Labyrinth(){
	setWindowTitle(tr("Labyrinth"));

	// vsemozny sracicky
	QLabel * label = new QLabel(tr("Your Nickname:"));
	QLabel * waitlabel = new QLabel(tr("WAITING"));
	QLabel * connectlabel = new QLabel(tr("CONNECTING"));
	QLineEdit *	lineEdit = new QLineEdit();
	QPushButton * okButton1 = new QPushButton("OK");
	QObject::connect(okButton1, SIGNAL(clicked()), this, SLOT(setOk()));
	QPushButton * okButton2 = new QPushButton("OK");
	QObject::connect(okButton2, SIGNAL(clicked()), this, SLOT(setBla()));


	// mainlayout
	mainlayout = new QVBoxLayout;

	//ostatni layouty a jejich widgety
	connectingpage = new QWidget;
	connectingpagelayout = new QVBoxLayout;
	connectingpage->setLayout(connectingpagelayout);

	nicknamepage = new QWidget;
	nicknamepagelayout = new QVBoxLayout;
	nicknamepage->setLayout(nicknamepagelayout);

	waitingpage = new QWidget;
	waitingpagelayout = new QVBoxLayout;
	waitingpage->setLayout(waitingpagelayout);

	// sracicky prirazene k layoutum
	connectingpagelayout->addWidget(connectlabel);

	nicknamepagelayout->addWidget(label);
	nicknamepagelayout->addWidget(lineEdit);
	nicknamepagelayout->addWidget(okButton1);

	waitingpagelayout->addWidget(waitlabel);
	waitingpagelayout->addWidget(okButton2);

	// vse nahozeno na main layoutu
	mainlayout->addWidget(nicknamepage);
	mainlayout->addWidget(waitingpage);

	// schovat vse krom connecting 
	//nicknamepage->hide();	
	waitingpage->hide();

	setLayout(mainlayout);
}

void Labyrinth::setOk(){
	nicknamepage->hide();
	waitingpage->show();
}

void Labyrinth::setBla(){
	connectingpage->hide();
	nicknamepage->show();
}