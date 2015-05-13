#include "labyrinth.h"

int main(int argv, char **args)
{
	QApplication app(argv, args);
	Labyrinth labyrinth;

	labyrinth.show();

	return app.exec();
}